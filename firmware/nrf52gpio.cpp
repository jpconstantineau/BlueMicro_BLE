/*
Copyright 2018-2020 <Pierre Constantineau>

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
#include "nrf52gpio.h"


static int16_t buf[] = {(int16_t)(1 << 15) | (int16_t) DEFAULT_PWM_VALUE}; // Inverse polarity (bit 15), 1500us duty cycle

void setupGpio()
{
      // this code enables the NFC pins to be GPIO.
     if ((NRF_UICR->NFCPINS & UICR_NFCPINS_PROTECT_Msk) == (UICR_NFCPINS_PROTECT_NFC << UICR_NFCPINS_PROTECT_Pos)){
       // Serial.println("Fix NFC pins");
        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy);
        NRF_UICR->NFCPINS &= ~UICR_NFCPINS_PROTECT_Msk;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy);
        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy);
        //Serial.println("Done");
        delay(500);
        NVIC_SystemReset();
      } // end of NFC switch code.

}

/**************************************************************************************************************************/
void setupPWM(uint8_t ledpin)
{
  // Configure BACKLIGHT_LED_PIN as output, and set it to 0
  NRF_GPIO->DIRSET = (1 << ledpin);
  NRF_GPIO->OUTCLR = (1 << ledpin);
  
  
  NRF_PWM2->PRESCALER   = PWM_PRESCALER_PRESCALER_DIV_8; // 1 us
  NRF_PWM2->PSEL.OUT[0] = ledpin ;
  NRF_PWM2->MODE        = (PWM_MODE_UPDOWN_Up << PWM_MODE_UPDOWN_Pos);
  NRF_PWM2->DECODER     = (PWM_DECODER_LOAD_Common     << PWM_DECODER_LOAD_Pos) | 
                          (PWM_DECODER_MODE_RefreshCount   << PWM_DECODER_MODE_Pos);
  NRF_PWM2->LOOP        = (PWM_LOOP_CNT_Disabled       << PWM_LOOP_CNT_Pos);
  NRF_PWM2->COUNTERTOP  = 10000; // 5ms period = 200 Hz PWM frequency
  
  
  NRF_PWM2->SEQ[0].CNT = ((sizeof(buf) / sizeof(uint16_t)) << PWM_SEQ_CNT_CNT_Pos);
  NRF_PWM2->SEQ[0].ENDDELAY = 0;
  NRF_PWM2->SEQ[0].PTR = (uint32_t)&buf[0];
  NRF_PWM2->SEQ[0].REFRESH = 0;
  NRF_PWM2->SHORTS = 0;//(PWM_SHORTS_LOOPSDONE_SEQSTART0_Enabled << PWM_SHORTS_LOOPSDONE_SEQSTART0_Pos);//0;
  
  NRF_PWM2->ENABLE = 1;
  NRF_PWM2->TASKS_SEQSTART[0] = 1; 
  
  }

/**************************************************************************************************************************/

void sendPWM(uint16_t value)
// send PWM config to PWM NRF52 device
// max value for PWM is 15 bits
// 16th bit is used for inverse polarity
{
    value = value & 0x7FFF;  // dropping the 16th bit.  DEFAULT_PWM_MAX_VALUE
    buf[0] = (1 << 15) | value; // Inverse polarity (bit 15), 1500us duty cycle
    NRF_PWM2->SEQ[0].PTR = (uint32_t)&buf[0];
    NRF_PWM2->TASKS_SEQSTART[0] = 1;
}


/**************************************************************************************************************************/
void switchVCC(bool value)
{
  #if VCC_ENABLE_GPIO == 1
  pinMode(VCC_PIN, OUTPUT);
  if(value)
  {
    digitalWrite(VCC_PIN, VCC_POLARITY_ON); 
  }
  else
  {
    digitalWrite(VCC_PIN, !VCC_POLARITY_ON); 
  }
  #endif
}

void switchCharger(bool value)
{
  #if VCC_ENABLE_CHARGER == 1
  pinMode(CHARGER_PIN, OUTPUT);
  if(value)
  {
    digitalWrite(CHARGER_PIN, CHARGER_POLARITY_ON); 
  }
  else
  {
    digitalWrite(CHARGER_PIN, !CHARGER_POLARITY_ON); 
  }
  #endif
}

void setupStatusLEDs(bool blevalue, bool kbvalue)
{
  #ifdef STATUS_BLE_LED_PIN 
      pinMode(STATUS_BLE_LED_PIN, OUTPUT);
  #endif
  #ifdef STATUS_KB_LED_PIN 
      pinMode(STATUS_KB_LED_PIN, OUTPUT);
  #endif

    for (int i=0; i<4; i++) { 
      #ifdef STATUS_BLE_LED_PIN
      if (blevalue) {digitalWrite(STATUS_BLE_LED_PIN, i%2 ? LOW : HIGH );}
      #endif
      #ifdef STATUS_KB_LED_PIN 
      if (kbvalue) {digitalWrite(STATUS_KB_LED_PIN, i%2 ? LOW : HIGH ); }
      #endif
      delay(200); 
    }
}