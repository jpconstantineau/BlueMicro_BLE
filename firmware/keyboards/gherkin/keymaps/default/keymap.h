/*
Copyright 2018 <Pierre Constantineau>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#ifndef KEYMAP_H
#define KEYMAP_H
#include <stdint.h>
#include "hid_keycodes.h"
#include "keyboard_config.h"
#include "advanced_keycodes.h"
#include "Key.h"
#include "KeyScanner.h"
#include <array>



#define KC_CAP_D MOD(MOD_LSHIFT, KC_D)

#define _QWERTY 0
#define _L1  1
#define _L2  2
#define _L3  3
#define _L4  4
#define _L5  5
#define _L6  6



#define FN1_SPC      XXXXXXX
#define FN1_SPC_TAP  KC_SPC
#define FN1_SPC_HOLD (LAYER_1)

#define FN2_BSPC       XXXXXXX
#define FN2_BSPC_TAP   KC_BSPC
#define FN2_BSPC_HOLD  (LAYER_2)

#define FN3_C        XXXXXXX
#define FN3_C_TAP    KC_C
#define FN3_C_HOLD   (LAYER_3)

#define FN4_V        XXXXXXX
#define FN4_V_TAP      KC_V
#define FN4_V_HOLD    (LAYER_4)

#define FN5_B         XXXXXXX
#define FN5_B_TAP     KC_B
#define FN5_B_HOLD    (LAYER_5)

#define CTL_Z         XXXXXXX
#define CTL_Z_TAP     KC_Z
#define CTL_Z_HOLD    (KC_LCTRL)

#define ALT_X         XXXXXXX
#define ALT_X_TAP     KC_X
#define ALT_X_HOLD    (KC_LALT)

#define ALT_N         XXXXXXX
#define ALT_N_TAP     KC_N
#define ALT_N_HOLD   ( KC_RALT)

#define CTL_M        XXXXXXX
#define CTL_M_TAP    KC_M
#define CTL_M_HOLD   (KC_RCTRL)

#define SFT_ENT       XXXXXXX
#define SFT_ENT_TAP   KC_ENT
#define SFT_ENT_HOLD  (KC_RSHIFT)


void setupKeymap();
extern std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix;


#define USER_MACRO_FUNCTION   0 

#define HOME_ADD MC(KC_A)
#define WORK_ADD MC(KC_B)
#define EMAIL_1  MC(KC_C)
#define EMAIL_2  MC(KC_D)
#define NAME_1   MC(KC_E)
#define NAME_2   MC(KC_F)
#define NAME_3   MC(KC_G)
#define CBR_FN   MC(KC_H)
#define BRC_FN   MC(KC_I)
#define PRN_FN   MC(KC_J)
#define TAB_DOWN_RTRN MC(KC_K)
#define TAB_UP_RTRN MC(KC_L)
#define PHONE_1  MC(KC_M)
#define PHONE_2  MC(KC_N)
#define INOWORD  MC(KC_O)
#define FOREXMPL MC(KC_P)
#define FF_TEXT  MC(KC_Q)
#define IN_R     MC(KC_R)
#define LARW_L   MC(KC_S)
#define LARW_R   MC(KC_T)
#define IPADDR   MC(KC_U)
#define SMILE    MC(KC_V)
#define IPSUM    MC(KC_W)
#define GITCOMMIT MC(KC_X)

void process_user_macros(uint16_t macroid);
extern void addStringToQueue(const char* str);
extern void addKeycodeToQueue(const uint16_t keycode);
#endif /* KEYMAP_H */


