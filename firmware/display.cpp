/*
Copyright 2020 <Pierre Constantineau>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "display.h"

Display::Display(uint8_t sda, uint8_t scl) 
{


}

bool Display::begin(uint8_t data)
{   
   u8g2.begin();
   return true;
}
void Display::clear()
{
 u8g2.clearBuffer();					// clear the internal memory
 row = 2;

}
void Display::battery(uint8_t data)
{
    char buffer [50];
    u8g2.setFont(u8g2_font_battery19_tn);	// choose a suitable font
    sprintf(buffer, "%d", (data+5)/20);
    u8g2.drawStr(22,19,buffer);
}

void Display::printline(char* data)
{
  u8g2.setFont(u8g2_font_u8glib_4_tf);	// choose a suitable font
  u8g2.drawStr(0,8+10*row,data);
  row++;
}
void Display::printline(uint8_t data)
{
    char buffer [50];
    sprintf(buffer, "%d", data);
  u8g2.setFont(u8g2_font_t0_12_mf);	// choose a suitable font
  u8g2.drawStr(0,8+10*row,buffer);
  row++;
}
void Display::printline(int8_t data)
{
    char buffer [50];
    sprintf(buffer, "%d", data);
  u8g2.setFont(u8g2_font_t0_12_mf);	// choose a suitable font
  u8g2.drawStr(0,8+10*row,buffer);
  row++;
}
void Display::printline(uint16_t data)
{
    char buffer [50];
    sprintf(buffer, "%d", data);
  u8g2.setFont(u8g2_font_t0_12_mf);	// choose a suitable font
  u8g2.drawStr(0,8+10*row,buffer);
  row++;
}
void Display::printline(uint32_t data)
{
    char buffer [50];
    sprintf(buffer, "%d", data);
  u8g2.setFont(u8g2_font_t0_12_mf);	// choose a suitable font
  u8g2.drawStr(0,8+10*row,buffer);
  row++;
}

bool Display::update(DynamicState keyboardstate)
{
  
    clear();
    battery(keyboardstate.vbat_per);
  //  printline(keyboardstate.batt_type);
 //   printline(keyboardstate.vbat_per);
 //   printline(keyboardstate.vbat_vdd);
  //  printline(keyboardstate.vbat_vddh);
    printline(keyboardstate.vbat_mv);
  //  printline(keyboardstate.vbat_raw);
  //  printline(keyboardstate.batterytimer);
 // printline(keyboardstate.rssi);
 printline(keyboardstate.peer_name_prph);
 printline(keyboardstate.rssi_prph);

char buffer [50];
  u8g2.setFont(u8g2_font_fub20_t_symbol);	// choose a suitable font
  sprintf(buffer, "%d", keyboardstate.layer);
  u8g2.drawStr(0,128,buffer);
  u8g2.sendBuffer();					// transfer internal memory to the display
  return true;
}

 void Display::sleep(void)
 {
     u8g2.clearBuffer();
     u8g2.sendBuffer();
     u8g2.setPowerSave(1);
 }
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C Display::u8g2(U8G2_R1, U8X8_PIN_NONE);