/*
Copyright 2018 <Pierre Constantineau>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include <stdint.h>
#include "hid_keycodes.h"
#include "keyboard_config.h"
#ifndef KEYMAP_H
#define KEYMAP_H

#define KEYMAP( \
    A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, \
    B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, \
    C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, \
    D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12 \
    ) { \
        {A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12}, \
        {B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12}, \
        {C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12}, \
        {D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12} \
    }





#define _QWERTY 0
#define _L1  1
#define _L2  2

const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = KEYMAP(    
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,      KC_T,     KC_Y,    KC_U,       KC_I,   KC_O,       KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,      KC_G,     KC_H,    KC_J,       KC_K,   KC_L,    KC_SCLN,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,      KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,    KC_SLSH,    KC_ENT ,
    KC_LCTL, KC_LALT, KC_LGUI, KC_PGDN, LAYER_1, KC_SPC,   KC_SPC, LAYER_2,    KC_LEFT, KC_DOWN,     KC_UP,    KC_RGHT ),


[_L1]  = KEYMAP(
    KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,      KC_5,     KC_6,    KC_7,       KC_8,   KC_9,       KC_0,    KC_DEL,
    KC_GRV,  KC_A,    KC_S,    KC_D,    KC_F,      KC_G,     KC_H, KC_MINS,    KC_PPLS, KC_LBRC,  KC_RBRC,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,      KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,    KC_SLSH,    KC_ENT ,
    KC_LCTL, KC_LALT, KC_LGUI, KC_PGDN, KC_LSFT, KC_SPC,   KC_SPC, LAYER_2,    KC_LEFT, KC_DOWN,     KC_UP,    KC_RGHT ),


[_L2] = KEYMAP(
   KC_TAB,   KC_1,     KC_2,     KC_3,     KC_4,       KC_5,      KC_6,    KC_7,       KC_8,   KC_9,       KC_0,     KC_DEL,
   KC_GRV,  KC_F1,    KC_F2,    KC_F3,    KC_F4,      KC_F5,     KC_F6,    KC_MINS, KC_PPLS,KC_LBRC,    KC_RBRC,    KC_QUOT,
   KC_LSFT, KC_F7,    KC_F8,    KC_F9,   KC_F10,     KC_F11,    KC_F12,    KC_M,    KC_COMM, KC_DOT,    KC_SLSH,    KC_ENT ,
   KC_LCTL, KC_LALT, KC_LGUI, KC_PGDN, LAYER_1, KC_SPC,   KC_SPC, LAYER_2,    KC_LEFT, KC_DOWN,     KC_UP,    KC_RGHT ),
 
};

#endif
