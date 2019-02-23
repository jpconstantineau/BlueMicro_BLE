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

/* Colemak
  * .-----------------------------------------.    .-----------------------------------------.
  * | Esc  |   Q  |   W  |   F  |   P  |   G  |    |   J  |   L  |   U  |   Y  |   ;  |   \  |
  * |------+------+------+------+------+------|    |------+------+------+------+------+------|
  * | TAB  |   A  |   R  |   S  |   T  |   D  |    |   H  |   N  |   E  |   I  |   O  |   '  |
  * |------+------+------+------+------+------|    |------+------+------+------+------+------|
  * | Shift|   Z  |   X  |   C  |   V  |   B  |    |   K  |   M  |   ,  |   .  |   /  |Shift |
  * |------+------+------+------+------+------|    |------+------+------+------+------+------|
  * | Ctrl |  GUI | Alt  | Ent  |Lower | Bksp |    | Space| Raise| Left |  Up  | Down | Right|
  * `-----------------------------------------'    `-----------------------------------------'
  */
 
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
     KC_ESC,      KC_Q,     KC_W,    KC_F,    KC_P,     KC_G,
     KC_TAB,      KC_A,     KC_R,    KC_S,    KC_T,     KC_D,
     OS(KC_LSFT), KC_Z,     KC_X,    KC_C,    KC_V,     KC_B,
     KC_LCTL,     KC_LGUI,  KC_LALT, KC_ENT,  LOWER,    KC_BSPC
  ) };

 
void setupKeymap() {

    /* Lower
     * .-----------------------------------------.    .-----------------------------------------.
     * | Esc  |   !  |   @  |   #  |   $  |   %  |    |   ^  |   &  |   *  |   (  |   )  | Del  |
     * |------+------+------+------+------+------|    |------+------+------+------+------+------|
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |    | F6   |   _  |   +  |   {  |   }  |Enter |
     * |------+------+------+------+------+------|    |------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |    | F12  |  `   |   ~  |      |Ctrl+\|  |   |
     * |------+------+------+------+------+------|    |------+------+------+------+------+------|
     * |      |      |      |      | Base | Bksp |    | Spc  |Raise |      | Vol+ | Vol- | Mute |
     * `-----------------------------------------'    `-----------------------------------------'
     */

    uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            KC_ESC,  KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,   KC_PERC,
            _______, KC_F1,    KC_F2,   KC_F3,   KC_F4,    KC_F5,
            _______, KC_F7,    KC_F8,   KC_F9,   KC_F10,   KC_F11,
            _______, _______,  _______, _______, _______,  KC_BSPC

       );

    /* Raise
     * .-----------------------------------------.    .-----------------------------------------.
     * | Esc  |   1  |   2  |   3  |   4  |   5  |    |   6  |   7  |   8  |   9  |   0  | Del  |
     * |------+------+------+------+------+------|    |------+------+------+------+------+------|
     * | CAPS |   4  |   5  |   6  |   +  |  F5  |    |  F6  |   -  |   =  |   [  |   ]  |Enter |
     * |------+------+------+------+------+------|    |------+------+------+------+------+------|
     * |Enter |   7  |   8  |   9  |   -  |  F11 |    |  F12 |      |      |      |Ctrl+\|   \  |
     * |------+------+------+------+------+------|    |------+------+------+------+------+------|
     * |      |   ,  |   0  |  .   |Lower | Bksp |    | Spc  | Base | Next | Vol+ | Vol- | Mute |
     * `-----------------------------------------'    `-----------------------------------------'
     */

    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            KC_ESC,  KC_1,    KC_2,  KC_3,   KC_4,    KC_5,
            KC_CAPS, KC_4,    KC_5,  KC_6,   KC_PLUS, KC_F5,
            KC_ENT,  KC_7,    KC_8,  KC_9,   KC_MINS, KC_F11,
            _______, KC_COMM, KC_0,  KC_DOT, LOWER,   KC_BSPC
        );


    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_LOWER, _PRESS, lower[row][col]);
            matrix[row][col].addActivation(_RAISE, _PRESS, raise[row][col]);
        }
    }

}


 #else
 

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {
        KEYMAP(
            KC_J,   KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
            KC_H,   KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
            KC_K,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OS(KC_RSFT),
            KC_SPC, RAISE,  KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
        )
    };

 
void setupKeymap() {


    uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            KC_CIRC, KC_AMPR, KC_ASTR,  KC_LPRN,  KC_RPRN,                  KC_DEL,
            KC_F6,   KC_UNDS, KC_PLUS,  KC_LCBR,  KC_RCBR,                  _______,
            KC_F12,  KC_GRV,  KC_TILD,  KC_MUTE,  MOD(MOD_LCTRL, KC_BSLS),  KC_PIPE,
            KC_SPC,  RAISE,   _______,  KC_VOLUP, KC_VOLDOWN,               KC_MUTE
    );


    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            KC_6,    KC_7,     KC_8,    KC_9,     KC_0,                   KC_DEL,
            KC_F6,   KC_MINS,  KC_EQL,  KC_LBRC,  KC_RBRC,                _______,
            KC_F12,  _______,  _______, _______,  MOD(MOD_LCTRL, KC_BSLS), KC_BSLS,
            KC_SPC,  _______,  _______, KC_VOLUP, KC_VOLDOWN,             KC_MUTE
    );

    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_LOWER, _PRESS, lower[row][col]);
            matrix[row][col].addActivation(_RAISE, _PRESS, raise[row][col]);
        }
    }

}


#endif