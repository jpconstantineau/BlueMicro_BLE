// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef HARDWAREVARIANTS_H
#define HARDWAREVARIANTS_H
#include "datastructures.h"

// putting this here since it's called in every keyboard_config and we need this for all the keymaps.
// THIS FILE CONTAINS THE MACRO DEFINITIONS THAT USERS MAY USE IN THEIR keymap.cpp/h FILES.
// FOR DATASTRUCTURES USED BY USER FUNCTIONS, SEE datastructures.h

#define NODIODES      0
#define COL2ROW       0  // TODO: add automatic selection of ANTI-GHOSTING...
#define ROW2COL       1

#define TEST 0
#define LEFT 1
#define RIGHT 2
#define SINGLE 3

#define KEYMAP2ARRAY(OTHERMACROHERE) {OTHERMACROHERE}
#define ADDLAYER(LAYER_INPUT,METHOD_INPUT,KEYMAP_INPUT )  for (int row = 0; row < MATRIX_ROWS; ++row) { for (int col = 0; col < MATRIX_COLS; ++col){ matrix[row][col].addActivation(LAYER_INPUT, METHOD_INPUT, KEYMAP_INPUT[row][col]);}}
#define _PINNUM(port, pin) ((port)*32 + (pin))
#endif  /*HARDWAREVARIANTS_H*/