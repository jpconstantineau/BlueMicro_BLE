/*
Copyright 2019-2020 <Pierre Constantineau>

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

#ifndef HARDWAREVARIANTS_H
#define HARDWAREVARIANTS_H
#include "datastructures.h"

// putting this here since it's called in every keyboard_config and we need this for all the keymaps.
// THIS FILE CONTAINS THE MACRO DEFINITIONS THAT USERS MAY USE IN THEIR keymap.cpp/h FILES.
// FOR DATASTRUCTURES USED BY USER FUNCTIONS, SEE datastructures.h

#define COL2ROW       0
#define ROW2COL       1

#define TEST 0
#define LEFT 1
#define RIGHT 2
#define SINGLE 3

#define KEYMAP2ARRAY(OTHERMACROHERE) {OTHERMACROHERE}
#define ADDLAYER(LAYER_INPUT,METHOD_INPUT,KEYMAP_INPUT )  for (int row = 0; row < MATRIX_ROWS; ++row) { for (int col = 0; col < MATRIX_COLS; ++col){ matrix[row][col].addActivation(LAYER_INPUT, METHOD_INPUT, KEYMAP_INPUT[row][col]);}}
#define _PINNUM(port, pin) ((port)*32 + (pin))
#endif  /*HARDWAREVARIANTS_H*/