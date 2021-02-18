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
         KC_VIRL,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
         KC_LGUI, KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,
         KC_TAB,     KC_A,    KC_O,    KC_E,    KC_U,    KC_I,
         KC_LCTL, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,
             KC_WINU,  KC_GRV,  KC_DEL, KC_BSPC,
        // left thumb
                              KC_LSFT, KC_LALT,
                                       KC_PGUP,
                     KC_LSFT, L_MEDIA, KC_PGDN,
        // right hand
         KC_F9, KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_CAPS,  KC_SPC,  KC_SPC, TG(L_GAME),
         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_VIRR,
         KC_F,    KC_G,    KC_C,    KC_R,    KC_L,  KC_EQL,
         KC_D,    KC_H,    KC_T,    KC_N,    KC_S, KC_SLSH,
         KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, KC_MINS,
             KC_ENT, KC_LBRC, KC_RBRC, KC_BSLS,
        // right thumb
        KC_NO, KC_NO,
        KC_END,
        KC_HOME,   L_NUM,  KC_SPC 
    )};

void setupKeymap() {
    uint32_t NUM[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, \
        _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, \
        _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, \
           _______, _______, _______, _______, \
        // left thumb
                           _______, _______, \
                                    _______, \
                  _______, _______, _______, \
        // right hand
        _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______,
           KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______, \
        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
           _______, _______, _______, _______, \
        // right thumb
        _______, _______, \
        _______, \
        _______, _______, _______      \
        );
    uint32_t MEDIA[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
            // left hand
       _______, _______, _______, _______, _______, _______, _______, _______, _______, \
       _______, KC_CAW1, KC_CAW2, KC_CAW3, KC_CAW4, KC_CAW5, \
       _______,  KC_CUT, KC_ALLL, KC_ALLD, KC_ALLU, KC_ALLR, \
       _______,  KC_PST, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, \
       _______, KC_COPY, KC_HOME, KC_PGDN, KC_PGUP, KC_END, \
             KC_PDFL, KC_PDFR, KC_WINL, KC_WINR, \
        // left thumb
                           _______, _______, \
                                    _______, \
                  _______, _______, _______, \
       // right hand
       _______, _______, _______, _______, _______, _______, _______, _______, _______, \
       _______, _______, _______, _______, _______, _______, \
       _______, _______, _______, _______, _______, _______, \
       _______, _______, _______, _______, _______, _______, \
       _______, _______, _______, _______, _______, _______, \
          _______, _______, _______, _______, \
       // right thumb
        _______, _______, \
        _______, \
        _______, _______, _______   \
        );
    uint32_t GAME[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
            // left hand
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8, \
        KC_EQL,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, \
          KC_T,  KC_TAB,    KC_Q,    KC_X,    KC_E,    KC_R, \
          KC_G, KC_LSFT,    KC_A,    KC_W,    KC_D,    KC_F, \
          KC_B, KC_LCTL,    KC_Z,    KC_S,    KC_C,    KC_V, \
             KC_LALT, KC_LGUI, KC_LEFT, KC_RGHT, \
        // left thumb
                              KC_7,    KC_8, \
                                       KC_9, \
                   KC_SPC,    KC_6,    KC_0, \
       // right hand
         KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_CAPS,  KC_SPC,  KC_SPC, TG(L_GAME), \
          KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS, \
          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS, \
          KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, \
          KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, \
            KC_UP, KC_DOWN, KC_LBRC, KC_RBRC, \
       // right thumb
          KC_NO,   KC_NO, \
        KC_PGUP, \
        KC_PGDN,  KC_ENT,  KC_SPC   \
        );
       /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_NUM, Method::PRESS, NUM[row][col]);
            matrix[row][col].addActivation(_MEDIA, Method::PRESS, MEDIA[row][col]);
            matrix[row][col].addActivation(_GAME, Method::PRESS, GAME[row][col]);
        }
    }  
    matrix[8][5].addActivation(_DVORAK, Method::MT_TAP, KC_VOLU); 
    matrix[9][6].addActivation(_DVORAK, Method::MT_TAP, KC_VOLD);
};
