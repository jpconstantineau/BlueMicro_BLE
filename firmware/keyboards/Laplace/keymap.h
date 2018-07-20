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
    A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, \
    B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11,      B13, \
    C1, C2, C3, C4, C5, C6, C7,     C9, C10, C11, C12, C13, \
    D1, D2, D3, D4, D5,     D7,         D10, D11, D12, D13 \
    ) { \
        {A1, A2, A3, A4, A5, A6, A7}, \
        {KC_NO, A13, A12, A11, A10, A9, A8}, \
        {B1, B2, B3, B4, B5, B6, B7}, \
        {KC_NO, B13, KC_NO, B11, B10, B9, B8}, \
        {C1, C2, C3, C4, C5, C6, C7}, \
        {KC_NO, C13, C12, C11, C10, C9, KC_NO}, \
        {D1, D2, D3, D4, D5, KC_NO, D7}, \
        {KC_NO, D13, D12, D11, D10, KC_NO, KC_NO} \
    }

//#define KEYMAP( \
//	 K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09 , K10 , K11, K12,  \
//	 K13,   K14,   K15,   K16,   K17,   K18,   K19,   K20,   K21,   K22 , K23 , K24, \
//	 K25,   K26,   K27,   K28,   K29,   K30,   K31,   K32,   K33,   K34 , K35 , K36,   \
//   K37,   K38,   K39,   K40,   K41,   K42,   K43,   K44,   K45,   K46 \
//) { \
//	{ K00,   K01,   K02,   K03,   K04,   K05,   K06 }, \
//  { KC_NO,   K08,   K09,   K10,   K11,   K12,   K13 }, \
//  { K14,   K15,   K16,   K17,   K18,   K19,   K20 }, \
//  { K21,   K22,   K23,   K24,   K25,   K26,   K27 }, \
//  { K28,   K29,   K30,   K31,   K32,   K33,   K34 }, \
//  { K35,   K36,   K37,   K38,   K39,   K40,   K41 }, \
//  { K42,   K43,   K44,   K45,   K46,   K47,   K48 }, \
//  { K49,   K50,   K51,   K,   K46,   K45,   K46 }, \
//}



#define _QWERTY 0
#define _L1  1
#define _L2  2


const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = KEYMAP(    
    KC_ESC,  KC_Q,       KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,      KC_U,       KC_I,    KC_O,       KC_P,     KC_NO, KC_BSPC,
    KC_TAB,  KC_A,       KC_S,    KC_D,    KC_F,    KC_G,    KC_H,      KC_J,       KC_K,    KC_L,   KC_QUOTE, KC_BSLASH,    
    KC_LSFT, KC_Z,       KC_X,    KC_C,    KC_V,    KC_B,    KC_N,      KC_M,    KC_COMM, KC_DOT, KC_SLASH,  KC_ENT,
    KC_LCTL,  KC_LALT,  KC_LGUI,  LAYER_1,      KC_SPC,   KC_SPC,   KC_RALT, KC_RCTL,      LAYER_2, KC_RCTL ),


[_L1]  = KEYMAP(
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,
    _______,    _______,  _______,  _______,  _______,  KC_LBRC,  KC_RBRC,  KC_4,     KC_5,     KC_6,     KC_SCLN,  _______,
    KC_LSFT, KC_Z,       KC_X,    KC_C,    KC_V,    KC_LBRACKET,    KC_RBRACKET,    KC_1,    KC_2, KC_3, KC_UP,  KC_ENT,
    KC_GRV , KC_LCTL, KC_LALT, _______, KC_BSPC,  KC_SPC, KC_RALT, KC_LEFT,      KC_DOWN, KC_RIGHT ),


[_L2] = KEYMAP(
    KC_ESC,  KC_F1,       KC_F2,    KC_F3,    KC_F4,    KC_T,    KC_Y,    KC_U,       KC_I,    KC_O,       KC_P,     KC_NO, KC_BSPC,
    KC_TAB,  KC_F5,       KC_F6,    KC_F7,    KC_F8,    KC_G,    KC_H,    KC_J,       KC_K,    KC_L,   KC_QUOTE, KC_BSLASH,    
    KC_LSFT, KC_F9,       KC_F10,    KC_F11,    KC_F12,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLASH,  KC_ENT,
    KC_GRV , KC_LCTL, KC_LALT, KC_LGUI, KC_BSPC,  KC_SPC, KC_RALT, KC_RCTL,  LAYER_2,   
    KC_DOWN ),
 
};

#endif
