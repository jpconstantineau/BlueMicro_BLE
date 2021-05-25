/*
Copyright 2021-2021 <Pierre Constantineau>

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

#include "input_processor.h"


Input_Processor::Input_Processor() {    // Constructor
    layer_processor_cb = default_layer_processor;
    process_user_layers_cb = default_process_user_layers;
}

void Input_Processor::add_input_device(Input_Device &device)
{
    hardwarelist.push_back(device);
}

void Input_Processor::update_data()
{
    std::for_each(hardwarelist.begin(), hardwarelist.end(),[this](Input_Device device ){device.update_data();});
}
void Input_Processor::get_layers()
{
    std::for_each(hardwarelist.begin(), hardwarelist.end(),[this](Input_Device device ){device.get_layers(SelectedLayers);}); 
   
}

void Input_Processor::get_digital()
{
    ActiveKeys.clear();
    std::for_each(hardwarelist.begin(), hardwarelist.end(),[this](Input_Device device ){device.get_digital(ActiveKeys,ActiveLayer);}); 
}

void Input_Processor::get_analog()
{
    ActiveInputs.clear();
    std::for_each(hardwarelist.begin(), hardwarelist.end(),[this](Input_Device device ){device.get_analog(ActiveInputs,ActiveLayer);}); 
}

void Input_Processor::sleep()
{
   std::for_each(hardwarelist.begin(), hardwarelist.end(),[this](Input_Device device ){device.sleep();}); 
}

void Input_Processor::process_layers()
{
    process_user_layers_cb(SelectedLayers);         // calls any user layer pre-processing (tri-layers)
    layer_processor_cb(ActiveLayer,SelectedLayers); // collapses the mask to a single layer.
}


void Input_Processor::process_digital()
{
    hidkeyboard_report.clear();
    uint8_t bufferpos = 0;
    std::for_each(ActiveKeys.begin(), ActiveKeys.end(),[this, bufferpos](KeyDefinition keycode){
            auto hidKeycode = static_cast<uint8_t>(keycode & 0x00FF);
            auto extraModifiers = static_cast<uint8_t>((keycode & 0xFF00) >> 8);

            //Standard Keyboard Report

            if (hidKeycode >= KC_A && hidKeycode <= KC_EXSEL)
            {
                hidkeyboard_report.keycode[bufferpos] = hidKeycode;
                bufferpos++;
            }

             //check if the hid keycode contains a modifier. // also check for macros.
            switch (hidKeycode) { 
                case KC_LCTRL:  hidkeyboard_report.modifier  |= 1;    break;
                case KC_LSHIFT: hidkeyboard_report.modifier  |= 2;    break;
                case KC_LALT:   hidkeyboard_report.modifier  |= 4;    break;
                case KC_LGUI:   hidkeyboard_report.modifier  |= 8;    break;
                case KC_RCTRL:  hidkeyboard_report.modifier  |= 16;   break;
                case KC_RSHIFT: hidkeyboard_report.modifier  |= 32;   break;
                case KC_RALT:   hidkeyboard_report.modifier  |= 64;   break;
                case KC_RGUI:   hidkeyboard_report.modifier  |= 128;  break;
                //case KC_RESERVED_A5: if(!processingmacros){macro = keycode; processingmacros=true; } extraModifiers=0; break;                 // KC_RESERVED_A5 is the keycode marker for user macros.
                //case KC_RESERVED_A6: if(!processingmacros){specialfunction = keycode; processingmacros=true;} extraModifiers=0; break;        // KC_RESERVED_A6 is the keycode marker for special keyboard functions.
                //case KC_RESERVED_A7: if(!processingmacros){consumer = keycode; processingmacros=true;} extraModifiers=0; break;               // KC_RESERVED_A7 is the keycode marker for consumer reports.
                //case KC_RESERVED_A8: consumer = keycode;  extraModifiers=0; break;              // KC_RESERVED_A8 is the keycode marker for repeating consumer reports.
                //case KC_RESERVED_A9: mouse = keycode; extraModifiers=0; break;                  // KC_RESERVED_A8 is the keycode marker for mouse reports. Mousekeys can be repeated... We therefore don't need the macro logic
                //case KC_RESERVED_AA: special_key = keycode; extraModifiers=0; break;            // KC_RESERVED_AA is the keycode marker for special keys.
                //case KC_RESERVED_AB: if(!processingmacros){specialfunction = keycode; processingmacros=true;} extraModifiers=0; break;               // KC_RESERVED_AB keycode for marking this as a specialfunction for international/special characters (ALT-0233 = é).
            }       

            // Add to Consumer Report

            // Add to Mouse Report (Buttons)

            // Add to Game Report (Buttons Only)


            // Add all of the extra modifiers into the current modifier 
            hidkeyboard_report.modifier  |= extraModifiers;
            if (bufferpos == 6)
            {
                bufferpos = 0;
            }
        
        }); 


}

void Input_Processor::process_analog()
{

}

void Input_Processor::process_inputs()
{
    get_layers();
    process_layers();
    get_digital();
    get_analog();
    //process_combos();  Still to do...
    process_digital();
    process_analog();


}


/**************************************************************************************************************************/
void Input_Processor::set_layer_processor_cb(layer_processor_cb_t callback)
{
    layer_processor_cb = callback;
}

void Input_Processor::set_process_user_layers_cb(process_user_layers_cb_t callback)
{
    process_user_layers_cb = callback;
}
/**************************************************************************************************************************/

void default_layer_processor(layernumber_t &layerid, layermask_t SelectedLayers)
{
    //this will return the highest layer
    layerid = 0;
    if (SelectedLayers>0)// skip the calc if no layers are selected
    {
    while (SelectedLayers >>= 1) {
        layerid++;
        }
    }
}

void default_process_user_layers(layermask_t layermask)
{
   ;
}

/**************************************************************************************************************************/
// inspired by QMK's update_tri_layer_state... Modified to replace instead of adding to detected layer keys
// can be called multiple times to catch multiple 2-layer patterns
/**************************************************************************************************************************/
void Input_Processor::process_for_tri_layers(uint8_t if_layer1, uint8_t and_layer2, uint8_t use_layer3)
{
    uint16_t mask12 = (1UL << if_layer1) | (1UL << and_layer2);             // merge the two layers with bitwise shifts to detect the triggered layer keys
    uint16_t mask3 = 1UL << use_layer3;                                     // create a mask to return the resulting layer
    SelectedLayers = (SelectedLayers & mask12) == mask12 ? ((SelectedLayers & ~mask12) | mask3) : (SelectedLayers); // if SelectedLayers has mask12 in it,remove mask12 and add extra layer; otherwise return as is.
}