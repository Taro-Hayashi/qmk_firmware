// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

// 追加するキーコード
enum TH_keycodes{
    CMD_CTL = QK_KB_0,
    CAPTCHA,
    CPI_I,
    CPI_D,
    ANG_I,
    ANG_D,
    INV,
    CHMOD,
    INV_SCRL,
    MOD_SCRL,
    AUTO_MOUSE,
    ESC_SCRL,
    TAB_SCRL,
    LNG1_SCRL,
    LNG2_SCRL,
    MOD_SLOW,
    ESC_SLOW,
    TAB_SLOW,
    LNG1_SLOW,
    LNG2_SLOW,
    BTN1_SLOW,
    BTN2_SLOW,
    BTN3_SLOW,
    MOD_KEY,
    ESC_KEY,
    TAB_KEY,
    LNG1_KEY,
    LNG2_KEY,
    MOD_CUR,
    RGB_LAYERS,
};

bool process_record_addedkeycodes(uint16_t keycode, keyrecord_t *record);
