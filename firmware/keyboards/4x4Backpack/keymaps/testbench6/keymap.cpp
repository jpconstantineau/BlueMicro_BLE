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

// MACRO tests


std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {{
        {MC(KC_A),   MC(KC_B), KC_NO ,KC_NO  ,},
        {KC_NO,    KC_NO ,    KC_NO,   KC_NO,},
        {KC_NO,  KC_NO,   KC_NO,   KC_NO,},
        {LAYER_1,   KC_0,     KC_NO,    RESET}
    }};

 
void setupKeymap() {

    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
           KC_NO,   KC_NO,   MC(KC_C), MC(KC_D),
           KC_NO,     KC_NO,    KC_NO,   KC_NO,
           KC_NO,  KC_NO,   KC_NO,   KC_NO,  
           _______, KC_1,    KC_NO,  KC_NO );

    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_L1, Method::PRESS, layer1[row][col]);
        }
    }

}

void process_user_macros(uint32_t macroid)
{
 switch (macroid)
 {
     case MC(KC_A):
     addStringToQueue("Hello World!");
     break;
     case MC(KC_B):
     addStringToQueue("The quick brown fox jumps over the lazy dog!");
     break;
     case MC(KC_C):
     addStringToQueue("macro C works");
     break;
     case MC(KC_D):
     addStringToQueue("This is macro D");
     break;
 }
}

