/*
Copyright 2018 <Pierre Constantineau, Julian Komaromy>

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
#include <cstdint>

#ifndef ADVANCED_KEYCODES_H
#define ADVANCED_KEYCODES_H

enum class Duration {
    MOMENTARY = 0,
    TOGGLE = 1,
    ONE_SHOT = 2,
};

#define MOD(M, KC) ((uint16_t) KC | (uint16_t) M)

#define MOD_LCTRL (1 << 8)
#define MOD_LSHIFT (2 << 8)
#define MOD_LALT (4 << 8)
#define MOD_LGUI (8 << 8)
#define MOD_RCTRL (16 << 8)
#define MOD_RSHIFT (32 << 8)
#define MOD_RALT (64 << 8)
#define MOD_RGUI (128 << 8)

#define TG(KC) ((static_cast<int>(Duration::TOGGLE) << 16) | KC)
#define OS(KC) ((static_cast<int>(Duration::ONE_SHOT) << 16) | KC)

#define S(KC) MOD(MOD_LSHIFT, KC)

// define any shift/ctl/alt key combinations
#define KC_TILD MOD(MOD_LSHIFT, KC_GRV)
#define KC_EXLM MOD(MOD_LSHIFT, KC_1)
#define KC_AT   MOD(MOD_LSHIFT, KC_2)
#define KC_HASH MOD(MOD_LSHIFT, KC_3)
#define KC_DLR  MOD(MOD_LSHIFT, KC_4)
#define KC_PERC MOD(MOD_LSHIFT, KC_5)
#define KC_CIRC MOD(MOD_LSHIFT, KC_6)
#define KC_AMPR MOD(MOD_LSHIFT, KC_7)
#define KC_ASTR MOD(MOD_LSHIFT, KC_8)
#define KC_LPRN MOD(MOD_LSHIFT, KC_9)
#define KC_RPRN MOD(MOD_LSHIFT, KC_0)
#define KC_UNDS MOD(MOD_LSHIFT, KC_MINUS)
#define KC_PLUS MOD(MOD_LSHIFT, KC_EQUAL)

#define KC_LCBR MOD(MOD_LSHIFT, KC_LBRC)
#define KC_RCBR MOD(MOD_LSHIFT, KC_RBRC)
#define KC_PIPE MOD(MOD_LSHIFT, KC_BSLS)

#define KC_COLN MOD(MOD_LSHIFT, KC_SCLN)
#define KC_DQUO MOD(MOD_LSHIFT, KC_QUOTE)

#define KC_LT   MOD(MOD_LSHIFT, KC_COMMA)
#define KC_GT   MOD(MOD_LSHIFT, KC_DOT)
#define KC_QUES MOD(MOD_LSHIFT, KC_SLASH)

#define KC_NUTL MOD(MOD_LSHIFT,KC_NUHS) // Non-US # and ~
#define KC_NUPI MOD(MOD_LSHIFT,KC_NUBS) // Non-US \ and |

#endif
