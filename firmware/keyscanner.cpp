// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include "keyscanner.h"

//todo refactor KeyScanner and split into get/update/send sequences

KeyScanner::KeyScanner(PersistentState* cfg, DynamicState* stat) {    // Constructor
    config=cfg;
    status=stat;
}

/**************************************************************************************************************************/
// KEYPRESS - THIS ROUTINE ENACTS A KEYPRESS - DEBOUNCE SHOULD BE HANDLED BY CALLER
/**************************************************************************************************************************/
void KeyScanner::press(unsigned long currentMillis, const int& row, const int& col){
    matrix[row][col].press(currentMillis);
    lastPressed = currentMillis;
}

/**************************************************************************************************************************/
// KEYRELEASE - THIS ROUTINE ENACTS A KEYRELEASE - DEBOUNCE SHOULD BE HANDLED BY CALLER
/**************************************************************************************************************************/
void KeyScanner::release(unsigned long currentMillis, const int& row, const int& col){
    matrix[row][col].clear(currentMillis);
}


/**************************************************************************************************************************/
void KeyScanner::resetReport() {
    bufferposition = 0;
    currentMod = 0;
    currentReport.keycode[0] = 0;
    currentReport.keycode[1] = 0;
    currentReport.keycode[2] = 0;
    currentReport.keycode[3] = 0;
    currentReport.keycode[4] = 0;
    currentReport.keycode[5] = 0;
    currentReport.modifier = 0;
}


/**************************************************************************************************************************/
uint8_t KeyScanner::getlayer(uint16_t layers)
{
    //this will return the highest layer
    uint8_t layerid = 0;
    if (layers>0)// skip the calc if no layers are selected
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
void KeyScanner::updateBuffer()
{
    activeKeys.clear();
    bool emptyOneshot = false;
    //bool emptyOneshotLayer = false;
    std::copy(encoderKeys.begin(), encoderKeys.end(), back_inserter(activeKeys));
    //for (auto keycode : encoderKeys) //Consider using std::copy algorithm instead of a raw loop.
   // {
   //   activeKeys.push_back(keycode);
   // }

    encoderKeys.clear();

// call the tri layer functions...
process_user_layers(detectedlayerkeys);

uint8_t layer = getlayer(detectedlayerkeys);

status->layer = layer;

    for(int row = 0; row < MATRIX_ROWS; ++row) {
        for (auto& key : matrix[row]) 
        {
            KeyDefinition activeKey = key.getActiveActivation(layer);
            uint16_t activeKeycode = activeKey.activations;
            Duration duration = activeKey.durations;

            if (activeKeycode != 0) 
            {
                activeKeys.push_back(activeKeycode);

                /*
                 * define behavior of
                 * toggle and oneshot keys 
                 * respectively
                 *
                 * empty oneshot when a keycode that's before
                 * the modifiers is pressed
                 */
                if (duration == Duration::TOGGLE) 
                {
                    auto it = std::find(toggleBuffer.begin(), toggleBuffer.end(), activeKeycode);
                    if (it != toggleBuffer.end())
                    {
                        toggleBuffer.erase(it);
                    }
                    else 
                    {
                        toggleBuffer.push_back(activeKeycode);
                    }
                }
                else if (duration == Duration::ONE_SHOT)
                {
                    auto it = std::find(oneshotBuffer.begin(), oneshotBuffer.end(), activeKeycode);
                    if (it != oneshotBuffer.end())
                    {
                        ;
                    }
                    else 
                    {
                        oneshotBuffer.push_back(activeKeycode);
                        uint8_t keyValue = static_cast<uint8_t>(activeKeycode & 0x00FF);
                        if (keyValue >= LAYER_0 && keyValue <= LAYER_F)
                        {  
                            oneshotLayer = oneshotLayer | (1 << (keyValue - 0xF0)) ;  // Add layer to layer mask for next scan  They must be handled separately due to needing layers ahead of picking up keycodes.
                        }
                    }
                    
                }
                else if ((activeKeycode & 0x00FF) < 0xE0) // it's active, not a modifier, not a layer, not toggle and not one shot, ignore attached modifiers...
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

    if (emptyOneshot) 
    {
        std::copy(oneshotBuffer.begin(), oneshotBuffer.end(), back_inserter(activeKeys));        
        oneshotBuffer.clear();
        oneshotLayer = 0;
    }
}

/**************************************************************************************************************************/
// inspired by QMK's update_tri_layer_state... Modified to replace instead of adding to detected layer keys
// can be called multiple times to catch multiple 2-layer patterns
/**************************************************************************************************************************/
void KeyScanner::process_for_tri_layers(uint8_t if_layer1, uint8_t and_layer2, uint8_t use_layer3)
{
    uint16_t mask12 = (1UL << if_layer1) | (1UL << and_layer2);             // merge the two layers with bitwise shifts to detect the triggered layer keys
    uint16_t mask3 = 1UL << use_layer3;                                     // create a mask to return the resulting layer
    detectedlayerkeys = (detectedlayerkeys & mask12) == mask12 ? ((detectedlayerkeys & ~mask12) | mask3) : (detectedlayerkeys); // if detectedlayerkeys has mask12 in it,remove mask12 and add extra layer; otherwise return as is.
}

void KeyScanner::add_to_encoderKeys(uint16_t keycode)
{
    encoderKeys.push_back(keycode);
}

#if USER_LAYER_FUNCTION == 1 
void process_user_layers(uint16_t layermask)
{
   ;
}
#endif
/**************************************************************************************************************************/
// Scan for layer changes - must do this first.
/**************************************************************************************************************************/
bool KeyScanner::updateLayer()
{
    
    detectedlayerkeys = localLayer  | oneshotLayer; // merge the layer masks
    // TODO: check is remotelayer being sent/received is a bitmasked layer
    // oneshotLayer is a bitmasked layer
    // localLayer is a bitmasked layer

    
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
    for (auto keycode : activeKeys)
    {
        // the first byte is the actual HID keycode of the key
        uint8_t keyValue = static_cast<uint8_t>(keycode & 0x00FF);
        if (keyValue >= LAYER_0 && keyValue <= LAYER_F)
        {  
            localLayer = localLayer | (1 << (keyValue - 0xF0)) ;  // Add layer to layer mask for next scan
        }
    }
    
    
    
    return true;
}


/**************************************************************************************************************************/

bool KeyScanner::getReport()
{

    resetReport();
    updateLayer();

    #ifdef ENABLE_COMBOS
        // process single-key substs (macros) first.
        if (combos.anyMacrosConfigured())
        {
            if(combos.anyMacrosActive(activeKeys))
            {
                activeKeys = combos.processActiveMacros(activeKeys);
            }
        }

        // process combos before generating HID reports
        if (combos.anyCombosConfigured())
        { 
            uint8_t triggercount = combos.countActiveCombosKeys(activeKeys);
            if  (triggercount>1)// we have a potential combo present
            {
                uint8_t activecount = combos.findActiveCombos(activeKeys);
                if (activecount>0) // at least 1
                {
                    if (activecount==1) // exactly 1
                    {
                        activeKeys = combos.processActiveKeycodewithCombos(activeKeys);
                        combotimer = status->timestamp;  // reset timers to current timestamp.
                        triggerkeytimer = status->timestamp;
                    }
                    else // more than 2
                    {
                        if (status->timestamp - combotimer > 200)// timeout to send biggest one...
                        {
                            activeKeys = combos.processActiveKeycodewithCombos(activeKeys);
                            combotimer = status->timestamp;  // reset timers to current timestamp.
                            triggerkeytimer = status->timestamp;
                        }
                        else // we are still transitioning remove all potential combo keys...
                        {
                            activeKeys = combos.processActiveKeycodewithComboKeys(activeKeys);
                        }
                    }
                }
                else
                { // if none are active, we might have to remove keycodes in case we are transitionning to/from a combo 
                    if (status->timestamp - combotimer < 75)// Transitionning out of a combo
                    {
                        activeKeys = combos.processActiveKeycodewithComboKeys(activeKeys); 
                    }
                }
            }
            else
            {
            if (triggercount==1) // we have a key used in a combo being pressed
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
                    if (status->timestamp - triggerkeytimer < 75)// Transitionning out/in of a combo
                    {
                        activeKeys = combos.processActiveKeycodewithComboKeys(activeKeys); 
                    }
            }
            else
            {
                    triggerkeytimer = status->timestamp;
                    combotimer = status->timestamp;
            }
            }    
        }

    #endif

    for (auto keycode : activeKeys) 
    {
        auto hidKeycode = static_cast<uint8_t>(keycode & 0x00FF);
        auto extraModifiers = static_cast<uint8_t>((keycode & 0xFF00) >> 8);

        if (hidKeycode >= KC_A && hidKeycode <= KC_EXSEL)
        {
            currentReport.keycode[bufferposition] = hidKeycode;
            bufferposition++;
        }
        
        //check if the hid keycode contains a modifier. // also check for macros.
        #define MOVE_STEP    5
        uint8_t steps = MOVE_STEP;

        switch (hidKeycode) { 
            case KC_LCTRL:  currentMod |= 1;    currentMod |= extraModifiers; break;
            case KC_LSHIFT: currentMod |= 2;    currentMod |= extraModifiers; break;
            case KC_LALT:   currentMod |= 4;    currentMod |= extraModifiers; break;
            case KC_LGUI:   currentMod |= 8;    currentMod |= extraModifiers; break;
            case KC_RCTRL:  currentMod |= 16;   currentMod |= extraModifiers; break;
            case KC_RSHIFT: currentMod |= 32;   currentMod |= extraModifiers; break;
            case KC_RALT:   currentMod |= 64;   currentMod |= extraModifiers; break;
            case KC_RGUI:   currentMod |= 128;  currentMod |= extraModifiers; break;
            case KC_RESERVED_A5: macroKeys.push_back(keycode); extraModifiers=0; break;                  // KC_RESERVED_A5 is the keycode marker for user macros.
            case KC_RESERVED_A6: specialfunctionKeys.push_back(keycode); extraModifiers=0; break;        // KC_RESERVED_A6 is the keycode marker for special keyboard functions.
            case KC_RESERVED_A7: consumerReports.push_back(keycode);  extraModifiers=0; break;               // KC_RESERVED_A7 is the keycode marker for consumer reports.
            case KC_RESERVED_A8: consumerReports.push_back(keycode);  extraModifiers=0; break;              // KC_RESERVED_A8 is the keycode marker for repeating consumer reports.
            case KC_RESERVED_A9: 
                HIDMouse thismousereport;
                switch (keycode)
                {
                    case KC_MS_OFF:   thismousereport.buttons  = RID_MOUSE; break;
                    case KC_MS_BTN1:  thismousereport.buttons  = MOUSE_BUTTON_LEFT; break;
                    case KC_MS_BTN2:  thismousereport.buttons  = MOUSE_BUTTON_RIGHT; break;
                    case KC_MS_BTN3:  thismousereport.buttons  = MOUSE_BUTTON_MIDDLE; break;
                    case KC_MS_BTN4:  thismousereport.buttons  = MOUSE_BUTTON_BACKWARD; break;
                    case KC_MS_BTN5:  thismousereport.buttons  = MOUSE_BUTTON_FORWARD; break;

                    case KC_MS_UP:    thismousereport.y = -steps; break;
                    case KC_MS_DOWN:  thismousereport.y =  steps; break;
                    case KC_MS_LEFT:  thismousereport.x = -steps; break;
                    case KC_MS_RIGHT: thismousereport.x =  steps; break;

                    case KC_MS_WH_UP:    thismousereport.wheel = -1; break;
                    case KC_MS_WH_DOWN:  thismousereport.wheel =  1; break;
                    case KC_MS_WH_LEFT:  thismousereport.pan   = -1; break;
                    case KC_MS_WH_RIGHT: thismousereport.pan   =  1; break;
                }
                mouseReports.push_back(thismousereport);
                extraModifiers=0;
            break;                  // KC_RESERVED_A8 is the keycode marker for mouse reports. Mousekeys can be repeated... We therefore don't need the macro logic
            case KC_RESERVED_AA: specialKeys.push_back(keycode); extraModifiers=0; break;               // KC_RESERVED_AA is the keycode marker for special keys.
            case KC_RESERVED_AB: specialfunctionKeys.push_back(keycode);  extraModifiers=0; break;      // KC_RESERVED_AB keycode for marking this as a specialfunction for international/special characters (ALT-0233 = é).
        }
        //add all of the extra modifiers into the curren modifier 
        currentMod |= extraModifiers;
        if (bufferposition == 6)
        {
            bufferposition = 0;
        }
    }

    currentReport.modifier = currentMod;
    if (currentReport.modifier || (currentReport.keycode[0]>0)) keyboardReports.push_back(currentReport);
    
    return true;
}

unsigned long KeyScanner::getLastPressed() 
{
    return lastPressed;
}
/**************************************************************************************************************************/

HIDKeyboard KeyScanner::currentReport = {0, {0, 0 ,0, 0, 0, 0}}; 



uint16_t KeyScanner::detectedlayerkeys = 0;
uint16_t KeyScanner::localLayer = 0;


std::vector<uint16_t> KeyScanner::macroKeys {};
std::vector<uint16_t> KeyScanner::specialfunctionKeys {};
std::vector<uint16_t> KeyScanner::specialKeys {};

std::vector<HIDKeyboard> KeyScanner::keyboardReports {};
std::vector<uint16_t> KeyScanner::consumerReports {};
std::vector<HIDMouse>    KeyScanner::mouseReports {};



uint32_t KeyScanner::combotimer = 0;
uint32_t KeyScanner::triggerkeytimer = 0;

uint16_t KeyScanner::oneshotLayer = 0;
uint8_t KeyScanner::currentMod = 0;
unsigned long KeyScanner::lastPressed = 0;
uint8_t KeyScanner::bufferposition = 0;




std::vector<uint16_t> KeyScanner::activeKeys {};
std::vector<uint16_t> KeyScanner::encoderKeys {};
std::vector<uint16_t> KeyScanner::macroBuffer {};
std::vector<uint16_t> KeyScanner::toggleBuffer {};
std::vector<uint16_t> KeyScanner::leaderBuffer {};
std::vector<uint16_t> KeyScanner::oneshotBuffer {};

PersistentState*  KeyScanner::config = NULL;
DynamicState*  KeyScanner::status  = NULL;
