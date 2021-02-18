/*
Copyright (C) 2020-2021 Jocelyn Turcotte <turcotte.j@gmail.com>

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
    {KEYMAP( \
         KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
         KC_EQL,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
         KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
         KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
         KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
              KC_GRV,  KC_INS,  KC_LEFT, KC_RGHT,
        // left thumb
                              KC_LCTL, KC_LALT,
                                       KC_HOME,
                     KC_BSPC,  KC_DEL,  KC_END,
        // right hand
         KC_F9, KC_F10,  KC_F11,  KC_F12, KC_PSCR, KC_SLCK, KC_PAUS, TG(L_NUM), KC_SPC,
         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
              KC_UP, KC_DOWN, KC_LBRC, KC_RBRC,
        // right thumb
        KC_LGUI, KC_RCTL,
        KC_PGUP,
        KC_PGDN,  KC_ENT,  KC_SPC 
    )};

void setupKeymap() {
    uint32_t NUM[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, \
        _______,  _______, _______, _______, _______, _______, \
           _______, _______, KC_LEFT, KC_RGHT, \
        // left thumb
                           _______, _______, \
                                    _______, \
                  _______, _______, _______, \
        // right hand
        _______, _______, _______, _______, _______, _______, _______, TG(L_NUM), _______, \
        _______, KC_NLCK,  KC_EQL, KC_SLSH, KC_ASTR, _______, \
        _______,    KC_7,    KC_8,    KC_9, KC_MINS, _______,
        _______,    KC_4,    KC_5,    KC_6, KC_PLUS, _______, \
        _______,    KC_1,    KC_2,    KC_3,  KC_ENT, _______, \
             KC_UP, KC_DOWN,  KC_DOT,  KC_ENT, \
        // right thumb
        _______, _______, \
        _______, \
        _______, _______,    KC_0      \
        );
       /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_NUM, Method::PRESS, NUM[row][col]);

        }
    }  
};
