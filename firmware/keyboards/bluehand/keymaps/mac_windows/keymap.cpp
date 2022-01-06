/*
Copyright 2018 <Pierre Constantineau>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include "keymap.h"

/*
Sample keymap demonstrating one firmware with mappings for macs and windows while also persisting the most recently used mode through device sleeps and restarts. 

There are a few different approachs for handling this, like having separate bluetooth profiles. 

This approach uses keyboardconfig to persist which mapping was used most recently. In order to use keyboard state add the following to keymap.h:
    extern PersistentState keyboardconfig;

In order to trigger saving of keyboardconfig, keyboardstate.save2flash must be triggered. keyboardstate Also needs to be included in keymap.h:
    extern DynamicState keyboardstate;
*/


std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {{
        KC_NO,    KC_NO,    KC_NO,    KC_NO,
        KC_NO,    KC_NO,    KC_NO,    KC_NO
    }};

//mac, LGUI=command
uint32_t layout_mac[MATRIX_ROWS][MATRIX_COLS] = {{
    LGUI(KC_A),    LGUI(KC_C),    LGUI(KC_V),    LGUI(KC_S),
    KC_NO,    KC_NO,    KC_NO,    MC_TOGGLE
}};

uint32_t layout_windows[MATRIX_ROWS][MATRIX_COLS] = {{
    LCTL(KC_A),    LCTL(KC_C),    LCTL(KC_V),    LCTL(KC_S),
    KC_NO,    KC_NO,    KC_NO,    MC_TOGGLE
}};

void setupKeymap() {
    pinMode(LED_G, OUTPUT);
    pinMode(LED_R, OUTPUT);
    activateLayout();
}

void process_user_macros(uint16_t macroid) {
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_R, LOW);

    switch(macroid) {
        case MC_TOGGLE: 
            keyboardconfig.mode = (keyboardconfig.mode == 1) ? 0 : 1;
            keyboardstate.save2flash = true;
            activateLayout();
        break;
    }
}

void activateLayout() {
    bool isMacMode = keyboardconfig.mode == 1;
    uint32_t (&layout)[MATRIX_ROWS][MATRIX_COLS] = (isMacMode ? layout_mac : layout_windows);

    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_L0, Method::PRESS, layout[row][col]);
        }
    }

    //alternate LEDs, red for mac mode, green for windows
    digitalWrite(LED_G, (isMacMode ? LOW : HIGH));
    digitalWrite(LED_R, (isMacMode ? HIGH : LOW));
}