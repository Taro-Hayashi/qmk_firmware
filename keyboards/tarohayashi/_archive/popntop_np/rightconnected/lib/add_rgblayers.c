// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "lib/common_popntop_np.h"

// レイヤーごとの発光場所、発光色の設定
const rgblight_segment_t PROGMEM base_layer[] = RGBLIGHT_LAYER_SEGMENTS( { 0, 0, HSV_YELLOW} );
const rgblight_segment_t PROGMEM onoff_layer[] = RGBLIGHT_LAYER_SEGMENTS( {27, 5, HSV_YELLOW}, {55, 4, HSV_YELLOW} );
const rgblight_segment_t PROGMEM offon_layer[] = RGBLIGHT_LAYER_SEGMENTS( {27, 5, HSV_MAGENTA}, {55, 4, HSV_MAGENTA} );
const rgblight_segment_t PROGMEM onon_layer[] = RGBLIGHT_LAYER_SEGMENTS( {27, 5, HSV_WHITE},  {55, 4, HSV_WHITE} );
const rgblight_segment_t PROGMEM lower_layer[] = RGBLIGHT_LAYER_SEGMENTS( {27, 5, HSV_BLUE}, {55, 4, HSV_BLUE} );
const rgblight_segment_t PROGMEM upper_layer[] = RGBLIGHT_LAYER_SEGMENTS( {27, 5, HSV_GREEN},{55, 4, HSV_GREEN} );

// レイヤーごとの発光方法の指定
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    base_layer,
    onoff_layer,
    offon_layer,
    onon_layer,
    lower_layer,
    upper_layer
);

void keyboard_post_init_kb(void) {
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, ptnp_config.rgb_layers && layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, ptnp_config.rgb_layers && layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, ptnp_config.rgb_layers && layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, ptnp_config.rgb_layers && layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, ptnp_config.rgb_layers && layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, ptnp_config.rgb_layers && layer_state_cmp(state, 5));
    return state;
}
