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
#include <stdint.h>
#include "hid_keycodes.h"
#include "keyboard_config.h"
#include "advanced_keycodes.h"
#include "Key.h"
#include <array>
#ifndef KEYMAP_H
#define KEYMAP_H

#define QWERTY  LAYER_0
#define LOWER   LAYER_1
#define RAISE   LAYER_2
#define ADMIN   LAYER_3
#define _______ KC_TRNS

#define KC_EXLM MOD(MOD_LSHIFT, KC_1)
#define KC_AT MOD(MOD_LSHIFT, KC_2)
#define KC_HASH MOD(MOD_LSHIFT, KC_3)
#define KC_DLR MOD(MOD_LSHIFT, KC_4)
#define KC_PERC MOD(MOD_LSHIFT, KC_5)
#define KC_CIRC MOD(MOD_LSHIFT, KC_6)
#define KC_AMPR MOD(MOD_LSHIFT, KC_7)
#define KC_ASTR MOD(MOD_LSHIFT, KC_8)
#define KC_LPRN MOD(MOD_LSHIFT, KC_9)
#define KC_RPRN MOD(MOD_LSHIFT, KC_0)
#define KC_LCBR MOD(MOD_LSHIFT, KC_LBRC)
#define KC_RCBR MOD(MOD_LSHIFT, KC_RBRC)
#define KC_UNDS MOD(MOD_LSHIFT, KC_MINS)
#define KC_PLUS MOD(MOD_LSHIFT, KC_EQL)
#define KC_TILD MOD(MOD_LSHIFT, KC_GRV)
#define KC_PIPE MOD(MOD_LSHIFT, KC_BSLS)

#define _QWERTY  0
#define _LOWER   1
#define _RAISE   2
#define _ADMIN   3

void setupKeymap();
extern std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix;

#endif
