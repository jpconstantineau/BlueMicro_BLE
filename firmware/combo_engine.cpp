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

// if you wonder about this std algorithmn black magic, see https://www.youtube.com/watch?v=bFSnXNIsK4A

#include "combo_engine.h"

ComboEngine combos;

ComboEngine::ComboEngine()
{
 combolist = {};
 activecombos = {};
 keycodesused = {};
}

void ComboEngine::addComboToList(trigger_keycodes_t trigger, uint16_t keycode)
{
  std::sort(trigger.begin(), trigger.end()); // pre-sorts before adding to combolist.
  combolist.push_back(make_pair(trigger, keycode));
  keycodesused.insert( keycodesused.end(), trigger.begin(), trigger.end());
  std::sort(keycodesused.begin(),keycodesused.end()); // needed for the next operation
  std::unique(keycodesused.begin(),keycodesused.end()); // keep the unique keycodes only
}

bool ComboEngine::anyCombosConfigured()
{
    return combolist.size()>0;
}

void ComboEngine::clearComboList()
{
   combolist.clear(); 
   keycodesused.clear();
}

uint8_t ComboEngine::findActiveCombos(trigger_keycodes_t activekeycodes)
{
    activecombos.clear();
    std::sort(activekeycodes.begin(), activekeycodes.end()); // include needs both to be sorted.
    std::copy_if (combolist.begin(), combolist.end(), std::back_inserter(activecombos), [activekeycodes] (combo_t combo){  return std::includes(activekeycodes.begin(),activekeycodes.end(), combo.first.begin(), combo.first.end() );}  ); 
    return activecombos.size();
}

uint8_t ComboEngine::countActiveCombosKeys(trigger_keycodes_t activekeycodes)
{
  trigger_keycodes_t keycodesusedbycombos = keycodesused;
  return std::count_if(activekeycodes.begin(), activekeycodes.end(), [keycodesusedbycombos] (uint16_t keycode){return (std::binary_search(keycodesusedbycombos.begin(),keycodesusedbycombos.end(),keycode));});
  
}

combo_t ComboEngine::findLargestCombo()
{
  combo_t it = *std::max_element(activecombos.begin(), activecombos.end(),[](combo_t comboa, combo_t combob){return (comboa.first.size() < combob.first.size());} ); 
  return  it;
}

trigger_keycodes_t ComboEngine::processActiveKeycodewithComboKeys(trigger_keycodes_t activekeycodes)
{
   trigger_keycodes_t keycodesusedbycombos = keycodesused;
   activekeycodes.erase(std::remove_if(activekeycodes.begin(), activekeycodes.end(), [keycodesusedbycombos] (uint16_t keycode){return (std::binary_search(keycodesusedbycombos.begin(),keycodesusedbycombos.end(),keycode));}),activekeycodes.end()); 
   return activekeycodes;
}

trigger_keycodes_t ComboEngine::processActiveKeycodewithCombos(trigger_keycodes_t activekeycodes)
{
    combo_t comboToUse = findLargestCombo();
    trigger_keycodes_t keycodesToRemove = comboToUse.first;
    uint16_t keycodeToAdd = comboToUse.second;

    activekeycodes.erase(std::remove_if(activekeycodes.begin(), activekeycodes.end(), [keycodesToRemove] (uint16_t keycode){return (std::binary_search(keycodesToRemove.begin(),keycodesToRemove.end(),keycode));}),activekeycodes.end()); 
    activekeycodes.push_back(keycodeToAdd);
    return activekeycodes;
}