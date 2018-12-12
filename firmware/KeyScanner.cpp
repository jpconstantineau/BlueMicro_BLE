/*
   copyright 2018 <pierre constantineau, julian komaromy>
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
#include "KeyScanner.h"
// ToDo: There seems to be lots of redundency in data.
// ToDo: consider interrupts or GPIOTE
// ToDo: there must be a better way to debounce
// ToDo: consider multiple boards and the merging of multiple buffers/modifiers and layer requests.
// ToDo: Action Keycodes - Bluetooth commands
// ToDo: Action Keycodes - Reset/DFU commands

KeyScanner::KeyScanner() {    // Constructor
    ;
}


/**************************************************************************************************************************/
// KEY SCANNING - THIS ROUTINE ONLY TAKES CARE OF THE DEBOUNCING LOGIC FOR EACH KEY
/**************************************************************************************************************************/
bool KeyScanner::scanMatrix(const int& currentState,unsigned long currentMillis, const int& row, const int& col)
{
    // 
#if DIODE_DIRECTION == COL2ROW
        if (currentState == 0 ) //if key pressed
#else
        if (currentState == 1 ) //if key pressed
#endif
        {
            if (timestamps[row][col] > 0) //if key was previously pressed
            {
                if((currentMillis - timestamps[row][col]) >= DEBOUNCETIME)
                {
                    matrix[row][col].press(currentMillis);
                }
                else // not enough debounce time
                {
                    ; // do nothing
                }
            }

            else //if key was NOT previously pressed
            {
                timestamps[row][col] = currentMillis;
            }
        }
        else // key not pressed
        {
            matrix[row][col].clear(currentMillis);
            timestamps[row][col] = 0;
        }
}


/**************************************************************************************************************************/
// Called by callback function when remote data is received
/**************************************************************************************************************************/
void KeyScanner::updateRemoteLayer(uint8_t data)
{
    remoteLayer = data;
}

/**************************************************************************************************************************/
// Called by callback function when remote data is received
/**************************************************************************************************************************/
void KeyScanner::updateRemoteReport(uint8_t data0, uint8_t data1, uint8_t data2,uint8_t data3, uint8_t data4, uint8_t data5,uint8_t data6)
{
    remoteMod=data0;
    remoteReport[0]= data0;
    remoteReport[1]= data1;
    remoteReport[2]= data2;
    remoteReport[3]= data3;
    remoteReport[4]= data4;
    remoteReport[5]= data5;
    remoteReport[6]= data6;
}


/**************************************************************************************************************************/
void KeyScanner::resetRemoteReport()
{
    remoteReport[0]= 0;
    remoteReport[1]= 0;
    remoteReport[2]= 0;
    remoteReport[3]= 0;
    remoteReport[4]= 0;
    remoteReport[5]= 0;
    remoteReport[6]= 0;
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
void KeyScanner::copyRemoteReport()
{
#if BLE_PERIPHERAL == 1  // PERIPHERAL MUST BE HANDLED DIFFERENTLY THAN CENTRAL - OTHERWISE, THE REPORTS WILL JUST KEEP BOUNCING FROM ONE BOARD TO THE OTHER 
    resetReport();
#else
    currentMod = remoteMod;
    //       currentReport[0] = remoteReport[0];
    bufferposition = 1;
    if (remoteReport[1]>0){currentReport[bufferposition] = remoteReport[1]; bufferposition++; }
    if (remoteReport[2]>0){currentReport[bufferposition] = remoteReport[2]; bufferposition++; }
    if (remoteReport[3]>0){currentReport[bufferposition] = remoteReport[3]; bufferposition++; }
    if (remoteReport[4]>0){currentReport[bufferposition] = remoteReport[4]; bufferposition++; }
    if (remoteReport[5]>0){currentReport[bufferposition] = remoteReport[5]; bufferposition++; }
    if (remoteReport[6]>0){currentReport[bufferposition] = remoteReport[6]; bufferposition++; }
#endif
}

/*
 * loop through the entire matrix, checking for 
 * activated keys and adding the activated ones
 * into a buffer
 */
void KeyScanner::updateBuffer(uint8_t layer)
{
    activeKeys.clear();
    bool emptyOneshot = false;

    for(int row = 0; row < MATRIX_ROWS; ++row) {
        for (auto& key : matrix[row]) 
        {
            //pair of activation/duration
            auto activation = key.getPair(layer);

            if (activation.first != 0) 
            {
                activeKeys.push_back(activation.first);

                /*
                 * define behavior of
                 * toggle and oneshot keys 
                 * respectively
                 *
                 * empty oneshot when a keycode that's before
                 * the modifiers is pressed
                 */
                if (activation.second == 1) 
                {
                    auto it = std::find(toggleBuffer.begin(), toggleBuffer.end(), activation.first);

                    if (it != toggleBuffer.end())
                    {
                        toggleBuffer.erase(it);
                    }
                    else 
                    {
                        toggleBuffer.push_back(activation.first);
                    }


                }
                else if (activation.second == 2)
                {
                    oneshotBuffer.push_back(activation.first);
                }
                else if (activation.first < 0xE0) 
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
    for (auto activation : toggleBuffer) 
    {
        activeKeys.push_back(activation);
    }
    if (emptyOneshot) 
    {
        for (auto activation : oneshotBuffer) 
        {
            activeKeys.push_back(activation);
        }

        oneshotBuffer.clear();
    }
}

/**************************************************************************************************************************/
// Scan for layer changes - must do this first.
/**************************************************************************************************************************/
bool KeyScanner::updateLayer()
{
    uint8_t prevlayer = localLayer;     // remember last layer

    // Select the layer which the selection is done on
    // this isthe larger of local and remote layers
    uint8_t selectionLayer = localLayer; 

    if (localLayer < remoteLayer)
    {
        selectionLayer = remoteLayer;
    }

    // read through the matrix and select all of the 
    // currently pressed keys 
    updateBuffer(selectionLayer);

    /* 
     * iterate through all of the currently pressed keys, if 
     * a layer key is pressed, change the layer accordingly
     * if no other layers are set in the buffer, the default
     * layer should be chosen
     */
    localLayer = LAYER_0 - 0xF0;
    for (auto keycode : activeKeys)
    {
        // the first byte is the actual HID keycode of the key
        uint8_t keyValue = static_cast<uint8_t>(keycode & 0x00FF);

        if (keyValue >= LAYER_0 && keyValue <= LAYER_F)
        {
            // calculate layer offset
            localLayer = keyValue - 0xF0;
        }
    }

    layerChanged = (prevlayer != localLayer);
    return layerChanged;
}

/**************************************************************************************************************************/
// Update Mods - can be done before or after rest of matrix
// All 8 modifiers are handled through a 8-bit byte.  This is the standard HID implementation
/**************************************************************************************************************************/
bool KeyScanner::updateModifiers()
{
    bool changed = false;                                // indicates "changed" mods

    for (auto keycode : activeKeys)
    {
        //seperate the keycode into the hid keycode and the additional modifiers
        auto extraModifiers = static_cast<uint8_t>((keycode & 0xFF00) >> 8);
        auto hidKeycode = static_cast<uint8_t>(keycode & 0x00FF);

        //check if the hid keycode contains a modifier
        switch (hidKeycode) { 
            case KC_LCTRL:  currentMod |= 1;   changed = true; break;
            case KC_LSHIFT: currentMod |= 2;   changed = true; break;
            case KC_LALT:   currentMod |= 4;   changed = true; break;
            case KC_LGUI:   currentMod |= 8;   changed = true; break;
            case KC_RCTRL:  currentMod |= 16;  changed = true; break;
            case KC_RSHIFT: currentMod |= 32;  changed = true; break;
            case KC_RALT:   currentMod |= 64;  changed = true; break;
            case KC_RGUI:   currentMod |= 128; changed = true; break;
        }

        //add all of the extra modifiers into the curren modifier 
        currentMod |= extraModifiers;
    }

    return changed;
}


/**************************************************************************************************************************/

bool KeyScanner::getReport()
{
    resetReport();
    copyRemoteReport();
    updateLayer();
    updateModifiers();

    for (auto keycode : activeKeys) 
    {
        auto hidKeycode = static_cast<uint8_t>(keycode & 0x00FF);

        if (hidKeycode >= KC_A && hidKeycode <= KC_EXSEL)
        {
            currentReport[bufferposition] = hidKeycode;
            ++bufferposition;
        }

        if (bufferposition == 7)
        {
            bufferposition = 1;
        }
    }

    currentReport[0] = currentMod;
    currentReport[7] = localLayer;

    if((currentReport[0] != 0) | (currentReport[1] != 0)| (currentReport[2] != 0)| (currentReport[3] != 0)| (currentReport[4] != 0)| (currentReport[5] != 0)| (currentReport[6] != 0))
    {reportEmpty = false;}
    else
    {reportEmpty = true;}

    return reportEmpty;
}

/**************************************************************************************************************************/


uint8_t KeyScanner::currentReport[8] = {0, 0, 0 ,0, 0, 0, 0, 0}; 
uint8_t KeyScanner::remoteReport[8]  = {0, 0, 0 ,0, 0, 0, 0, 0};
bool    KeyScanner::layerChanged = false;
bool    KeyScanner::reportEmpty = true;
uint8_t KeyScanner::localLayer = 0;
uint8_t KeyScanner::remoteLayer = 0;
uint8_t KeyScanner::remoteMod = 0;
uint8_t KeyScanner::currentMod = 0;
unsigned long KeyScanner::timestamps[MATRIX_ROWS][MATRIX_COLS]  = {0};
uint8_t KeyScanner::bufferposition = 0;
uint8_t KeyScanner::layerMode = 0;
std::vector<uint16_t> KeyScanner::activeKeys {};
std::vector<uint16_t> KeyScanner::macroBuffer {};
std::vector<uint16_t> KeyScanner::toggleBuffer {};
std::vector<uint16_t> KeyScanner::leaderBuffer {};
std::vector<uint16_t> KeyScanner::oneshotBuffer {};

