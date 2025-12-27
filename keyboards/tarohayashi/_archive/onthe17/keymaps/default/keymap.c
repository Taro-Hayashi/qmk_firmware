// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "lib/add_keycodes.h"

enum layer_names {
  BASE = 0,
  LOWER,
  UPPER,
  MOUSE,
  BALL_SETTINGS,
  LIGHT_SETTINGS
};

// キーマップd
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
      TAB_SCRL,  LT(BALL_SETTINGS, KC_Q),
                        KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,                        KC_KP_7, KC_KP_8, KC_KP_9,
      CMD_CTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,                         KC_KP_4, KC_KP_5, KC_KP_6,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                        KC_KP_1, KC_KP_2, KC_KP_3,   KC_PAST,    KC_PSLS,
      KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, LNG2_SCRL,LT(LOWER, KC_SPC), LT(LOWER, KC_SPC), LNG1_SLOW, KC_LGUI, KC_LALT, MS_BTN2, MS_BTN1, KC_KP_0, KC_EQL,  KC_KP_DOT, KC_KP_PLUS, KC_KP_MINUS,
      KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
    ),
    [LOWER] =  LAYOUT(
      KC_ESC, _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, KC_DEL,                              S(KC_7), S(KC_8), S(KC_9),
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_QUOT, _______,                            S(KC_4), S(KC_5), S(KC_6),
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, _______,                            S(KC_1), S(KC_2), S(KC_3), _______, _______,
      _______, _______, _______, _______, _______, LT(LOWER, KC_SPC), LT(LOWER, KC_SPC), _______, _______, BTN3_SLOW, BTN2_SLOW, BTN1_SLOW,  S(KC_0), _______, _______, _______, _______,
      _______, _______, _______, _______
    ),
    [UPPER] =  LAYOUT(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______
    ),
    [MOUSE] =  LAYOUT(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______
    ),
    [BALL_SETTINGS] =  LAYOUT(
      XXXXXXX, LT(BALL_SETTINGS, KC_1),
                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AUTO_MOUSE,
      XXXXXXX, CPI_I,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      ANG_I,   INV,     ANG_D,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, CPI_D,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};
