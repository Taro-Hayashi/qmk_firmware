// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "analog.h"
#include <math.h>


// CO2濃度警告の閾値
#define ALARTTHRESHOLD 2000
// 安全圏の色
#define SAFEHUE 150
// 更新間隔（秒）
#define SPAN 4
// サンプル数
#define COUNTMAX 31

// 定数
#define AD_VCC 4.8
#define EMF_RANGE 0.045
#define EMF_0_PPM 400.0
#define EMF_1_PPM 4000.0
#define EMF_MAX 0.22
#define EMF_CHK_RANGE 0.002
#define BOARD_GAIN 10.0

// 変数
double emf_max = 0.2;
double emf_chk = 0.2;
double sum = 0.0;
int16_t pre_ppmint = 0;

// キーコードの追加
enum co2_keycode{
    CO2_SAFE_RANGE = SAFE_RANGE,
    CHANGE_MODE,
};
uint16_t startup_timer;

enum led_mode{
    GRADATION = 0,
    THRESHOLD,
    OFF,
};
uint8_t mode = GRADATION;
uint8_t premode = GRADATION;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_1key(
    CHANGE_MODE
  ),
};

uint16_t count;
uint16_t oled_timer;
uint16_t count_timer;
int16_t val[COUNTMAX];

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_timer = timer_read();
    count_timer = timer_read();
    count = 0;
    return OLED_ROTATION_180;
}

// フォントの定義
static const char PROGMEM numfont[][4][5] = {
    // 0
    {{0x23, 0x24, 0x25, 0x26, 0}, {0x27, 0x22, 0x22, 0x2A, 0}, {0x2B, 0x22, 0x22, 0x2E, 0}, {0x2F, 0x30, 0x31, 0x32, 0}},
    // 1
    {{0x22, 0x22, 0x22, 0x26, 0}, {0x22, 0x22, 0x22, 0x2A, 0}, {0x22, 0x22, 0x22, 0x2E, 0}, {0x22, 0x22, 0x22, 0x32, 0}},
    // 2
    {{0x22, 0x24, 0x25, 0x26, 0}, {0x22, 0x28, 0x29, 0x2A, 0}, {0x2B, 0x2C, 0x2D, 0x22, 0}, {0x2F, 0x30, 0x31, 0x22, 0}},
    // 3
    {{0x22, 0x24, 0x25, 0x26, 0}, {0x22, 0x28, 0x29, 0x2A, 0}, {0x22, 0x2C, 0x2D, 0x2E, 0}, {0x22, 0x30, 0x31, 0x32, 0}},
    // 4
    {{0x23, 0x22, 0x22, 0x26, 0}, {0x27, 0x28, 0x29, 0x2A, 0}, {0x22, 0x2C, 0x2D, 0x2E, 0}, {0x22, 0x22, 0x22, 0x32, 0}},
    // 5
    {{0x23, 0x24, 0x25, 0x22, 0}, {0x27, 0x28, 0x29, 0x22, 0}, {0x22, 0x2C, 0x2D, 0x2E, 0}, {0x22, 0x30, 0x31, 0x32, 0}},
    // 6
    {{0x23, 0x24, 0x25, 0x22, 0}, {0x27, 0x28, 0x29, 0x22, 0}, {0x2B, 0x2C, 0x2D, 0x2E, 0}, {0x2F, 0x30, 0x31, 0x32, 0}},
    // 7
    {{0x22, 0x24, 0x25, 0x26, 0}, {0x22, 0x22, 0x22, 0x2A, 0}, {0x22, 0x22, 0x22, 0x2E, 0}, {0x22, 0x22, 0x22, 0x32, 0}},
    // 8
    {{0x23, 0x24, 0x25, 0x26, 0}, {0x27, 0x28, 0x29, 0x2A, 0}, {0x2B, 0x2C, 0x2D, 0x2E, 0}, {0x2F, 0x30, 0x31, 0x32, 0}},
    // 9
    {{0x23, 0x24, 0x25, 0x26, 0}, {0x27, 0x28, 0x29, 0x2A, 0}, {0x22, 0x2C, 0x2D, 0x2E, 0}, {0x22, 0x30, 0x31, 0x32, 0}},
    // NULL
    {{0x22, 0x22, 0x22, 0x22, 0}, {0x22, 0x22, 0x22, 0x22, 0}, {0x22, 0x22, 0x22, 0x22, 0}, {0x22, 0x22, 0x22, 0x22, 0}}
};
static const char PROGMEM ppmfont[] = {
    0x33, 0x34, 0x35, 0x36, 0x37, 0
};


// 計算とOLEDの表示
bool oled_task_user(void) {
    if (timer_elapsed(count_timer) > 100){
        count = count % COUNTMAX;
        val[count] = analogReadPin(F7);
        count++;
        count_timer = timer_read();
    }

    if (timer_elapsed(oled_timer) > SPAN * 1000){

        // 中央値を求める
        int16_t temp;
        int16_t tempval[COUNTMAX];
        for(uint16_t i = 0; i < COUNTMAX; i++){
            tempval[i] = val[i];
        }

        for(uint16_t j = 0; j < COUNTMAX; j++){
            for(uint16_t k = 0; k < COUNTMAX; k++){
                if (tempval[j] < tempval[k]){
                    temp = tempval[j];
                    tempval[j] = tempval[k];
                    tempval[k] = temp;
                }
            }
        }
        int16_t median = tempval[(COUNTMAX - 1) / 2];

        // ppm決定
        double e = (double)median / 1024.0 * AD_VCC / BOARD_GAIN;
        double k = (1.0 / EMF_RANGE) * log10( EMF_1_PPM / EMF_0_PPM);
        double ppm = EMF_0_PPM * pow(10.0, (k * (emf_max - e)));

        // 最大電圧更新
        if(ppm < EMF_0_PPM){
            emf_chk = emf_max + EMF_CHK_RANGE;
            if(e >= emf_chk){
                emf_max = e;
            }
        }


        // OLED処理
        uint8_t ppmindex[4];
        uint16_t ppmint = (uint16_t)ppm;
        if(ppm > 8888){
            ppm = 8888;
        }else if(ppmint == pre_ppmint){
            ppmint += 11;
        }
        pre_ppmint = ppmint;
        ppmindex[0] = ppmint / 1000;
        ppmindex[1] = (ppmint % 1000) / 100;
        ppmindex[2] = (ppmint % 100) / 10;
        ppmindex[3] = ppmint % 10;
        if(ppmindex[0] == 0){
            ppmindex[0] = 10;
        }
        oled_set_cursor(0,0);
        oled_write_P(numfont[ppmindex[0]][0], false);
        oled_write_P(numfont[ppmindex[1]][0], false);

        oled_write_P(numfont[ppmindex[2]][0], false);
        oled_write_P(numfont[ppmindex[3]][0], false);
        oled_set_cursor(0,1);
        oled_write_P(numfont[ppmindex[0]][1], false);
        oled_write_P(numfont[ppmindex[1]][1], false);
        oled_write_P(numfont[ppmindex[2]][1], false);
        oled_write_P(numfont[ppmindex[3]][1], false);
        oled_set_cursor(0,2);
        oled_write_P(numfont[ppmindex[0]][2], false);
        oled_write_P(numfont[ppmindex[1]][2], false);
        oled_write_P(numfont[ppmindex[2]][2], false);
        oled_write_P(numfont[ppmindex[3]][2], false);
        oled_set_cursor(0,3);
        oled_write_P(numfont[ppmindex[0]][3], false);
        oled_write_P(numfont[ppmindex[1]][3], false);
        oled_write_P(numfont[ppmindex[2]][3], false);
        oled_write_P(numfont[ppmindex[3]][3], false);
        oled_write_P(ppmfont, false);

        // LED処理
        oled_set_cursor(0,3);
        if(mode == GRADATION){
            uint16_t hue;
            if(ppm >= ALARTTHRESHOLD){
                hue = 0;
            } else{
                hue= SAFEHUE - (SAFEHUE * (ppm - EMF_0_PPM) / (ALARTTHRESHOLD - EMF_0_PPM) );
            }
            rgblight_sethsv(hue, 255, 200);
            if(premode != mode){
                oled_write_ln("LIGHTING: GRADATION", false);
                premode = mode;
            }
        } else if(mode == THRESHOLD){
            if(ppm <= ALARTTHRESHOLD){
                rgblight_sethsv(255, 255, 0);
            } else{
                rgblight_sethsv(255, 255, 200);
            }
            if(premode != mode){
                oled_write_ln("LIGHTING: THRESHOLD", false);
                premode = mode;
            }
        } else{
            rgblight_sethsv(255, 255, 0);
            if(premode != mode){
                oled_write_ln("LIGHTING: OFF", false);
                premode = mode;
            }
        }
        oled_timer = timer_read();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // 短押しでモード変更、長押しでリセット
    if (keycode == CHANGE_MODE) {
        if(record->event.pressed){

        startup_timer = timer_read();
        }else{
            if(timer_elapsed(startup_timer) < 1000){
                mode = (mode + 1) % 3;
            }else {
                timer_clear();
                count = 0;
                for(uint16_t i = 0; i < COUNTMAX; i++){
                    val[i] = 0;
                }
                oled_timer = timer_read();
                count_timer = timer_read();
                oled_clear();
            }
        }
    }

    return true;
}
