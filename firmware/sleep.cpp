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
#include "gpioExtension.h"


/**************************************************************************************************************************/
// Prepare sense pins for waking up from complete shutdown
/**************************************************************************************************************************/
void setupWakeUp() {
  uint32_t pindata = 0;
  int loopOne = 0;
  int loopTwo = 0;


  //handle direction
  #if READ_DIRECTION == READ_ON_COLS
    loopOne = MATRIX_ROWS;
    loopTwo = MATRIX_COLS;
  #else //READ_DIRECTION == READ_ON_ROWS
    loopOne = MATRIX_COLS;
    loopTwo = MATRIX_ROWS;
  #endif


  #if DIODE_DIRECTION == COL2ROW && defined(SHIFT_REGISTER_KEYBOARD)
    shiftOutToMakeAllLow();
  #elif DIODE_DIRECTION == ROW2COL && defined(SHIFT_REGISTER_KEYBOARD)
    shiftOutToMakeAllHigh();
  #else
      //sets BIAS gpios (any gpio that is an OUTPUT in the matrix)
    for(int j = 0; j < loopOne; ++j) {                             
      pinMode(gpioBias[j], OUTPUT);
      #if DIODE_DIRECTION == COL2ROW                                         
      digitalWrite(gpioBias[j], LOW);                                       // 'enables' a specific row to be "low" 
      #else
      digitalWrite(gpioBias[j], HIGH);                                       // 'enables' a specific row to be "HIGH"
      #endif
    }
  #endif


  //sets READ IN gpios (any gpio that is an INPUT in the matrix)
  for (int i = 0; i < loopTwo; ++i) {
      #if DIODE_DIRECTION == COL2ROW                                         
        pinMode(gpioReadIn[i], INPUT_PULLUP_SENSE);              // 'enables' the column High Value on the diode; becomes "LOW" when pressed - Sense makes it wake up when sleeping
      #else
        pinMode(gpioReadIn[i], INPUT_PULLDOWN_SENSE);            // 'enables' the column High Value on the diode; becomes "LOW" when pressed - Sense makes it wake up when sleeping
      #endif
  }

}


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
