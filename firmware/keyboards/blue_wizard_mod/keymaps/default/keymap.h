/*
Copyright (C) 2020, Jocelyn Turcotte <turcotte.j@gmail.com>

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
#define MAX_NO_LAYERS 4
#include "Key.h"
#include <array>

#ifndef KEYMAP_H
#define KEYMAP_H

#define _DVORAK 0 // Base Dvorak layer
#define _NUM 1 // Number Layer
#define _MEDIA 2  // Media layer
#define _GAME 3 // Game Layer

#define L_NUM (LAYER_0 + _NUM)
#define L_MEDIA (LAYER_0 + _MEDIA)
#define L_GAME (LAYER_0 + _GAME)

#define XXXXXXX KC_NO
#define _______ KC_TRNS
#define KC_ALLU LSFT(LCTL(KC_UP))
#define KC_ALLL LSFT(LCTL(KC_LEFT))
#define KC_ALLR LSFT(LCTL(KC_RIGHT))
#define KC_ALLD LSFT(LCTL(KC_DOWN))
#define KC_COPY LCTL(KC_C)
#define KC_PST LCTL(KC_V)
#define KC_CUT LCTL(KC_X)
#define KC_CALD LCTL(LALT(KC_DEL))
#define KC_WINL LGUI(KC_LEFT)		//Window Snap
#define KC_WINR LGUI(KC_RIGHT)
#define KC_WINU LGUI(KC_UP)
#define KC_WIND LGUI(KC_DOWN)
#define KC_VIRL LCTL(LGUI(KC_LEFT))	//Virtual Desktop
#define KC_VIRR LCTL(LGUI(KC_RIGHT))	//Virtual Desktop 
#define KC_LOCK LGUI(KC_L)
#define KC_PDFL LSFT(LCTL(KC_TAB))	//PDF Tab Switch
#define KC_PDFR LCTL(KC_TAB)
#define KC_CAW1 LCTL(LALT(LGUI(KC_1)))	// Move to monitor custom hotkey
#define KC_CAW2 LCTL(LALT(LGUI(KC_2)))
#define KC_CAW3 LCTL(LALT(LGUI(KC_3)))
#define KC_CAW4 LCTL(LALT(LGUI(KC_4)))
#define KC_CAW5 LCTL(LALT(LGUI(KC_5)))
#define KC_CAW6 LCTL(LALT(LGUI(KC_6)))
#define KC_CAW7 LCTL(LALT(LGUI(KC_7)))
#define KC_CAW8 LCTL(LALT(LGUI(KC_8)))
#define KC_CAW9 LCTL(LALT(LGUI(KC_9)))

void setupKeymap();
extern std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix;

#endif /* KEYMAP_H */
