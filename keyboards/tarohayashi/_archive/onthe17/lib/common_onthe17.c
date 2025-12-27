// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lib/common_onthe17.h"
#include "math.h"
#include "lib/add_keycodes.h"

/* ポインティングデバイス用変数 */
ot17_config_t ot17_config;      // eeprom保存用
bool force_scrolling; // 一時的モード変更用
bool force_cursoring; // 一時的モード変更用
bool force_key_input; // 一時的モード変更用
bool slow_mode;       // 一時的モード変更用
float prev_x, prev_y;
float x_accumulator, y_accumulator, h_accumulator, v_accumulator; // 端数保存用

// 仮想十字キー設定用変数
keypos_t key_up;
keypos_t key_left;
keypos_t key_right;
keypos_t key_down;
int8_t layer;
int16_t keycode_up;
int16_t keycode_down;
int16_t keycode_left;
int16_t keycode_right;
int16_t key_timer;

/* eeprom */
// 初期化
void eeconfig_init_kb(void) {
    ot17_config.spd = SPD_DEFAULT;
    ot17_config.angle = ANGLE_DEFAULT;
    ot17_config.pd_mode = MODE_DEFAULT;
    ot17_config.inv = INVERT_DEFAULT;
    ot17_config.inv_sc = INVERT_SCROLL_DEFAULT;
    ot17_config.auto_mouse = AUTO_MOUSE_DEFAULT;
    ot17_config.rgb_layers = RGB_LAYER_DEFAULT;
    eeconfig_update_kb(ot17_config.raw);

    eeconfig_init_user();
}

/* キースキャン */
// マウスキー登録
bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case MOD_SCRL: // 一時的にスクロール
            return true;
        case MOD_SLOW: // 一時的に減速
            return true;
        case BTN1_SLOW: // マウス1 / 長押しスロー
            return true;
        case BTN2_SLOW: // マウス2 / 長押しスロー
            return true;
        case BTN3_SLOW: // マウス3 / 長押しスロー
            return true;
        case MOD_CUR: // 一時的にカーソル移動
            return true;
        default:
            return false;
    }

    return  is_mouse_record_user(keycode, record);
}

// 実タスク
bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    // 追加キーコードタスク
    process_record_addedkeycodes(keycode, record);

    return process_record_user(keycode, record);
}

/* マトリクス走査 */
// 初期化
void matrix_init_kb(void) {
    key_left.row = 0;
    key_left.col = 15;
    key_up.row = 0;
    key_up.col = 16;
    key_down.row = 1;
    key_down.col = 15;
    key_right.row = 1;
    key_right.col = 16;
    force_scrolling = false;
    force_cursoring = false;
    force_key_input = false;
    slow_mode = false;
    key_timer = timer_read();

    matrix_init_user();
}

/* カーソル操作 */
// 初期化
void pointing_device_init_kb(void){
    ot17_config.raw = eeconfig_read_kb();
    x_accumulator = 0.0;
    y_accumulator = 0.0;
    h_accumulator = 0.0;
    v_accumulator = 0.0;
    prev_x = 0.0;
    prev_y = 0.0;
    pointing_device_set_cpi(400 + ot17_config.spd * 200);
    set_auto_mouse_enable(ot17_config.auto_mouse);

    pointing_device_init_user();
}

// 実タスク
#define constrain_hid(amt) ((amt) < -127 ? -127 : ((amt) > 127 ? 127 : (amt)))
report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {

    // 角度補正
    float rad;
    rad = (float)ot17_config.angle * 6.0 * (M_PI / 180.0) * -1.0;
    float x_rev =  + (float)mouse_report.x * cos(rad) - (float)mouse_report.y * sin(rad);
    float y_rev =  + (float)mouse_report.x * sin(rad) + (float)mouse_report.y * cos(rad);

    float smoothed_x = prev_x * SMOOTHING_FACTOR + x_rev * (1.0 - SMOOTHING_FACTOR);
    float smoothed_y = prev_y * SMOOTHING_FACTOR + y_rev * (1.0 - SMOOTHING_FACTOR);
    prev_x = smoothed_x;
    prev_y = smoothed_y;

    // 動作量で移動量を変える
    float movement_magnitude = sqrt(smoothed_x * smoothed_x + smoothed_y * smoothed_y);
    float dynamic_multiplier = 1.0 + movement_magnitude / 10.0;
    dynamic_multiplier = fmin(fmax(dynamic_multiplier, 0.5), 3.0);
    x_rev *= SENSITIVITY_MULTIPLIER * dynamic_multiplier;
    y_rev *= SENSITIVITY_MULTIPLIER * dynamic_multiplier;

    // x軸反転処理
    if(ot17_config.inv){
            x_rev = -1 * x_rev;
    }

    // スクロール処理
    if(!force_key_input && (force_scrolling || ot17_config.pd_mode == SCROLL_MODE)){
        // 斜め成分を消す
        if (abs(x_rev) > abs(y_rev)) {
            y_rev = 0;
        } else {
            x_rev = 0;
        }

        // スクロール反転処理
        if(!ot17_config.inv_sc ){
            x_rev = -1.0 * x_rev;
            y_rev = -1.0 * y_rev;
        }

        // 端数処理
        h_accumulator += x_rev * SENSITIVITY_DIVISOR / SCROLL_DIVISOR;
        v_accumulator += y_rev * SENSITIVITY_DIVISOR / SCROLL_DIVISOR;
        mouse_report.h = (int8_t)constrain_hid(h_accumulator);
        mouse_report.v = (int8_t)constrain_hid(v_accumulator);
        h_accumulator -= mouse_report.h;
        v_accumulator -= mouse_report.v;

        mouse_report.x = 0;
        mouse_report.y = 0;
    // カーソル移動処理
    }else if(!force_key_input && (force_cursoring || ot17_config.pd_mode == CURSOR_MODE)){
        x_accumulator += x_rev * SENSITIVITY_DIVISOR;
        y_accumulator += y_rev * SENSITIVITY_DIVISOR;
        mouse_report.x = (int8_t)constrain_hid(x_accumulator);
        mouse_report.y = (int8_t)constrain_hid(y_accumulator);
        x_accumulator -= mouse_report.x;
        y_accumulator -= mouse_report.y;

        mouse_report.h = 0;
        mouse_report.v = 0;
    // キー入力処理
    }else if(force_key_input || ot17_config.pd_mode == KEY_INPUT){
        // 入力キーの座標指定
        mouse_report.x = 0;
        mouse_report.y = 0;
        mouse_report.h = 0;
        mouse_report.v = 0;
        layer = layer_switch_get_layer(key_up);
        keycode_up = keymap_key_to_keycode(layer, key_up);
        keycode_left = keymap_key_to_keycode(layer, key_left);
        keycode_right = keymap_key_to_keycode(layer, key_right);
        keycode_down = keymap_key_to_keycode(layer, key_down);

        // 斜め成分を消す
        if (abs(x_rev) > abs(y_rev)) {
            y_rev = 0;
        } else {
            x_rev = 0;
        }

        // トラックボール時は単入力を一定時間間隔
        if(timer_elapsed(key_timer) > TIMEOUT_KEY){
            if((int16_t)x_rev > KEY_OFFSET){
                tap_code16(keycode_right);
            }else if((int16_t)x_rev  < -KEY_OFFSET){
                tap_code16(keycode_left);
            }

            if((int16_t)y_rev > KEY_OFFSET){
                tap_code16(keycode_down);
            }else if((int16_t)y_rev < -KEY_OFFSET){
                tap_code16(keycode_up);
            }

            key_timer = timer_read();
        }
    }

    return pointing_device_task_user(mouse_report);
}

/* 諸関数 */
// モードチェンジ時端数削除
void clear_keyinput(void){
    unregister_code(keycode_left);
    unregister_code(keycode_up);
    unregister_code(keycode_down);
    unregister_code(keycode_right);
    x_accumulator = 0.0;
    y_accumulator = 0.0;
    v_accumulator = 0.0;
    h_accumulator = 0.0;
    prev_x = 0.0;
    prev_y = 0.0;
}

/* インターフェース */
// モード変更
void cycle_mode(void){
    ot17_config.pd_mode = (ot17_config.pd_mode + 1) % 3;
    eeconfig_update_kb(ot17_config.raw);
    clear_keyinput();
}
// 一時的モード変更
void is_scroll_mode(bool is_force_scrolling){
    force_scrolling = is_force_scrolling;
    clear_keyinput();
}
void is_cursor_mode(bool is_force_cursoring){
    force_cursoring = is_force_cursoring;
    clear_keyinput();
}
void is_key_mode(bool is_force_key_input){
    force_key_input = is_force_key_input;
    clear_keyinput();
}
void is_slow_mode(bool is_slow_mode){
    slow_mode = is_slow_mode;
    if(is_slow_mode){
                pointing_device_set_cpi(CPI_SLOW);
    }else{
                pointing_device_set_cpi(400 + ot17_config.spd * 200);
    }
    clear_keyinput();
}
