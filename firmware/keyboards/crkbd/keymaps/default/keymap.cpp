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


#if KEYBOARD_SIDE == MASTER
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
            KC_1,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
            KC_2,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
            KC_3,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
            KC_NO,  KC_NO,  KC_NO,   KC_4,    KC_5,    KC_6
    )};

void setupKeymap() {

   // no layers for master keymap
   // this is a keymap that's used for testing that each key is responding properly to key presses
   // flash this keymap to both left and right to test whether each half works properly.
   // once tested, you can flash the left and right to their respective halves.

}
#endif


#if KEYBOARD_SIDE == LEFT

/* Qwerty
 * ,-----------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |
 * |------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |
 * |------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |
 * |------+------+------+------+------+------|
 * |      |      |      |  GUI | L(1) |Space |
 * `-----------------------------------------'
 */

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T, 
        KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,     KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,
        KC_NO,   KC_NO,   KC_NO,   KC_LGUI, LAYER_1,  KC_SPC
    )};

 
void setupKeymap() {

/* Layer 1 (Raise)
 * ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |
 * |------+------+------+------+------+------|
 * | CTRL |      |      |      |      |      |
 * |------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |
 * |------+------+------+------+------+------|
 * |      |      |      |  GUI | L(1) |Space |
 * `-----------------------------------------'
 */
    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
              KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5, \
              KC_LCTL,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, \
              KC_LSFT,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, \
              KC_NO,    KC_NO,   KC_NO,   KC_LGUI, LAYER_1, KC_SPC \
        );

    /* Layer 2 (lower)
 * ,-----------------------------------------.
 * |  Esc |   !  |   @  |   #  |   $  |   %  |
 * |------+------+------+------+------+------|
 * | Ctrl |      |      |      |      |      |
 * |------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |
 * |------+------+------+------+------+------|
 * |      |      |      | GUI  | L(1) |Space |
 * `-----------------------------------------'
 */
    uint32_t layer2[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
              KC_ESC,  KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC, \
              KC_LCTL, KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO, \
              KC_LSFT, KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO, \
              KC_NO,   KC_NO,   KC_NO,  KC_LGUI, LAYER_1, KC_SPC \
        );
    /*
     * add the other layers on the regular presses.
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_L1, _PRESS, layer1[row][col]);
            matrix[row][col].addActivation(_L2, _PRESS, layer2[row][col]);
        }
    }

    // if you want to add Tap/Hold or Tap/Doubletap activations, then you add them below.

}

#endif  // left



#if KEYBOARD_SIDE == RIGHT

/* Qwerty
 * ,-----------------------------------------.
 * |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+-------------|
 * |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------|------|
 * |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------|
 * | Space| L(2) | Left | Down |  Up  |Right |
 * `-----------------------------------------'
 */

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_BSPACE, 
            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCOLON, KC_QUOTE,
            KC_N,    KC_M,    KC_COMMA,KC_DOT,  KC_SLSH,   KC_RSFT,
            KC_ENT,  LAYER_2, KC_RALT, KC_NO,   KC_NO,   KC_NO
    )};

void setupKeymap() {

/* Layer 1 (Raise)
 * ,-----------------------------------------.
 * |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+-------------|
 * |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------|------|
 * |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------|
 * | Space| L(2) | Left |      |      |      |
 * `-----------------------------------------'
 */
    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
              KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_BSPC, \
              KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_NO,   KC_NO, \
              KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO, \
              KC_SPC,  LAYER_2, KC_RALT, KC_NO,    KC_NO,   KC_NO \
        );

    /* Layer 2 (lower)
 * ,-----------------------------------------.
 * |   ^  |   &  |   *  |   (  |   )  | Bspc |
 * |------+------+------+------+-------------|
 * |   -  |   =  |   {  |   }  |   |  |  `   |
 * |------+------+------+------+------|------|
 * |   _  |   +  |   [  |   ]  |   \  |  ~   |
 * |------+------+------+------+------+------|
 * | Space| L(2) |  Alt |      |      |      |
 * `-----------------------------------------'
 */
    uint32_t layer2[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
                KC_CIRC,  KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
                KC_MINS,  KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE, KC_GRV, \
                KC_UNDS,  KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD, \
                KC_ENT,   LAYER_2, KC_RALT, KC_NO,   KC_NO, KC_NO \
        );
    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_L1, _PRESS, layer1[row][col]);
            matrix[row][col].addActivation(_L2, _PRESS, layer2[row][col]);
        }
    }

}

#endif

