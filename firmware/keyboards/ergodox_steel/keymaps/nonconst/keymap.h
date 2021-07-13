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
#include <stdint.h>
#include "hid_keycodes.h"
#include "keyboard_config.h"
#include "advanced_keycodes.h"
#include "Key.h"
#include <array>
#include <vector>
#include <tuple>

#ifndef KEYMAP_H
#define KEYMAP_H

#define KC_CAP_D MOD(MOD_LSHIFT, KC_D)
#define NUM_LAYERS 2

#define _QWERTY 0
#define _L1  1

using layer_t = std::array<std::array<uint32_t, MATRIX_COLS>, MATRIX_ROWS>;
using main_layer_t = std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS>;

extern std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix;

inline void addLayers(const std::vector<std::tuple<uint8_t, Method, layer_t>>& layers) 
{
    for (int row = 0; row < MATRIX_ROWS; ++row)
    { 
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            for (const auto& t : layers) 
            {
                matrix[row][col].addActivation(std::get<0>(t), std::get<1>(t), 
                        std::get<2>(t)[row][col]);
            }
        }
    }
}


void setupKeymap();

#endif /* KEYMAP_H */
