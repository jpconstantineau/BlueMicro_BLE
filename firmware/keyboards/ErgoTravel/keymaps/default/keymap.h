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


#define _QWERTY 0
#define _L1  1
#define _L2  2
#define _L3  3

#if KEYBOARD_SIDE == LEFT

const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | L(3) | L(1) |    Space    | L(2) | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_LBRC,  \
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_A,   \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_SPC,  \
  KC_LCTL, KC_LGUI, KC_LALT, LAYER_3, LAYER_1, KC_SPC,_______ \
),

/* Layer 1
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |      |      |      |      |      |      |   _  |   +  |      |   \  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | L(3) | L(1) |    Space    | L(2) | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_L1] =  KEYMAP( \
  KC_GRAVE,KC_1,    KC_2,    KC_3,    KC_4,    KC_5,KC_MINUS,  \
  KC_TAB  ,_______,_______,_______,_______,_______,_______,   \
  KC_LSFT ,_______,_______,_______,_______,_______,  KC_SPC,  \
  KC_LCTL , KC_LGUI, KC_LALT, LAYER_3, LAYER_1, KC_SPC,_______ \
),

/* Layer 2
 * ,-----------------------------------------------------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   F7 |   F8 |   F9 |  F10 | Ins  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F11 |  F12 |      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | L(3) | L(1) |    Space    | L(2) | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_L2] = KEYMAP( \
  KC_GRAVE,KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,KC_MINUS,  \
  KC_TAB  ,KC_F11,KC_F12,_______,_______,_______,_______,   \
  KC_LSFT ,_______,_______,_______,_______,_______,  KC_SPC,  \
  KC_LCTL , KC_LGUI, KC_LALT, LAYER_3, LAYER_1, KC_SPC,_______ \
),

/* Layer 3
 * ,-----------------------------------------------------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   F7 |   F8 |   F9 |  F10 | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F11 |  F12 |      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | L(3) | L(1) |    Space    | L(2) | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_L3] = KEYMAP( \
  KC_GRAVE,KC_1,    KC_2,    KC_3,    KC_4,    KC_5,KC_MINUS,  \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_A,   \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_SPC,  \
  KC_LCTL , KC_LGUI, KC_LALT, LAYER_3, LAYER_1, KC_SPC,_______ \
)
};
#endif
#if KEYBOARD_SIDE == RIGHT
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | L(3) | L(1) |    Space    | L(2) | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
KC_RBRC,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_BSPACE,  \
  KC_B,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCOLON, KC_QUOTE,   \
  KC_C,   KC_N,    KC_M,    KC_COMMA,KC_DOT,  KC_SLSH,   KC_ENT,  \
  KC_SPC, LAYER_2, LAYER_2, KC_LEFT, KC_UP,   KC_DOWN,   KC_RIGHT \
),

/* Layer 1
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |      |      |      |      |      |      |   _  |   +  |      |   \  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | L(3) | L(1) |    Space    | L(2) | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_L1] =  KEYMAP( \
  KC_A,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_DEL,  \
  KC_B,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10, KC_QUOTE,   \
  KC_C,   KC_N,    KC_M,    KC_COMMA,KC_DOT,  KC_SLSH,   KC_ENT,  \
  KC_NO, LAYER_1,   LAYER_1, KC_LEFT, KC_UP,   KC_DOWN,   KC_RIGHT \
),

/* Layer 2
 * ,-----------------------------------------------------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   F7 |   F8 |   F9 |  F10 | Ins  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F11 |  F12 |      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | L(3) | L(1) |    Space    | L(2) | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_L2] = KEYMAP( \
  KC_A,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_0,      KC_INS,  \
  KC_B,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10, KC_QUOTE,   \
  KC_C,   KC_N,    KC_M,    KC_COMMA,KC_DOT,  KC_SLSH,   KC_ENT,  \
  KC_NO, LAYER_1,   LAYER_1, KC_LEFT, KC_UP,   KC_DOWN,   KC_RIGHT \
),

/* Layer 3
 * ,-----------------------------------------------------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   F7 |   F8 |   F9 |  F10 | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F11 |  F12 |      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | L(3) | L(1) |    Space    | L(2) | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_L3] = KEYMAP( \
  KC_A,   KC_6,    KC_7,    KC_8,    KC_9,    KC_9,      KC_DEL,  \
  KC_B,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10, KC_QUOTE,   \
  KC_C,   KC_N,    KC_M,    KC_COMMA,KC_DOT,  KC_SLSH,   KC_ENT,  \
  KC_NO, LAYER_1,   LAYER_1, KC_LEFT, KC_UP,   KC_DOWN,   KC_RIGHT \
)
};

#endif
#endif

