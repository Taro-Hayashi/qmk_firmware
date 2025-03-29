// Copyright 2025 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "lib/add_keycodes.h"

enum layer_names {
    BASE = 0,
    TEMPLATE_BLANK = 3,
    TEMPLATE_TRANSPALENT = 4,
    SETTING = 5
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        // キースイッチ、クリックボタン
        KC_A, KC_B, KC_C, KC_D,
        KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L,
        // ロータリーエンコーダー
        KC_M, KC_N, KC_O, KC_P,
        // マウスボタン
        KC_Q, KC_R,
        // レバーボタン
        KC_S, KC_T, KC_U,
        KC_V, KC_W, KC_X,
        // 側面ボタン
        KC_1, KC_2,
        KC_3, KC_4,
        // 背面ボタン
        KC_5, KC_6, KC_7,
        // スライドスイッチ
        MO(5),
        // センタープッシュ（無効）
        XXXXXXX
    ),
    [TEMPLATE_BLANK] = LAYOUT(
        // キースイッチ、クリックボタン
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // ロータリーエンコーダー
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // マウスボタン
        XXXXXXX, XXXXXXX,
        // レバーボタン
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,
        // 側面ボタン
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,
        // 背面ボタン
        XXXXXXX, XXXXXXX, XXXXXXX,
        // スライドスイッチ
        XXXXXXX,
        // センタープッシュ（無効）
        XXXXXXX
    ),
    [TEMPLATE_TRANSPALENT] = LAYOUT(
        // キースイッチ、クリックボタン
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        // ロータリーエンコーダー
        _______, _______, _______, _______,
        // マウスボタン
        _______, _______,
        // レバーボタン
        _______, _______, _______,
        _______, _______, _______,
        // 側面ボタン
        _______, _______,
        _______, _______,
        // 背面ボタン
        _______, _______, _______,
        // スライドスイッチ
        _______,
        // センタープッシュ（無効）
        _______
    ),
    [SETTING] = LAYOUT(
        // キースイッチ、クリックボタン
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // ロータリーエンコーダー
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // マウスボタン
        XXXXXXX, XXXXXXX,
        // レバーボタン
        UG_NEXT,  XXXXXXX, UG_PREV,
        UG_NEXT,  XXXXXXX, UG_PREV,
        // 側面ボタン
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,
        // 背面ボタン
        XXXXXXX, XXXXXXX, RGB_LAYERS,
        // スライドスイッチ
        MO(5),
        // センタープッシュ（無効）
        XXXXXXX
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] =   {
        ENCODER_CCW_CW(KC_1,   KC_2),
        ENCODER_CCW_CW(KC_3,   KC_4),
        ENCODER_CCW_CW(KC_5,   KC_6)
    },
    [TEMPLATE_BLANK] =   {
        ENCODER_CCW_CW(XXXXXXX, XXXXXXX),
        ENCODER_CCW_CW(XXXXXXX, XXXXXXX),
        ENCODER_CCW_CW(XXXXXXX, XXXXXXX)
    },
    [TEMPLATE_TRANSPALENT] =   {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [SETTING] =   {
        ENCODER_CCW_CW(UG_HUEU, UG_HUED),
        ENCODER_CCW_CW(UG_VALU, UG_VALD),
        ENCODER_CCW_CW(UG_SATU, UG_SATD)
    }
};
