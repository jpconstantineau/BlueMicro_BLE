/*
Copyright 2018-2020 <Pierre Constantineau, Julian Komaromy>

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

#include "firmware_config.h"

/* About the firmware:
 *   
 * https://github.com/jpconstantineau/BlueMicro_BLE
 * 
 * 
 */

 /* Making Changes
  * 
  * Edit the following files:
  * keyboard_config.h:  This file contains the Bluetooth definition as well as the Single/Left/Right configuration of your keyboard.
  * hardware_config.h:  This file contains the pin assignments for the keyboard and nRF52 module you use. 
  * keymap.cpp:         This file contains your keymap.  
  * keymap.h:           This file contains your keymap helper definitions and macros.
  * 
  * The folder "keyboards" contains a number of example config files you can copy to get started.
  */

  /* Required Software and Libraries
   * 
   * Follow the steps for the Adafruit NRF52 BSP
   * https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/arduino-bsp-setup
   * 
   */

   /* Compiling and Flashing
    * 
    * Once you have completed installing the required libraries, you should be able to compile and flash the firmware.
    * 
    * Board Selected:
    * Most nrf52832 based boards: Adafruit nRF52 Feather
    * Most nrf52840 based boards: PCA10056
    * Programmer: Bootloader DFU for BlueFruit nRF52
    * 
    * Note that for serial DFU (Device Firmware Upgrade) you may need to manually press the "reset" button if the serial reset circuitry using the DTR line is not used.  
    * For PCA10056 boards, you may need to manually "double-reset" to put the board in DFU mode. 
    */

    /*  Flashing the Bootloader
     * 
     * In order to flash the bootloader and the Nordic Softdevice, you will need a j-link (SWD flasher)
     * The Adafruit library uses nrfutil; which in turns calls the j-link libraries from Segger.  
     * Segger manufactures the genuine J-link.  They also provide the j-link embedded in the Nordic nRF52832-DK.
     * The cheapest Genuine Segger J-link is the J-Link EDU Mini.
     * There are a number of chinese J-Link clones that may work with the j-link software your mileage may vary...
     * 
     * Required Bootloader: Depends on board you have.
     * 
     * Follow the instructions at Adafruit (link above) to download, install the necessary software
     * 
     * Other SWD programmers are available but other software will need to be used to flash the bootloader to the device.
     * Unless you have experience with these devices, we cannot recommend going with them if you are just starting out.
     * Such device include:
     * ST-Link V2 - OpenOCD
     * Black Magic Probe - arm-none-eabi-gdb
     * 
     * Refer to Joric's wiki for more information on flashing the bootloader using other tools
     * https://github.com/joric/nrfmicro/wiki/Bootloader
     */

     /* Useful Tools
      * 
      * http://www.keyboardtester.com/
      * https://config.qmk.fm/#/test
      * http://gadzikowski.com/nkeyrollover.html
      * 
      */
