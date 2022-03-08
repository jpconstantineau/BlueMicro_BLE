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
#include <bluemicro_hid.h>
#include <stdint.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include "hid_keycodes.h"
#include "advanced_keycodes.h"
#include "keymap.h"


typedef std::vector <uint16_t> trigger_keycodes_t;
typedef std::pair <trigger_keycodes_t , uint16_t> combo_t;
typedef std::vector < combo_t > combolist_t;

typedef std::pair <trigger_keycodes_t , trigger_keycodes_t> subst_t;
typedef std::vector < subst_t > substlist_t;

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

#define COMB(name, key, ...) combos.addComboToList(trigger_keycodes_t {__VA_ARGS__}, key);

//SUBS(substitution_test,       "I'd just like to interject for a moment.",       KC_H, KC_J, KC_K, KC_L);
#define SUBS(name, stringtosend, ...) combos.addSubstitutionToList(trigger_keycodes_t {__VA_ARGS__},  stringtosend);

//KEYS(keys_hello_world_test, {KC_H, KC_E, KC_L, KC_L, KC_O, KC_SPC, KC_W, KC_O, KC_R, KC_L, KC_D}, KC_A, KC_R, KC_T, KC_S)
#define KEYS(name, keycodestosend, ...) combos.addKeycodeStringToList(trigger_keycodes_t {__VA_ARGS__},  trigger_keycodes_t keycodestosend);

class ComboEngine {
    public:
    ComboEngine();
    void addComboToList(trigger_keycodes_t trigger, uint16_t keycode);
    void addSubstitutionToList(trigger_keycodes_t trigger,char* stringtosend);
    void addKeycodeStringToList(trigger_keycodes_t trigger, trigger_keycodes_t keycodestosend);
    void addKeycodeStringToBuffer(trigger_keycodes_t keycodestosend);
    void clearLists();
    bool anyCombosConfigured();
    bool anySubstConfigured();
    bool anyMacrosConfigured();
    bool anyMacrosActive(trigger_keycodes_t activekeycodes);
    uint8_t findActiveCombos(trigger_keycodes_t activekeycodes);
    uint8_t countActiveCombosKeys(trigger_keycodes_t activekeycodes);
    trigger_keycodes_t processActiveKeycodewithCombos(trigger_keycodes_t activekeycodes);
    trigger_keycodes_t convertCStrToKeycodeVector(char* stringtoconvert);
    trigger_keycodes_t processActiveKeycodewithComboKeys(trigger_keycodes_t activekeycodes);
    trigger_keycodes_t processActiveMacros(trigger_keycodes_t activekeycodes);

    trigger_keycodes_t keycodebuffertosend;

    private:
    combo_t findLargestCombo();
    subst_t findLargestSubst();

    combolist_t combolist; // multi-key swap
    combolist_t monolist;  // single-key swap
    substlist_t substlist; // multi-key macro
    substlist_t macrolist; // single-key macro
    trigger_keycodes_t keycodesused_multi; //keys used for multi
    trigger_keycodes_t keycodesused_single; //keys used for single
    combolist_t activecombos;
    substlist_t activesubst;
    substlist_t activemacro;
    uint8_t activecomboscount;
    uint8_t activesubstcount;
    uint8_t activemacrocount;

    bool activemacrosent;
};

#ifdef ENABLE_COMBOS
   extern ComboEngine combos;
#endif


#endif 
