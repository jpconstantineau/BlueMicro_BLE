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
 
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {{
        {KC_TAB,    KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,     KC_BSPACE,},
        {KC_ESC,    KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN,  KC_QUOT,},
        {KC_LSFT,   KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,    KC_N,    KC_M,   KC_COMMA,KC_DOT,  KC_SLASH, KC_ENTER,},
        {L_MACRO,   KC_LCTL, KC_LALT, KC_LGUI,L_LOWER, KC_SPC,  KC_SPC,  L_RAISE,KC_LEFT, KC_DOWN,   KC_UP,  KC_RIGHT}
    }};

 
void setupKeymap() {

    uint32_t colemak[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
        KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
        L_MACRO, KC_LCTL, KC_LALT, KC_LGUI, L_LOWER, KC_SPC,  KC_SPC,  L_RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT);
    uint32_t dvorak[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
           KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
           KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
           KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT ,
           L_MACRO, KC_LCTL, KC_LALT, KC_LGUI, L_LOWER, KC_SPC,  KC_SPC,  L_RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT);

    uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
        _______, _______, _______, _______, L_LOWER, _______, _______, L_ADJUST,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY);

    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, L_ADJUST, _______, _______, L_RAISE, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY);

    uint32_t adjust[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    _______, RESET,   _______,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, _______,  _______,   _______,  _______, _______, _______,  _______,  _______,  _______,  _______,
    _______, _______,  _______,  _______,   _______,  _______,   _______,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, L_ADJUST, _______, _______, L_ADJUST, _______,  _______, _______, _______);

    uint32_t macro[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    _______, HOME_ADD, EMAIL_1,  NAME_1, CBR_FN, PHONE_1, TAB_DOWN_RTRN, INOWORD, IN_R,  IPADDR, SMILE, IPSUM ,
    _______, WORK_ADD, EMAIL_2,  NAME_2, BRC_FN, PHONE_2, TAB_UP_RTRN, FOREXMPL,  _______,  _______,  _______,  _______,
    _______, _______,  _______,  NAME_3, PRN_FN, _______,   _______,  FF_TEXT, _______, LARW_L, LARW_R, _______,
    L_MACRO, _______, _______, _______, L_LOWER, _______, _______, L_RAISE, _______,  _______, _______, _______);

    /*
     * add the other layers
     */
 
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
          //  matrix[row][col].addActivation(_COLEMAK, Method::PRESS, colemak[row][col]);
          //  matrix[row][col].addActivation(_DVORAK, Method::PRESS,  dvorak[row][col]);
            matrix[row][col].addActivation(_LOWER, Method::PRESS,   lower[row][col]);
            matrix[row][col].addActivation(_RAISE, Method::PRESS,   raise[row][col]);
            matrix[row][col].addActivation(_ADJUST, Method::PRESS,  adjust[row][col]);
            matrix[row][col].addActivation(_MACRO, Method::PRESS,   macro[row][col]);
        }
    }

}


void process_user_macros(uint16_t macroid)
{
 switch (macroid)
 {
     case HOME_ADD:
     sendString("123 Quiet Crescent");
     break;
     case WORK_ADD:
     sendString("123 Work Place");
      break;
     case EMAIL_1:
     sendString("Primary@Email");
      break;
     case EMAIL_2:
     sendString("Other@Email");
      break;
     case NAME_1:
     sendString("First Name");
      break;
     case NAME_2:
     sendString("Middle Name");
      break;
     case NAME_3:
     sendString("Last Name");
      break;
     case CBR_FN:
     sendString("{}"); // more to add here
      break;
     case BRC_FN:
     sendString("[]"); // more to add here
      break;
     case PRN_FN:
     sendString("()"); // more to add here 
      break;
     case TAB_DOWN_RTRN:
     sendString("%in%"); // different here
      break;
     case TAB_UP_RTRN:
     sendString("%in%"); // different here
      break;
     case PHONE_1:
     sendString("234-567-8901");
      break;
     case PHONE_2:
     sendString("987-654-3210");
      break;
     case INOWORD:
     sendString("(i.e., )");  // more to add here
      break;
     case FOREXMPL:
     sendString("(e.g., )"); // more to add here
      break;
     case FF_TEXT:
     sendString("rff"); // more to add here
      break;
     case IN_R:
     sendString("%in%");
      break;
     case LARW_L:
     sendString("<-");
      break;
     case LARW_R:
     sendString("->");
      break;
     break;
     case IPADDR:
     sendString("192.168.1.");
      break;
     break;
     case SMILE:
     sendString(":)");
      break;
     break;
     case IPSUM:
     sendString("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
     break;
 }
}


