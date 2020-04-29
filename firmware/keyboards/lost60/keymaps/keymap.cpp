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


/*
Working keyboard config for LOST60 V1.0 hardware (no shift registers)
and for LOST60 V2.0 hardware (shift registers for scanning columns)
NOTE: uses modified "Variant.cpp" for adafruit_feather_nrf52840 to fix pin mappings
*/


#include "keymap.h"


#if KEYBOARD_SIDE == MASTER


//lost60 ansi layout (fairly standard 60% keyboard mapping)
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
{{
    {KC_ESC,    KC_1,    KC_2,    KC_3,   KC_4,    KC_5,     KC_6,    KC_7,      KC_8,    KC_9,     KC_0,     KC_MINUS,   KC_EQUAL,       KC_BSPACE,},
    {KC_TAB,    KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,     KC_Y,    KC_U,      KC_I,    KC_O,     KC_P,     KC_LBRC,    KC_RBRACKET,    KC_BSLASH},
    {LAYER_1,   KC_A,    KC_S,    KC_D,   KC_F,    KC_G,     KC_H,    KC_J,      KC_K,    KC_L,     KC_SCLN,  KC_QUOT,    KC_NO,          KC_ENTER},
    {KC_LSFT,   KC_NO,   KC_Z,    KC_X,   KC_C,    KC_V,     KC_B,    KC_N,      KC_M,    KC_COMMA, KC_DOT,   KC_SLASH,   KC_NO,          KC_RSFT},
    {KC_LCTL,   KC_LGUI, KC_LALT, KC_NO,  KC_NO,   KC_SPACE, KC_NO,   KC_NO,     KC_NO,   KC_NO,    KC_LEFT,  KC_RIGHT,   KC_DOWN,        KC_UP}
}};


/*
//lost60 ansi layout - COL and ROW flipped (used for testing)
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
{{
    {KC_ESC,    KC_TAB,     KC_CAPS,    KC_LSFT,    KC_LCTL,    },
    {KC_1,      KC_Q,       KC_A,       KC_NO,       KC_LGUI,    },
    {KC_2,      KC_W,       KC_S,       KC_Z,       KC_LALT,    },
    {KC_3,      KC_E,       KC_D,       KC_X,       KC_NO,       },
    {KC_4,      KC_R,       KC_F,       KC_C,       KC_NO,       },
    {KC_5,      KC_T,       KC_G,       KC_V,       KC_SPACE,       },
    {KC_6,      KC_Y,       KC_H,       KC_B,       KC_NO,       },
    {KC_7,      KC_U,       KC_J,       KC_N,       KC_NO,   },
    {KC_8,      KC_I,       KC_K,       KC_M,       KC_NO,       },
    {KC_9,      KC_O,       KC_L,       KC_COMMA,   KC_NO,       },
    {KC_0,      KC_P,       KC_SCLN,    KC_DOT,     KC_LEFT,    },
    {KC_MINUS,  KC_LBRC,    KC_QUOT,    KC_SLASH,   KC_RIGHT,   },
    {KC_EQL,    KC_RBRC,    KC_NO,       KC_NO,       KC_DOWN,    },
    {KC_BSPACE, KC_BSLASH,  KC_RSFT,    KC_RSFT,    KC_UP,      }
}};
*/


void setupKeymap() {

    //add other layers here
    
    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
    KEYMAP( \
    KC_GRV,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_DEL,     \
    KC_TRNS,    KC_TRNS,    KC_UP,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_PSCR,    KC_SLCK,    KC_PAUS,    KC_TRNS,    \
    KC_TRNS,    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_INS,     KC_HOME,    KC_PGUP,    KC_TRNS,    KC_TRNS,    \
    KC_TRNS,    KC_TRNS,    KC_VOLU,    KC_VOLD,    KC_MUTE,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_END,     KC_PGDN,    KC_TRNS,    KC_TRNS,    \
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    LAYER_2,      KC_TRNS,    KC_TRNS    \
    ); 

    
    uint32_t layer2[MATRIX_ROWS][MATRIX_COLS] =
    KEYMAP( \
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    RESET,      \
    BL_TOGG,    BL_INC,     BL_DEC,     BL_STEP,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    \
    RGB_TOG,    RGB_MOD,    RGB_HUI,    RGB_SAI,    RGB_VAI,    RGB_SPI,    RGB_M_P,    RGB_M_B,    RGB_M_R,    RGB_M_SW,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    \
    KC_TRNS,    RGB_RMOD,   RGB_HUD,    RGB_SAD,    RGB_VAD,    RGB_SPD,    RGB_M_SN,   RGB_M_K,    RGB_M_X,    RGB_M_G,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    \
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS     \
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
        }
    }

}
#endif


#if KEYBOARD_SIDE == LEFT
    //LOST60 is not split board
#endif  // left


#if KEYBOARD_SIDE == RIGHT
    //LOST60 is not split board
#endif




