// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

// if you wonder about this std algorithmn black magic, see https://www.youtube.com/watch?v=bFSnXNIsK4A

#include "combo_engine.h"

#ifdef ENABLE_COMBOS
   ComboEngine combos;
#endif


ComboEngine::ComboEngine()
{
 /*combolist = {};
 monolist = {}; 
 substlist = {};
 macrolist = {};
 activecombos = {};
 activesubst = {};
 keycodesused_multi = {};
 keycodesused_single = {};
 keycodebuffertosend = {};*/ // these get initialized with empty vectors anyways...
 activemacrosent= false;
 activecomboscount = 0;
 activesubstcount = 0;
 activemacrocount = 0;
}

// cppcheck-suppress unusedFunction
void ComboEngine::clearLists()
{
   combolist.clear();
   monolist.clear();
   substlist.clear(); 
   macrolist.clear();
   keycodesused_multi.clear();
   keycodesused_single.clear();
}

/**************************************************************************************************************************/
/* COMBOS BELOW...                                                                                                        */
/**************************************************************************************************************************/
// cppcheck-suppress unusedFunction
void ComboEngine::addComboToList(trigger_keycodes_t trigger, uint16_t keycode)
{
  std::sort(trigger.begin(), trigger.end()); // pre-sorts before adding to combolist.
  if (trigger.size()>1)              // combos should always replace 2 keystrokes with 1... 
  {
    combolist.push_back(make_pair(trigger, keycode));
    keycodesused_multi.insert(keycodesused_multi.end(), trigger.begin(), trigger.end());
    std::sort(keycodesused_multi.begin(), keycodesused_multi.end());   // needed for the next operation
    keycodesused_multi.erase(std::unique(keycodesused_multi.begin(), keycodesused_multi.end()), keycodesused_multi.end()); // keep the unique keycodes only
  }
}

// cppcheck-suppress unusedFunction
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
  trigger_keycodes_t keycodesusedbycombos = keycodesused_multi; // this includes both combos and substs
  return std::count_if(activekeycodes.begin(), activekeycodes.end(), [keycodesusedbycombos] (uint16_t keycode){return (std::binary_search(keycodesusedbycombos.begin(),keycodesusedbycombos.end(),keycode));});
}


combo_t ComboEngine::findLargestCombo()
{
  combo_t it = *std::max_element(activecombos.begin(), activecombos.end(),[](combo_t comboa, combo_t combob){return (comboa.first.size() < combob.first.size());} ); 
  return  it;
}


trigger_keycodes_t ComboEngine::processActiveKeycodewithComboKeys(trigger_keycodes_t activekeycodes)
{
   trigger_keycodes_t keycodesusedbycombos = keycodesused_multi;  // this includes both combos and substs
   activekeycodes.erase(std::remove_if(activekeycodes.begin(), activekeycodes.end(), [keycodesusedbycombos] (uint16_t keycode){return (std::binary_search(keycodesusedbycombos.begin(),keycodesusedbycombos.end(),keycode));}),activekeycodes.end()); 
   return activekeycodes;
}


trigger_keycodes_t ComboEngine::processActiveKeycodewithCombos(trigger_keycodes_t activekeycodes)
{
  combo_t comboToUse = {};
  subst_t substToUse = {};
  uint8_t combosize = 0;
  uint8_t substsize = 0;
  trigger_keycodes_t keycodesToRemove;

    if (activecomboscount) {comboToUse = findLargestCombo(); combosize = comboToUse.first.size();}
    if (activesubstcount)  {substToUse = findLargestSubst(); substsize = substToUse.first.size();}

    if (combosize<substsize)
    {
       keycodesToRemove = substToUse.first;
       addKeycodeStringToBuffer(substToUse.second);
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
/* SUBSTITUTIONS BELOW...                                                                                                 */
/**************************************************************************************************************************/
trigger_keycodes_t ComboEngine::convertCStrToKeycodeVector(char* stringtoconvert)
{
  trigger_keycodes_t v;  
  char ch;
  while( (ch = *stringtoconvert++) != 0 )
  {
    uint8_t modifier = ( hid_ascii_to_keycode[(uint8_t)ch][0] ) ? KEYBOARD_MODIFIER_LEFTSHIFT : 0;
    uint8_t keycode = hid_ascii_to_keycode[(uint8_t)ch][1];
    uint16_t keyreport = MOD( modifier << 8 , keycode);
    v.insert(v.end() , keyreport);
  }
  return v;
}

// cppcheck-suppress unusedFunction
void ComboEngine::addSubstitutionToList(const trigger_keycodes_t trigger,char* stringtosend) // added const by cppcheck recommendation
{
  trigger_keycodes_t v = convertCStrToKeycodeVector(stringtosend);   
  addKeycodeStringToList(trigger, v);
}

// cppcheck-suppress unusedFunction
bool ComboEngine::anySubstConfigured()
{
    return substlist.size()>0;
}


subst_t ComboEngine::findLargestSubst()
{
  subst_t it = *std::max_element(activesubst.begin(), activesubst.end(),[](subst_t comboa, subst_t combob){return (comboa.first.size() < combob.first.size());} ); 
  return  it;
}

/**************************************************************************************************************************/
/* BUFFER OPERATIONS BELOW...                                                                                             */
/**************************************************************************************************************************/
void ComboEngine::addKeycodeStringToBuffer(trigger_keycodes_t keycodestosend)
{
  keycodebuffertosend.reserve(keycodebuffertosend.size()+keycodestosend.size());
  keycodebuffertosend.insert(keycodebuffertosend.end(), keycodestosend.begin(),keycodestosend.end());
}


void ComboEngine::addKeycodeStringToList(trigger_keycodes_t trigger, trigger_keycodes_t keycodestosend)
{
  std::sort(trigger.begin(), trigger.end()); // pre-sorts before adding to substlist.
  if (trigger.size()>1)
  {
    substlist.push_back(make_pair(trigger, keycodestosend));
    keycodesused_multi.insert(keycodesused_multi.end(), trigger.begin(), trigger.end());
    std::sort(keycodesused_multi.begin(), keycodesused_multi.end());   // needed for the next operation
    keycodesused_multi.erase(std::unique(keycodesused_multi.begin(), keycodesused_multi.end()),keycodesused_multi.end()); // keep the unique keycodes only
  } else {
    macrolist.push_back(make_pair(trigger, keycodestosend));
    keycodesused_single.insert(keycodesused_single.end(), trigger.begin(), trigger.end());
    std::sort(keycodesused_single.begin(), keycodesused_single.end());   // needed for the next operation 
    keycodesused_single.erase(std::unique(keycodesused_single.begin(), keycodesused_single.end()), keycodesused_single.end());// keep the unique keycodes only

  }
}

bool ComboEngine::anyMacrosConfigured()
{
  return macrolist.size()>0;
}

bool ComboEngine::anyMacrosActive(trigger_keycodes_t activekeycodes)
{
  activemacrocount = 0;
  activemacro.clear();
  std::sort(activekeycodes.begin(), activekeycodes.end()); // include needs both to be sorted.
  std::copy_if (macrolist.begin(), macrolist.end(), std::back_inserter(activemacro), [activekeycodes] (subst_t combo){  return std::includes(activekeycodes.begin(),activekeycodes.end(), combo.first.begin(), combo.first.end() );}  ); 
  activemacrocount = activemacro.size();
  if (activemacrocount<1){activemacrosent = false;} // reset sent state when no macros are triggered.
  return activemacrocount>0;
}

trigger_keycodes_t ComboEngine::processActiveMacros(trigger_keycodes_t activekeycodes)
{
  subst_t macro = activemacro.back();
  trigger_keycodes_t keycodesToRemove = macro.first; 
  if (!activemacrosent)
  {
    addKeycodeStringToBuffer(macro.second);   // send the macro to the buffer
    activemacrosent = true; // set sent state so that it doesn't get sent twice. Will be reset in anyMacrosActive
  }

  // remove trigger regardless of sent or not.
  activekeycodes.erase(std::remove_if(activekeycodes.begin(), activekeycodes.end(), [keycodesToRemove] (uint16_t keycode){return (std::binary_search(keycodesToRemove.begin(),keycodesToRemove.end(),keycode));}),activekeycodes.end()); 
  return activekeycodes;
}