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
#include "KeyScanner.h"
#include <array>

// Layers Definitions

#define  _QWERTY 0
#define  _LOWER 1
#define  _RAISE 2
#define _ADJUST 3
#define _EXTRA 4
#define _SHIFT 5
#define _MACRO 6

// Layers keycodes Definitions

#define L_QWERTY   (LAYER_0 + _QWERTY)
#define L_LOWER    (LAYER_0 + _LOWER)
#define L_RAISE    (LAYER_0 + _RAISE)
#define L_ADJUST   (LAYER_0 + _ADJUST)
#define L_EXTRA    (LAYER_0 + _EXTRA)
#define L_SHIFT    (LAYER_0 + _SHIFT)
#define L_MACRO    (LAYER_0 + _MACRO)

// Layers keycodes with oneshot Definitions

#define LOWER OS(L_LOWER)
#define RAISE OS(L_RAISE)
#define EXTRA OS(L_EXTRA)
#define SHIFTL OS(L_SHIFT)
#define MACRRO OS(L_MACRO)

// Modded keys definitions

#define ENOTE1 LALT(KC_7)
#define ENOTE2 LALT(KC_6)
#define ENOTE3 LALT(KC_2)
#define BANDW  LGUI(LCTL(KC_C))
#define HCNTRST LALT(LSFT(KC_PSCR))
#define KC_QUIT LALT(KC_F4) 
#define TAB_PRE LCTL(KC_PGUP)
#define TAB_NXT LCTL(KC_PGDN)
#define TAB_CLS LCTL(KC_W)
#define TAB_RVS LCTL(LSFT(KC_T))
#define KC_FBCK LALT(KC_LEFT)
#define KC_FFWD LALT(KC_RIGHT)

// tap/double-tap definitions

#define TD_Y_AMPR XXXXXXX //[TD_Y_AMPR]  = ACTION_TAP_DANCE_DOUBLE(KC_Y, KC_AMPR)
#define TD_Y_AMPR_TAP KC_Y //[TD_Y_AMPR]  = ACTION_TAP_DANCE_DOUBLE(KC_Y, KC_AMPR)
#define TD_Y_AMPR_DTAP KC_AMPR //[TD_Y_AMPR]  = ACTION_TAP_DANCE_DOUBLE(KC_Y, KC_AMPR)

#define TD_SCLN_MINS XXXXXXX //[TD_SCLN_MINS]  = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_MINS),
#define TD_SCLN_MINS_TAP KC_SCLN
#define TD_SCLN_MINS_DTAP KC_MINS

#define TD_MINS_UNDS XXXXXXX// ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS),
#define TD_MINS_UNDS_TAP KC_MINS
#define TD_MINS_UNDS_DTAP KC_UNDS
#define TD_LBRC_LCBR XXXXXXX// ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LCBR),
#define TD_LBRC_LCBR_TAP KC_LBRC
#define TD_LBRC_LCBR_DTAP KC_LCBR
#define TD_RBRC_RCBR XXXXXXX// ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RCBR),
#define TD_RBRC_RCBR_TAP KC_RBRC
#define TD_RBRC_RCBR_DTAP KC_RCBR
#define TD_LPRN_LABK XXXXXXX// ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_LABK),
#define TD_LPRN_LABK_TAP KC_LPRN
#define TD_LPRN_LABK_DTAP KC_LABK
#define TD_RPRN_RABK XXXXXXX// ACTION_TAP_DANCE_DOUBLE(KC_RPRN, KC_RABK)
#define TD_RPRN_RABK_TAP KC_RPRN
#define TD_RPRN_RABK_DTAP KC_RABK
#define TD_QUOT_DQT  XXXXXXX// ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQT),
#define TD_QUOT_DQT_TAP  KC_QUOT
#define TD_QUOT_DQT_DTAP  KC_DQT

// tap/hold definitions

#define CTRLESC XXXXXXX //#define CTRLESC MT(MOD_LCTL, KC_ESC)
#define CTRLESC_TAP KC_ESC //#define CTRLESC MT(MOD_LCTL, KC_ESC)
#define CTRLESC_HOLD KC_LCTL //#define CTRLESC MT(MOD_LCTL, KC_ESC)

#define SFTSLSH XXXXXXX //#define SFTSLSH MT(MOD_LSFT, KC_SLSH)
#define SFTSLSH_TAP KC_SLSH
#define SFTSLSH_HOLD KC_LSHIFT

#define MACRODEL XXXXXXX//#define MACRODEL LT(_MACRRO, KC_DEL)
#define MACRODEL_TAP  KC_DEL
#define MACRODEL_HOLD L_MACRO



#define KC_GESC XXXXXXX //KC_GESC  https://github.com/qmk/qmk_firmware/blob/master/docs/feature_grave_esc.md  TODO

// define macro hooks

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

#define USER_MACRO_FUNCTION   0 
void process_user_macros(uint16_t macroid);


#define USER_LAYER_FUNCTION   0 
void process_user_layers(uint16_t layermask);


void setupKeymap();
extern std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix;
extern void addStringToQueue(const char* str);
extern void addKeycodeToQueue(const uint16_t keycode);

#endif


