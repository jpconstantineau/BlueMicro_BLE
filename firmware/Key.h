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
#include "KeyState.h"
#include "advanced_keycodes.h"
#include "hid_keycodes.h"
#include <array>
#include <utility>

#ifndef KEY_H
#define KEY_H

#define MAX_NO_LAYERS 10 //6

using ActArray = std::array<std::array<uint16_t, 5>, MAX_NO_LAYERS>;
using DurArray = std::array<std::array<Duration, 5>, MAX_NO_LAYERS>;

class Key {
    public:
    // cppcheck-suppress noExplicitConstructor     // cannot make this an explicit constructor as we are relying on conversion of keycodes to uint32_t
        Key(uint32_t activation);

        void press(unsigned long currentMillis);
        void clear(unsigned long currentMillis);
        void addActivation(const uint8_t layer, const Method method, const uint32_t activation);
        std::pair<uint16_t, Duration> getActiveActivation(uint8_t layer);

    private:
        Method lastMethod;
        std::pair<uint16_t, Duration> lastActivation;
        KeyState state;

        ActArray activations;
        DurArray durations;
};

#endif /* KEY_H */
