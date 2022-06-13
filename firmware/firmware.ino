// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause
/**************************************************************************************************************************/
/* About the BlueeMicro_BLE firmware:
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
   * bluemicro_engine
   */

   /* Compiling and Flashing
    * 
    * Once you have completed installing the required libraries, you should be able to compile and flash the firmware.
    * 
    * Board Selected:
    * Most nrf52832 based boards: Adafruit nRF52 Feather
    * Most nrf52840 based boards: Nordic nRF52840 DK (PCA10056)
    * Programmer: Bootloader DFU for BlueFruit nRF52
    * 
    * Note that for serial DFU (Device Firmware Upgrade) you may need to manually press the "reset" button if the serial reset circuitry using the DTR line is not used.  
    * For PCA10056 boards, you may need to manually "double-reset" to put the board in DFU mode. 
    */

/**************************************************************************************************************************/
#include "firmware.h"

// cppcheck-suppress unusedFunction
void setup() {
  addsetupcommands();
  addkeyboardcommands();
  addloopcommands();
  SORTCOMMANDS(commandList);
  RUNCOMMANDS(setupQueue, commandList);
}

// cppcheck-suppress unusedFunction
void loop() {  
  static uint32_t last_timestamp = 0;
  RUNCOMMANDS(loopQueue, commandList);   
  uint32_t end_timestamp = millis();
  uint32_t diff = (last_timestamp + HIDREPORTINGINTERVAL > end_timestamp) ? last_timestamp + HIDREPORTINGINTERVAL - end_timestamp:1;
  last_timestamp = end_timestamp;
  delay(diff); 
}

// cppcheck-suppress unusedFunction  
extern "C" void vApplicationIdleHook(void) {
    sd_power_mode_set(NRF_POWER_MODE_LOWPWR); // 944uA
    //sd_power_mode_set(NRF_POWER_MODE_CONSTLAT); // 1.5mA
    sd_app_evt_wait();  // puts the nrf52 to sleep when there is nothing to do.  You need this to reduce power consumption. (removing this will increase current to 8mA)
};
