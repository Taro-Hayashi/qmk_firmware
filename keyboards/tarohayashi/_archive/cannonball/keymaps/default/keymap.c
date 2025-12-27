// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "lib/add_keycodes.h"

enum layer_names {
  BASE = 0,
  LIGHT = 5,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
                    CAPTCHA, PASTE, COPY,  KC_BSPC,
        SC_RESET, SAVE,   KC_UP,   SAVEAS,
                    KC_LEFT,   KC_DOWN, KC_RGHT, KC_ENT,
        // LEVER
        PREVTAB, CLOSETAB, NEXTTAB
  )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] =   {
      ENCODER_CCW_CW(KC_1, KC_2),
      ENCODER_CCW_CW(KC_3, KC_4),
      ENCODER_CCW_CW(KC_5, KC_6)
      }
};
