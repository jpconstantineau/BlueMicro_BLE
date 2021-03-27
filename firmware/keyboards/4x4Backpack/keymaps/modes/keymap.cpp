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

#define EMPTYROW { KC_NO, KC_NO, KC_NO, KC_NO }
#define EMPTYKEYMAP {{ EMPTYROW, EMPTYROW, EMPTYROW, EMPTYROW }}
#define SAVEANDREBOOT  keyboardstate.save2flash = true; keyboardstate.needReset = true;
      
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix = EMPTYKEYMAP;

void setupKeymapmode0() {

    uint32_t layer0[MATRIX_ROWS][MATRIX_COLS] = KEYMAP(
        KC_7,    KC_8,    KC_9,    KC_KP_SLASH,
        KC_4,    KC_5,    KC_6,    KC_KP_ASTERISK,
        KC_1,    KC_2,    KC_3,    KC_KP_MINUS,
        LAYER_1, KC_0,    KC_DOT,  KC_KP_PLUS);

    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] = KEYMAP(
        KC_HOME,    KC_UP,    KC_PGUP,    KC_ESCAPE,    
        KC_LEFT,    KC_NO,    KC_RIGHT,   KC_DELETE,  
        KC_END,     KC_DOWN,  KC_PGDN,    KC_KP_ENTER,    
        LAYER_1,    KC_INS,   GOTOMODE0,  GOTOMODE1);

    ADDLAYER(_L0, Method::PRESS , layer0);
    ADDLAYER(_L1, Method::PRESS , layer1);

}
 
void setupKeymapmode1() {
    
    uint32_t layer0[MATRIX_ROWS][MATRIX_COLS] = KEYMAP(
        GITCOMMIT,    CBR_FN,    KC_NO,    KC_NO,
        GITCOMMIT,    BRC_FN,    KC_UP,    KC_NO,
        GITCOMMIT,    PRN_FN,    KC_DOWN,    KC_NO,
        LAYER_1, KC_NO,    KC_NO,  KC_NO);

    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] = KEYMAP(
        KC_HOME,    KC_UP,    KC_PGUP,    KC_ESCAPE,    
        KC_LEFT,    KC_NO,    KC_RIGHT,   KC_DELETE,  
        KC_END,     KC_DOWN,  KC_PGDN,    KC_KP_ENTER,    
        LAYER_1,    KC_INS,   GOTOMODE0,  GOTOMODE1);

    ADDLAYER(_L0, Method::PRESS , layer0);
    ADDLAYER(_L1, Method::PRESS , layer1);
}

void setupKeymap() {

    switch (keyboardconfig.mode)
    {
    case 1:
        setupKeymapmode1();
        break;

    default:
        setupKeymapmode0();
        break;
    } 

}

void process_user_macros(uint16_t macroid)
{
    switch ((macroid))
    { 
        case GITCOMMIT:
            addStringToQueue("git add .");
            addKeycodeToQueue(KC_ENTER);
            addStringToQueue("git commit -m \"\""); 
            addKeycodeToQueue(KC_LEFT);
        break;
        case (CBR_FN):
            addStringToQueue("{}"); 
            addKeycodeToQueue(KC_LEFT);
        break;
        case (BRC_FN):
            addStringToQueue("[]");
            addKeycodeToQueue(KC_LEFT);
        break;
        case PRN_FN:
            addStringToQueue("()"); 
            addKeycodeToQueue(KC_LEFT);
        break;
        case GOTOMODE0:
            keyboardconfig.mode = 0;
            SAVEANDREBOOT;
        break;
        case GOTOMODE1:
            keyboardconfig.mode = 1;
            SAVEANDREBOOT;
        break;
    }
}

