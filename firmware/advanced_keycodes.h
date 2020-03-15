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

#define BIT_LCTRL (1)
#define BIT_LSHIFT (2 << 8)
#define BIT_LALT (4 << 8)
#define BIT_LGUI (8 << 8)
#define BIT_RCTRL (16 << 8)
#define BIT_RSHIFT (32 << 8)
#define BIT_RALT (64 << 8)
#define BIT_RGUI (128 << 8)

#define MOD_LCTRL (BIT_LCTRL << 8)
#define MOD_LSHIFT (BIT_LSHIFT << 8)
#define MOD_LALT (BIT_LALT << 8)
#define MOD_LGUI (BIT_LGUI << 8)
#define MOD_RCTRL (BIT_RCTRL << 8)
#define MOD_RSHIFT (BIT_RSHIFT << 8)
#define MOD_RALT (BIT_RALT << 8)
#define MOD_RGUI (BIT_RGUI << 8)

#define MC(KC) (((uint16_t) KC << 8 ) | KC_RESERVED_A5 )             // move KC to upper 8 bits and use KC_RESERVED_A5 keycode for marking this as a macro.
#define KB(KC) (((uint16_t) KC << 8 ) | KC_RESERVED_A6 )             // move KC to upper 8 bits and use KC_RESERVED_A6 keycode for marking this as a special keyboard function.
#define MK(KC) (((uint16_t) KC << 8 ) | KC_RESERVED_A7 )             // move KC to upper 8 bits and use KC_RESERVED_A7 keycode for marking this as a media key.
#define MR(KC) (((uint16_t) KC << 8 ) | KC_RESERVED_A8 )             // move KC to upper 8 bits and use KC_RESERVED_A8 keycode for marking this as a repeating media key.
#define MS(KC) (((uint16_t) KC << 8 ) | KC_RESERVED_A9 )             // move KC to upper 8 bits and use KC_RESERVED_A9 keycode for marking this as a mouse key.
#define KS(KC) (((uint16_t) KC << 8 ) | KC_RESERVED_AA )             // move KC to upper 8 bits and use KC_RESERVED_AA keycode for marking this as a special key.
#define TG(KC) ((static_cast<int>(Duration::TOGGLE) << 16) | KC)
#define OS(KC) ((static_cast<int>(Duration::ONE_SHOT) << 16) | KC)
#define MAC(KC) ((static_cast<int>(Duration::ONE_SHOT) << 16) |  (KC << 8 ) | KC_RESERVED_A5)
#define S(KC) MOD(MOD_LSHIFT, KC)

#define SEND_KC(KC) (static_cast<uint8_t>(KC & 0x00FF))

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
#define KC_DQT  KC_DQUO

#define KC_LT   MOD(MOD_LSHIFT, KC_COMMA)
#define KC_GT   MOD(MOD_LSHIFT, KC_DOT)
#define KC_QUES MOD(MOD_LSHIFT, KC_SLASH)

#define KC_NUTL MOD(MOD_LSHIFT,KC_NUHS) // Non-US # and ~
#define KC_NUPI MOD(MOD_LSHIFT,KC_NUBS) // Non-US \ and |

#define LALT(KEY) MOD(MOD_LALT, KEY)
#define RALT(KEY) MOD(MOD_RALT, KEY)
#define LCTL(KEY) MOD(MOD_LCTRL, KEY)
#define RCTL(KEY) MOD(MOD_RCTRL, KEY)
#define RSFT(KEY) MOD(MOD_RSHIFT, KEY)
#define LSFT(KEY) MOD(MOD_LSHIFT, KEY)
#define LGUI(KEY) MOD(MOD_LGUI, KEY)
#define RGUI(KEY) MOD(MOD_RGUI, KEY)


#endif
