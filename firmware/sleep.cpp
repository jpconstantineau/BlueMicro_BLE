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
#include "sleep.h"
#include "LedRGB.h"


#if !defined(SHIFT_REGISTER_KEYBOARD)
/**************************************************************************************************************************/
// Prepare sense pins for waking up from complete shutdown
/**************************************************************************************************************************/
void setupWakeUp() {
  uint32_t pindata = 0;
  for(int j = 0; j < MATRIX_ROWS; ++j) {                             
    //set the current row as OUPUT and LOW
    pinMode(rows[j], OUTPUT);
    #if DIODE_DIRECTION == COL2ROW                                         
    digitalWrite(rows[j], LOW);                                       // 'enables' a specific row to be "low" 
    #else
    digitalWrite(rows[j], HIGH);                                       // 'enables' a specific row to be "HIGH"
    #endif
  }
  //loops thru all of the columns
  for (int i = 0; i < MATRIX_COLS; ++i) {
      #if DIODE_DIRECTION == COL2ROW                                         
        pinMode(columns[i], INPUT_PULLUP_SENSE);              // 'enables' the column High Value on the diode; becomes "LOW" when pressed - Sense makes it wake up when sleeping
      #else
        pinMode(columns[i], INPUT_PULLDOWN_SENSE);            // 'enables' the column High Value on the diode; becomes "LOW" when pressed - Sense makes it wake up when sleeping
      #endif
  }
}
#endif 


#if defined(SHIFT_REGISTER_KEYBOARD)
/**************************************************************************************************************************/
// Prepare sense pins for waking up from complete shutdown
/**************************************************************************************************************************/
void setupWakeUp() {
  uint32_t pindata = 0;

  //make all column shift registers high - we want all buttons to wait for any one button press
  shiftOutToMakeAllColumnsHigh2();

  //loops thru all of the rows
  for (int i = 0; i < MATRIX_ROWS; ++i) {
        pinMode(rows[i], INPUT_PULLDOWN_SENSE);            // 'enables' the column High Value on the diode; becomes "LOW" when pressed - Sense makes it wake up when sleeping
  }

}
#endif


/**************************************************************************************************************************/
void gotoSleep(unsigned long timesincelastkeypress,bool connected)
{
  // shutdown when unconnected and no keypresses for SLEEPING_DELAY ms
  if ((timesincelastkeypress>SLEEPING_DELAY)&&(!connected))
  {
    LOG_LV2("SLEEP","Not Connected Sleep %i", timesincelastkeypress);
    #if WS2812B_LED_ON == 1 
    suspendRGB();
    #endif
    setupWakeUp();
    sd_power_system_off();
  } 

  // shutdown when unconnected and no keypresses for SLEEPING_DELAY_CONNECTED ms
  if ((timesincelastkeypress>SLEEPING_DELAY_CONNECTED)&&(connected))
  {
    LOG_LV2("SLEEP","Connected Sleep %i", timesincelastkeypress);
    #if WS2812B_LED_ON == 1 
    suspendRGB();
    #endif
    setupWakeUp();
    sd_power_system_off();
  } 
}
 

//********************************************************************************************//
//* Helper functions for Keyboards using Shift Registers to drive columns high in order to   *//
//* save I/O on nrf52840                                                                     *//
//* Shift register code is currently setup to use                                            *//
//********************************************************************************************//
#if defined(SHIFT_REGISTER_KEYBOARD)
 
    //makes a specific "pin"
    void shiftOutToMakeColumnHigh2(int column){

        uint16_t shiftValue = pow(2, column);
        uint8_t shiftValLow = shiftValue & 0xFF;
        uint8_t shiftValHigh = (shiftValue & 0xFF00) >> 8;

        digitalWrite(SER_LATCH, LOW);
        shiftOut(SER_DATA, SER_CLK, MSBFIRST, shiftValHigh); //first number to 255
        shiftOut(SER_DATA, SER_CLK, MSBFIRST, shiftValLow); //second number to 255
        digitalWrite(SER_LATCH, HIGH);
    }


    void shiftOutToMakeAllColumsLow2(){

        uint8_t shiftValLow = 0x00;
        uint8_t shiftValHigh = 0x00;

        digitalWrite(SER_LATCH, LOW);
        shiftOut(SER_DATA, SER_CLK, LSBFIRST, shiftValHigh); //first number to 255
        shiftOut(SER_DATA, SER_CLK, LSBFIRST, shiftValLow); //second number to 255
        digitalWrite(SER_LATCH, HIGH);
    }


    void shiftOutToMakeAllColumnsHigh2(){

        uint8_t shiftValLow = 0xFF;
        uint8_t shiftValHigh = 0xFF;

        digitalWrite(SER_LATCH, LOW);
        shiftOut(SER_DATA, SER_CLK, LSBFIRST, shiftValHigh); //first number to 255
        shiftOut(SER_DATA, SER_CLK, LSBFIRST, shiftValLow); //second number to 255
        digitalWrite(SER_LATCH, HIGH);
    }

#endif 