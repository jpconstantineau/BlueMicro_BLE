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



#define  _QWERTY 0
#define  _LOWER 1
#define  _RAISE 2
#define _ADJUST 3  // _LOWER + _RAISE
#define _EXTRAL 4  //  
#define _EXTRAR 5  // 
#define _MACROL 6  // _LOWER + _EXTRAL
#define _MACROR 7  // _RAISE + _EXTRAR
#define _MACRO 8  // _EXTRAL + _EXTRAR


#define L_QWERTY   (LAYER_0 + _QWERTY)
#define L_LOWER    (LAYER_0 + _LOWER)
#define L_RAISE    (LAYER_0 + _RAISE)
#define L_ADJUST   (LAYER_0 + _ADJUST)
#define L_EXTRAL   (LAYER_0 + _EXTRAL) 
#define L_EXTRAR   (LAYER_0 + _EXTRAR) 
#define L_MACROL   (LAYER_0 + _MACROL)
#define L_MACROR   (LAYER_0 + _MACROR)
#define L_MACRO    (LAYER_0 + _MACRO)


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

#endif /* KEYMAP_H */