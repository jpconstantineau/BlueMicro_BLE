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

#include "input_device.h"



        void Input_Device::setup()
        {
            setup_cb();
        }
        void Input_Device::update_data()
        {
            update_data_cb();
        }
        void Input_Device::get_layers(layermask_t &SelectedLayers)
        {
            get_Layers_cb(SelectedLayers);
        }

        void Input_Device::get_digital(DigitalInput_queue_t &ActiveKeys, layernumber_t layer)
        {
            get_Digital_inputs_cb(ActiveKeys, layer);
        }
        void Input_Device::get_analog(AnalogInput_queue_t &ActiveInputs, layernumber_t layer)
        {
            get_Analog_inputs_cb(ActiveInputs, layer);

        }
        void Input_Device::sleep()
        {
            sleep_cb();
        }

        void Input_Device::set_setup_cb(input_device_setup_hardware_cb_t callback)
        {
            setup_cb=callback;
        }
        void Input_Device::set_update_data_cb(input_device_update_data_cb_t callback)
        {
            update_data_cb=callback;
        }
        void Input_Device::set_get_Layers_cb(input_device_get_Layers_cb_t callback)
        {
            get_Layers_cb=callback;
        }
        void Input_Device::set_get_Digital_inputs_cb(input_device_get_Digital_inputs_cb_t callback)
        {
            get_Digital_inputs_cb=callback;
        }
        void Input_Device::set_get_Analog_inputs_cb(input_device_get_Analog_inputs_cb_t callback)
        {
            get_Analog_inputs_cb=callback;
        }
        void Input_Device::set_sleep_cb(input_device_sleep_cb_t callback)
        {
            sleep_cb=callback;
        }