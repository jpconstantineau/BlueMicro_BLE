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
    {KEYMAP(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ESC,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO )};

 
void setupKeymap() {

    uint32_t qwerty_tap[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_Z,     KC_X,     KC_C,     KC_V,     KC_SPC,    KC_BSPC,  KC_B,     KC_N,     KC_M,     KC_ENT );


    uint32_t qwerty_hold[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    OS(KC_LCTL),OS(KC_LSFT),OS(KC_LALT),    TG(LAYER_3),    TG(LAYER_1),   TG(LAYER_2),    TG(LAYER_4),    KC_LGUI,    KC_NO,    OS(KC_RSFT) );

   uint32_t qwerty_stap[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO );

    uint32_t qwerty_dtap[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO );

    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    KC_1,       KC_2,       KC_3,        KC_4,     KC_5,        KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
    KC_F1,      KC_F2,      KC_F3,       KC_F4,    KC_F5,       KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,
    OS(KC_LCTL),OS(KC_LSFT),OS(KC_LALT), KC_NO,    TG(LAYER_1), KC_DEL,   KC_INS,   KC_NO,    KC_NO,    OS(KC_RSFT) );

    uint32_t layer2[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    KC_EXLM,    KC_AT,      KC_HASH,     KC_DLR,   KC_PERC,     KC_CIRC,     KC_AMPR,  KC_ASTR,     KC_LPRN,     KC_RPRN,
    KC_F11,     KC_F12,     KC_NO,       KC_NO,    KC_NO,       KC_NO,       KC_NO,    KC_NO,       KC_TILD,     KC_GRV,
    OS(KC_LCTL),OS(KC_LSFT),OS(KC_LALT), KC_NO,    TG(LAYER_2), TG(LAYER_2), KC_NO,    KC_NO,       KC_NO,       OS(KC_RSFT) );


    uint32_t layer3[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    KC_NO,      KC_NO,      KC_NO,       KC_NO,      KC_NO,       KC_MINUS,    KC_EQUAL,    KC_LBRC,     KC_RBRC,    KC_BSLS,
    KC_TAB,     KC_NO,      KC_NO,       KC_NO,      KC_NO,       KC_COMMA,    KC_DOT,      KC_SLASH,    KC_SCLN,    KC_QUOTE,
    OS(KC_LCTL),OS(KC_LSFT),OS(KC_LALT), TG(LAYER_3),TG(LAYER_3), KC_NO,       KC_LEFT,     KC_UP,       KC_DOWN,    KC_RIGHT );


    uint32_t layer4[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    KC_NO,      KC_NO,      KC_NO,       KC_NO,      KC_NO,       KC_UNDS,     KC_PLUS,     KC_LCBR,     KC_RCBR,    KC_PIPE,
    KC_TAB,     KC_NO,      KC_NO,       KC_NO,      KC_NO,       KC_LT,       KC_GT,       KC_QUES,     KC_COLN,    KC_DQUO,
    OS(KC_LCTL),OS(KC_LSFT),OS(KC_LALT), KC_NO,      TG(LAYER_4), KC_NO,       KC_HOME,     KC_PGUP,     KC_PGDOWN,  KC_END );
    
    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            ADDLAYER(_QWERTY, Method::MT_TAP , qwerty_tap[row][col]);
            ADDLAYER(_QWERTY, Method::MT_HOLD, qwerty_hold[row][col]);

            ADDLAYER(_QWERTY, Method::DT_TAP, qwerty_stap[row][col]);
            ADDLAYER(_QWERTY, Method::DT_DOUBLETAP, qwerty_dtap[row][col]);
      
            ADDLAYER(_L1, Method::PRESS, layer1[row][col]);
            ADDLAYER(_L2, Method::PRESS, layer2[row][col]);
            ADDLAYER(_L3, Method::PRESS, layer3[row][col]);
            ADDLAYER(_L4, Method::PRESS, layer4[row][col]);
            
        }
    }

}
