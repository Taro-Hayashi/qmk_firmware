// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "lib/add_keycodes.h"

enum custom_keycode {
  BASE = 0,
  LIGHT = 5,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        SAVE, LCTL(KC_L), RCS(KC_N), LCTL(KC_U), KC_BSPC,
        LSFT(KC_F7), LCTL(KC_M), LCTL(KC_T), KC_M, LCTL(KC_D),
        KC_X, KC_F13, UNDO, KC_F14, SC_RESET,
        KC_O, KC_S, KC_Y, KC_I, KC_F15,
        LCTL(KC_H), KC_U, LALT_T(KC_E), LCTL_T(KC_B), LSFT_T(KC_P),
        // LEVER
        KC_T, KC_G, KC_J
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] =   {
      ENCODER_CCW_CW(SC_UP, SC_DOWN),
      ENCODER_CCW_CW(KC_RBRC, KC_LBRC),
      ENCODER_CCW_CW(KC_MINS, KC_QUOT)
      }
};
