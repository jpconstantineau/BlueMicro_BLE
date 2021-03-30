/*
Copyright 2018-2021 <Pierre Constantineau, Julian Komaromy>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include "KeyScanner.h"

KeyScanner::KeyScanner(PersistentState *cfg, DynamicState *stat) { // Constructor
  config = cfg;
  status = stat;
}

/**************************************************************************************************************************/
// KEYPRESS - THIS ROUTINE ENACTS A KEYPRESS - DEBOUNCE SHOULD BE HANDLED BY CALLER
/**************************************************************************************************************************/
void KeyScanner::press(unsigned long currentMillis, const int &row, const int &col) {
  matrix[row][col].press(currentMillis);
  lastPressed = currentMillis;
}

/**************************************************************************************************************************/
// KEYRELEASE - THIS ROUTINE ENACTS A KEYRELEASE - DEBOUNCE SHOULD BE HANDLED BY CALLER
/**************************************************************************************************************************/
void KeyScanner::release(unsigned long currentMillis, const int &row, const int &col) { matrix[row][col].clear(currentMillis); }

/**************************************************************************************************************************/
// Called by callback function when remote data is received
/**************************************************************************************************************************/
void KeyScanner::updateRemoteLayer(uint8_t data) { remoteLayer = data; }

/**************************************************************************************************************************/
// Called by callback function when remote data is received
/**************************************************************************************************************************/
void KeyScanner::updateRemoteReport(uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4, uint8_t data5, uint8_t data6) {
  remoteMod = data0;
  remoteReport[0] = data0;
  remoteReport[1] = data1;
  remoteReport[2] = data2;
  remoteReport[3] = data3;
  remoteReport[4] = data4;
  remoteReport[5] = data5;
  remoteReport[6] = data6;
}

/**************************************************************************************************************************/
void KeyScanner::resetReport() {
  bufferposition = 1;
  currentMod = 0;
  currentReport[0] = 0;
  currentReport[1] = 0;
  currentReport[2] = 0;
  currentReport[3] = 0;
  currentReport[4] = 0;
  currentReport[5] = 0;
  currentReport[6] = 0;
}

/**************************************************************************************************************************/
void KeyScanner::copyRemoteReport() {
#if BLE_PERIPHERAL == 1 // PERIPHERAL MUST BE HANDLED DIFFERENTLY THAN CENTRAL - OTHERWISE, THE REPORTS WILL JUST KEEP BOUNCING FROM ONE BOARD TO THE OTHER
  resetReport();
#else
  currentMod = remoteMod;
  //       currentReport[0] = remoteReport[0];
  bufferposition = 1;
  if (remoteReport[1] > 0) {
    currentReport[bufferposition] = remoteReport[1];
    bufferposition++;
  }
  if (remoteReport[2] > 0) {
    currentReport[bufferposition] = remoteReport[2];
    bufferposition++;
  }
  if (remoteReport[3] > 0) {
    currentReport[bufferposition] = remoteReport[3];
    bufferposition++;
  }
  if (remoteReport[4] > 0) {
    currentReport[bufferposition] = remoteReport[4];
    bufferposition++;
  }
  if (remoteReport[5] > 0) {
    currentReport[bufferposition] = remoteReport[5];
    bufferposition++;
  }
  if (remoteReport[6] > 0) {
    currentReport[bufferposition] = remoteReport[6];
    bufferposition++;
  }
#endif
}

/**************************************************************************************************************************/
uint8_t KeyScanner::getlayer(uint16_t layers) {
  // this will return the highest layer
  uint8_t layerid = 0;
  if (layers > 0) // skip the calc if no layers are selected
  {
    while (layers >>= 1) {
      layerid++;
    }
  }
  return layerid;
}

/**************************************************************************************************************************/
/*
 * loop through the entire matrix, checking for
 * activated keys and adding the activated ones
 * into a buffer
 */
void KeyScanner::updateBuffer() {
  activeKeys.clear();
  bool emptyOneshot = false;
  // bool emptyOneshotLayer = false;
  std::copy(encoderKeys.begin(), encoderKeys.end(), back_inserter(activeKeys));
  // for (auto keycode : encoderKeys) //Consider using std::copy algorithm instead of a raw loop.
  // {
  //   activeKeys.push_back(keycode);
  // }

  encoderKeys.clear();

  // call the tri layer functions...
  process_user_layers(detectedlayerkeys);

  uint8_t layer = getlayer(detectedlayerkeys);

  status->layer = layer;

  for (int row = 0; row < MATRIX_ROWS; ++row) {
    for (auto &key : matrix[row]) {
      uint16_t activeKeycode;
      Duration duration;
      std::tie(activeKeycode, duration) = key.getActiveActivation(layer);

      if (activeKeycode != 0) {
        activeKeys.push_back(activeKeycode);

        /*
         * define behavior of
         * toggle and oneshot keys
         * respectively
         *
         * empty oneshot when a keycode that's before
         * the modifiers is pressed
         */
        if (duration == Duration::TOGGLE) {
          auto it = std::find(toggleBuffer.begin(), toggleBuffer.end(), activeKeycode);
          if (it != toggleBuffer.end()) {
            toggleBuffer.erase(it);
          } else {
            toggleBuffer.push_back(activeKeycode);
          }
        } else if (duration == Duration::ONE_SHOT) {
          auto it = std::find(oneshotBuffer.begin(), oneshotBuffer.end(), activeKeycode);
          if (it != oneshotBuffer.end()) {
            ;
          } else {
            oneshotBuffer.push_back(activeKeycode);
            uint8_t keyValue = static_cast<uint8_t>(activeKeycode & 0x00FF);
            if (keyValue >= LAYER_0 && keyValue <= LAYER_F) {
              oneshotLayer =
                  oneshotLayer |
                  (1 << (keyValue -
                         0xF0)); // Add layer to layer mask for next scan  They must be handled separately due to needing layers ahead of picking up keycodes.
            }
          }

        } else if ((activeKeycode & 0x00FF) < 0xE0) // it's active, not a modifier, not a layer, not toggle and not one shot, ignore attached modifiers...
        {
          emptyOneshot = true;
        }
      }
    }
  }

  /*
   * empty the toggle
   * buffer into the main buffer and empty the
   * oneshot buffer if a non-oneshot
   * key has been pressed
   */

  std::copy(toggleBuffer.begin(), toggleBuffer.end(), back_inserter(activeKeys));

  if (emptyOneshot) {
    std::copy(oneshotBuffer.begin(), oneshotBuffer.end(), back_inserter(activeKeys));
    oneshotBuffer.clear();
    oneshotLayer = 0;
  }
}

/**************************************************************************************************************************/
// inspired by QMK's update_tri_layer_state... Modified to replace instead of adding to detected layer keys
// can be called multiple times to catch multiple 2-layer patterns
/**************************************************************************************************************************/
void KeyScanner::process_for_tri_layers(uint8_t if_layer1, uint8_t and_layer2, uint8_t use_layer3) {
  uint16_t mask12 = (1UL << if_layer1) | (1UL << and_layer2); // merge the two layers with bitwise shifts to detect the triggered layer keys
  uint16_t mask3 = 1UL << use_layer3;                         // create a mask to return the resulting layer
  detectedlayerkeys = (detectedlayerkeys & mask12) == mask12
                          ? ((detectedlayerkeys & ~mask12) | mask3)
                          : (detectedlayerkeys); // if detectedlayerkeys has mask12 in it,remove mask12 and add extra layer; otherwise return as is.
}

void KeyScanner::add_to_encoderKeys(uint16_t keycode) { encoderKeys.push_back(keycode); }

#if USER_LAYER_FUNCTION == 1
void process_user_layers(uint16_t layermask) { ; }
#endif
/**************************************************************************************************************************/
// Scan for layer changes - must do this first.
/**************************************************************************************************************************/
bool KeyScanner::updateLayer() {
  uint16_t prevlayer = localLayer;                             // remember last layer mask
  detectedlayerkeys = localLayer | remoteLayer | oneshotLayer; // merge the layer masks

  // read through the matrix and select all of the
  // currently pressed keys
  updateBuffer();

  /*
   * iterate through all of the currently pressed keys, if
   * a layer key is pressed, change the layer mask accordingly
   * if no other layers are set in the buffer, the default
   * layer should be chosen (=0)
   */
  localLayer = 0; // reset the layer mask before we fill it again
  for (auto keycode : activeKeys) {
    // the first byte is the actual HID keycode of the key
    uint8_t keyValue = static_cast<uint8_t>(keycode & 0x00FF);
    if (keyValue >= LAYER_0 && keyValue <= LAYER_F) {
      localLayer = localLayer | (1 << (keyValue - 0xF0)); // Add layer to layer mask for next scan
    }
  }

  layerChanged = (prevlayer != localLayer);
  return layerChanged;
}

/**************************************************************************************************************************/

bool KeyScanner::getReport() {
  previousReport[0] = currentReport[0];
  previousReport[1] = currentReport[1];
  previousReport[2] = currentReport[2];
  previousReport[3] = currentReport[3];
  previousReport[4] = currentReport[4];
  previousReport[5] = currentReport[5];
  previousReport[6] = currentReport[6];
  previousReport[7] = currentReport[7];

  resetReport();
  copyRemoteReport();
  updateLayer();
  if (remotespecialkeycode > 0) {
    activeKeys.push_back(remotespecialkeycode);
    remotespecialkeycode = 0;
  }

  // process single-key substs (macros) first.
  if (combos.anyMacrosConfigured()) {
    if (combos.anyMacrosActive(activeKeys)) {
      activeKeys = combos.processActiveMacros(activeKeys);
    }
  }

  // process combos before generating HID reports
  if (combos.anyCombosConfigured()) {
    uint8_t triggercount = combos.countActiveCombosKeys(activeKeys);
    if (triggercount > 1) // we have a potential combo present
    {
      uint8_t activecount = combos.findActiveCombos(activeKeys);
      if (activecount > 0) // at least 1
      {
        if (activecount == 1) // exactly 1
        {
          activeKeys = combos.processActiveKeycodewithCombos(activeKeys);
          combotimer = status->timestamp; // reset timers to current timestamp.
          triggerkeytimer = status->timestamp;
        } else // more than 2
        {
          if (status->timestamp - combotimer > 200) // timeout to send biggest one...
          {
            activeKeys = combos.processActiveKeycodewithCombos(activeKeys);
            combotimer = status->timestamp; // reset timers to current timestamp.
            triggerkeytimer = status->timestamp;
          } else // we are still transitioning remove all potential combo keys...
          {
            activeKeys = combos.processActiveKeycodewithComboKeys(activeKeys);
          }
        }
      } else {                                   // if none are active, we might have to remove keycodes in case we are transitionning to/from a combo
        if (status->timestamp - combotimer < 75) // Transitionning out of a combo
        {
          activeKeys = combos.processActiveKeycodewithComboKeys(activeKeys);
        }
      }
    } else {
      if (triggercount == 1) // we have a key used in a combo being pressed
      {
        // check if we have a "mono"
        /* if (combos.findActiveCombos(activeKeys)) // at least 1
          {
              if (combos.keycodebuffertosend.empty()) // buffer has stuff in it - skip adding the "mono"
              {
              activeKeys = combos.processActiveKeycodewithCombos(activeKeys);
              combotimer = status->timestamp;  // reset timers to current timestamp.
              triggerkeytimer = status->timestamp;
              }
          }
          else */
        if (status->timestamp - triggerkeytimer < 75) // Transitionning out/in of a combo
        {
          activeKeys = combos.processActiveKeycodewithComboKeys(activeKeys);
        }
      } else {
        triggerkeytimer = status->timestamp;
        combotimer = status->timestamp;
      }
    }
  }

  for (auto keycode : activeKeys) {
    auto hidKeycode = static_cast<uint8_t>(keycode & 0x00FF);
    auto extraModifiers = static_cast<uint8_t>((keycode & 0xFF00) >> 8);

    if (hidKeycode >= KC_A && hidKeycode <= KC_EXSEL) {
      currentReport[bufferposition] = hidKeycode;
      ++bufferposition;
    }

    // check if the hid keycode contains a modifier. // also check for macros.
    switch (hidKeycode) {
    case KC_LCTRL:
      currentMod |= 1;
      currentMod |= extraModifiers;
      break;
    case KC_LSHIFT:
      currentMod |= 2;
      currentMod |= extraModifiers;
      break;
    case KC_LALT:
      currentMod |= 4;
      currentMod |= extraModifiers;
      break;
    case KC_LGUI:
      currentMod |= 8;
      currentMod |= extraModifiers;
      break;
    case KC_RCTRL:
      currentMod |= 16;
      currentMod |= extraModifiers;
      break;
    case KC_RSHIFT:
      currentMod |= 32;
      currentMod |= extraModifiers;
      break;
    case KC_RALT:
      currentMod |= 64;
      currentMod |= extraModifiers;
      break;
    case KC_RGUI:
      currentMod |= 128;
      currentMod |= extraModifiers;
      break;
    case KC_RESERVED_A5:
      if (!processingmacros) {
        macro = keycode;
        processingmacros = true;
      }
      extraModifiers = 0;
      break; // KC_RESERVED_A5 is the keycode marker for user macros.
    case KC_RESERVED_A6:
      if (!processingmacros) {
        specialfunction = keycode;
        processingmacros = true;
      }
      extraModifiers = 0;
      break; // KC_RESERVED_A6 is the keycode marker for special keyboard functions.
    case KC_RESERVED_A7:
      if (!processingmacros) {
        consumer = keycode;
        processingmacros = true;
      }
      extraModifiers = 0;
      break; // KC_RESERVED_A7 is the keycode marker for consumer reports.
    case KC_RESERVED_A8:
      consumer = keycode;
      extraModifiers = 0;
      break; // KC_RESERVED_A8 is the keycode marker for repeating consumer reports.
    case KC_RESERVED_A9:
      mouse = keycode;
      extraModifiers = 0;
      break; // KC_RESERVED_A8 is the keycode marker for mouse reports. Mousekeys can be repeated... We therefore don't need the macro logic
    case KC_RESERVED_AA:
      special_key = keycode;
      extraModifiers = 0;
      break; // KC_RESERVED_AA is the keycode marker for special keys.
    case KC_RESERVED_AB:
      if (!processingmacros) {
        specialfunction = keycode;
        processingmacros = true;
      }
      extraModifiers = 0;
      break; // KC_RESERVED_AB keycode for marking this as a specialfunction for international/special characters (ALT-0233 = é).
    }
    // add all of the extra modifiers into the curren modifier
    currentMod |= extraModifiers;
    if (bufferposition == 7) {
      bufferposition = 1;
    }
  }

  currentReport[0] = currentMod;
  currentReport[7] = localLayer;

  if (activeKeys.empty() && processingmacros) {
    processingmacros = false;
  }

  if ((currentReport[0] != previousReport[0]) | (currentReport[1] != previousReport[1]) | (currentReport[2] != previousReport[2]) |
      (currentReport[3] != previousReport[3]) | (currentReport[4] != previousReport[4]) | (currentReport[5] != previousReport[5]) |
      (currentReport[6] != previousReport[6]) | (currentReport[7] != previousReport[7])) {
    reportChanged = true;
    status->lastreporttime = status->timestamp;
    if (processingmacros)
      if ((currentReport[0] == 0) && (currentReport[1] == 0) && (currentReport[2] == 0) && (currentReport[3] == 0) && (currentReport[4] == 0) &&
          (currentReport[5] == 0) && (currentReport[6] == 0)) {
        processingmacros = false;
        macro = 0;
        specialfunction = 0;
        consumer = 0;
        mouse = 0;
      }
  } else {
    reportChanged = false;
  }
  if ((status->timestamp) - (status->lastreporttime) > 125) // make sure we have at least 1 report every 125 ms even if we don't type.
  {
    reportChanged = true;
    status->lastreporttime = status->timestamp;
  }

  return reportChanged;
}

unsigned long KeyScanner::getLastPressed() { return lastPressed; }
/**************************************************************************************************************************/

uint8_t KeyScanner::currentReport[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t KeyScanner::remoteReport[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t KeyScanner::previousReport[8] = {0, 0, 0, 0, 0, 0, 0, 0};
bool KeyScanner::layerChanged = false;
bool KeyScanner::reportChanged = false;
bool KeyScanner::processingmacros = false;
uint16_t KeyScanner::detectedlayerkeys = 0;
uint16_t KeyScanner::localLayer = 0;
uint16_t KeyScanner::macro = 0;
uint16_t KeyScanner::specialfunction = 0;
uint16_t KeyScanner::consumer = 0;
uint16_t KeyScanner::mouse = 0;
uint16_t KeyScanner::special_key = 0;
uint16_t KeyScanner::remoteLayer = 0;
uint16_t KeyScanner::remotespecialkeycode = 0;
uint32_t KeyScanner::combotimer = 0;
uint32_t KeyScanner::triggerkeytimer = 0;

uint16_t KeyScanner::oneshotLayer = 0;
uint8_t KeyScanner::remoteMod = 0;
uint8_t KeyScanner::currentMod = 0;
unsigned long KeyScanner::lastPressed = 0;
uint8_t KeyScanner::bufferposition = 0;
std::vector<uint16_t> KeyScanner::activeKeys{};
std::vector<uint16_t> KeyScanner::encoderKeys{};
std::vector<uint16_t> KeyScanner::macroBuffer{};
std::vector<uint16_t> KeyScanner::toggleBuffer{};
std::vector<uint16_t> KeyScanner::leaderBuffer{};
std::vector<uint16_t> KeyScanner::oneshotBuffer{};

PersistentState *KeyScanner::config = NULL;
DynamicState *KeyScanner::status = NULL;
