// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

// 定数
// CPI = 400 + spd * 200 / AMP = 4.0 + (double)spd * 3.0
#define SPD_DEFAULT 5
#define SPD_OPTION_MAX 15

// 角度 = angle * 6
#define ANGLE_DEFAULT_LEFT 16
#define ANGLE_DEFAULT_RIGHT 15
#define ANGLE_OPTION_MAX 59

#define CPI_SLOW 300 // スローモード時CPI
#define AMP_SLOW 4.0 // スローモード時AMP

// ジョイスティク用定数
#define NO_JOYSTICK_VAL 100         // JSの有無判定閾値
#define KEY_OFFSET 7                // キー入力閾値
#define TIMEOUT_KEY 80              // キー入力間隔
#define JOYSTICK_MOVE_OFFSET 100    // ジョイスティック移動閾値

#define SCROLL_DIVISOR 100.0        // スクロール用数値調整
#define JOYSTICK_DIVISOR 40.0       // ジョイスティック用調整用

// 一時的モード変更タップ判定ms
#define TERM_TEMP 100

// OLED切り替え時間
#define INTERRUPT_TIME 600

// 入力モード
enum pdmode{
    KEY_INPUT,
    CURSOR_MODE,
    SCROLL_MODE
};

// OLED
enum oledmode{
    SHOW_LAYER = 0,
    SHOW_STATS,
    TURN_OFF
};

// 保存される設定の定義
typedef union{
    uint32_t raw;
    struct{
        uint8_t spd     :4; // ポインター速度 最大値15
        uint8_t angle   :6; // ポインター角度 最大値59 
        uint8_t pd_mode :2; // カーソル移動/スクロールモード/キー入力モード
        bool inv        :1; // トラックボール / ジョイスティック左右反転ON/OFF
        bool inv_sc     :1; // スクロールの反転ON/OFF
        bool auto_mouse :1; // オートマウスON/OFF
        uint8_t oled_mode :2; // OLEDがレイヤー表示/スタッツ表示/オフ
        bool dpad_exclusion  :1; // 十字キー同時押し禁止ON/OFF
        bool rgb_layer  :1; // RGBレイヤーON/OFF
    };
} kw_config_t;

// 外部参照用
extern kw_config_t kw_config;

// インターフェース
bool get_joystick_attached(void);             // ジョイスティックの有無
void cycle_mode(void);                        // モード変更
void is_scroll_mode(bool is_force_scrolling); // 一時的モード変更
void is_cursor_mode(bool is_force_scrolling);
void is_key_mode(bool is_force_key_input);
void is_slow_mode(bool is_slow_mode);