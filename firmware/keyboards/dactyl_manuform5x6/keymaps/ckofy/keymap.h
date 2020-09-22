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
#include "hardware_variants.h"
#include "keyboard_config.h"
#include "advanced_keycodes.h"
#include "KeyScanner.h"
#include <array>

// Layers Definitions

#define _COLEMAK 0
#define _FOURTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
//#define _SHIFT 4
#define _MACRO 5

// Layers keycodes Definitions

#define L_COLEMAK  (LAYER_0 + _COLEMAK)
#define L_FOURTY (LAYER_0 + _FOURTY)
#define L_LOWER    (LAYER_0 + _LOWER)
#define L_RAISE    (LAYER_0 + _RAISE)
#define L_ADJUST   (LAYER_0 + _ADJUST)
//#define L_SHIFT    (LAYER_0 + _SHIFT)
#define L_MACRO    (LAYER_0 + _MACRO)


// Layers keycodes with oneshot Definitions
//#define SHIFTL OS(L_SHIFT)


#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_CUT  LCTL(KC_X)	// CUT
#define KC_CPY  LCTL(KC_C)	// COPY
#define KC_PST  LCTL(KC_V)	// PASTE
#define KC_UND  LCTL(KC_Z)	// UNDO
#define KC_REDO LCTL(KC_Y)	// REDO
#define KC_PRTN LCTL(KC_P)    // Print
#define KC_SVE  LCTL(KC_S)    // Save
#define KC_DUP  LCTL(KC_D)    // Duplicate line
#define KC_LOCK LGUI(KC_L)    // Lock

#define KC_BRK  LCTL(KC_B)    // LabVIEW remove broken wires
#define KC_SWP  LCTL(KC_E)    // LabVIEW show block diagram/show front panel

/*
#define KC_SETG MOD(MOD_LGUI, KC_I)		// Settings
#define KC_EXPL MOD(MOD_LGUI, KC_E)		// File Explorer
#define KC_DESK MOD(MOD_LGUI, KC_D)		// Desktop

#define KC_CMD  MOD(MOD_LGUI, KC_R)		// Command Prompt
#define KC_SRCH MOD(MOD_LGUI, KC_S)		// Search
#define KC_MINW MOD(MOD_LGUI, KC_DOWN)	// Minimize window
*/

// tap/double-tap definitions
#define TD_MINS_UNDS XXXXXXX// ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS),
#define TD_MINS_UNDS_TAP KC_MINS
#define TD_MINS_UNDS_DTAP KC_UNDS

// tap/hold definitions

#define SHESC XXXXXXX //#define SHESC MT(MOD_LSFT, KC_ESC)
#define SHESC_TAP KC_ESC 
#define SHESC_HOLD KC_LSHIFT 

#define SHENT XXXXXXX //#define SHEND MT(MOD_LSFT, KC_ENT)
#define SHENT_TAP KC_ENT 
#define SHENT_HOLD KC_LSHIFT 

// define macro hooks

#define KM_COLEMAK  MC(KC_1)
#define KM_FOURTY MC(KC_2)

#define HOME_ADD MC(KC_A)
#define WORK_ADD MC(KC_B)
#define EMAIL_1  MC(KC_C)
#define EMAIL_2  MC(KC_D)

#define USER_MACRO_FUNCTION   0 
void process_user_macros(uint16_t macroid);


#define USER_LAYER_FUNCTION   0 
void process_user_layers(uint16_t layermask);

void setupKeymap();
extern std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix;
extern void addStringToQueue(const char* str);
extern void addKeycodeToQueue(const uint16_t keycode);

#endif /* KEYMAP_H */
