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

#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H
#include <stdint.h>
#include <vector>

#include "Key.h"


enum class AnalogInputType {
    NONE = 0,
    MOUSE_X = 1,
    MOUSE_Y= 2,
    MOUSE_WHEEL = 3,
    MOUSE_PAN = 4,
    GAME_LEFT_X = 5,
    GAME_LEFT_Y = 6,
    GAME_RIGHT_X = 7,
    GAME_RIGHT_Y = 8,  
    GAME_TRIGGER_L = 9,
    GAME_TRIGGER_R = 10, 
};

typedef struct {
    AnalogInputType type;
    int8_t value;
} AnalogInput_t;

typedef uint16_t layermask_t;
typedef uint8_t  layernumber_t;

typedef void (*layer_processor_cb_t)(layernumber_t &activeLayer, layermask_t SelectedLayers); 
typedef void (*process_user_layers_cb_t)(layermask_t layermask);

typedef std::vector<AnalogInput_t>  AnalogInput_queue_t;
typedef std::vector<KeyDefinition> DigitalInput_queue_t;

typedef std::vector<Input_Device>  Input_Device_List_t;

typedef void (*input_device_setup_hardware_cb_t)(); 
typedef void (*input_device_update_data_cb_t)(); 
typedef void (*input_device_get_Layers_cb_t)(layermask_t &SelectedLayers); 
typedef void (*input_device_get_Digital_inputs_cb_t)(DigitalInput_queue_t &ActiveKeys, layernumber_t layer); 
typedef void (*input_device_get_Analog_inputs_cb_t)(AnalogInput_queue_t &ActiveInputs, layernumber_t layer); 
typedef void (*input_device_sleep_cb_t)(); 

  class Input_Device {
    public:
        void setup();
        void update_data();
        void get_layers(layermask_t &SelectedLayers);
        void get_digital(DigitalInput_queue_t &ActiveKeys, layernumber_t layer);
        void get_analog(AnalogInput_queue_t &ActiveInputs, layernumber_t layer);
        void sleep();

        void set_setup_cb(input_device_setup_hardware_cb_t callback);
        void set_update_data_cb(input_device_update_data_cb_t callback);
        void set_get_Layers_cb(input_device_get_Layers_cb_t callback);
        void set_get_Digital_inputs_cb(input_device_get_Digital_inputs_cb_t callback);
        void set_get_Analog_inputs_cb(input_device_get_Analog_inputs_cb_t callback);
        void set_sleep_cb(input_device_sleep_cb_t callback);

    private:
        input_device_setup_hardware_cb_t        setup_cb;
        input_device_update_data_cb_t           update_data_cb;
        input_device_get_Layers_cb_t            get_Layers_cb;
        input_device_get_Digital_inputs_cb_t    get_Digital_inputs_cb;
        input_device_get_Analog_inputs_cb_t     get_Analog_inputs_cb;
        input_device_sleep_cb_t                 sleep_cb;
  }

#endif /* INPUT_DEVICE_H */