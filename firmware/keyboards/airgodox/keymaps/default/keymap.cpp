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

#if KEYBOARD_SIDE == LEFT

/*
 * initiialize the default layer (QWERTY/PRESS) with the following
 * keymap
 */
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {{
        {KC_ESC,    KC_Q,    KC_W,    KC_E,     KC_R,     KC_T},
        {KC_TAB,      KC_NO,    KC_S,    KC_CAP_D, KC_F,     KC_G},
        {KC_LSHIFT, TG(KC_LSHIFT),    KC_X,    KC_C,     KC_V,     KC_B},
        {KC_NO,     KC_NO,   KC_NO,   LAYER_1,  KC_LCTRL, KC_LGUI}
    }};

/*
 * add extra layers or single keys to this function 
 */
void setupKeymap() 
{
    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            KC_GRV,    KC_1,    KC_2,     KC_3,    KC_4,     KC_5,
            KC_CAPS,   KC_F1,   KC_F2,    KC_F3,   KC_F4,    KC_F5,
            KC_LSHIFT, KC_F6,   KC_F7,    KC_F8,   KC_F9,    KC_F10,
            KC_NO,     KC_NO,   KC_NO,    LAYER_1, KC_LCTRL, KC_LGUI);

    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_L1, Method::PRESS, layer1[row][col]);
        }
    }

    /* 
     * add special, single activations with the 
     * layer, activation method and activation
     */
    matrix[2][3].addActivation(_QWERTY, Method::MT_TAP, KC_Y);
    matrix[1][1].addActivation(_QWERTY, Method::MT_TAP, TG(KC_LSHIFT));
}

#else

/*
 * TODO: configure right side
 */

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {{
        {KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_BSPC,},
        {KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,KC_ENTER,},
        {KC_N,    KC_M,    KC_COMMA,KC_DOT,  KC_SLSH,KC_RALT,},
        {KC_RSFT, KC_SPC,  LAYER_1, KC_NO,   KC_NO,   KC_NO}
    }};

void setupKeymap() 
{
    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
           KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS,
            KC_LBRC, KC_RBRC, KC_BSLS, KC_UP,  KC_QUOT, KC_EQL,
             KC_F11,  KC_F12,  KC_LEFT, KC_DOWN,KC_RGHT, _______,
            KC_RSFT, KC_APP,  LAYER_0, KC_NO,  KC_NO,   KC_NO );

    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_L1, Method::PRESS, layer1[row][col]);
        }
    }

    /* 
     * add special, single activations with the 
     * layer, activation method and activation
     */
    matrix[2][3].addActivation(_QWERTY, Method::MT_TAP, KC_Y);
    matrix[1][1].addActivation(_QWERTY, Method::MT_TAP, TG(KC_LSHIFT));
}


#endif /* KEYBOARD_SIDE */

