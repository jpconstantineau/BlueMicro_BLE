// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include "sleep.h"

//todo refactor sleep so that each module can register a pre-sleep command.

extern led_handler statusLEDs; /// Typically a Blue and Red LED
/**************************************************************************************************************************/
// Prepare sense pins for waking up from complete shutdown
/**************************************************************************************************************************/
void prepareSleep() {
  

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
      #ifdef BLUEMICRO_CONFIGURED_DISPLAY
      OLED.sleep();
      #endif
#ifdef ENABLE_AUDIO
  #ifdef SPEAKER_PIN
    pinMode(SPEAKER_PIN, OUTPUT);
    digitalWrite(SPEAKER_PIN, LOW);
        tone(SPEAKER_PIN, NOTE_E5, 50);
        delay(65);
        tone(SPEAKER_PIN, NOTE_A4, 50);
        delay(65);
        tone(SPEAKER_PIN, NOTE_E4, 50);
        delay(65);
          digitalWrite(SPEAKER_PIN, LOW);
          pinMode(SPEAKER_PIN, INPUT);
  #endif
  #endif

      #if VCC_ENABLE_GPIO ==1 
      switchVCC(false); // turn off VCC when going to sleep. This isn't an optional thing...
      #endif

  statusLEDs.sleep(); 
  sendPWM(0);  // forces PWM backlight off
  
}

void sleepNow()
{
  delay(300);    // delay to let any keys be released
  prepareSleep();
  #if WS2812B_LED_ON == 1 
    suspendRGB();
  #endif
  sd_power_system_off();
}

/**************************************************************************************************************************/
void gotoSleep(unsigned long timesincelastkeypress,bool connected)
{
  // shutdown when unconnected and no keypresses for SLEEPING_DELAY ms
  if ((timesincelastkeypress>SLEEPING_DELAY)&&(!connected))
  {
    LOG_LV2("SLEEP","Not Connected Sleep %i", timesincelastkeypress);
    sleepNow();
  } 

  // shutdown when unconnected and no keypresses for SLEEPING_DELAY_CONNECTED ms
  if ((timesincelastkeypress>SLEEPING_DELAY_CONNECTED)&&(connected))
  {
    LOG_LV2("SLEEP","Connected Sleep %i", timesincelastkeypress);
    sleepNow();
  } 
}
