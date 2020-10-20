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
        KC_1,  KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
        KC_7,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_8,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_9,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                        KC_2,    KC_3,    
                                          KC_4,    KC_5,
                                          KC_6,    KC_7,
                                          KC_8,    KC_9
    )};

void setupKeymap() {

   // no layers for master keymap
   // this is a keymap that's used for testing that each key is responding properly to key presses
   // flash this keymap to both left and right to test whether each half works properly.
   // once tested, you can flash the left and right to their respective halves.

}

void process_user_macros(uint16_t macroid)
{
	
}	

void process_user_layers(uint16_t layermask)
{
	
}	
#endif


#if KEYBOARD_SIDE == LEFT

/* Qwerty
 * ,-----------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  | 
 * |-----------------------------------------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  | 
 * |------+------+------+------+------+------|
 * | Shift|   A  |   S  |   D  |   F  |   G  |
 * |------+------+------+------+------+------|
 * | Ctrl |   Z  |   X  |   C  |   V  |   B  |
 * `------+------+------+------+------+------'
 *               |   [  |   ]  |
 *               `---------------------------.
 *                             |Lower |Space |
 *                             `-------------------------. 
 *                                           | Tab | Home|
 *                                           ------------| 
 *                                           | BSpc|  `  |
 *                                           ------------' 
 */

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5, 
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, 
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                          KC_LBRC, KC_RBRC, 
                                            L_LOWER, KC_SPC,
                                            KC_TAB,  KC_HOME,
                                            KC_BSPC, KC_GRAVE
    )};

 
void setupKeymap() {


/* Lower
 * ,-----------------------------------------.
 * |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |
 * |-----------------------------------------|
 * |      |      |      |      |      |   [  | 
 * |------+------+------+------+------+------|
 * | Caps | Home | PgDn | PgUp | End  |   (  |
 * |------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy | Paste|      |
 * `-----------------------------------------'
 *               |      |      |
 *               `---------------------------.
 *                             |      |      |
 *                             `---------------------------. 
 *                                           |      |      |
 *                                           --------------| 
 *                                           |      |      |
 *                                           --------------' 
 */
    uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
  KC_F12, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5, \
  _______,_______,_______,_______,_______,KC_LBRC, \
  KC_CAPS,KC_HOME,KC_PGDN,KC_PGUP,KC_END, KC_LPRN, \
  _______,KC_UND, KC_CUT, KC_CPY, KC_PST, _______, \
                  _______,_______,                 \
                                  _______,_______, \
                                  _______,_______, \
                                  _______,_______  \
);

/* Raise
 * ,-----------------------------------------.
 * |   ~  |  !   |  @   |  #   |  $   |  %   |
 * |-----------------------------------------|
 * | Mute |      |      |      |      |  [   |
 * |------+------+------+------+------+------|
 * | Vol+ | Left | Down |  Up  | Right|  (   |
 * |------+------+------+------+------+------|
 * | Vol- |      |      |      |      |      |
 * `-----------------------------------------'
  *              |      |      |
 *               `---------------------------.
 *                             |      |      |
 *                             `---------------------------. 
 *                                           |      |      |
 *                                           --------------| 
 *                                           |      |      |
 *                                           --------------' 
 */
    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
  KC_TILD,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC, \
  KC_MUTE,_______,_______,_______,_______,KC_LBRC, \
  KC_VOLU,KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_LPRN, \
  KC_VOLD,_______,_______,_______,_______,_______, \
                  _______,_______,                 \
                                  _______,_______, \
                                  _______,_______, \
                                  _______,_______  \
);
 
/* Adjust
 * ,-----------------------------------------.
 * |Batt  |  M1  |  M2  |  M3  |  M4  |      |
 * |------+------+------+------+------+-------
 * |      |      |      |      |      |      |
 * |------+------+------+------+------+------|
 * |      |      |      |      |      |      |
 * |------+------+------+------+------+------+
 * |Board |      |      |      |      |      |
 * `-----------------------------------------'
  *              |      |      |
 *               `---------------------------.
 *                             |      |      |
 *                             `---------------------------. 
 *                                           |      |      |
 *                                           --------------| 
 *                                           |      |      |
 *                                           --------------' 
 */
    uint32_t adjust[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
  PRINT_BATTERY,HOME_ADD,WORK_ADD,EMAIL_1,EMAIL_2,_______,   \
  _______, _______,_______,_______, _______, _______, \
  _______, _______,_______,_______, _______, _______,  \
  PRINT_INFO,_______,_______,_______,_______,_______, \
                      _______,_______,                 \
                                     _______,_______, \
                                     _______,_______, \
                                     _______,_______  \ 
);

    /*
     * add the other layers on the regular presses.
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {		
            matrix[row][col].addActivation(_LOWER, Method::PRESS, lower[row][col]);
            matrix[row][col].addActivation(_RAISE, Method::PRESS, raise[row][col]);
            matrix[row][col].addActivation(_ADJUST, Method::PRESS, adjust[row][col]);
        }
    }

}

void process_user_macros(uint16_t macroid)
{	  
		  
 switch ((macroid))
 {  
     case HOME_ADD:
     addStringToQueue("123 Quiet Crescent");
     break;
     case WORK_ADD:
     addStringToQueue("123 Work Place");
      break;
     case EMAIL_1:
     addStringToQueue("Primary@Email");
      break;
     case EMAIL_2:
     addStringToQueue("Other@Email");
      break;  
 }
}

void process_user_layers(uint16_t layermask)
{
    KeyScanner::process_for_tri_layers(_LOWER, _RAISE, _ADJUST);
}

#endif  // left



#if KEYBOARD_SIDE == RIGHT

/* Qwerty
 *                ,-----------------------------------------.
 *                |   6  |   7  |   8  |   9  |   0  | Bksp |
 *                |-----------------------------------------|
 *                |   Y  |   U  |   I  |   O  |   P  |  -   |
 *                |------+------+------+------+-------------|
 *                |   H  |   J  |   K  |   L  |   ;  |  '   |
 *                |------+------+------+------+------|------|
 *                |   N  |   M  |   ,  |   .  |   /  |   \  |
 *                `-----------------------------------------'
 *                              |   +  |   =  |
 *                ,---------------------------'
 *                | Enter| Raise|
 *    ,-------------------------' 
 *    | End | Del |
 *    |-----------| 
 *    | GUI | Alt |
 *    `-----------' 
 */

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_BSPACE, 
        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_MINS, 
        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCOLON,KC_QUOTE,
        KC_N,    KC_M,    KC_COMMA,KC_DOT,  KC_SLSH,  KC_BSLS,
                          KC_PLUS ,KC_EQL, 
        KC_ENT,  L_RAISE,
        KC_END,  KC_DEL,  
        KC_LGUI, KC_LALT
    )};

 

void setupKeymap() {


/* Lower
 *                ,-----------------------------------------.
 *                |   F6 |  F7  |  F8  |  F9  | F10  | F11  |
 *                |-----------------------------------------|
 *                |  ]   |      |      | Ins  |      | Mute |
 *                |------+------+------+------+-------------|
 *                |  )   | Prev | Play | Next |      | Vol+ |
 *                |------+------+------+------+------|------|
 *                |      |      |      |      |      | Vol- |
 *                `-----------------------------------------'
 *                              |      |      |
 *                ,---------------------------'
 *                |      |      |
 *  ,---------------------------' 
 *  |      |      |
 *  |-------------| 
 *  |      |      |
 *  `-------------' 
 */
    uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   \
  KC_RBRC, _______, _______, KC_INS , _______, KC_MUTE,  \
  KC_RPRN, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_VOLU,  \
  _______, _______, _______, _______, _______, KC_VOLD,  \
                    _______, _______,                    \
  _______, _______,                                      \
  _______, _______,                                      \
  _______, _______                                       \ 
);

/* Raise
 *                ,-----------------------------------------.
 *                |   ^  |   &  |  *   |   (  |   )  |  Del |
 *                |-----------------------------------------|
 *                |   ]  |   7  |  8   |   9  |   -  |   _  |
 *                |------+------+------+------+-------------|
 *                |   )  |   4  |  5   |   6  |   +  |   |  |
 *                |------+------+------+------+------|------|
 *                |Numlck|   1  |  2   |   3  |   /  |      |
 *                `-----------------------------------------'
 *                              |  0   |   .  |
 *                ,---------------------------'
 *                |      |      |
 *  ,---------------------------' 
 *  |      |      |
 *  |-------------| 
 *  |      |      |
 *  `-------------' 
 */
    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,   \
  KC_RBRC, KC_P7 ,  KC_P8 ,  KC_P9 ,  KC_MINS, KC_UNDS,  \
  KC_RPRN, KC_P4 ,  KC_P5 ,  KC_P6 ,  KC_PLUS, KC_PIPE,  \
  KC_NLCK, KC_P1 ,  KC_P2 ,  KC_P3 ,  KC_SLSH, _______,  \
                    KC_P0 ,  KC_DOT,                     \
  _______, _______,                                      \
  _______, _______,                                      \
  _______, _______                                       \ 
);

/* Adjust
 *                ,-----------------------------------------.
 *                |      |      |      |      |      |Batt  |
 *                |-----------------------------------------|
 *                |      |      |      |      |      |      |
 *                |------+------+------+------+-------------|
 *                |      |      |      |      |      |      |
 *                |------+------+------+------+------|------|
 *                |      |      |      |      |      |Board |
 *                `-----------------------------------------'
 *                              |      |      |
 *                ,---------------------------'
 *                |      |      |
 *  ,---------------------------' 
 *  |      |      |
 *  |-------------| 
 *  |      |      |
 *  `-------------' 
 */
    uint32_t adjust[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
  _______, _______, _______, _______, _______,PRINT_BATTERY,  \
  _______, _______, _______, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______,  \   
  _______, _______, _______, _______, _______, PRINT_INFO,\
                    _______, _______,                    \
  _______, _______,                                      \
  _______, _______,                                      \
  _______, _______                                       \ 
);

    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_LOWER, Method::PRESS, lower[row][col]);
            matrix[row][col].addActivation(_RAISE, Method::PRESS, raise[row][col]);
            matrix[row][col].addActivation(_ADJUST, Method::PRESS, adjust[row][col]);
        }
    }

}

void process_user_macros(uint16_t macroid)
{	

}


void process_user_layers(uint16_t layermask)
{
    KeyScanner::process_for_tri_layers(_LOWER, _RAISE, _ADJUST);
}

#endif
