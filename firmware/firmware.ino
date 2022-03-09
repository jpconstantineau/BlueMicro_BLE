// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include "firmware_config.h"

/* About the firmware:
 *  
 * Documentation: http://bluemicro.jpconstantineau.com/docs/  
 * Youtube Channel: https://www.youtube.com/channel/UCFpGp4hHe03nvF9c8_gF_jA
 * Github Repository: https://github.com/jpconstantineau/BlueMicro_BLE
 * 
 */

 /* Making Changes for your own keyboard:
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
   * Follow the steps for the Adafruit NRF52 Board Support Package
   * https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/arduino-bsp-setup
   * 
   * You will need the following libraries installed:
   * bluemicro_hid
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
