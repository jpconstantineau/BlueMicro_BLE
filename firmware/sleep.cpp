/*
Copyright 2018-2021 <Pierre Constantineau>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include "sleep.h"

extern led_handler statusLEDs; /// Typically a Blue and Red LED
/**************************************************************************************************************************/
// Prepare sense pins for waking up from complete shutdown
/**************************************************************************************************************************/
void prepareSleep() {

  for (int j = 0; j < MATRIX_ROWS; ++j) {
    // set the current row as OUPUT and LOW
    pinMode(rows[j], OUTPUT);
#if DIODE_DIRECTION == COL2ROW
    digitalWrite(rows[j], LOW); // 'enables' a specific row to be "low"
#else
    digitalWrite(rows[j], HIGH); // 'enables' a specific row to be "HIGH"
#endif
  }
  // loops thru all of the columns
  for (int i = 0; i < MATRIX_COLS; ++i) {
#if DIODE_DIRECTION == COL2ROW
    pinMode(columns[i], INPUT_PULLUP_SENSE); // 'enables' the column High Value on the diode; becomes "LOW" when pressed - Sense makes it wake up when sleeping
#else
    pinMode(columns[i],
            INPUT_PULLDOWN_SENSE); // 'enables' the column High Value on the diode; becomes "LOW" when pressed - Sense makes it wake up when sleeping
#endif
  }
#ifdef BLUEMICRO_CONFIGURED_DISPLAY
  OLED.sleep();
#endif

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

#if VCC_ENABLE_GPIO == 1
  switchVCC(false); // turn off VCC when going to sleep. This isn't an optional thing...
#endif

  statusLEDs.sleep();
  sendPWM(0); // forces PWM backlight off
}

void sleepNow() {
  delay(300); // delay to let any keys be released
  prepareSleep();
#if WS2812B_LED_ON == 1
  suspendRGB();
#endif
  sd_power_system_off();
}

/**************************************************************************************************************************/
void gotoSleep(unsigned long timesincelastkeypress, bool connected) {
  // shutdown when unconnected and no keypresses for SLEEPING_DELAY ms
  if ((timesincelastkeypress > SLEEPING_DELAY) && (!connected)) {
    LOG_LV2("SLEEP", "Not Connected Sleep %i", timesincelastkeypress);
    sleepNow();
  }

  // shutdown when unconnected and no keypresses for SLEEPING_DELAY_CONNECTED ms
  if ((timesincelastkeypress > SLEEPING_DELAY_CONNECTED) && (connected)) {
    LOG_LV2("SLEEP", "Connected Sleep %i", timesincelastkeypress);
    sleepNow();
  }
}
