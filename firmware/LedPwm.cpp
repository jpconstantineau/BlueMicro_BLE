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
#include "LedPwm.h"
/**************************************************************************************************************************/

#if BACKLIGHT_PWM_ON == 1  //setup PWM module
int16_t pwmval = DEFAULT_PWM_VALUE;
static int16_t buf[] = {(int16_t)(1 << 15) | (int16_t) DEFAULT_PWM_VALUE}; // Inverse polarity (bit 15), 1500us duty cycle


void setupPWM(void)
{
  // Configure BACKLIGHT_LED_PIN as output, and set it to 0
  NRF_GPIO->DIRSET = (1 << BACKLIGHT_LED_PIN);
  NRF_GPIO->OUTCLR = (1 << BACKLIGHT_LED_PIN);
  
  
  NRF_PWM0->PRESCALER   = PWM_PRESCALER_PRESCALER_DIV_8; // 1 us
  NRF_PWM0->PSEL.OUT[0] = BACKLIGHT_LED_PIN;
  NRF_PWM0->MODE        = (PWM_MODE_UPDOWN_Up << PWM_MODE_UPDOWN_Pos);
  NRF_PWM0->DECODER     = (PWM_DECODER_LOAD_Common     << PWM_DECODER_LOAD_Pos) | 
                          (PWM_DECODER_MODE_RefreshCount   << PWM_DECODER_MODE_Pos);
  NRF_PWM0->LOOP        = (PWM_LOOP_CNT_Disabled       << PWM_LOOP_CNT_Pos);
  NRF_PWM0->COUNTERTOP  = 10000; // 5ms period = 200 Hz PWM frequency
  
  
  NRF_PWM0->SEQ[0].CNT = ((sizeof(buf) / sizeof(uint16_t)) << PWM_SEQ_CNT_CNT_Pos);
  NRF_PWM0->SEQ[0].ENDDELAY = 0;
  NRF_PWM0->SEQ[0].PTR = (uint32_t)&buf[0];
  NRF_PWM0->SEQ[0].REFRESH = 0;
  NRF_PWM0->SHORTS = 0;//(PWM_SHORTS_LOOPSDONE_SEQSTART0_Enabled << PWM_SHORTS_LOOPSDONE_SEQSTART0_Pos);//0;
  
  NRF_PWM0->ENABLE = 1;
  NRF_PWM0->TASKS_SEQSTART[0] = 1; 
  
  }


void updatePWM(unsigned long timesincelastkeypress)
{
if (timesincelastkeypress<PWM_TOUCH_INTERVAL)
{
    pwmval = DEFAULT_PWM_VALUE;

}else
{
  if (pwmval > 19) {pwmval = pwmval-10 ;} else {pwmval = 0 ;}
}

  // send PWM config to PWM NRF52 device
  buf[0] = (1 << 15) | pwmval; // Inverse polarity (bit 15), 1500us duty cycle
  NRF_PWM0->SEQ[0].PTR = (uint32_t)&buf[0];
  NRF_PWM0->TASKS_SEQSTART[0] = 1;
}

#endif