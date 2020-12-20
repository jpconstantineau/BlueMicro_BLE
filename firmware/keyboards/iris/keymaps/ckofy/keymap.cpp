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

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(

     KC_ESC,  KC_7,    KC_5,    KC_3,    KC_1,     KC_9,                
     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,     KC_B, 
     KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,     KC_G,
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,     KC_V,  ,KC_LCTL,
                                KC_LCTL, L_LOWER,  KC_SPC 
  )};

 
void setupKeymap() {



    uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                
        _______, KC_LOCK, XXXXXXX, KC_SWP,  KC_CAPS, KC_BRK, 
        _______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_SVE, 
        _______, KC_UND,  KC_CUT,  KC_CPY,  KC_PST,  XXXXXXX, _______,
                                   _______, _______, _______ 
       );
    
	uint32_t mlower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( 
        _______, _______, _______, _______, _______, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS, XXXXXXX, 
        _______, KC_LCTL, KC_LALT, KC_LSFT, KC_LGUI, KC_MSVE, 
        _______, KC_MUND, KC_MCUT, KC_MCPY, KC_MPST, XXXXXXX, KC_LGUI,
                                   KC_LGUI, L_MLOWER,KC_SPC 
        );

    uint32_t layer2[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                
        KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,
        KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,
        KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,KC_HOME,
                                 KC_LGUI,LAYER_1,KC_ENT 
        );


    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                
        _______, KC_AMPR, KC_PERC, KC_HASH, KC_LPRN, KC_EXLM, 
        _______, KC_7,    KC_5,    KC_3,    KC_1,    KC_9,   
        _______, KC_GRAVE,KC_LBRC, KC_RBRC, KC_UNDS, KC_EQL, _______,
                                    _______, _______, _______ 
        );
    uint32_t adjust[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( 
		_______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
  PRINT_BATTERY,XXXXXXX,XXXXXXX,KM_MAC,KM_COLEMAK,XXXXXXX,
     PRINT_INFO,HOME_ADD,EMAIL_1,EMAIL_2,WORK_ADD,XXXXXXX, _______,
                                 _______, _______, _______
        );

    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_LOWER, Method::PRESS, lower[row][col]);
            matrix[row][col].addActivation(_MLOWER, Method::PRESS, mlower[row][col]);
            matrix[row][col].addActivation(_RAISE, Method::PRESS, raise[row][col]);
            matrix[row][col].addActivation(_ADJUST, Method::PRESS, adjust[row][col]);
        }
    }

}

void process_user_macros(uint16_t macroid)
{

uint32_t colemak[MATRIX_ROWS][MATRIX_COLS] =
    KEYMAP(
        KC_ESC,  KC_7,    KC_5,    KC_3,    KC_1,     KC_9,     
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,     KC_B, 
        KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,     KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,     KC_V, KC_LCTL,
                                   KC_LCTL, L_LOWER,  KC_SPC
    );

uint32_t mac[MATRIX_ROWS][MATRIX_COLS] =
    KEYMAP(    
        KC_ESC,  KC_7,    KC_5,    KC_3,    KC_1,     KC_9, 
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,     KC_B, 
        KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,     KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,     KC_V, KC_LGUI,
                                   KC_LGUI, L_MLOWER, KC_SPC
    );
  
 switch ((macroid))
 { 
     case (KM_COLEMAK):
        for (int row = 0; row < MATRIX_ROWS; ++row)
        {
            for (int col = 0; col < MATRIX_COLS; ++col)
            {
                matrix[row][col].addActivation(_COLEMAK, Method::PRESS, colemak[row][col]);
            }
        }
     break;
	 case (KM_MAC):
        for (int row = 0; row < MATRIX_ROWS; ++row)
        {
            for (int col = 0; col < MATRIX_COLS; ++col)
            {
                matrix[row][col].addActivation(_MAC, Method::PRESS, mac[row][col]);
            }
        }
     break;
    
     case HOME_ADD:
     addStringToQueue("123 Quiet Crescent");
     break;
     case WORK_ADD:
     addStringToQueue("456 Work Place");
      break;
     case EMAIL_1:
     addStringToQueue("Primary@Email");
      break;
     case EMAIL_2:
     addStringToQueue("Secondary@Email");
      break;   
 }
}

void process_user_layers(uint16_t layermask)
{
    KeyScanner::process_for_tri_layers(_LOWER, _RAISE, _ADJUST);
    KeyScanner::process_for_tri_layers(_MLOWER, _RAISE, _ADJUST);
}

#endif //left

#if KEYBOARD_SIDE == RIGHT


std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
            KC_8,    KC_0,    KC_2,    KC_4,    KC_6,    KC_BSPC,
            KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, 
            KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOTE,
     KC_ENT,KC_K,    KC_H,    KC_COMMA,KC_DOT,  KC_SLSH, KC_ENT,
            KC_LSFT, L_RAISE, KC_LALT
    )};

 
void setupKeymap() {


    uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
            KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,  _______, 
            KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, _______, 
    _______,KC_INS , XXXXXXX, KC_COMMA,KC_DOT,  KC_SLSH, _______, 
            _______, _______, _______  \
    );

	uint32_t mlower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( 
            _______, _______, _______, _______, _______, _______,		
            KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,  _______, 
            KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, _______, 
    _______,KC_INS , XXXXXXX, KC_COMMA,KC_DOT,  KC_SLSH, _______, 
            _______, _______, _______  
        );

    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
             KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
             KC_ASTR, KC_RPRN, KC_AT,   KC_DLR,  KC_CIRC, _______, 
             KC_8,    KC_0,    KC_2,    KC_4,    KC_6,    KC_BSLS, 
     _______,KC_PLUS, KC_MINUS,KC_COMMA,KC_DOT,  KC_SLSH, _______, 
             _______, _______, _______  \
    );


    uint32_t adjust[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( 
            _______, _______, _______, _______, _______, _______,		
            _______, _______, _______, _______, _______, _______,
            XXXXXXX,  XXXXXXX,  XXXXXXX, KC_F11,KC_F12,PRINT_BATTERY, 
    _______,XXXXXXX,  XXXXXXX,  XXXXXXX,XXXXXXX,XXXXXXX,PRINT_INFO, 
            _______, _______, _______  \
        );

    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_LOWER, Method::PRESS, lower[row][col]);
            matrix[row][col].addActivation(_MLOWER, Method::PRESS, mlower[row][col]);
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
    KeyScanner::process_for_tri_layers(_MLOWER, _RAISE, _ADJUST);
}

#endif  // right
