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
 substlist = {};
 activecombos = {};
 activesubst = {};
 keycodesused = {};
 keycodebuffertosend = {};
}

void ComboEngine::clearLists()
{
   combolist.clear();
   substlist.clear(); 
   keycodesused.clear();
}

/**************************************************************************************************************************/
/* COMBOS BELOW...            */
/**************************************************************************************************************************/

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


uint8_t ComboEngine::findActiveCombos(trigger_keycodes_t activekeycodes)
{
    activecombos.clear();
    activesubst.clear();
    std::sort(activekeycodes.begin(), activekeycodes.end()); // include needs both to be sorted.
    std::copy_if (combolist.begin(), combolist.end(), std::back_inserter(activecombos), [activekeycodes] (combo_t combo){  return std::includes(activekeycodes.begin(),activekeycodes.end(), combo.first.begin(), combo.first.end() );}  ); 
    std::copy_if (substlist.begin(), substlist.end(), std::back_inserter(activesubst), [activekeycodes] (subst_t combo){  return std::includes(activekeycodes.begin(),activekeycodes.end(), combo.first.begin(), combo.first.end() );}  ); 
    activecomboscount = activecombos.size();
    activesubstcount = activesubst.size();
    return activecomboscount + activesubstcount;
}


uint8_t ComboEngine::countActiveCombosKeys(trigger_keycodes_t activekeycodes)
{
  trigger_keycodes_t keycodesusedbycombos = keycodesused; // this includes both combos and substs
  return std::count_if(activekeycodes.begin(), activekeycodes.end(), [keycodesusedbycombos] (uint16_t keycode){return (std::binary_search(keycodesusedbycombos.begin(),keycodesusedbycombos.end(),keycode));});
  
}


combo_t ComboEngine::findLargestCombo()
{
  combo_t it = *std::max_element(activecombos.begin(), activecombos.end(),[](combo_t comboa, combo_t combob){return (comboa.first.size() < combob.first.size());} ); 
  return  it;
}


trigger_keycodes_t ComboEngine::processActiveKeycodewithComboKeys(trigger_keycodes_t activekeycodes)
{
   trigger_keycodes_t keycodesusedbycombos = keycodesused;  // this includes both combos and substs
   activekeycodes.erase(std::remove_if(activekeycodes.begin(), activekeycodes.end(), [keycodesusedbycombos] (uint16_t keycode){return (std::binary_search(keycodesusedbycombos.begin(),keycodesusedbycombos.end(),keycode));}),activekeycodes.end()); 
   return activekeycodes;
}


trigger_keycodes_t ComboEngine::processActiveKeycodewithCombos(trigger_keycodes_t activekeycodes)
{
  combo_t comboToUse = {};
  subst_t substToUse = {};
  uint8_t combosize = 0;
  uint8_t substsize = 0;
    if (activecomboscount) {comboToUse = findLargestCombo(); combosize = comboToUse.first.size();}
    if (activesubstcount)  {substToUse = findLargestSubst(); substsize = substToUse.first.size();}

    trigger_keycodes_t keycodesToRemove;

    if (combosize<substsize)
    {
       keycodesToRemove = substToUse.first;
       //std::vector<char> s = substToUse.second;
       // add the string to the buffer...
       std::copy(substToUse.second.begin(), substToUse.second.end(), std::back_inserter(keycodebuffertosend));
       //keycodebuffertosend.insert(keycodebuffertosend.end(), substToUse.second.begin(),substToUse.second.end());
    }
    else 
    {
      keycodesToRemove = comboToUse.first;
      activekeycodes.push_back(comboToUse.second);
    }

    activekeycodes.erase(std::remove_if(activekeycodes.begin(), activekeycodes.end(), [keycodesToRemove] (uint16_t keycode){return (std::binary_search(keycodesToRemove.begin(),keycodesToRemove.end(),keycode));}),activekeycodes.end()); 
    return activekeycodes;
}

/**************************************************************************************************************************/
/* SUBSTITUTIONS BELOW...            */
/**************************************************************************************************************************/
trigger_keycodes_t ComboEngine::convertCStrToKeycodeVector(char* stringtoconvert)
{
  trigger_keycodes_t v;   
  size_t i = 0;
  while (stringtoconvert[i] != '\0') {       /* Stop looping when we reach the null-character. */
    uint8_t modifier = ( hid_ascii_to_keycode[(uint8_t)stringtoconvert[i]][0] ) ? KEYBOARD_MODIFIER_LEFTSHIFT : 0;
    uint8_t keycode = hid_ascii_to_keycode[(uint8_t)stringtoconvert[i]][1];
    uint16_t keyreport = MOD( modifier << 8 , keycode);
    v.push_back(keyreport);
    i++;
  }
  return v;
}


void ComboEngine::addSubstitutionToList(trigger_keycodes_t trigger,char* stringtosend)
{
  trigger_keycodes_t v = convertCStrToKeycodeVector(stringtosend);   
  addKeycodeStringToList(trigger, v);
}

bool ComboEngine::anySubstConfigured()
{
    return substlist.size()>0;
}

subst_t ComboEngine::findLargestSubst()
{
  subst_t it = *std::max_element(activesubst.begin(), activesubst.end(),[](subst_t comboa, subst_t combob){return (comboa.first.size() < combob.first.size());} ); 
  return  it;
}


void ComboEngine::addKeycodeStringToBuffer(trigger_keycodes_t keycodestosend)
{
  keycodebuffertosend.insert(keycodebuffertosend.end(), keycodestosend.begin(),keycodestosend.end());
}


void ComboEngine::addKeycodeStringToList(trigger_keycodes_t trigger, trigger_keycodes_t keycodestosend)
{
  std::sort(trigger.begin(), trigger.end()); // pre-sorts before adding to substlist.
  substlist.push_back(make_pair(trigger, keycodestosend));
  keycodesused.insert( keycodesused.end(), trigger.begin(), trigger.end());
  std::sort(keycodesused.begin(),keycodesused.end()); // needed for the next operation
  std::unique(keycodesused.begin(),keycodesused.end()); // keep the unique keycodes only
}