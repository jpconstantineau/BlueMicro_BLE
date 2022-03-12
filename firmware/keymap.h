// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include <stdint.h>
#include "hid_keycodes.h"
#include "keyboard_config.h"
#include "advanced_keycodes.h"
#include "key.h"
#include <array>

#define ENABLE_AUDIO


#ifndef KEYMAP_H
#define KEYMAP_H

#define KC_CAP_D MOD(MOD_LSHIFT, KC_D)

#define _QWERTY 0
#define _L1  1
#define _L2  2
#define _L3  3

#define CBR_FN   MC(KC_H)
#define BRC_FN   MC(KC_I)
#define PRN_FN   MC(KC_J)
#define IPADDR   MC(KC_U)
#define SMILE    MC(KC_V)
#define GITCOMMIT MC(KC_X)
#define CHARGE    MC(KC_Y)
#define BIRTHDAY  MC(KC_Z)

#ifdef ENABLE_AUDIO
//todo re-install audio features as module
//extern BlueMicro_tone speaker; 
#endif

void setupKeymap();
extern std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix;

#define USER_MACRO_FUNCTION   0 
void process_user_macros(uint16_t macroid);

extern void addStringToQueue(const char* str);
extern void addKeycodeToQueue(const uint16_t keycode);

#endif /* KEYMAP_H */
