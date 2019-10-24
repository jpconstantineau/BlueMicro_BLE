/*
Copyright 2018 <Pierre Constantineau>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "keymap.h"
 std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {{
        {KC_TAB,    KC_Q,    KC_W,    KC_F,   KC_P,    KC_B,    KC_J,    KC_L,   KC_U,    KC_Y,    KC_SCLN,  KC_BSPACE,},
        {KC_BSPACE, KC_A,    KC_R,    KC_S,   KC_T,    KC_G,    KC_M,    KC_N,   KC_E,    KC_I,    KC_O,     KC_QUOT,},
        {KC_ESC,    KC_Z,    KC_X,    KC_C,   KC_D,    KC_V,    KC_K,    KC_H,   KC_COMMA,KC_DOT,  KC_SLASH, KC_ENTER,},
        {KC_LCTL,   KC_LALT, KC_LGUI, KC_LCTL,LAYER_1, KC_SPC,  KC_LSFT, LAYER_2,KC_LEFT, KC_UP,   KC_DOWN,  KC_RIGHT}
    }};

 
void setupKeymap() {

    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        KC_TAB,    _______, _______, _______,KC_CAPS, _______, KC_PGUP, KC_HOME,KC_UP,   KC_END,  KC_DEL,   KC_BSPACE,  
        KC_BSPC,   KC_LGUI, KC_LALT, KC_LSFT,KC_LCTL, KC_SVE,  KC_PGDN, KC_LEFT,KC_DOWN, KC_RGHT, KC_BSPC,  KC_QUOTE,
        KC_ESC,    KC_UND,  KC_CUT,  KC_CPY, KC_PST,  _______, KC_INS , _______,KC_COMMA,KC_DOT,  KC_SLSH,  KC_ENT, 
        _______,   _______, _______, LAYER_3,LAYER_1, KC_SPC,  KC_SPC,  LAYER_2,_______, _______, _______,  _______);

    uint32_t layer2[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        KC_TAB,    KC_AMPR, KC_PERC, KC_HASH,KC_LPRN, KC_EXLM, KC_ASTR, KC_RPRN, KC_AT,   KC_DLR, KC_CIRC,KC_BSPACE,  
        KC_BSPC,   KC_7,    KC_5,    KC_3,   KC_1,    KC_9,    KC_8,    KC_0,    KC_2,    KC_4,   KC_6,   KC_BSLS,
        KC_LSFT,   KC_GRAVE,KC_LBRC, KC_RBRC,KC_UNDS, KC_EQL,  KC_PLUS, KC_MINUS,KC_COMMA,KC_DOT, KC_SLSH,KC_ENT, 
        _______,   _______, _______, _______,LAYER_1, KC_SPC,  KC_LSFT, LAYER_2, _______, _______,_______,_______);

    uint32_t layer3[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        KC_GRAVE,KC_F1,  KC_F2,  KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,  _______,  
        _______, _______,_______,_______, _______, _______, _______,  _______,  _______,  KC_F11,   KC_F12,  _______,
        _______, _______,_______,_______, _______, _______, _______,  _______,  _______,  _______,  _______, _______, 
        _______, _______,_______,_______, _______, _______, _______,  _______,  _______,  _______,  _______, _______);
	
    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_L1, _PRESS, layer1[row][col]);
            matrix[row][col].addActivation(_L2, _PRESS, layer2[row][col]);
            matrix[row][col].addActivation(_L3, _PRESS, layer3[row][col]);
        }
    }

}

