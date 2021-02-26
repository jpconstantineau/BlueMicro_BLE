/*
Copyright 2021 <Pierre Constantineau>

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

// MACRO tests


std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {{
        {KC_NO,  KC_NO,  KC_NO ,  KC_NO},
        {KC_NO,  KC_NO , KC_NO,   KC_NO},
        {KC_NO,  KC_NO , KC_NO,   KC_NO},
        {KC_NO,  KC_NO , KC_NO,   KC_NO}
    }};

 
void setupKeymap() {

    uint32_t layer_base_press[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
           KC_NO,  KC_NO,  KC_NO,   KC_NO,
           KC_NO,  KC_NO,  KC_NO,   KC_NO,
           KC_A,   KC_R,   KC_T,    KC_S,  
           KC_E   ,KC_Y,   KC_I,    KC_O);

    uint32_t layer_base_hold[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
           KC_NO,  KC_NO,  KC_NO,   KC_NO,
           KC_NO,  KC_NO,  KC_NO,   KC_NO,
           LAYER_3,  KC_NO,  KC_NO,   LAYER_1,  
           LAYER_2,  KC_NO,  KC_NO,   LAYER_4);

    uint32_t layer_num[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
           KC_NO,   KC_NO,   KC_NO,   KC_NO,
           KC_NO,   KC_NO,   KC_NO,   KC_NO,
           KC_1,    KC_2,    KC_3,    KC_NO,  
           KC_4,    KC_5,    KC_6,    KC_NO);

    uint32_t layer_sym[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
           KC_NO,   KC_NO,    KC_NO,   KC_NO,
           KC_NO,   KC_NO,    KC_NO,   KC_NO,
           KC_NO,   KC_BSLS,  KC_SCOLON,   KC_GRAVE,  
           KC_NO,   KC_MINUS, KC_EQUAL,    KC_NO );

    uint32_t layer_brac[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
           KC_NO,   KC_NO,    KC_NO,   KC_NO,
           KC_NO,   KC_NO,    KC_NO,   KC_NO,
           KC_NO,   KC_LPRN,  KC_RPRN,   KC_LCBR,  
           KC_NO,   KC_LBRACKET, KC_RBRACKET,    KC_RCBR  );


    uint32_t layer_nav[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
           KC_NO,   KC_NO,    KC_NO,   KC_NO,
           KC_NO,   KC_NO,    KC_NO,   KC_NO,
           KC_HOME, KC_UP,    KC_END,   KC_NO ,  
           KC_LEFT, KC_DOWN,  KC_RIGHT,    KC_NO );

    uint32_t layer_mou[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
           KC_NO,   KC_NO,    KC_NO,   KC_NO,
           KC_NO,   KC_NO,    KC_NO,   KC_NO,
           KC_MS_BTN1, KC_MS_UP,    KC_MS_BTN2,   KC_PGUP  ,  
           KC_MS_LEFT, KC_MS_DOWN,  KC_MS_RIGHT,  KC_PGDN  );

    /*
     * add the other layers
     */
    // from https://www.artsey.io/_FILES/images/ARTSEY.jpg
    ADDLAYER(_ARTSEY_BASE,Method::PRESS, layer_base_press);
   // ADDLAYER(_ARTSEY_BASE,Method::MT_HOLD,layer_base_hold);
    ADDLAYER(_ARTSEY_NUM, Method::PRESS , layer_num);
    ADDLAYER(_ARTSEY_SYM, Method::PRESS , layer_sym);
    ADDLAYER(_ARTSEY_BRAC,Method::PRESS , layer_brac);
    ADDLAYER(_ARTSEY_NAV, Method::PRESS , layer_nav);
    ADDLAYER(_ARTSEY_MOU, Method::PRESS , layer_mou);

   /* COMB(chord_a,    KC_A,            KC_A);
    COMB(chord_r,    KC_R,            KC_R);
    COMB(chord_tt,   KC_T,            KC_T);
    COMB(chord_s,    KC_S,            KC_S);
    COMB(chord_e,    KC_E,            KC_E);
    COMB(chord_y,    KC_Y,            KC_Y);
    COMB(chord_i,    KC_I,            KC_I);
    COMB(chord_o,    KC_O,            KC_O);*/

    COMB(chord_b,    KC_B,            KC_E, KC_O);
    COMB(chord_c,    KC_C,            KC_E, KC_Y);
    COMB(chord_d,    KC_D,            KC_A, KC_R, KC_T);
    COMB(chord_f,    KC_F,            KC_A, KC_R);
    COMB(chord_g,    KC_G,            KC_R, KC_T);
    COMB(chord_h,    KC_H,            KC_E, KC_I);
    COMB(chord_j,    KC_J,            KC_T, KC_S);
    COMB(chord_k,    KC_K,            KC_Y, KC_O);
    COMB(chord_l,    KC_L,            KC_E, KC_Y, KC_I);
    COMB(chord_m,    KC_M,            KC_Y, KC_I, KC_O);
    COMB(chord_n,    KC_N,            KC_I, KC_O);
    COMB(chord_p,    KC_P,            KC_E, KC_I, KC_O);
    COMB(chord_q,    KC_Q,            KC_A, KC_T, KC_S);
    COMB(chord_u,    KC_U,            KC_Y, KC_I);
    COMB(chord_v,    KC_V,            KC_R, KC_S);
    COMB(chord_w,    KC_W,            KC_A, KC_S);
    COMB(chord_x,    KC_X,            KC_R, KC_T, KC_S);
    COMB(chord_z,    KC_Z,            KC_A, KC_R, KC_T, KC_S);
    COMB(chord_enter,KC_ENTER,        KC_A, KC_E);
    COMB(chord_quote,KC_QUOTE,        KC_A, KC_Y, KC_I);
    COMB(chord_dot,  KC_DOT,          KC_A, KC_Y);
    COMB(chord_comma,KC_COMMA,        KC_A, KC_I);
    COMB(chord_slash,KC_SLASH,        KC_A, KC_O);
    COMB(chord_bspac,KC_BSPACE,       KC_E, KC_R);
    COMB(chord_space,KC_SPACE,        KC_E, KC_Y, KC_I, KC_O);
    COMB(chord_esc,  KC_ESC,          KC_A, KC_R, KC_O);
    COMB(chord_tab,  KC_TAB,          KC_A, KC_R, KC_T, KC_O);
    COMB(chord_ctrl, KC_LCTRL,        KC_E, KC_S); // to do: oneshot
    COMB(chord_gui,  KC_LGUI,         KC_Y, KC_S); // to do: oneshot
    COMB(chord_alt,  KC_LALT,         KC_I, KC_S); // to do: oneshot
    COMB(chord_shift,KC_LSHIFT,       KC_E, KC_R, KC_T, KC_S); // to do: oneshot
    COMB(chord_caps, KC_LSHIFT,       KC_A, KC_Y, KC_I, KC_O); // to do: toggle

    COMB(chord_7,    KC_7,            KC_1, KC_2);
    COMB(chord_8,    KC_8,            KC_2, KC_3);
    COMB(chord_9,    KC_9,            KC_4, KC_5);
    COMB(chord_0,    KC_0,            KC_5, KC_6);

    COMB(chord_f7,   KC_F7,            KC_F1, KC_F2);
    COMB(chord_f8,   KC_F8,            KC_F2, KC_F3);
    COMB(chord_f9,   KC_F9,            KC_F4, KC_F5);
    COMB(chord_f0,   KC_F10,           KC_F5, KC_F6);

    COMB(chord_mslck,KC_0,            KC_A, KC_Y, KC_T); // to do macro to swich layer to mouse...
    COMB(chord_msulk,KC_0,            KC_MS_BTN1, KC_MS_BTN2, KC_MS_DOWN); // to do macro to swich layer to _ARTSEY_BASE...

}

void process_user_macros(uint32_t macroid)
{
 switch (macroid)
 {
     case MC(KC_A):
     addStringToQueue("Hello World!");
     break;
     case MC(KC_B):
     addStringToQueue("The quick brown fox jumps over the lazy dog!");
     break;
     case MC(KC_C):
     addStringToQueue("macro C works");
     break;
     case MC(KC_D):
     addStringToQueue("This is macro D");
     break;
 }
}

