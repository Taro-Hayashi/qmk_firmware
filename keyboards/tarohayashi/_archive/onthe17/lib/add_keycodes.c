// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lib/add_keycodes.h"
#include "os_detection.h"
#include "lib/common_onthe17.h"

uint16_t startup_timer;

bool process_record_addedkeycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CMD_CTL:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                }
            } else {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    unregister_code(KC_LGUI);
                } else {
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CAPTCHA:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_4);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_S);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                }
            }
            return false;
            break;
        case CPI_I:
            if (record->event.pressed) {
                ot17_config.spd = ot17_config.spd + 1;
                if(ot17_config.spd >= SPD_OPTION_MAX){
                    ot17_config.spd = SPD_OPTION_MAX-1;
                }
                eeconfig_update_user(ot17_config.raw);
                pointing_device_set_cpi(400 + ot17_config.spd * 200);
            }
            return false;
            break;
        case CPI_D:
            if (record->event.pressed) {
                if(ot17_config.spd > 0){
                    ot17_config.spd = ot17_config.spd - 1;
                }
                eeconfig_update_user(ot17_config.raw);
                pointing_device_set_cpi(400 + ot17_config.spd * 200);
            }
            return false;
            break;
        case ANG_I:
            if (record->event.pressed) {
                ot17_config.angle = (ot17_config.angle + 1) % ANGLE_OPTION_MAX;
                eeconfig_update_user(ot17_config.raw);
            }
            return false;
            break;
        case ANG_D:
            if (record->event.pressed) {
                ot17_config.angle = (ANGLE_OPTION_MAX + ot17_config.angle - 1) % ANGLE_OPTION_MAX;
                eeconfig_update_user(ot17_config.raw);
            }
            return false;
            break;
        case INV:
            if (record->event.pressed) {
                ot17_config.inv = !ot17_config.inv;
                eeconfig_update_user(ot17_config.raw);
            }
            return false;
            break;
        case CHMOD:
            if (record->event.pressed) {
                cycle_mode();
            }
            return false;
            break;
        case INV_SCRL:
            if (record->event.pressed) {
                ot17_config.inv_sc = !ot17_config.inv_sc;
                eeconfig_update_user(ot17_config.raw);
            }
            return false;
            break;
        case MOD_SCRL:
            is_scroll_mode(record->event.pressed);
            return false;
            break;
        case AUTO_MOUSE:
            if (record->event.pressed) {
                ot17_config.auto_mouse = !ot17_config.auto_mouse;
                set_auto_mouse_enable(ot17_config.auto_mouse);
                eeconfig_update_user(ot17_config.raw);
            }
            return false;
            break;
        case ESC_SCRL:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_scroll_mode(true);
            } else {
                is_scroll_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_ESC);
                }
            }
            return false;
            break;
        case TAB_SCRL:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_scroll_mode(true);
            } else {
                is_scroll_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_TAB);
                }
            }
            return false;
            break;
        case LNG1_SCRL:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_scroll_mode(true);
            } else {
                is_scroll_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_LNG1);
                }
            }
            return false;
            break;
        case LNG2_SCRL:
          if (record->event.pressed) {
                startup_timer = timer_read();
                is_scroll_mode(true);
            } else {
                is_scroll_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_LNG2);
                }
            }
            return false;
            break;
        case MOD_SLOW:
            is_slow_mode(record->event.pressed);
            return false;
            break;
        case ESC_SLOW:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_scroll_mode(true);
            } else {
                is_scroll_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_ESC);
                }
            }
            return false;
            break;
        case TAB_SLOW:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_scroll_mode(true);
            } else {
                is_scroll_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_TAB);
                }
            }
            return false;
            break;
        case LNG1_SLOW:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_scroll_mode(true);
            } else {
                is_scroll_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_LNG1);
                }
            }
            return false;
            break;
        case LNG2_SLOW:
          if (record->event.pressed) {
                startup_timer = timer_read();
                is_scroll_mode(true);
            } else {
                is_scroll_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_LNG2);
                }
            }
            return false;
            break;
        case BTN1_SLOW:
            if (record->event.pressed) {
                register_code(MS_BTN1);
                is_scroll_mode(true);
            } else {
                is_scroll_mode(false);
                unregister_code(MS_BTN1);
            }
            return false;
            break;
        case BTN2_SLOW:
            if (record->event.pressed) {
                register_code(MS_BTN2);
                is_scroll_mode(true);
            } else {
                is_scroll_mode(false);
                unregister_code(MS_BTN2);
            }
            return false;
            break;
        case BTN3_SLOW:
          if (record->event.pressed) {
                register_code(MS_BTN3);
                is_scroll_mode(true);
            } else {
                is_scroll_mode(false);
                unregister_code(MS_BTN3);
            }
            return false;
            break;
        // 押している間キー入力
        case MOD_KEY:
            is_key_mode(record->event.pressed);
            return false;
            break;
        case ESC_KEY:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_key_mode(true);
            } else {
                is_key_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_ESC);
                }
            }
            return false;
            break;
        case TAB_KEY:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_key_mode(true);
            } else {
                is_key_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_TAB);
                }
            }
            return false;
            break;
        case LNG1_KEY:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_key_mode(true);
            } else {
                is_key_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_LNG1);
                }
            }
            return false;
            break;
        case LNG2_KEY:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_key_mode(true);
            } else {
                is_key_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_LNG2);
                }
            }
            return false;
                break;
        // 押している間カーソル移動
        case MOD_CUR:
            is_cursor_mode(record->event.pressed);
            return false;
            break;
        // RGBレイヤーオンオフ
        case RGB_LAYERS:
            if (record->event.pressed) {
                ot17_config.rgb_layers = !ot17_config.rgb_layers;
                eeconfig_update_kb(ot17_config.raw);
            }
            return false;
            break;
    }
    return true;
}
