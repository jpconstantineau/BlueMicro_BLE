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
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,    KC_F,  
        KC_G,  KC_H,    KC_I,    KC_J,    KC_K,    KC_L,  
        KC_M,  KC_N,    KC_O,    KC_P,    KC_Q,    KC_R,  
        KC_S,  KC_T,    KC_U,    KC_V,    KC_W,    KC_X 
    )};

void setupKeymap() {

   // no layers for master keymap
   // this is a keymap that's used for testing that each key is responding properly to key presses
   // flash this keymap to both left and right to test whether each half works properly.
   // once tested, you can flash the left and right to their respective halves.

}
#endif

#if KEYBOARD_SIDE == LEFT

/* QWERTY
  * .-----------------------------------------.    .-----------------------------------------.
  * | Esc  |   1  |   2  |   3  |   4  |   5  |    |   6  |   7  |   8  |   9  |   0  | BSPC |
  * |------+------+------+------+------+------|    |------+------+------+------+------+------|
  * | TAB  |   Q  |   W  |   E  |   R  |   T  |    |   Y  |   U  |   I  |   O  |   P  |   \  |
  * |------+------+------+------+------+------|    |------+------+------+------+------+------|
  * | CAPS |   A  |   S  |   D  |   F  |   G  |    |   H  |   J  |   K  |   L  |   ;  |   "  |
  * |------+------+------+------+------+------|    |------+------+------+------+------+------|
  * | Shift|  Z   |   X  |   C  |   V  |   B  |    |   N  |   M  |   ,  |   .  |   /  |  Ent |
  * |-----------------------------------------|    |-----------------------------------------|
  * | Ctrl |  Alt | LGui |  DEL | Lower| Space|    | Space| Raise| Left | Down |  Up  | Right|
  * `-----------------------------------------'    `-----------------------------------------'
  */
 
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
     KC_ESC,      KC_1,     KC_2,    KC_3,    KC_4,     KC_5,
     KC_TAB,     KC_Q,   KC_W,  KC_E,    KC_R,   KC_T,
     KC_CAPS,   KC_A,   KC_S,    KC_D,    KC_F,   KC_G,
     KC_LSFT,     KC_Z,   KC_X,    KC_C,    KC_V,   KC_B,
     KC_LCTL,     KC_LALT, KC_LGUI, KC_DEL, LAYER_1,   KC_SPC
  ) };

 
void setupKeymap() {

    /* Lower
  * .-----------------------------------------.    .-----------------------------------------.
  * | F12  |   F1 |   F2 |  F3  |  F4  |  F5  |    |   F6 |   F7 |   F8 |   F9 |  F10 |  F11 |
  * |------+------+------+------+------+------|    |------+------+------+------+------+------|
  * | TAB  |      |   Up |      |      |      |    |      |      |      |      |      | Home |
  * |------+------+------+------+------+------|    |------+------+------+------+------+------|
  * | Esc  | Left | Down | Right|      |      |    |      |      |      |      | Mute | PgUp |
  * |------+------+------+------+------+------|    |------+------+------+------+------+------|
  * |      |      |      |      |      |      |    |      |      | MNxt | Mply | VolU | PgDn |
  * |-----------------------------------------|    |-----------------------------------------|
  * |      |      |      | Admin|      |      |    |      |      | MPrv | MStp | VolD |  End |
  * `-----------------------------------------'    `-----------------------------------------'
     */

    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,
            KC_TAB, _______, KC_UP, _______, _______, _______,
            KC_ESC, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
            _______, _______, _______, _______, _______, _______,
            _______, _______, _______, LAYER_3, _______, _______

       );

    /* Raise
  * .-----------------------------------------.    .-----------------------------------------.
  * |  ~   |   !  |   @  |   #  |   $  |   %  |    |   ^  |   &  |   *  |   (  |   )  |   \  |
  * |------+------+------+------+------+------|    |------+------+------+------+------+------|
  * |  ~   |   !  |   @  |   #  |   $  |   %  |    |   ^  |   &  |   *  |   (  |   )  |  Del |
  * |------+------+------+------+------+------|    |------+------+------+------+------+------|
  * | Del  |   F1 |  F2  |  F3  |  F4  |  F5  |    |   F6 |   _  |   +  |   {  |   }  |  |   |
  * |------+------+------+------+------+------|    |------+------+------+------+------+------|
  * |      |   F7 |  F8  |  F9  | F10  | F11  |    |  F12 |      |      |      |      |      |
  * |-----------------------------------------|    |-----------------------------------------|
  * |      |      |      |      |      |      |    |      |      | MNxt | VolD | VolU | MPLY |
  * `-----------------------------------------'    `-----------------------------------------'
     */

    uint32_t layer2[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,
            KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,
            KC_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,
            _______, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
            _______, _______, _______, _______, _______, _______
        );
         /* ADMIN
  * .-----------------------------------------.    .-----------------------------------------.
  * | F1   |   F2 |   F3 |  F4  |  F5  |  F6  |    |      |      |   /  |   *  |   -  |      |
  * |------+------+------+------+------+------|    |------+------+------+------+------+------|
  * |      |Reset |      |      |      |      |    |      |   7  |   8  |   9  |   +  | Del  |
  * |------+------+------+------+------+------|    |------+------+------+------+------+------|
  * |      |      |      |      |      |      |    |      |   4  |   5  |   6  |   -  |      |
  * |------+------+------+------+------+------|    |------+------+------+------+------+------|
  * |      |      |      |      |      |      |    |      |   1  |   2  |   3  |   =  |      |
  * |-----------------------------------------|    |-----------------------------------------|
  * |      |      |      |      |      |      |    |      |      |   0  |   .  |  End |      |
  * `-----------------------------------------'    `-----------------------------------------'
     */

    uint32_t layer3[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
            _______,_______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______
        );



    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_L1, Method::PRESS, layer1[row][col]);
            matrix[row][col].addActivation(_L2, Method::PRESS, layer2[row][col]);
            matrix[row][col].addActivation(_L3, Method::PRESS, layer3[row][col]);
        }
    }

}


#endif //left



#if KEYBOARD_SIDE == RIGHT
 

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
            KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
            KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, 
            KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
            KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
            KC_SPC, LAYER_2, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
        )};

 
void setupKeymap() {

 
    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
            _______, _______, _______, _______, _______, KC_HOME,
            _______, _______, _______, _______, KC_MUTE, KC_PGUP,
            _______, _______, _______, _______, KC_VOLUP, KC_PGDN,
            _______, _______, _______, _______, KC_VOLDOWN, KC_END
    );


    uint32_t layer2[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
            KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC, KC_BSPC,
            KC_F6, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
            KC_F12, _______, _______, _______,_______,_______,
            _______, _______, _______, KC_VOLDOWN, KC_VOLUP, _______
    );
    
    uint32_t layer3[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            _______, _______, KC_PSLS, KC_PAST, KC_PMNS, _______,
            _______, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_DEL,
            _______, KC_P4, KC_P5, KC_P6, KC_PCMM, _______,
            _______, KC_P1, KC_P2, KC_P3, KC_PEQL, _______,
            _______, _______, KC_P0, KC_PDOT, KC_PENT, _______
    );

    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_L1, Method::PRESS, layer1[row][col]);
            matrix[row][col].addActivation(_L2, Method::PRESS, layer2[row][col]);
            matrix[row][col].addActivation(_L3, Method::PRESS, layer3[row][col]);
        }
    }

}


#endif
