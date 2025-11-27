// Copyright 2025 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "lib/add_keycodes.h"
#include "os_detection.h"
#include "lib/common_handyman_v2.h"

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
        case CC_A:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_A);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_A);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_B:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_B);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_B);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_C:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_C);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_C);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_D:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_D);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_D);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_E:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_E);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_E);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_F:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_F);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_F);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_G:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_G);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_G);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_H:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_H);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_H);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_I:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_I);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_I);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_J:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_J);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_J);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_K:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_K);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_K);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_L:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_L);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_L);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_M:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_M);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_M);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_N:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_N);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_N);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_O:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_O);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_O);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_P:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_P);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_P);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_Q:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_Q);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_Q);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_R:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_R);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_R);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_S:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_S);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_S);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_T:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_T);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_T);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_U:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_U);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_U);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_V:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_V);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_V);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_W:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_W);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_W);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_X:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_X);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_X);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_Y:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_Y);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_Y);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_Z:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_Z);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_Z);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_MIN:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_PMNS);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_PMNS);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_PLUS:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_PPLS);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_PPLS);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_0:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_0);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_0);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CC_TAB:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_TAB);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_TAB);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case RGB_LAYERS:
                if (record->event.pressed) {
                    h2_config.rgb_layers = !h2_config.rgb_layers;
                    eeconfig_update_kb(h2_config.raw);
                }
                return false;
                break;
    }

    return true;
}
