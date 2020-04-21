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
        KC_4,  KC_5,    KC_6
    )};

void setupKeymap() {

   // no layers for master keymap
   // this is a keymap that's used for testing that each key is responding properly to key presses
   // flash this keymap to both left and right to test whether each half works properly.
   // once tested, you can flash the left and right to their respective halves.

}
#endif


#if KEYBOARD_SIDE == LEFT



std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  
        KC_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  
        KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  
                                  L_EXTRAL, L_LOWER,   KC_SPC
    )};

 
void setupKeymap() {


    uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        KC_GRAVE,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,  \
        KC_DEL  ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,    \
        KC_LSFT ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,   \
                                  L_EXTRAL, L_LOWER, KC_SPC \
        );

    uint32_t extral[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  \
        KC_ESC,    LCTL(KC_A),    KC_S,    KC_D,    KC_F,    KC_G,  \
        KC_LSFT,   LCTL(KC_Z),    LCTL(KC_X),    LCTL(KC_C),    LCTL(KC_V),    LCTL(KC_B),  \
                                    L_EXTRAL, L_LOWER, KC_SPC \
        );

 
    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,  \
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    \
        KC_LSFT ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11 , \
                                 L_EXTRAL, L_LOWER, KC_SPC \
        );

 
 uint32_t extrar[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        LALT(KC_TAB),   KC_Q,          KC_W,    KC_E,    KC_R,    KC_T,  \
        KC_ESC,         LALT(KC_A),    KC_S,    KC_D,    KC_F,    KC_G,  \
        KC_LSFT,        LALT(KC_Z),    LALT(KC_X),    LALT(KC_C),    LALT(KC_V),    LALT(KC_B),  \
                                         L_EXTRAL, L_LOWER, KC_SPC \
        );

    uint32_t adjust[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        XXXXXXX,XXXXXXX,RGB_TOG,RGB_HUI, RGB_SAI, RGB_VAI,  \
        XXXXXXX,XXXXXXX,RGB_MOD,RGB_HUD, RGB_SAD, RGB_VAD,   \
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,  \
                                            L_EXTRAL, L_LOWER,KC_SPC \
        );


    uint32_t macrol[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, CBR_FN, XXXXXXX,  \
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, BRC_FN, XXXXXXX,    \
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, PRN_FN, XXXXXXX,  \
                                L_EXTRAL, L_LOWER,KC_SPC \
        );
    uint32_t macror[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,  \
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,    \
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,  \
                                    L_EXTRAL, L_LOWER,KC_SPC \
    );

    uint32_t macro[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
    PRINT_BATTERY,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,  \
    PRINT_INFO,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   \
    RESET,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,   SERIAL_DFU,  \
                                    L_EXTRAL, L_LOWER,KC_SPC \
);

    /*
     * add the other layers on the regular presses.
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_LOWER,  Method::PRESS,   lower[row][col]);
            matrix[row][col].addActivation(_RAISE,  Method::PRESS,   raise[row][col]);
            matrix[row][col].addActivation(_ADJUST, Method::PRESS,  adjust[row][col]);
            matrix[row][col].addActivation(_EXTRAL, Method::PRESS,  extral[row][col]);
            matrix[row][col].addActivation(_EXTRAR, Method::PRESS,  extrar[row][col]);
            matrix[row][col].addActivation(_MACROL, Method::PRESS,  macrol[row][col]);
            matrix[row][col].addActivation(_MACROR, Method::PRESS,  macror[row][col]);
            matrix[row][col].addActivation(_MACRO,  Method::PRESS,   macro[row][col]);
        }
    }

    // if you want to add Tap/Hold or Tap/Doubletap activations, then you add them below.

}

#endif  // left



#if KEYBOARD_SIDE == RIGHT


std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_BSPACE, 
        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCOLON, KC_QUOTE,
        KC_N,    KC_M,    KC_COMMA,KC_DOT,  KC_SLSH,   KC_ENT,
        KC_SPC,  L_RAISE, L_EXTRAR
    )};

 

void setupKeymap() {

    uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        KC_6,    KC_7,    KC_8,    KC_9,     KC_0,      KC_DEL,  \
        KC_F6,   KC_MINS, KC_EQL,  KC_LBRC,  KC_RBRC,   KC_BSLS,   \
        KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,   _______,  \
        KC_SPC,   L_RAISE, L_EXTRAR\
    );

    uint32_t extral[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        _______,  _______, _______, _______,  _______,   _______,  \
        _______,  _______, _______, _______,  _______,   _______,   \
        _______,  _______, _______, _______,  _______,   _______,  \
         KC_SPC,   L_RAISE, L_EXTRAR\
    );

    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,  \
        KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,   \
        KC_F12,  KC_NUTL, KC_NUPI,_______, _______, _______,  \
        KC_SPC,  L_RAISE, L_EXTRAR \
    );

    uint32_t extrar[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        _______,  _______, _______, _______,  _______,   _______,  \
        _______,  _______, _______, _______,  _______,   _______,   \
        _______,  _______, _______, _______,  _______,   _______,  \
        KC_SPC,   L_RAISE, L_EXTRAR\
    );

    uint32_t adjust[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        SERIAL_DFU,XXXXXXX,RGB_TOG,RGB_HUI, RGB_SAI, RGB_VAI,  \
        XXXXXXX,XXXXXXX,RGB_MOD,RGB_HUD, RGB_SAD, RGB_VAD,   \
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,  \
        KC_SPC,   L_RAISE,  L_EXTRAR \
    );

    uint32_t macrol[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,  \
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,   \
        XXXXXXX,XXXXXXX, KC_LEFT, KC_DOWN,  KC_UP,     KC_RIGHT,  \
         KC_SPC,      L_RAISE,    L_EXTRAR \
    );

    uint32_t macror[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        KC_VOLU,  KC_MSEL, KC_WWW, KC_CALC,  KC_MYCM,    XXXXXXX,  \
        KC_VOLD,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   \
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,  \
        KC_SPC,      L_RAISE,    L_EXTRAR \
    );

    uint32_t macro[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
        XXXXXXX,  XXXXXXX,    XXXXXXX,   XXXXXXX,  XXXXXXX,    PRINT_BATTERY,  \
        XXXXXXX,  XXXXXXX,    XXXXXXX,   XXXXXXX,  XXXXXXX,    PRINT_INFO,   \
        SERIAL_DFU,  XXXXXXX, XXXXXXX,   XXXXXXX,  XXXXXXX,    RESET,  \
        KC_SPC,      L_RAISE,    L_EXTRAR \
    );

    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_LOWER,  Method::PRESS,   lower[row][col]);
            matrix[row][col].addActivation(_RAISE,  Method::PRESS,   raise[row][col]);
            matrix[row][col].addActivation(_ADJUST, Method::PRESS,  adjust[row][col]);
            matrix[row][col].addActivation(_EXTRAL, Method::PRESS,  extral[row][col]);
            matrix[row][col].addActivation(_EXTRAR, Method::PRESS,  extrar[row][col]);
            matrix[row][col].addActivation(_MACROL, Method::PRESS,  macrol[row][col]);
            matrix[row][col].addActivation(_MACROR, Method::PRESS,  macror[row][col]);
            matrix[row][col].addActivation(_MACRO,  Method::PRESS,   macro[row][col]);
        }
    }

}


#endif



/*
void setupKeymap() {
   

    uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
        _______, _______, _______, _______, L_LOWER, _______, _______, L_RAISE,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY);

    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, L_LOWER, _______, _______, L_RAISE, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY);

    uint32_t adjust[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    _______, RESET,   _______,  RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI,   RGB_SAD,    RGB_VAI,   RGB_VAD,   KC_DEL ,
    _______, _______, _______,  _______, _______, _______, _______, KM_QWERTY, KM_COLEMAK, KM_DVORAK, KM_PLOVER, _______,
    _______, _______, _______,  _______, _______, _______, _______, _______,   _______,    _______,   _______,   _______,
    _______, _______, _______,  _______, L_LOWER, _______, _______, L_RAISE,   _______,    _______,   _______,   _______);

    uint32_t macro[MATRIX_ROWS][MATRIX_COLS] =            // XXXXXXX = nothing    _______ = transparent = use lower layer keycode
        KEYMAP(
    PRINT_BATTERY, HOME_ADD, EMAIL_1,  NAME_1,  CBR_FN,  PHONE_1, TAB_DOWN_RTRN, INOWORD,  IN_R,      IPADDR,     SMILE,     IPSUM ,
    PRINT_INFO   , WORK_ADD, EMAIL_2,  NAME_2,  BRC_FN,  PHONE_2, TAB_UP_RTRN,   FOREXMPL, XXXXXXX,   XXXXXXX,    XXXXXXX,   XXXXXXX,
    XXXXXXX      , XXXXXXX,  XXXXXXX,  NAME_3,  PRN_FN,  XXXXXXX, XXXXXXX,       FF_TEXT,  XXXXXXX,   LARW_L,     LARW_R,    XXXXXXX,
    L_MACRO      , XXXXXXX,  XXXXXXX,  XXXXXXX, L_LOWER, XXXXXXX, XXXXXXX,       L_RAISE,  KM_QWERTY, KM_COLEMAK, KM_DVORAK, KM_PLOVER);



}
*/

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
    KeyScanner::process_for_tri_layers(_LOWER, _RAISE,  _ADJUST);
    KeyScanner::process_for_tri_layers(_LOWER, _EXTRAL, _MACROL);  
    KeyScanner::process_for_tri_layers(_RAISE, _EXTRAR, _MACROR);
    KeyScanner::process_for_tri_layers(_EXTRAL,_EXTRAR, _MACRO );
}