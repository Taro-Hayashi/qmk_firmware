// Copyright 2025 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "lib/common_handyman_v2.h"

// レイヤーごとの発光場所、発光色の設定
const rgblight_segment_t PROGMEM base_layer[] = RGBLIGHT_LAYER_SEGMENTS( { 0, 0, HSV_YELLOW} );
const rgblight_segment_t PROGMEM layer1[] = RGBLIGHT_LAYER_SEGMENTS( { 0, 22, HSV_CYAN} );
const rgblight_segment_t PROGMEM layer2[] = RGBLIGHT_LAYER_SEGMENTS( { 0, 22, HSV_MAGENTA} );
const rgblight_segment_t PROGMEM layer3[] = RGBLIGHT_LAYER_SEGMENTS( { 0, 22, HSV_WHITE} );
const rgblight_segment_t PROGMEM layer4[] = RGBLIGHT_LAYER_SEGMENTS( { 0, 22, HSV_BLUE} );
const rgblight_segment_t PROGMEM layer5[] = RGBLIGHT_LAYER_SEGMENTS( { 0, 22, HSV_GREEN} );

// レイヤーごとの発光方法の指定
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    base_layer,
    layer1,
    layer2,
    layer3,
    layer4,
    layer5
);

void keyboard_post_init_kb(void) {
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, h2_config.rgb_layers && layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, h2_config.rgb_layers && layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, h2_config.rgb_layers && layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, h2_config.rgb_layers && layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, h2_config.rgb_layers && layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, h2_config.rgb_layers && layer_state_cmp(state, 5));
    return state;
}
