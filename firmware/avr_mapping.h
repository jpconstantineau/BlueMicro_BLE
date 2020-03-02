/*
Copyright 2018 <Pierre Constantineau>

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

/*
These defines map the AVR-based ports of the Arduino Pro to the NRF52832 GPIO pins.
This makes it simpler to migrate from the Arduino Pro Micro to the BlueMicro.
*/

#ifndef AVR_MAPPING_H
#define AVR_MAPPING_H

// AVAILABLE OPTIONS - IDs defined in Hardware_variants.h
// FEATHERNRF52832 Not an AVR/Pro Micro Footprint
// BLUEMICROV1_0   CR2032   Serial connected to D3/D2. Nothing connected to RAW.
// BLUEMICROV1_1   CR2032   Serial not connected to D3/D2. Nothing connected to RAW.
// BLUEMICROV2_0   LiPo     RAW not connected through a jumper to LiPo Charger.  Serial not connected to D3/D2. CH340 on board but did not work (design flaw)
// BLUEMICROV2_0B  LiPo     RAW not connected through a jumper to LiPo Charger. Serial not connected to D3/D2. Good for gherkin
// BLUEMICROV2_0C  LiPo     RAW connected to LiPo Charger. Serial connected to D3/D2
// BLUENANO1_0     No Batt  3.3v regulator on board, no charger.  
// BLUENANO2_0     LiPo     RAW connected to LiPo Charger.
// BLUEMICRO840V1  LiPo     To Come... Currently being designed.

#ifdef ARDUINO_NRF52832_FEATHER
    #if HARDWARE_MAPPING == BLUEMICROV1_0
        #define BATTERY_TYPE BATT_CR2032
        #define D3      6  //
        #define D2      8   //
        #define D1      25  //sda
        #define D0      26  //scl
        #define D4      27
        #define C6      28
        #define D7      29
        #define E6      30
        #define B4      15
        #define B5      16

        #define F4      5
        #define F5      4
        #define F6      3
        #define F7      2
        #define B1      12  //sck
        #define B3      14  //miso
        #define B2      13  //mosi
        #define B6      11
        
    #elif HARDWARE_MAPPING == BLUEMICROV1_1
        #define BATTERY_TYPE BATT_CR2032
        #define D3      17  //
        #define D2      7   //
        #define D1      25  //sda
        #define D0      26  //scl
        #define D4      27
        #define C6      28
        #define D7      29
        #define E6      30
        #define B4      15
        #define B5      16

        #define F4      5
        #define F5      4
        #define F6      3
        #define F7      2
        #define B1      12  //sck
        #define B3      14  //miso
        #define B2      13  //mosi
        #define B6      11

 #elif HARDWARE_MAPPING == BLUEMICROV2_0
        #define BATTERY_TYPE BATT_LIPO
        #define D3      17  //
        #define D2      7   //
        #define D1      25  //sda
        #define D0      26  //scl
        #define D4      27
        #define C6      28
        #define D7      29
        #define E6      30
        #define B4      15
        #define B5      16

        #define F4      5
        #define F5      4
        #define F6      3
        #define F7      2
        #define B1      12  //sck
        #define B3      14  //miso
        #define B2      13  //mosi
        #define B6      11

    #elif HARDWARE_MAPPING == BLUEMICROV2_0B
        #define BATTERY_TYPE BATT_LIPO
        #define D3      17  //
        #define D2      7   //
        #define D1      25  //sda
        #define D0      26  //scl
        #define D4      27
        #define C6      28
        #define D7      29
        #define E6      30
        #define B4      15
        #define B5      16

        #define F4      5
        #define F5      4
        #define F6      3
        #define F7      2
        #define B1      12  //sck
        #define B3      14  //miso
        #define B2      13  //mosi
        #define B6      11
    #elif HARDWARE_MAPPING == BLUEMICROV2_0C
        #define BATTERY_TYPE BATT_LIPO
        #define D3      6  //
        #define D2      8   //
        #define D1      25  //sda
        #define D0      26  //scl
        #define D4      27
        #define C6      28
        #define D7      29
        #define E6      30
        #define B4      15
        #define B5      16

        #define F4      5
        #define F5      4
        #define F6      3
        #define F7      2
        #define B1      12  //sck
        #define B3      14  //miso
        #define B2      13  //mosi
        #define B6      11
    #elif HARDWARE_MAPPING == BLUEMICROV2_1A
        #define BATTERY_TYPE BATT_LIPO
        #define D3      18  // NOTE on board serial
        #define D2      7   // NOTE on board serial
        #define D1      25  //sda
        #define D0      26  //scl
        #define D4      27
        #define C6      28
        #define D7      29
        #define E6      30
        #define B4      15
        #define B5      16

        #define F4      5
        #define F5      4
        #define F6      3
        #define F7      2
        #define B1      12  //sck
        #define B3      14  //miso
        #define B2      13  //mosi
        #define B6      11
    #elif HARDWARE_MAPPING == BLUENANO1_0
        #define BATTERY_TYPE BATT_UNKNOWN
        #define D3      5  //
        #define D2      4   //
        #define D1      25  //sda
        #define D0      26  //scl
        #define D4      3
        #define C6      2
        #define D7      30
        #define E6      29
        #define B4      28
        #define B5      27

        #define F4      7
        #define F5      9
        #define F6      10
        #define F7      11
        #define B1      12  //sck
        #define B3      14  //miso
        #define B2      13  //mosi
        #define B6      18
    #elif HARDWARE_MAPPING == BLUENANO2_0
        #define BATTERY_TYPE BATT_LIPO
        #define D3      5  //
        #define D2      4   //
        #define D1      3  
        #define D0      2  
        #define D4      30
        #define C6      29
        #define D7      28
        #define E6      27
        #define B4      26
        #define B5      25

        #define F4      7
        #define F5      9
        #define F6      10
        #define F7      11
        #define B1      12  
        #define B3      13  
        #define B2      14
        #define B6      18
    #else // use elseif  Use BlueMicro V2.0c config details as default.
        #define BATTERY_TYPE BATT_LIPO
        #define D3      6  //
        #define D2      8   //
        #define D1      25  //sda
        #define D0      26  //scl
        #define D4      27
        #define C6      28
        #define D7      29
        #define E6      30
        #define B4      15
        #define B5      16

        #define F4      5
        #define F5      4
        #define F6      3
        #define F7      2
        #define B1      12  //sck
        #define B3      14  //miso
        #define B2      13  //mosi
        #define B6      11
    #endif
#endif

#ifdef ARDUINO_NRF52840_PCA10056
  #if HARDWARE_MAPPING == BLUEMICRO840V1_0
        #define BATTERY_TYPE BATT_LIPO
        #define D3      6  
        #define D2      8   
        #define D1      15  
        #define D0      17  
        #define D4      20
        #define C6      13
        #define D7      24
        #define E6      9
        #define B4      10
        #define B5      38 //1.06 = 32+6

        #define F4      30
        #define F5      26  
        #define F6      29
        #define F7      2
        #define B1      45 //1.13  = 32+13
        #define B3      3
        #define B2      28
        #define B6      43 //1.11 = 32+11
  #endif
#endif

#endif /* AVR_MAPPING_H */
