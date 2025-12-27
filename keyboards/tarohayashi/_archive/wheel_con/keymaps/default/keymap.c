// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* NONE */
        KC_C, KC_F, KC_I, KC_L, KC_O
  )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   {
      ENCODER_CCW_CW(KC_A, KC_B), 
      ENCODER_CCW_CW(KC_D, KC_E), 
      ENCODER_CCW_CW(KC_G, KC_H), 
      ENCODER_CCW_CW(KC_J, KC_K), 
      ENCODER_CCW_CW(KC_M, KC_N)
      }
};
