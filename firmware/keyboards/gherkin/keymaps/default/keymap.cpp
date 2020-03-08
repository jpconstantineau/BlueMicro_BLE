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
    {KEYMAP(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,          KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,          KC_J,    KC_K,    KC_L,    KC_ESC,
    CTL_Z,   ALT_X,   FN3_C,   FN4_V,   FN2_BSPC,FN1_SPC,       FN5_B,   ALT_N,   CTL_M,   SFT_ENT
    )};

 
void setupKeymap() {

    uint32_t layer0_tap[MATRIX_ROWS][MATRIX_COLS] =
KEYMAP(
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,       XXXXXXX,     XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,       XXXXXXX,     XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
    CTL_Z_TAP, ALT_X_TAP, FN3_C_TAP, FN4_V_TAP, FN2_BSPC_TAP,  FN1_SPC_TAP, FN5_B_TAP, ALT_N_TAP, CTL_M_TAP, SFT_ENT_TAP );

    uint32_t layer0_hold[MATRIX_ROWS][MATRIX_COLS] =
KEYMAP(
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    CTL_Z_HOLD, ALT_X_HOLD, FN3_C_HOLD, FN4_V_HOLD, FN2_BSPC_HOLD,  FN1_SPC_HOLD, FN5_B_HOLD, ALT_N_HOLD, CTL_M_HOLD, SFT_ENT_HOLD );

    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
KEYMAP(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX );


    uint32_t layer2[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_GRV,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX );


    uint32_t layer3[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH, KC_SCLN, KC_QUOT,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT );

    uint32_t layer4[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LABK, KC_RABK, KC_QUES, KC_COLN, KC_DQUO,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END );

    uint32_t layer5[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    KC_CALC,       KC_WHOM, KC_MAIL, KC_MYCM, XXXXXXX, BL_STEPINC, BL_ON,   BL_OFF,  BL_STEP, BL_TOGG,
    PRINT_BATTERY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BL_STEPDEC, BL_BRTG, BL_REACT,BL_DEC,  BL_INC,
    GITCOMMIT,     XXXXXXX, XXXXXXX, XXXXXXX, RESET,   XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, SERIAL_DFU );

    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_QWERTY, Method::MT_TAP, layer0_tap[row][col]);
            matrix[row][col].addActivation(_QWERTY, Method::MT_HOLD, layer0_hold[row][col]);
            matrix[row][col].addActivation(_L1, Method::PRESS, layer1[row][col]);
            matrix[row][col].addActivation(_L2, Method::PRESS, layer2[row][col]);
            matrix[row][col].addActivation(_L3, Method::PRESS, layer3[row][col]);
            matrix[row][col].addActivation(_L4, Method::PRESS, layer4[row][col]);
            matrix[row][col].addActivation(_L5, Method::PRESS, layer5[row][col]);
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
     case NAME_1:
     addStringToQueue("First Name");
      break;
     case NAME_2:
     addStringToQueue("Middle Name");
      break;
     case NAME_3:
     addStringToQueue("Last Name");
      break;
     case (CBR_FN):
      addStringToQueue("{}"); 
      addKeycodeToQueue(KC_LEFT);
      break;
     case (BRC_FN):
      addStringToQueue("[]");
      addKeycodeToQueue(KC_LEFT);
      break;
     case PRN_FN:
      addStringToQueue("()"); 
      addKeycodeToQueue(KC_LEFT);
      break;
     case TAB_DOWN_RTRN:
      addKeycodeToQueue(KC_TAB);
      addKeycodeToQueue(KC_DOWN);
      addKeycodeToQueue(KC_ENTER);
      break;
     case TAB_UP_RTRN:
       addKeycodeToQueue(KC_TAB);
       addKeycodeToQueue(KC_UP);
       addKeycodeToQueue(KC_ENTER);
      break;
     case PHONE_1:
     addStringToQueue("234-567-8901");
      break;
     case PHONE_2:
     addStringToQueue("987-654-3210");
      break;
     case INOWORD:
     addStringToQueue("(i.e., )");  
     addKeycodeToQueue(SEND_KC(KC_LEFT));
      break;
     case FOREXMPL:
     addStringToQueue("(e.g., )"); 
     addKeycodeToQueue(KC_LEFT);
      break;
     case FF_TEXT:
     addKeycodeToQueue(KC_LALT);
     addStringToQueue("rff"); 
     addKeycodeToQueue(KC_LEFT);
     addKeycodeToQueue(KC_ENTER);
      break;
     case IN_R:
     addStringToQueue("%in%");
      break;
     case LARW_L:
     addStringToQueue("<-");
      break;
     case LARW_R:
     addStringToQueue("->");
      break;
     break;
     case IPADDR:
     addStringToQueue("192.168.1.");
      break;
     break;
     case SMILE:
     addStringToQueue(":)");
      break;
     break;
     case IPSUM:
     addStringToQueue("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
     break;
     case GITCOMMIT:
      addStringToQueue("git add .");
      addKeycodeToQueue(KC_ENTER);
      addStringToQueue("git commit -m \"\""); 
      addKeycodeToQueue(KC_LEFT);
     break;
 }
}