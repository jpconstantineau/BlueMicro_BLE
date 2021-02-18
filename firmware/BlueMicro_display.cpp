/*
Copyright 2018-2021 <Pierre Constantineau>

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
#include "BlueMicro_display.h"


#ifdef BLUEMICRO_CONFIGURED_DISPLAY
    #ifdef U8X8_HAVE_HW_I2C
      TwoWire  Wire2(NRF_TWIM0, NRF_TWIS0, SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn,I2C_SDA_PIN, I2C_SCK_PIN );
    #endif
    DISPLAY_U8G2_CONSTRUCTOR u8g2(DISPLAY_U8G2_ROTATION, /* reset=*/ U8X8_PIN_NONE); 
#endif
/**************************************************************************************************************************/
BlueMicro_Display::BlueMicro_Display(PersistentState* cfg, DynamicState* stat) {    // Constructor
    config=cfg;
    status=stat;
    updatemode = DISPLAY_UPDATE_STARTUP;
    _startupUpdateDisplay_cb = drawStartup;
    _statusUpdateDisplay_cb = drawStatus;
    _debugUpdateDisplay_cb = drawDebug;
}

/**************************************************************************************************************************/
void BlueMicro_Display::setStartupDisplayCallback(updateDisplay_cb_t callback)
{
_startupUpdateDisplay_cb = callback;
}
/**************************************************************************************************************************/
void BlueMicro_Display::setStatusDisplayCallback(updateDisplay_cb_t callback)
{
_statusUpdateDisplay_cb = callback;
}
/**************************************************************************************************************************/
void BlueMicro_Display::setDebugDisplayCallback(updateDisplay_cb_t callback)
{
_debugUpdateDisplay_cb = callback;
}
/**************************************************************************************************************************/
void BlueMicro_Display::changeUpdateMode(DisplayUpdateType mode)
{
    updatemode = mode;
}
/**************************************************************************************************************************/
void BlueMicro_Display::begin(void)
{
    #ifdef BLUEMICRO_CONFIGURED_DISPLAY
        #ifdef U8X8_HAVE_HW_I2C
            Wire = Wire2;
        #endif
        switchVCC(true);
        u8g2.begin();
        u8g2.clearBuffer();
        _startupUpdateDisplay_cb(config,status);
        u8g2.sendBuffer();
    #endif
}
/**************************************************************************************************************************/
void BlueMicro_Display::update(void)
{
    #ifdef BLUEMICRO_CONFIGURED_DISPLAY
        u8g2.clearBuffer();
        switch(updatemode)
        {
        case DISPLAY_UPDATE_STARTUP: _startupUpdateDisplay_cb(config,status); break;  
        case DISPLAY_UPDATE_STATUS: _statusUpdateDisplay_cb(config,status); break;  
        case DISPLAY_UPDATE_DEBUG: _debugUpdateDisplay_cb(config,status); break;  
        }
        u8g2.sendBuffer();
    #endif
}
/**************************************************************************************************************************/
void BlueMicro_Display::clear()
{
    #ifdef BLUEMICRO_CONFIGURED_DISPLAY
        u8g2.clearBuffer();					// clear the internal memory
    #endif
}
/**************************************************************************************************************************/
 void BlueMicro_Display::sleep(void)
 {
     #ifdef BLUEMICRO_CONFIGURED_DISPLAY
        u8g2.clearBuffer();
        u8g2.sendBuffer();
        u8g2.setPowerSave(1);
     #endif
 }
/**************************************************************************************************************************/
// Supporting functions for callbacks.

void battery(uint8_t x, uint8_t y,uint8_t data)
{
    #ifdef BLUEMICRO_CONFIGURED_DISPLAY
        char buffer [50];
        u8g2.setFont(u8g2_font_battery19_tn);	// choose a suitable font
        sprintf(buffer, "%d", (data+5)/20);
        u8g2.drawStr(x,y,buffer);
    #endif
}

void printline(uint8_t x, uint8_t y,char* data)
{
    #ifdef BLUEMICRO_CONFIGURED_DISPLAY
        u8g2.setFont(u8g2_font_u8glib_4_tf);	// choose a suitable font
        u8g2.drawStr(x,y,data);
    #endif
}

void printline(uint8_t x, uint8_t y,int8_t data)
{
    #ifdef BLUEMICRO_CONFIGURED_DISPLAY
        char buffer [50];
        sprintf(buffer, "%d", data);
        u8g2.setFont(u8g2_font_t0_12_mf);	// choose a suitable font
        u8g2.drawStr(x,y,buffer);
    #endif
}
void printline(uint8_t x, uint8_t y,uint16_t data)
{
    #ifdef BLUEMICRO_CONFIGURED_DISPLAY
        char buffer [50];
        sprintf(buffer, "%d", data);
        u8g2.setFont(u8g2_font_t0_12_mf);	// choose a suitable font
        u8g2.drawStr(x,y,buffer);
    #endif
}
void printline(uint8_t x, uint8_t y,uint32_t data)
{
    #ifdef BLUEMICRO_CONFIGURED_DISPLAY
        char buffer [50];
        sprintf(buffer, "%u", data);
        u8g2.setFont(u8g2_font_t0_12_mf);	// choose a suitable font
        u8g2.drawStr(x,y,buffer);
    #endif
}


/**************************************************************************************************************************/
// Examples of callbacks.  These are the defaults used by the firmware.

void drawStartup(PersistentState* cfg, DynamicState* stat)
{
    #ifdef BLUEMICRO_CONFIGURED_DISPLAY
    u8g2.setFontMode(1);	// Transparent
    u8g2.setFontDirection(1);
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.drawStr(4, 0, DEVICE_NAME);
    #endif
}

void drawStatus(PersistentState* cfg, DynamicState* stat)
{
    #ifdef BLUEMICRO_CONFIGURED_DISPLAY
    u8g2.setFontMode(1);	// Transparent
    u8g2.setFontDirection(0);
    battery(22,19,stat->vbat_per);
    printline(0,8,stat->vbat_mv);
    printline(0,18,stat->rssi_prph);
    printline(0,28,stat->peer_name_prph);

    char buffer [50];
    u8g2.setFont(u8g2_font_helvB12_tf);	// choose a suitable font
    sprintf(buffer, "%d", stat->layer);
    u8g2.drawStr(0,128,buffer);
    #endif
}

void drawDebug(PersistentState* cfg, DynamicState* stat)
{
    #ifdef BLUEMICRO_CONFIGURED_DISPLAY
    u8g2.setFontMode(1);	// Transparent
    u8g2.setFontDirection(0);
    battery(22,19,stat->vbat_per);
    printline(0,8,stat->vbat_mv);
    printline(0,18,stat->rssi_prph);
    printline(0,28,stat->peer_name_prph);

    char buffer [50];
    u8g2.setFont(u8g2_font_helvB12_tf);	// choose a suitable font
    sprintf(buffer, "%d", stat->layer);
    u8g2.drawStr(0,128,buffer);
    #endif
}


/**************************************************************************************************************************/