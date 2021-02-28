/*
Copyright 2020-2021 <Pierre Constantineau>

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



#ifndef USB_H
#define USB_H

    #include <bluefruit.h>
    #include "firmware_config.h"
    #include "keymap.h"
    #include "datastructures.h"
    #include "HID.h"

    #ifdef NRF52840_XXAA  // only the 840 has USB available.
        #ifdef ARDUINO_NRF52_ADAFRUIT
            // do nothing since the Adafruit BSP doesn't support ediv.
        #endif
        #ifdef ARDUINO_NRF52_COMMUNITY
            #include "Adafruit_TinyUSB.h"
            #define TINYUSB_AVAILABLE 1
        #endif
    #endif



    // these functions will be defined for all cases (nrf52832 and nrf52840) but will work differently.
    void usb_setup();
    bool usb_isConnected();
    void usb_wakeup();
    void usb_sendKeys(uint8_t currentReport[8]);
    void usb_sendKeys(std::array<uint8_t,8> currentReport);
    void usb_sendMediaKey(uint16_t keycode);
    void usb_sendMouseKey(uint16_t keycode);
    void usb_sendMouseMove(uint16_t keycode, uint16_t steps);
    void hid_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize);

#endif