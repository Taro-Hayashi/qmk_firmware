// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "lib/add_keycodes.h"

// キーマップ
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
      KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,
      KC_1, KC_2, KC_3, KC_4, KC_5, KC_GRV,
      KC_6, KC_7, KC_8, KC_9, KC_0, KC_LSFT
    )
};
