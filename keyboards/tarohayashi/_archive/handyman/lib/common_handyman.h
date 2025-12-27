// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

// 保存される設定の定義
typedef union{
    uint32_t raw;
    struct{
        bool rgb_layers  :1; // RGBレイヤーON/OFF
    };
} hm_config_t;

// 外部参照用
extern hm_config_t hm_config;
