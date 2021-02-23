/*
Copyright 2021-2021 <Pierre Constantineau, Julian Komaromy>

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
#ifndef COMBO_ENGINE_H
#define COMBO_ENGINE_H
#include <stdint.h>
#include <vector>
#include <utility>
#include <algorithm>



typedef std::vector <uint16_t> trigger_keycodes_t;
typedef std::pair <trigger_keycodes_t , uint16_t> combo_t;
typedef std::vector < combo_t > combolist_t;

template <typename T>
bool IsSubset(std::vector<T> A, std::vector<T> B)
{
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    return std::includes(A.begin(), A.end(), B.begin(), B.end());
}

template <typename T>
bool IsSubsetPreSorted(std::vector<T> A, std::vector<T> B)
{
    return std::includes(A.begin(), A.end(), B.begin(), B.end());
}

#define COMB(name, key, ...) combos.addComboToList(std::vector <uint16_t>{__VA_ARGS__}, key);

class ComboEngine {
    public:
    ComboEngine();
    void addComboToList(trigger_keycodes_t trigger, uint16_t keycode);
    void clearComboList();
    bool anyCombosConfigured();
    bool findActiveCombos(trigger_keycodes_t activekeycodes);
    trigger_keycodes_t processActiveKeycodewithCombos(trigger_keycodes_t activekeycodes);

    private:
    combo_t findLargestCombo();

    combolist_t combolist;
    combolist_t activecombos;
};


extern ComboEngine combos;

#endif 