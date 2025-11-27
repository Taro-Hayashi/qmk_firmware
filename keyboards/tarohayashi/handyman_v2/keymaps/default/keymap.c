// Copyright 2025 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "lib/add_keycodes.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A, KC_B, KC_C, KC_D, KC_E,
        KC_F, KC_G, KC_H, KC_I, KC_J,
        KC_K, KC_L, KC_M, KC_N, KC_O,
        KC_P, KC_Q, KC_R, KC_S, KC_T,
        KC_U, KC_V, KC_W, KC_X, KC_Y,
        KC_1, KC_2, KC_3,
        KC_Z,
        KC_4
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   {
        ENCODER_CCW_CW(KC_1,   KC_2),
        ENCODER_CCW_CW(KC_3,   KC_4),
        ENCODER_CCW_CW(KC_5,   KC_6)
    }
};
