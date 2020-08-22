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

// Initialize matrix with nothing...
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    KEYMAP2ARRAY(KEYMAP(
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO
    ));


void setupKeymap() {

   // no layers for SINGLE keymap
   // this is a keymap that's used for testing that each key is responding properly to key presses
   // flash this keymap to both left and right to test whether each half works properly.
   // once tested, you can flash the left and right to their respective halves.
   uint32_t layer0_single[MATRIX_ROWS][MATRIX_COLS] = KEYMAP(
        KC_1,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_Y, 
        KC_2,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_H,
        KC_3,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_N,
        KC_4,  KC_5,    KC_6,    KC_7,    KC_8,    KC_9,  KC_0 
    );


/* Qwerty LEFT
 * ,------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y* | 
 * |------+------+------+------+------+-------------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H* |
 * |------+------+------+------+------+------|------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |Space |
 * |------+------+------+------+------+------+------'
 * | Ctrl | GUI  | Alt  | L(3) | L(1) |Space |
 * `-----------------------------------------'
 */

uint32_t layer0_left[MATRIX_ROWS][MATRIX_COLS] =
    KEYMAP(
        PRINT_BLE,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_Y, 
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_H,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_SPC,
        KC_LCTL, KC_LGUI, KC_LALT, LAYER_3, LAYER_1, KC_SPC,_______
    );

 /* Qwerty RIGHT
 * ,------------------------------------------------.
 * |   =  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------|
 * |   \  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------|
 * | Space|   N  |   M  |   ,  |   .  |   /  |Enter |
 * `------+------+------+------+------+------+------|
 *        | Space| L(2) | Left | Down |  Up  |Right |
 *        `-----------------------------------------'
 */

uint32_t layer0_right[MATRIX_ROWS][MATRIX_COLS] =
    KEYMAP(
        KC_EQUAL, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      PRINT_BLE, 
        KC_BSLS,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCOLON, KC_QUOTE,
        KC_SPC,   KC_N,    KC_M,    KC_COMMA,KC_DOT,  KC_SLSH,   KC_ENT,
        _______,  KC_SPC,  LAYER_2, KC_LEFT, KC_UP,   KC_DOWN,   KC_RIGHT
    );



 /* Layer 1 (Raise) LEFT
 * ,------------------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |   -  | 
 * |------+------+------+------+------+-------------|
 * | Del  |  F1  | F2   |  F3  | F4   |  F5  |  [   |
 * |------+------+------+------+------+------|------|
 * | Shift|  F7  | F8   |  F9  |  F10 | F11  |Space |
 * |------+------+------+------+------+------+------'
 * | Ctrl | GUI  | Alt  | L(3) | L(1) |Space |
 * `-----------------------------------------'
 */
    uint32_t layer1_left[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        KC_GRAVE,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,    KC_MINUS,  \
        KC_DEL  ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  , KC_LBRC,   \
        KC_LSFT ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 , KC_SPC,  \
        KC_LCTL , KC_LGUI, KC_LALT, LAYER_3, LAYER_1, KC_SPC,_______ \
        );


 /* Layer 1 (Raise)  RIGHT
 * ,------------------------------------------------.
 * |   +  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------|
 * |   ]  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------|
 * | Space|  F12 |   ~  |   |  |   _  |   _  |Enter |
 * `------+------+------+------+------+------+------|
 *        | Space| L(2)*| Left | Down |  Up  |Right |
 *        `-----------------------------------------'
 */
    uint32_t layer1_right[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        KC_PLUS, KC_6,    KC_7,    KC_8,    KC_9,     KC_0,      KC_DEL,  \
        KC_RBRC, KC_F6,   KC_MINS, KC_EQL,  KC_LBRC,  KC_RBRC,   KC_BSLS,   \
        KC_SPC,  KC_F12,  KC_TILD, KC_PIPE, KC_UNDS,  KC_UNDS,   KC_ENTER,  \
        _______, KC_SPC,  LAYER_2, KC_LEFT, KC_DOWN,  KC_UP,     KC_RIGHT \
        );

     /* Layer 2 (lower)  LEFT
 * ,------------------------------------------------.
 * |  ~   |   !  |   @  |   #  |   $  |   %  |   _  |
 * |------+------+------+------+------+-------------|
 * | Del  |  F1  | F2   |  F3  | F4   |  F5  |  (   |
 * |------+------+------+------+------+------|------|
 * | Shift|  F7  | F8   |  F9  |  F10 | F11  |Space |
 * |------+------+------+------+------+------+------'
 * | Ctrl | GUI  | Alt  | L(3) | L(1) |Space |
 * `-----------------------------------------'
 */
    uint32_t layer2_left[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        KC_TILD ,KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_UNDS,  \
        KC_DEL  ,KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_LPRN,   \
        KC_LSFT ,KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_SPC,  \
        KC_LCTL ,KC_LGUI, KC_LALT, LAYER_3, LAYER_1, KC_SPC,  _______ \
        );

/* Layer 2 (lower) RIGHT
 * ,------------------------------------------------.
 * |   =  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------|
 * |   )  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------|
 * | Space| F12  |ISO ~ |ISO | |   [  |   ]  |ENTER |
 * `------+------+------+------+------+------+------|
 *        | Space| L(2)*| Left | Down |  Up  |Right |
 *        `-----------------------------------------'
 */
    uint32_t layer2_right[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        KC_EQUAL,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,  \
        KC_RPRN,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,   \
        KC_SPC,    KC_F12,  KC_NUTL, KC_NUPI, KC_LBRC, KC_RBRC, KC_ENTER,  \
        _______,   KC_SPC,  LAYER_2, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT \
        );

/* Layer 3  LEFT
 * ,------------------------------------------------.
 * | ESC* |  F1  |  F2  |  F3  |  F4  |  F5  |PRTSCR| 
 * |------+------+------+------+------+-------------|
 * | CAPL*| PUP* | NEXT*| PLAY*| PREV*| VOL+*| MUTE*|
 * |------+------+------+------+------+------|------|
 * | Shift|PDOWN*| INS* | HOME*| END* | VOL-*|Space |
 * |------+------+------+------+------+------+------'
 * | Ctrl | GUI  | Alt  | L(3) | L(1) |Space |
 * `-----------------------------------------'
 */
    uint32_t layer3_left[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        KC_ESC,       KC_F1,      KC_F2,              KC_F3,                  KC_F4,                  KC_F5,      KC_PSCREEN,  \
        KC_CAPSLOCK,  KC_PGUP,    KC_MEDIA_NEXT_TRACK,KC_MEDIA_PLAY_PAUSE,    KC_MEDIA_PREV_TRACK,    KC_VOLU,    KC_MUTE,   \
        KC_LSFT,      KC_PGDN,    KC_INS,             KC_HOME,                KC_END,                 KC_VOLD,    KC_SPC,  \
        KC_LCTL ,     KC_LGUI,    KC_LALT,            LAYER_3,                LAYER_1,                KC_SPC,     _______ \
        );

      /* Layer 3 RIGHT
 * ,------------------------------------------------.
 * |NULOCK|  F6  |  F7  |  F8  |  F9  |  F10 | NUM- |
 * |------+------+------+------+------+-------------|
 * |      | NUM1 | NUM2 | NUM3 | NUM4 | NUM5 | NUM+ |
 * |------+------+------+------+------+------|------|
 * | Space| NUM6 | NUM7 | NUM8 | NUM9 | NUM10|NENTER|
 * `------+------+------+------+------+------+------|
 *        | Space| L(2)*|NUMINS| NUM. | NUM* | NUM/ |
 *        `-----------------------------------------'
 */
    uint32_t layer3_right[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        KC_NUMLOCK,   KC_F6,    KC_F7,    KC_F8,    KC_F9,        KC_F10,         KC_KP_MINUS,  \
        XXXXXXX,      KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_KP_4,      KC_KP_5,        KC_KP_PLUS,   \
        KC_SPC ,      KC_KP_6,  KC_KP_7,  KC_KP_8,  KC_KP_9,      KC_KP_0,        KC_KP_ENTER,  \
        _______,      KC_SPC,   LAYER_2,  KC_INSERT,  KC_KP_DOT,  KC_KP_ASTERISK, KC_KP_SLASH \
        );


    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            #if KEYBOARD_SIDE == SINGLE
                matrix[row][col].addActivation(_L0, Method::PRESS, layer0_single[row][col]);
            #endif
            #if KEYBOARD_SIDE == LEFT
                matrix[row][col].addActivation(_L0, Method::PRESS, layer0_left[row][col]);
                matrix[row][col].addActivation(_L1, Method::PRESS, layer1_left[row][col]);
                matrix[row][col].addActivation(_L2, Method::PRESS, layer2_left[row][col]);
                matrix[row][col].addActivation(_L3, Method::PRESS, layer3_left[row][col]);
            #endif
            #if KEYBOARD_SIDE == RIGHT
                matrix[row][col].addActivation(_L0, Method::PRESS, layer0_right[row][col]);
                matrix[row][col].addActivation(_L1, Method::PRESS, layer1_right[row][col]);
                matrix[row][col].addActivation(_L2, Method::PRESS, layer2_right[row][col]);
                matrix[row][col].addActivation(_L3, Method::PRESS, layer3_right[row][col]);
            #endif
            // if you want to add Tap/Hold or Tap/Doubletap activations, then you add them below.

        }
    }
}






