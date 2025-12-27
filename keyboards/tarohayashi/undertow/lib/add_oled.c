// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lib/add_oled.h"
#include "os_detection.h"
#include "lib/common_undertow.h"
#include "lib/glcdfont.c"
#include "lib/add_keycodes.h"
#include "analog.h"

uint8_t pre_layer, cur_layer;
bool interrupted;
uint16_t interrupted_time, interrupt_type;
bool tempch;
uint16_t tempch_time;
uint16_t tempch_type;

// 初期化
void oled_init_addedoled(void){
    pre_layer = 0;
    cur_layer = 0;
    interrupted = false;
    interrupted_time = 0;
    interrupt_type = 0;
    tempch = 0;
    tempch_time = 0;
    tempch_type = 0;
}

bool oled_task_addedoled(void) {
    // 割り込み表示
    if(interrupted){
        if(timer_elapsed(interrupted_time) < INTERRUPT_TIME){
            oled_set_cursor(0, 3);
            switch (interrupt_type){
                case UG_HUEU:
                    oled_write_P(PSTR("INCREASE HUE         "), false);
                    break;
                case UG_HUED:
                    oled_write_P(PSTR("DECREASE HUE         "), false);
                    break;
                case UG_SATU:
                    oled_write_P(PSTR("INCREASE SATURATION  "), false);
                    break;
                case UG_SATD:
                    oled_write_P(PSTR("DECREASE SATURATION  "), false);
                    break;
                case UG_VALU:
                    oled_write_P(PSTR("INCREASE VALUE       "), false);
                    break;
                case UG_VALD:
                    oled_write_P(PSTR("DECREASE VALUE       "), false);
                    break;
                case UG_SPDU:
                    oled_write_P(PSTR("INCREASE LIGHT SPEED "), false);
                    break;
                case UG_SPDD:
                    oled_write_P(PSTR("DECREASE LIGHT SPEED "), false);
                    break;
                case UG_NEXT:
                    oled_write_P(PSTR("NEXT LIGHT PATTERN   "), false);
                    break;
                case UG_PREV:
                    oled_write_P(PSTR("PREV LIGHT PATTERN   "), false);
                    break;
                case UG_TOGG:
                    if(rgblight_is_enabled()){
                        oled_write_P(PSTR("RGB ON               "), false);
                    }else{
                        oled_write_P(PSTR("RGB OFF              "), false);
                    }
                    break;
                // 設定系
                case SPD_I_0:
                    oled_write_P(PSTR("SPEED UP SIDE0       "), false);
                    break;
                case SPD_I_1:
                    oled_write_P(PSTR("SPEED UP SIDE1       "), false);
                    break;
                case SPD_D_0:
                    oled_write_P(PSTR("SPEED DOWN SIDE0     "), false);
                    break;
                case SPD_D_1:
                    oled_write_P(PSTR("SPEED DOWN SIDE1     "), false);
                    break;
                case ANG_I_0:
                    oled_write_P(PSTR("TURNED CW SIDE0      "), false);
                    break;
                case ANG_I_1:
                    oled_write_P(PSTR("TURNED CW SIDE1      "), false);
                    break;
                case ANG_D_0:
                    oled_write_P(PSTR("TURNED CCW SIDE0     "), false);
                    break;
                case ANG_D_1:
                    oled_write_P(PSTR("TURNED CCW SIDE1     "), false);
                    break;
                case INV_0:
                    oled_write_P(PSTR("AXIS INVERTED SIDE0  "), false);
                    break;
                case INV_1:
                    oled_write_P(PSTR("AXIS INVERTED SIDE1  "), false);
                    break;
                case INV_SCRL:
                    oled_write_P(PSTR("SCROLL INVERTED      "), false);
                    break;
                case CHMOD_0:
                    if(ut_config.pd_mode_0 == SCROLL_MODE){
                        oled_write_P(PSTR("SCROLL MODE SIDE0    "), false);
                    }else if(ut_config.pd_mode_0 == CURSOR_MODE){
                        oled_write_P(PSTR("CURSOR MODE SIDE0    "), false);
                    }else if(ut_config.pd_mode_0 == KEY_INPUT){
                        oled_write_P(PSTR("KEY INPUT MODE SIDE0 "), false);
                    }else if(ut_config.pd_mode_0 == GAME_MODE){
                        oled_write_P(PSTR("KEY INPUT MODE SIDE0 "), false);
                    }
                    break;
                case CHMOD_1:
                    if(ut_config.pd_mode_1 == SCROLL_MODE){
                        oled_write_P(PSTR("SCROLL MODE SIDE1    "), false);
                    }else if(ut_config.pd_mode_1 == CURSOR_MODE){
                        oled_write_P(PSTR("CURSOR MODE SIDE1    "), false);
                    }else if(ut_config.pd_mode_1 == KEY_INPUT){
                        oled_write_P(PSTR("KEY INPUT MODE SIDE1 "), false);
                    }else if(ut_config.pd_mode_1 == GAME_MODE){
                        oled_write_P(PSTR("KEY INPUT MODE SIDE0 "), false);
                    }
                    break;
                case AUTO_MOUSE:
                    if(ut_config.auto_mouse){
                        oled_write_P(PSTR("AUTO MOUSE ON        "), false);
                    }else{
                        oled_write_P(PSTR("AUTO MOUSE OFF       "), false);
                    }
                    break;
                case OLED_MOD:
                    if(ut_config.oled_mode){
                        oled_write_P(PSTR("SHOW LAYER           "), false);
                    }else{
                        oled_write_P(PSTR("SHOW STATS           "), false);
                    }
                    break;
                case DPAD_MOD:
                    if(get_dpad_exclusion()){
                        oled_write_P(PSTR("DPAD EXCLUSION ON    "), false);
                    }else{
                        oled_write_P(PSTR("DPAD EXCLUSION OFF   "), false);
                    }
                    break;
                case RGB_LAYERS:
                    if(get_rgblayers()){
                        oled_write_P(PSTR("RGBLIGHT LAYER ON   "), false);
                    }else{
                        oled_write_P(PSTR("RGBLIGHT LAYER OFF  "), false);
                    }
                    break;
                case JS_RESET:
                        oled_write_P(PSTR("JOYSTICK INITIALIZED "), false);
                    break;
                case OFFSET_MIN_D:
                case OFFSET_MIN_I:
                        oled_write_P(PSTR("OFFSET MIN: "), false);
                        oled_write(get_u16_str(get_joystick_offset_min(), ' '), false);
                        oled_write_P(PSTR("   "), false);
                    break;
                case OFFSET_MAX_D:
                case OFFSET_MAX_I:
                        oled_write_P(PSTR("OFFSET MAX: "), false);
                        oled_write(get_u16_str(get_joystick_offset_max(), ' '), false);
                        oled_write_P(PSTR("   "), false);
                    break;
            }
        }else{
            interrupted = false;
        }
    // 切り替え表示
    }else if(tempch && timer_elapsed(tempch_time) > TERM_TEMP){
        oled_set_cursor(0, 3);
        switch (tempch_type){
            case MOD_SCRL:
                oled_write_P(PSTR("SCROLL MODE          "), false);
                break;
            case MOD_SLOW:
                oled_write_P(PSTR("SLOW MODE            "), false);
                break;
            case MOD_CUR:
                oled_write_P(PSTR("CURSOR MODE          "), false);
                break;
            case MOD_KEY:
                oled_write_P(PSTR("KEY INPUT MODE       "), false);
                break;
            case MOD_GAME:
                oled_write_P(PSTR("GAME MODE            "), false);
                break;
        }
    // レイヤー表示処理
    }else if(ut_config.oled_mode){
        oled_set_cursor(0, 0);
        cur_layer = get_highest_layer(layer_state);
        oled_write_raw_P(reverse_number[cur_layer], sizeof(reverse_number[cur_layer]));
    // スタッツ表示処理
    }else{
        oled_set_cursor(0, 0);
        oled_write_P(PSTR("SPD "), false);
        if(get_joystick_attached() == 0){
            oled_write_P(PSTR(" J:"), false);
            oled_write_P(get_u16_str(16 + (uint16_t)ut_config.spd_0 * 3, ' '), false);
        }else{
            oled_write_P(PSTR(" 0:"), false);
            oled_write(get_u16_str(1000 + (uint16_t)ut_config.spd_0 * 250, ' '), false);
        }
        if(get_joystick_attached() == 1){
            oled_write_P(PSTR(" J:"), false);
            oled_write(get_u16_str(16 + (uint16_t)ut_config.spd_1 * 3, ' '), false);
        }else{
            oled_write_P(PSTR(" 1:"), false);
            oled_write_P(get_u16_str(1000 + (uint16_t)ut_config.spd_1 * 250, ' '), false);
        }

        oled_set_cursor(0, 1);
        oled_write_P(PSTR("ANG "), false);
        if(get_joystick_attached() == 0){
            oled_write_P(PSTR(" J:"), false);
        }else{
            oled_write_P(PSTR(" 0:"), false);
        }
        oled_write(get_u16_str((uint16_t)ut_config.angle_0 * 12, ' '), false);
        if(get_joystick_attached() == 1){
            oled_write_P(PSTR(" J:"), false);
        }else{
            oled_write_P(PSTR(" 1:"), false);
        }
        oled_write(get_u16_str((uint16_t)ut_config.angle_1 * 12, ' '), false);

        oled_set_cursor(0, 2);
        oled_write_P(PSTR("AXIS"), false);
        if(get_joystick_attached() == 0){
            oled_write_P(PSTR(" J:"), false);
        }else{
            oled_write_P(PSTR(" 0:"), false);
        }
        if (ut_config.inv_0){
            oled_write_P(PSTR("  INV"), false);
        }else{
            oled_write_P(PSTR("     "), false);
        }
        if(get_joystick_attached() == 1){
            oled_write_P(PSTR(" J:"), false);
        }else{
            oled_write_P(PSTR(" 1:"), false);
        }
        if (ut_config.inv_1){
            oled_write_P(PSTR("  INV"), false);
        }else{
            oled_write_P(PSTR("     "), false);
        }

        oled_set_cursor(0, 3);
        oled_write_P(PSTR("MODE"), false);
        if(get_joystick_attached() == 0){
            oled_write_P(PSTR(" J:"), false);
        }else{
            oled_write_P(PSTR(" 0:"), false);
        }
        if (ut_config.pd_mode_0 == SCROLL_MODE){
            oled_write_P(PSTR("SCROL"), false);
        }else if(ut_config.pd_mode_0 == CURSOR_MODE){
            oled_write_P(PSTR("CURSR"), false);
        }else if(ut_config.pd_mode_0 == GAME_MODE){
            oled_write_P(PSTR(" GAME"), false);
        }else{
            oled_write_P(PSTR("  KEY"), false);
        }
        if(get_joystick_attached() == 1){
            oled_write_P(PSTR(" J:"), false);
        }else{
            oled_write_P(PSTR(" 1:"), false);
        }
        if (ut_config.pd_mode_1 == SCROLL_MODE){
            oled_write_P(PSTR("SCROL"), false);
        }else if(ut_config.pd_mode_1 == CURSOR_MODE){
            oled_write_P(PSTR("CURSR"), false);
        }else if(ut_config.pd_mode_1 == GAME_MODE){
            oled_write_P(PSTR(" GAME"), false);
        }else{
            oled_write_P(PSTR("  KEY"), false);
        }
    }
    // 修飾キー表示処理
    uint8_t mod_state = get_mods();
    if(mod_state){
        oled_set_cursor(0, 3);
        if(mod_state & MOD_MASK_SHIFT){
            oled_write_P(PSTR("SHIFT  "), false);
        }else{
            oled_write_P(PSTR("       "), false);
        }
        if(mod_state & MOD_MASK_CTRL){
            oled_write_P(PSTR("CTRL  "), false);
        }else{
            oled_write_P(PSTR("      "), false);
        }
        if(mod_state & MOD_MASK_ALT){
            if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                oled_write_P(PSTR("OPT  "), false);
            }else{
                oled_write_P(PSTR("ALT  "), false);
            }
        }else{
            oled_write_P(PSTR("     "), false);
        }
        if(mod_state & MOD_MASK_GUI){
            if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                oled_write_P(PSTR("CMD"), false);
            }else{
                oled_write_P(PSTR("WIN"), false);
            }
        }else{
            oled_write_P(PSTR("   "), false);
        }
    }
    return true;
}

void oled_interrupt(uint16_t keycode){
    interrupted = true;
    interrupted_time = timer_read();
    interrupt_type = keycode;
}

void oled_tempch(bool on, uint16_t keycode){
    tempch = on;
    tempch_time = timer_read();
    tempch_type = keycode;
}
