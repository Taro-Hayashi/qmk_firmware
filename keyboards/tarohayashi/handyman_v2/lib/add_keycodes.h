// Copyright 2025 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "quantum.h"

enum TH_keycodes{
    CMD_CTL = QK_KB_0,
    CC_A,
    CC_B,
    CC_C,
    CC_D,
    CC_E,
    CC_F,
    CC_G,
    CC_H,
    CC_I,
    CC_J,
    CC_K,
    CC_L,
    CC_M,
    CC_N,
    CC_O,
    CC_P,
    CC_Q,
    CC_R,
    CC_S,
    CC_T,
    CC_U,
    CC_V,
    CC_W,
    CC_X,
    CC_Y,
    CC_Z,
    CC_MIN,
    CC_PLUS,
    CC_0,
    CC_TAB,
    RGB_LAYERS
};

bool process_record_addedkeycodes(uint16_t keycode, keyrecord_t *record);
