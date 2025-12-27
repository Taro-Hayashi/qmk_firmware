// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"
#include "config.h"

// 保存される設定の定義
typedef union{
    uint32_t raw;
    struct{
        uint8_t spd             :4; // ポインター速度 最大値15
        uint8_t angle           :6; // ポインター角度 最大値59
        uint8_t pd_mode         :2; // カーソル移動/スクロールモード/キー入力モード
        bool inv                :1; // トラックボール / ジョイスティック左右反転ON/OFF
        bool inv_sc             :1; // スクロールの反転ON/OFF
        bool auto_mouse         :1; // オートマウスON/OFF
        bool rgb_layers         :1; // RGBレイヤーON/OFF
    };
} ot17_config_t;

// 外部参照用
extern ot17_config_t ot17_config;

// インターフェース
void cycle_mode(void);                        // モード変更
void is_scroll_mode(bool is_force_scrolling); // 一時的モード変更
void is_cursor_mode(bool is_force_scrolling);
void is_key_mode(bool is_force_key_input);
void is_slow_mode(bool is_slow_mode);
