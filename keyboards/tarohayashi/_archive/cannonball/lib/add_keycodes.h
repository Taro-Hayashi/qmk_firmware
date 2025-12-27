// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

enum TH_keycodes{
    CMD_CTL = QK_KB_0,
    UNDO,
    REDO,
    COPY,
    CUT,
    PASTE,
    SC_UP,
    SC_DOWN,
    SC_RESET,
    CAPTCHA,
    SAVE,
    SAVEAS,
    NEXTTAB,
    PREVTAB,
    CLOSETAB,
    RSTRTAB,
    NEXTAPP,
    PREVAPP,
    SEARCH,
    IPADHOME,
    IPADDOCK,
    RGB_LAYERS,
};

bool process_record_addedkeycodes(uint16_t keycode, keyrecord_t *record);
