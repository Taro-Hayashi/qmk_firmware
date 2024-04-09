// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

// 定数
// CPI = 1000 + spd * 250 / AMP = 16.0 + (double)spd * 3.0
#define SPD_DEFAULT 3
#define SPD_OPTION_MAX 7

// 角度 = angle * 12
#define ANGLE_DEFAULT_LEFT 8
#define ANGLE_DEFAULT_RIGHT 7
#define ANGLE_OPTION_MAX 29

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
    KEY_INPUT = 0,
    CURSOR_MODE,
    SCROLL_MODE
};

// ジョイスティックの状態ydfqsdfqwe4
enum jsmode{
    NO_JOYSTICK = 0,
    JOYSTICK_LEFT,
    JOYSTICK_RIGHT
};

// OLED
enum oledmode{
    SHOW_STATS = 0,
    SHOW_LAYER,
    TURN_OFF
};


// 保存される設定の定義
typedef union{
    uint32_t raw;
    struct{
        uint8_t spd_l     :3; // ポインター速度 最大値7
        uint8_t angle_l   :5; // ポインター角度 最大値59 
        uint8_t pd_mode_l :2; // カーソル移動/スクロールモード/キー入力モード
        bool inv_l        :1; // トラックボール / ジョイスティック左右反転ON/OFF
        
        uint8_t spd_r     :3; // ポインター速度 最大値7
        uint8_t angle_r   :5; // ポインター角度 最大値59 
        uint8_t pd_mode_r :2; // カーソル移動/スクロールモード/キー入力モード
        bool inv_r        :1; // トラックボール / ジョイスティック左右反転
        
        bool inv_sc     :1; // スクロールの反転ON/OFF
        bool auto_mouse :1; // オートマウスON/OFF
        bool rgb_layer  :1; // RGBレイヤーON/OFF
        bool oled_mode  :1; // oled表示
    };
} kw_config_t;

// 外部参照用
extern kw_config_t kw_config;

// インターフェース
uint8_t get_joystick_attached(void);             // ジョイスティックの有無
void cycle_mode_l(void);                        // モード変更
void cycle_mode_r(void);
void is_scroll_mode(bool is_force_scrolling); // 一時的モード変更
void is_cursor_mode(bool is_force_scrolling);
void is_key_mode(bool is_force_key_input);
void is_slow_mode(bool is_slow_mode);

bool get_dpad_exclusion(void);
void toggle_dpad_exclusion(void);