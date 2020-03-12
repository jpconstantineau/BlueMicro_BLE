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
        {KC_TAB,    KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,      TD_Y_AMPR,KC_U,   KC_I,    KC_O,    KC_P,         KC_BSPACE,},
        {CTRLESC,   KC_A,    KC_S,    KC_D,   KC_F,    KC_G,      KC_H,     KC_J,   KC_K,    KC_L,    TD_SCLN_MINS, KC_ENT,},
        {SFTSLSH,   KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,      KC_N,     KC_M,   KC_COMMA,KC_DOT,  KC_UP,        SHIFTL,},
        {KC_GESC,   EXTRA,   KC_LGUI, KC_LALT,L_LOWER, MACRODEL,  KC_SPC,   L_RAISE,KC_RALT, KC_LEFT, KC_DOWN,      KC_RIGHT}
    }};

 
void setupKeymap() {
   
    uint32_t qwerty_tap[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TD_Y_AMPR_TAP, XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, TD_SCLN_MINS_TAP, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX);

    uint32_t qwerty_dtap[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TD_Y_AMPR_DTAP, XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,           XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX, TD_SCLN_MINS_DTAP, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,           XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,           XXXXXXX);

    uint32_t qwerty_taph[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX,
        CTRLESC_TAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX,
        SFTSLSH_TAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MACRODEL_TAP, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX);

    uint32_t qwerty_hold[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX,
        CTRLESC_HOLD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX,
        SFTSLSH_HOLD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MACRODEL_HOLD, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX);    

    uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,        KC_9,          KC_0,    TD_MINS_UNDS, KC_EQL,
            CTRLESC, KC_VOLD, KC_VOLU, KC_MUTE, ENOTE3, ENOTE1, ENOTE1, KC_LEFT, KC_UP, KC_DOWN,   KC_RGHT, KC_BSLS,
            KC_LSFT, _______, KC_CUT, KC_COPY, KC_PASTE, ENOTE2, ENOTE2,  _______, TD_LBRC_LCBR, TD_RBRC_RCBR,  KC_PLUS, KC_RSFT,
            KC_GRV, _______, _______, _______, _______, _______, _______, _______,     KC_RALT,       KC_TILD, KC_MINS, KC_EQL);

    uint32_t lower_tap[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, TD_MINS_UNDS_TAP, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    TD_LBRC_LCBR_TAP,    TD_RBRC_RCBR_TAP, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX);

    uint32_t lower_dtap[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX, TD_MINS_UNDS_DTAP, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,           XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    TD_LBRC_LCBR_DTAP,    TD_RBRC_RCBR_DTAP, XXXXXXX,           XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,           XXXXXXX);


    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11,  KC_F12,
            CTRLESC,  KC_VOLD, KC_VOLU, KC_MUTE, ENOTE3, ENOTE1, ENOTE1, LCTL(KC_LEFT), LCTL(KC_UP),    LCTL(KC_DOWN),   LCTL(KC_RGHT), KC_BSLS,
            KC_LSFT, _______, KC_CUT, KC_COPY, KC_PASTE, ENOTE2, ENOTE2, _______, TD_LBRC_LCBR, TD_RBRC_RCBR, KC_PGUP, KC_RSFT,
            KC_GRV, _______, _______, _______, _______, _______, _______, _______, KC_RCTL,       KC_HOME,      KC_PGDN, KC_END);

    uint32_t raise_tap[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    TD_LBRC_LCBR_TAP,    TD_RBRC_RCBR_TAP, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX);

    uint32_t raise_dtap[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,           XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    TD_LBRC_LCBR_DTAP,    TD_RBRC_RCBR_DTAP, XXXXXXX,           XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,           XXXXXXX);

    uint32_t shift[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    RSFT(KC_TAB),  RSFT(KC_Q),    RSFT(KC_W),    RSFT(KC_E),    RSFT(KC_R),    RSFT(KC_T),    RSFT(KC_Y),   RSFT(KC_U),   RSFT(KC_I),    RSFT(KC_O),    RSFT(KC_P),    RSFT(KC_BSPC),
    RSFT(KC_LCTL), RSFT(KC_A),    RSFT(KC_S),    RSFT(KC_D),    RSFT(KC_F),    RSFT(KC_G),    RSFT(KC_H),   RSFT(KC_J),   RSFT(KC_K),    RSFT(KC_L),    RSFT(KC_SCLN), TD_QUOT_DQT,
    RSFT(KC_QUOT), RSFT(KC_Z),    RSFT(KC_X),    RSFT(KC_C),    RSFT(KC_V),    RSFT(KC_B),    RSFT(KC_N),   RSFT(KC_M),   TD_LPRN_LABK,  TD_RPRN_RABK,  RSFT(KC_SLSH), SHIFTL,
    _______,       _______,       RSFT(KC_LGUI), RSFT(KC_LALT), _______,      RSFT(KC_DEL),   RSFT(KC_SPC), _______,      _______,       RSFT(KC_LEFT), RSFT(KC_DOWN), RSFT(KC_RIGHT));

    uint32_t shift_tap[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          TD_QUOT_DQT_TAP,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    TD_LPRN_LABK_TAP,    TD_RPRN_RABK_TAP, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX);

    uint32_t shift_dtap[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,           XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,           TD_QUOT_DQT_DTAP,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    TD_LPRN_LABK_DTAP,    TD_RPRN_RABK_DTAP, XXXXXXX,           XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,           XXXXXXX);



    uint32_t adjust[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, TD_LPRN_LABK, TD_RPRN_RABK,  KC_UNDS, KC_PLUS,
            _______, _______, _______,  _______,   _______,  _______, _______, _______,  RGB_TOG,  RGB_MOD, RGB_HUI, RGB_HUD,
            KC_LSFT, _______,  _______,  _______,   _______,  _______,   _______,  _______, RGB_SAI,  RGB_SAD, RGB_VAI, KC_RSFT,
            RESET,   _______, _______, _______, _______, _______, _______, _______, _______,  BL_TOGG, BANDW,   HCNTRST);

    uint32_t adjust_tap[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    TD_LPRN_LABK_TAP,    TD_RPRN_RABK_TAP, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX);

    uint32_t adjust_dtap[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    TD_LPRN_LABK_DTAP,    TD_RPRN_RABK_DTAP, XXXXXXX,           XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,           XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,           XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,           XXXXXXX);



        uint32_t extra[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
            KC_ESC,  KC_NO,   KC_QUIT, KC_NO,   _______, KC_MINS, KC_7,    KC_8,    KC_9,     KC_INS,  KC_HOME, KC_PGUP, 
            _______, TAB_PRE, TAB_CLS, TAB_NXT, _______, KC_PLUS, KC_4,    KC_5,    KC_6,     KC_DEL,  KC_END,  KC_PGDN,
            KC_LSFT, KC_FBCK, TAB_RVS, KC_FFWD, _______, KC_NUBS, KC_1,    KC_2,    KC_3,     _______, KC_PLUS, KC_RSFT,
            KC_CAPS, _______, _______, _______, _______, _______, _______, KC_0,    KC_DOT,   KC_TILD, KC_MINS, KC_EQL);

    uint32_t macro[MATRIX_ROWS][MATRIX_COLS] =            // XXXXXXX = nothing    _______ = transparent = use lower layer keycode
        KEYMAP(
            PRINT_BATTERY, HOME_ADD, EMAIL_1,  NAME_1,  CBR_FN,  PHONE_1, TAB_DOWN_RTRN, INOWORD,  IN_R,      IPADDR,     SMILE,     IPSUM ,
            PRINT_INFO   , WORK_ADD, EMAIL_2,  NAME_2,  BRC_FN,  PHONE_2, TAB_UP_RTRN,   FOREXMPL, XXXXXXX,   XXXXXXX,    XXXXXXX,   XXXXXXX,
            XXXXXXX      , XXXXXXX,  XXXXXXX,  NAME_3,  PRN_FN,  XXXXXXX, XXXXXXX,       FF_TEXT,  XXXXXXX,   LARW_L,     LARW_R,    XXXXXXX,
            XXXXXXX      , XXXXXXX,  XXXXXXX,  XXXXXXX, L_LOWER, XXXXXXX, XXXXXXX,       L_RAISE,  XXXXXXX,   XXXXXXX,    XXXXXXX,   XXXXXXX);

    /*
     * add the other layers
     */
 
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_QWERTY, Method::MT_TAP,  qwerty_taph[row][col]);
            matrix[row][col].addActivation(_QWERTY, Method::MT_HOLD, qwerty_hold[row][col]);
            matrix[row][col].addActivation(_QWERTY, Method::DT_TAP,  qwerty_tap[row][col]);
            matrix[row][col].addActivation(_QWERTY, Method::DT_DOUBLETAP, qwerty_dtap[row][col]);

            matrix[row][col].addActivation(_LOWER,  Method::PRESS,   lower[row][col]);
            matrix[row][col].addActivation(_LOWER,  Method::DT_TAP,  lower_tap[row][col]);
            matrix[row][col].addActivation(_LOWER,  Method::DT_DOUBLETAP, lower_dtap[row][col]);

            matrix[row][col].addActivation(_RAISE,  Method::PRESS,   raise[row][col]);
            matrix[row][col].addActivation(_RAISE,  Method::DT_TAP,  raise_tap[row][col]);
            matrix[row][col].addActivation(_RAISE,  Method::DT_DOUBLETAP, raise_dtap[row][col]);

            matrix[row][col].addActivation(_ADJUST, Method::PRESS,  adjust[row][col]);
            matrix[row][col].addActivation(_ADJUST, Method::DT_TAP,  adjust_tap[row][col]);
            matrix[row][col].addActivation(_ADJUST, Method::DT_DOUBLETAP,  adjust_dtap[row][col]);

            matrix[row][col].addActivation(_EXTRA,  Method::PRESS,   extra[row][col]);

            matrix[row][col].addActivation(_SHIFT,  Method::PRESS,   shift[row][col]);
            matrix[row][col].addActivation(_SHIFT,  Method::DT_TAP,  shift_tap[row][col]);
            matrix[row][col].addActivation(_SHIFT,  Method::DT_DOUBLETAP,  shift_dtap[row][col]);

            matrix[row][col].addActivation(_MACRO,  Method::PRESS,   macro[row][col]);
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


void process_user_layers(uint16_t layermask)
{
    KeyScanner::process_for_tri_layers(_LOWER, _RAISE, _ADJUST);
}