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

#include "nrf52battery.h"

/**************************************************************************************************************************/
  BLEBas blebas;                                                                    // Battery Service

Battery::Battery() {    // Constructor
    vbat_raw = 0;
    vbat_mv = 0;
    vbat_vdd = 0;
    vbat_per = 0;
    batt_type = BATT_UNKNOWN;
    _mvToPercent_cb = mvToPercent_default;
}


/**************************************************************************************************************************/
uint32_t Battery::analogReadVDD()
{
  // thanks to vladkozlov69 on github.
  // from https://gist.github.com/vladkozlov69/2500a27cd93245d71573164cda789539

   // uint32_t pin = SAADC_CH_PSELP_PSELP_VDD;
    //uint32_t resolution;
    int16_t value;

    //resolution = 10;


    NRF_SAADC->RESOLUTION = SAADC_RESOLUTION_VAL_10bit;

    NRF_SAADC->ENABLE = (SAADC_ENABLE_ENABLE_Enabled << SAADC_ENABLE_ENABLE_Pos);
    for (int i = 0; i < 8; i++) 
    {
        NRF_SAADC->CH[i].PSELN = SAADC_CH_PSELP_PSELP_NC;
        NRF_SAADC->CH[i].PSELP = SAADC_CH_PSELP_PSELP_NC;
    }
    NRF_SAADC->CH[0].CONFIG =   ((SAADC_CH_CONFIG_RESP_Bypass     << SAADC_CH_CONFIG_RESP_Pos)   & SAADC_CH_CONFIG_RESP_Msk)
                                | ((SAADC_CH_CONFIG_RESP_Bypass     << SAADC_CH_CONFIG_RESN_Pos)   & SAADC_CH_CONFIG_RESN_Msk)
                                | ((SAADC_CH_CONFIG_GAIN_Gain1_6    << SAADC_CH_CONFIG_GAIN_Pos)   & SAADC_CH_CONFIG_GAIN_Msk)
                                | ((SAADC_CH_CONFIG_REFSEL_Internal << SAADC_CH_CONFIG_REFSEL_Pos) & SAADC_CH_CONFIG_REFSEL_Msk)
                                | ((SAADC_CH_CONFIG_TACQ_3us        << SAADC_CH_CONFIG_TACQ_Pos)   & SAADC_CH_CONFIG_TACQ_Msk)
                                | ((SAADC_CH_CONFIG_MODE_SE         << SAADC_CH_CONFIG_MODE_Pos)   & SAADC_CH_CONFIG_MODE_Msk);
    NRF_SAADC->CH[0].PSELN = SAADC_CH_PSELP_PSELP_VDD;
    NRF_SAADC->CH[0].PSELP = SAADC_CH_PSELP_PSELP_VDD;


    NRF_SAADC->RESULT.PTR = (uint32_t)&value;
    NRF_SAADC->RESULT.MAXCNT = 1; // One sample

    NRF_SAADC->TASKS_START = 0x01UL;

    while (!NRF_SAADC->EVENTS_STARTED);
    NRF_SAADC->EVENTS_STARTED = 0x00UL;

    NRF_SAADC->TASKS_SAMPLE = 0x01UL;

    while (!NRF_SAADC->EVENTS_END);
    NRF_SAADC->EVENTS_END = 0x00UL;
    NRF_SAADC->TASKS_STOP = 0x01UL;

    while (!NRF_SAADC->EVENTS_STOPPED);
    NRF_SAADC->EVENTS_STOPPED = 0x00UL;

    if (value < 0) 
    {
        value = 0;
    }

    NRF_SAADC->ENABLE = (SAADC_ENABLE_ENABLE_Disabled << SAADC_ENABLE_ENABLE_Pos);

    return value; 
}
/**************************************************************************************************************************/
uint32_t Battery::readVBAT(void) {
  analogReference(AR_INTERNAL_3_0); // Set the analog reference to 3.0V (default = 3.6V)
  analogReadResolution(12);         // Set the resolution to 12-bit (0..4095) // Can be 8, 10, 12 or 14
  delay(1);                         // Let the ADC settle  OK since we are calling this from the long term monitoring loop
  vbat_raw = analogRead(VBAT_PIN);       // Get the raw 12-bit, 0..3000mV ADC value
  analogReference(AR_DEFAULT);      // Set the ADC back to the default settings - just in case we use it somewhere else
  analogReadResolution(10);         // Set the ADC back to the default settings - just in case we use it somewhere else
  return vbat_raw;
};
/**************************************************************************************************************************/
void Battery::updateBattery(void)
{
  switch (batt_type)
  {
    case BATT_UNKNOWN:
        vbat_vdd =  analogReadVDD()*3600/1024; // returns a uint32_t value of the mV. 0.6V*6/10bits
        if (vbat_vdd<3000) batt_type=BATT_CR2032;
        vbat_raw = readVBAT();                                // Get a raw ADC reading
        vbat_mv = vbat_raw * VBAT_MV_PER_LSB * VBAT_DIVIDER_COMP;
        if (vbat_mv>3400) batt_type=BATT_LIPO;
    break;
    case BATT_CR2032:
        vbat_vdd =  analogReadVDD()*3600/1024; // returns a uint32_t value of the mV. 0.6V*6/10bits
        vbat_mv = vbat_vdd;
    break;
    case BATT_LIPO:
        vbat_raw = readVBAT();                                // Get a raw ADC reading
                // Convert the raw value to compensated mv, taking the resistor-
                // divider into account (providing the actual LIPO voltage)
                // ADC range is 0..3000mV and resolution is 12-bit (0..4095),
                // VBAT voltage divider is 2M + 0.806M, which needs to be added back
        vbat_mv = vbat_raw * VBAT_MV_PER_LSB * VBAT_DIVIDER_COMP;
    break;
  }
    
  _mvToPercent_cb(vbat_per, vbat_mv, batt_type);            // Convert from raw mv to percentage (default is based on LIPO chemistry)
  blebas.notify(vbat_per);                                  // update the Battery Service.  Use notify instead of write to ensure that subscribers receive the new value.
}

/**************************************************************************************************************************/
void Battery::setmvToPercentCallback(mvToPercent_cb_t callback)
{
  _mvToPercent_cb = callback;
}
/**************************************************************************************************************************/
// Callbacks must be defined outside of the class.
/**************************************************************************************************************************/
void mvToPercent_default(uint8_t & vbat_per, uint32_t mvolts, uint8_t batt_type)
{
  switch (batt_type)
  {
    case BATT_UNKNOWN:
       vbat_per = 50;
    break;
    case BATT_CR2032:
      if(mvolts<2600) vbat_per= 0;
      if(mvolts >3000) vbat_per= 100;
      mvolts -= 2600;
      vbat_per= (mvolts /4 );  // the range really meeds testing...  /4 = 2600 to 3000 /2 = 2800 to 3000
    break;
    case BATT_LIPO:
      if(mvolts<3300) vbat_per= 0;
      if(mvolts <3600) {
        mvolts -= 3300;
        vbat_per= mvolts/30;
      }
      mvolts -= 3600;
      vbat_per= (uint8_t) 10 + (uint8_t)((mvolts * 15)/100);  // thats mvolts /6.66666666
      if (vbat_per>100){vbat_per=100;} // checks if we are higher than 100%. when this is the case windows doesn't show anything...
    break;    
  } 
}
/**************************************************************************************************************************/

void mvToPercent_test(uint8_t & vbat_per, uint32_t mvolts, uint8_t batt_type)
{
  vbat_per = mvolts/100; // converts mvolts (3000 - 4200 mv on lipo) to 30-42% to see mv directly in battery service...
}
