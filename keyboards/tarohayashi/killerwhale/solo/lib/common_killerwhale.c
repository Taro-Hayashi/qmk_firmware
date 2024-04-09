// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lib/common_killerwhale.h"
#include "analog.h"
#include "math.h"
#include "lib/add_keycodes.h"
#include "lib/add_oled.h"

/* ポインティングデバイス用変数 */
kw_config_t kw_config;      // eeprom保存用
bool force_scrolling; // 一時的モード変更用
bool force_cursoring; // 一時的モード変更用
bool force_key_input; // 一時的モード変更用
bool slow_mode;       // 一時的モード変更用
bool joystick_attached;     // ジョイスティックの有無
float scroll_accumulated_h; // スクロール端数保存用
float scroll_accumulated_v; // スクロール端数保存用

int16_t gp27_newt; // ジョイスティックの初期値
int16_t gp28_newt; // ジョイスティックの初期値

// 仮想十字キー設定用
keypos_t key_up;
keypos_t key_left;
keypos_t key_right;
keypos_t key_down;
bool pressed_up = false;
bool pressed_down = false;
bool pressed_left = false;
bool pressed_right = false;
int8_t layer;
int16_t keycode_up;
int16_t keycode_down;
int16_t keycode_left;
int16_t keycode_right;
int16_t key_timer;

// 十字キー排他設定
uint8_t dpad_pressed;

/* eeprom */
// 初期化
void eeconfig_init_kb(void) {
    kw_config.spd = SPD_DEFAULT;
    if(readPin(GP10)){
        kw_config.angle = ANGLE_DEFAULT_RIGHT;
    }else {
        kw_config.angle = ANGLE_DEFAULT_LEFT;
    }
    kw_config.rgb_layer = false;
    kw_config.pd_mode = CURSOR_MODE;
    kw_config.inv = true;
    kw_config.inv_sc = false;
    kw_config.auto_mouse = true;
    kw_config.oled_mode = SHOW_LAYER;
    kw_config.dpad_exclusion = true;
    eeconfig_update_kb(kw_config.raw);

    eeconfig_init_user();
}

/* キースキャン */
// マウスキー登録
bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case MOD_SCRL: // 一時的にスクロール
            return true;
        case QK_USER_4: // 一時的に減速
            return true;
        case QK_USER_9: // マウス1 / 長押しスロー
            return true;
        case QK_USER_10: // マウス2 / 長押しスロー
            return true;
        case QK_USER_11: // マウス3 / 長押しスロー
            return true;
        case QK_USER_12: // 一時的にカーソル移動
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
    keypos_t key = record->event.key;
    if(key.col == 6 && kw_config.dpad_exclusion){
        switch (key.row){
            case 1:
            case 2:
            case 3:
            case 4:
                if(dpad_pressed == 0 && record->event.pressed){
                    if(record->event.pressed){
                        dpad_pressed = key.row;
                    }
                }else if(dpad_pressed == key.row && !record->event.pressed){
                    dpad_pressed = 0;
                }else if(record->event.pressed){
                    return false;
                }
        }
    }

    return process_record_user(keycode, record);
}

/* マトリクス走査 */
// 初期化
void matrix_init_kb(void) {
    key_up.row = 3;
    key_up.col = 6;
    key_left.row = 2;
    key_left.col = 6;
    key_right.row = 4;
    key_right.col = 6;
    key_down.row = 1;
    key_down.col = 6;
    dpad_pressed = 0;
    force_scrolling = false;
    force_cursoring = false;
    force_key_input = false;
    slow_mode = false;
    gp27_newt = analogReadPin(GP27);
    gp28_newt = analogReadPin(GP28);
    if(gp27_newt < NO_JOYSTICK_VAL ||  gp28_newt < NO_JOYSTICK_VAL ){
        joystick_attached = false;
    }else{
        joystick_attached = true;
    }
    key_timer = timer_read();

    matrix_init_user();
}

/* カーソル操作 */
// 初期化
void pointing_device_init_kb(void){
    kw_config.raw = eeconfig_read_kb();
    scroll_accumulated_h = 0;
    scroll_accumulated_v = 0;
    pointing_device_set_cpi(400 + kw_config.spd * 200);
    set_auto_mouse_enable(kw_config.auto_mouse);

    pointing_device_init_user();
}
// 実タスク
report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    double x_val = 0.0;
    double y_val = 0.0;
    double amp_temp = 1.0;
    double rad;
    // ジョイスティックの場合は定期的に値を取り出す
    if(joystick_attached){
        // amprifier値決定
        if(slow_mode){
            amp_temp = AMP_SLOW;
        }else{
            amp_temp = 4.0 + (double)kw_config.spd * 3.0;
        }
        switch (kw_config.pd_mode){
            case KEY_INPUT:
                amp_temp = amp_temp / 10;
                break;
            case CURSOR_MODE:
                amp_temp = amp_temp / 20;
                break;
            case SCROLL_MODE:
                amp_temp = amp_temp / 50;
                break;
        }

        // 数値補正
        int16_t gp28val = analogReadPin(GP28) - gp28_newt;
        int16_t gp27val = analogReadPin(GP27) - gp27_newt;
        if(abs(gp28val)<JOYSTICK_MOVE_OFFSET){
            gp28val = 0;
        }
        if(abs(gp27val)<JOYSTICK_MOVE_OFFSET){
            gp27val = 0;
        }
        x_val = ( (double)gp28val / JOYSTICK_DIVISOR ) * amp_temp;
        y_val = ( (double)gp27val / JOYSTICK_DIVISOR ) * amp_temp;
    // マウスの時は数値はそのまま使う
    }else{
        x_val = (double)mouse_report.x;
        y_val = (double)mouse_report.y;
    }
    // 角度補正
    rad = (double)kw_config.angle * 6.0 * (M_PI / 180.0) * -1.0;
    double x_rev =  + x_val * cos(rad) - y_val * sin(rad);
    double y_rev =  + x_val * sin(rad) + y_val * cos(rad);

    // x軸反転処理
    if(kw_config.inv){
            x_rev = -1 * x_rev;
    }

    // スクロール処理
    if(!force_key_input && (force_scrolling || kw_config.pd_mode == SCROLL_MODE)){
        // 斜め成分を消す
        if (abs(x_rev) > abs(y_rev)) {
            y_rev = 0;
        } else {
            x_rev = 0;
        }

        // スクロール反転処理
        if(!kw_config.inv_sc ){
            x_rev = -1.0 * x_rev;
            y_rev = -1.0 * y_rev;
        }

        // 端数処理
        scroll_accumulated_h += (float)x_rev / SCROLL_DIVISOR;
        scroll_accumulated_v += (float)y_rev / SCROLL_DIVISOR;
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        mouse_report.x = 0;
        mouse_report.y = 0;
    // カーソル移動処理
    }else if(!force_key_input && (force_cursoring || kw_config.pd_mode == CURSOR_MODE)){
        mouse_report.x = (int8_t)x_rev;
        mouse_report.y = (int8_t)y_rev;
        mouse_report.h = 0;
        mouse_report.v = 0;
    // キー入力処理
    }else if(force_key_input || kw_config.pd_mode == KEY_INPUT){
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

        // 斜めを除外
        if(kw_config.dpad_exclusion){
            if (abs(x_rev) > abs(y_rev)) {
                y_rev = 0;
            } else {
                x_rev = 0;
            }
        }

        // ジョイスティック時は倒している間押しっぱなし
        if(joystick_attached){
            if(!pressed_left && (int16_t)x_rev > KEY_OFFSET){
                pressed_left = true;
                register_code(keycode_right);
            }else if(pressed_left && (int16_t)x_rev  < KEY_OFFSET){
                pressed_left = false;
                unregister_code(keycode_right);
            }else if(!pressed_right && (int16_t)x_rev  < -KEY_OFFSET){
                pressed_right = true;
                register_code(keycode_left);
            }else if (pressed_right && (int16_t)x_rev  > -KEY_OFFSET){
                pressed_right = false;
                unregister_code(keycode_left);
            }

            if(!pressed_up && (int16_t)y_rev > KEY_OFFSET){
                pressed_up = true;
                register_code(keycode_down);
            }else if(pressed_up && (int16_t)y_rev < KEY_OFFSET){
                pressed_up = false;
                unregister_code(keycode_down);
            }else if(!pressed_down && (int16_t)y_rev < -KEY_OFFSET){
                pressed_down = true;
                register_code(keycode_up);
            }else if(pressed_down && (int16_t)y_rev > -KEY_OFFSET){
                pressed_down = false;
                unregister_code(keycode_up);
            }
        // トラックボール時は単入力を一定時間間隔
        }else if(timer_elapsed(key_timer) > TIMEOUT_KEY){
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


/* OLED */
// 初期化
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    // 追加OLED初期化
    oled_init_addedoled();

    return oled_init_user(rotation);
}
// 実タスク
bool oled_task_kb(void) {
    // 追加OLEDタスク
    oled_task_addedoled();

    return oled_task_user();
}

/* 諸関数 */
// モードチェンジ時端数削除
void clear_keyinput(void){
    unregister_code(keycode_up);
    unregister_code(keycode_down);
    unregister_code(keycode_left);
    unregister_code(keycode_right);
    scroll_accumulated_v = 0;
    scroll_accumulated_h = 0;
}
/* インターフェース */
// ジョイスティックの有無
bool get_joystick_attached(void){ return joystick_attached; }
// モード変更
void cycle_mode(void){
    kw_config.pd_mode = (kw_config.pd_mode + 1) % 3;
    eeconfig_update_kb(kw_config.raw);
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
                pointing_device_set_cpi(400 + kw_config.spd * 200);
    }
    clear_keyinput();
}


