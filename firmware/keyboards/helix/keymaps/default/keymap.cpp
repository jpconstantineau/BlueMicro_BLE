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



#if KEYBOARD_SIDE == SINGLE
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
        KC_1,  KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
        KC_1,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_2,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_3,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_SPC,
        KC_4,  KC_5,    KC_6,    KC_7,    KC_SPC,  KC_SPC, KC_SPC
    )};

void setupKeymap() {

   // no layers for master keymap
   // this is a keymap that's used for testing that each key is responding properly to key presses
   // flash this keymap to both left and right to test whether each half works properly.
   // once tested, you can flash the left and right to their respective halves.

}
#endif


#if KEYBOARD_SIDE == LEFT

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
        KC_GRAVE, KC_1,   KC_2,    KC_3,    KC_4, KC_5,
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R, KC_T,
        KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F, KC_G,
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V, KC_B,    KC_LBRC,
        LAYER_3,  KC_ESC, KC_LALT, KC_LCMD, EISU, LAYER_1, KC_SPC
    )};

 
void setupKeymap() {


    uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,  KC_PERC,         
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,  KC_PERC,         
        _______, KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,           
        _______, KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_LPRN,
        _______, _______, _______, _______,  _______, LAYER_1, KC_SPC
);

    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            
        KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           
        _______,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______,
        _______,  _______, _______, _______, _______, LAYER_3, _______ 
);


    uint32_t adjust[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,           
        _______, _______, _______, _______, _______, _______,         
        _______, _______, _______, _______, _______, _______,         
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______ 
);

    /*
     * add the other layers on the regular presses.
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_L1, Method::PRESS, lower[row][col]);
            matrix[row][col].addActivation(_L2, Method::PRESS, raise[row][col]);
            matrix[row][col].addActivation(_L3, Method::PRESS, adjust[row][col]);
        }
    }

    // if you want to add Tap/Hold or Tap/Doubletap activations, then you add them below.

}

#endif  // left



#if KEYBOARD_SIDE == RIGHT

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
                 KC_6,    KC_7, KC_8,     KC_9,    KC_0,      KC_DEL,
                 KC_Y,    KC_U, KC_I,     KC_O,    KC_P,      KC_BSPACE,
                 KC_H,    KC_J, KC_K,     KC_L,    KC_SCOLON, KC_QUOTE,
        KC_RBRC, KC_N,    KC_M, KC_COMMA, KC_DOT,  KC_SLSH,   KC_ENT,
        KC_SPC,  LAYER_2, EISU, KC_LEFT,  KC_DOWN, KC_UP,     KC_RGHT
    )};


void setupKeymap() {


    uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
                 KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
                 KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
                 KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        KC_RBRC, KC_F12,  _______, _______, KC_HOME, KC_END,  _______,
        _______, LAYER_3, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY 
);


    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
                 KC_6,    KC_7,     KC_8,     KC_9,    KC_0,    KC_BSPACE,
                 KC_6,    KC_7,     KC_8,     KC_9,    KC_0,    KC_DEL,
                 KC_F6,   KC_MINUS, KC_EQUAL, KC_LBRC, KC_RBRC, KC_BSLS,
        _______, KC_F12,  _______,  _______,  KC_PGDN, KC_PGUP, _______,
        _______, LAYER_2, _______,  KC_MNXT,  KC_VOLD, KC_VOLU, KC_MPLY
);


    uint32_t adjust[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
                 KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
                 _______, _______, _______, _______, _______, KC_DEL,
                 _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______
);

    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_L1, Method::PRESS, lower[row][col]);
            matrix[row][col].addActivation(_L2, Method::PRESS, raise[row][col]);
            matrix[row][col].addActivation(_L3, Method::PRESS, adjust[row][col]);
        }
    }

}


#endif




