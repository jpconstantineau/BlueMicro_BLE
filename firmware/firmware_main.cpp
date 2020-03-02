/*
Copyright 2018 <Pierre Constantineau, Julian Komaromy>

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
/**************************************************************************************************************************/
#include <bluefruit.h>
#include "firmware.h"
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

using namespace Adafruit_LittleFS_Namespace;
/**************************************************************************************************************************/
// Keyboard Matrix
byte rows[] MATRIX_ROW_PINS;        // Contains the GPIO Pin Numbers defined in keyboard_config.h
byte columns[] MATRIX_COL_PINS;     // Contains the GPIO Pin Numbers defined in keyboard_config.h  

SoftwareTimer keyscantimer, batterytimer;//, RGBtimer;
//extern float vbat_mv;
KeyScanner keys;
Battery batterymonitor;

static std::vector<uint16_t> stringbuffer; // buffer for macros to type into...

/**************************************************************************************************************************/
// put your setup code here, to run once:
/**************************************************************************************************************************/
void setup() {
 Serial.begin(115200);
  while ( !Serial ) delay(10);   // for nrf52840 with native usb

  LOG_LV1("BLEMIC","Starting %s" ,DEVICE_NAME);

  setupGpio();                                                                // checks that NFC functions on GPIOs are disabled.

  keyscantimer.begin(HIDREPORTINGINTERVAL, keyscantimer_callback);
  batterytimer.begin(30*1000, batterytimer_callback);
  //RGBtimer.begin(WS2812B_LED_COUNT*25, RGBtimer_callback);
  setupBluetooth();

  #if BACKLIGHT_PWM_ON == 1 //setup PWM module
    setupPWM();
  #endif
  #if WS2812B_LED_ON == 1 //setup PWM module
    setupRGB();
  #endif
  // Set up keyboard matrix and start advertising
  setupKeymap();
  setupMatrix();
  startAdv(); 
  keyscantimer.start();
  batterytimer.start();
  //RGBtimer.start();
  suspendLoop(); // this commands suspends the main loop.  We are no longer using the loop but scheduling things using the timers.
  stringbuffer.clear();
};
/**************************************************************************************************************************/
//
/**************************************************************************************************************************/
void setupMatrix(void) {
    //inits all the columns as INPUT
   for (const auto& column : columns) {
      LOG_LV2("BLEMIC","Setting to INPUT Column: %i" ,column);
      pinMode(column, INPUT);
    }

   //inits all the rows as INPUT_PULLUP
   for (const auto& row : rows) {
      LOG_LV2("BLEMIC","Setting to INPUT_PULLUP Row: %i" ,row);
      pinMode(row, INPUT_PULLUP);
    }
};
/**************************************************************************************************************************/
// Keyboard Scanning
/**************************************************************************************************************************/
void scanMatrix() {
  uint32_t pindata0 = 0;
  uint32_t pindata1 = 0;
  unsigned long timestamp = millis();   // lets call it once per scan instead of once per key in the matrix
    
  for (int i = 0; i < MATRIX_COLS; ++i) {                               // Setting columns before scanning.
        #if DIODE_DIRECTION == COL2ROW                                         
        pinMode(columns[i], INPUT_PULLUP);                              // 'enables' the column High Value on the diode; becomes "LOW" when pressed 
        #else
        pinMode(columns[i], INPUT_PULLDOWN);                            // 'enables' the column High Value on the diode; becomes "LOW" when pressed
        #endif
  }

  for(int j = 0; j < MATRIX_ROWS; ++j) {                             
    //set the current row as OUPUT and LOW
    pinMode(rows[j], OUTPUT);
    #if DIODE_DIRECTION == COL2ROW                                         
    digitalWrite(rows[j], LOW);                                       // 'enables' a specific row to be "low" 
    #else
    digitalWrite(rows[j], HIGH);                                       // 'enables' a specific row to be "HIGH"
    #endif

        nrfx_coredep_delay_us(1);   // need for the GPIO lines to settle down electrically before reading.

        #ifdef NRF52840_XXAA        // This is chip dependent and not on the board.  As such, we need this to also support the nrf52840 feather which remaps the numbers of the GPIOs to Pins numbers.
          pindata0 = NRF_P0->IN;                                         // read all pins at once
          pindata1 = NRF_P1->IN;                                         // read all pins at once
          for (int i = 0; i < MATRIX_COLS; ++i) {
            int ulPin = g_ADigitalPinMap[columns[i]];                               // This maps the Board Pin to the GPIO.
            if (ulPin<32)
            {
              KeyScanner::scanMatrix((pindata0>>(ulPin))&1, timestamp, j, i);       // This function processes the logic values and does the debouncing 
            } else
            {
              KeyScanner::scanMatrix((pindata1>>(ulPin-32))&1, timestamp, j, i);    // This function processes the logic values and does the debouncing 
            }
          } 
        #else
          pindata0 = NRF_GPIO->IN;                                                // read all pins at once
          for (int i = 0; i < MATRIX_COLS; ++i) {
            int ulPin = g_ADigitalPinMap[columns[i]];                             // This maps the Board Pin to the GPIO. Added to ensure compatibility with potential new nrf52832 boards
            KeyScanner::scanMatrix((pindata0>>(ulPin))&1, timestamp, j, i);       // This function processes the logic values and does the debouncing
          }
        #endif
    pinMode(rows[j], INPUT);                                          //'disables' the row that was just scanned
   }                                                                  // done scanning the matrix

  for (int i = 0; i < MATRIX_COLS; ++i) {                             //Scanning done, disabling all columns
    pinMode(columns[i], INPUT);                                     
  }
};

/**************************************************************************************************************************/
/**************************************************************************************************************************/
#if USER_MACRO_FUNCTION == 1  
    void process_user_macros(uint16_t macroid)
    {
        switch ((macroid))
        {
            case MC(KC_A):
            addStringToQueue( "Macro Example 1");
            break;
        }
    }
#endif
/**************************************************************************************************************************/
// macro string queue management
/**************************************************************************************************************************/
void addStringToQueue(const char* str)
{
  auto it = stringbuffer.begin();
  uint8_t modifier;
  uint8_t keycode;
  uint16_t keyreport;
  char ch;
  while( (ch = *str++) != 0 )
  {
    modifier = ( hid_ascii_to_keycode[(uint8_t)ch][0] ) ? KEYBOARD_MODIFIER_LEFTSHIFT : 0;
    keycode = hid_ascii_to_keycode[(uint8_t)ch][1];
    keyreport = MOD( modifier << 8 , keycode);
    it = stringbuffer.insert(it, keyreport);
  }

}
/**************************************************************************************************************************/
/**************************************************************************************************************************/
void addKeycodeToQueue(const uint16_t keycode)
{
  auto it = stringbuffer.begin();
  auto hidKeycode = static_cast<uint8_t>(keycode & 0x00FF);

        if (hidKeycode >= KC_A && hidKeycode <= KC_EXSEL)  // only insert keycodes if they are valid keyboard codes...
        {
            it = stringbuffer.insert(it, keycode);
        }
  }
/**************************************************************************************************************************/
/**************************************************************************************************************************/
void process_keyboard_function(uint16_t keycode)
{
  char buffer [50];
  uint8_t intval;
   switch(keycode)
  {
    case RESET:
      NVIC_SystemReset();
      break;
    case DEBUG:
      break;
    case EEPROM_RESET:
      InternalFS.format();
      break;
    case CLEAR_BONDS:
      InternalFS.format();
      break;      
    case DFU:
      enterOTADfu();
      break;
    case SERIAL_DFU:
      enterSerialDfu();
      break;

    case OUT_AUTO:
      break;
    case OUT_USB:
      break;
    case OUT_BT:
      break;  

    case BL_TOGG:
      break;
    case BL_STEP:
      break;
    case BL_ON:
      break;
    case BL_OFF:
      break;      
    case BL_INC:
      break;
    case BL_DEC:
      break;
    case BL_BRTG:
      break;
    case BL_REACT:
      break;
    case BL_STEPINC:
      break;   
    case BL_STEPDEC:
      break;   

    case RGB_TOG:
      break;
    case RGB_MODE_FORWARD:
      break;
    case RGB_MODE_REVERSE:
      break;
    case RGB_HUI:
      break;      
    case RGB_HUD:
      break;
    case RGB_SAI:
      break;
    case RGB_SAD:
      break;
    case RGB_VAI:
      break;
    case RGB_VAD:
      break;   
    case RGB_MODE_PLAIN:
      break;
    case RGB_MODE_BREATHE:
      break;
    case RGB_MODE_RAINBOW:
      break;
    case RGB_MODE_SWIRL:
      break;   
    case RGB_MODE_SNAKE:
      break;
    case RGB_MODE_KNIGHT:
      break;
    case RGB_MODE_XMAS:
      break;   
    case RGB_MODE_GRADIENT:
      break;
    case RGB_MODE_RGBTEST:
      break;
    case RGB_SPI:
      break;   
    case RGB_SPD:
      break;    
    case PRINT_BATTERY:
      intval = Battery::vbat_per;

      switch (Battery::batt_type)
      {
        case BATT_UNKNOWN:
            snprintf (buffer, sizeof(buffer), "VDD = %.0f mV, VBatt = %.0f mV", Battery::vbat_vdd*1.0, Battery::vbat_mv*1.0);
        break;
        case BATT_CR2032:
            if (intval>99)
            {
              snprintf (buffer, sizeof(buffer), "VDD = %.0f mV (%4d %%)", Battery::vbat_mv*1.0, intval);
            }
            else
            {
              snprintf (buffer, sizeof(buffer), "VDD = %.0f mV (%3d %%)", Battery::vbat_mv*1.0, intval);
            }
            
        break;
        case BATT_LIPO:
            if (intval>99)
            {
              sprintf (buffer, "LIPO = %.0f mV (%4d %%)", Battery::vbat_mv*1.0, intval);
            }
            else
            {
              sprintf (buffer, "LIPO = %.0f mV (%3d %%)", Battery::vbat_mv*1.0, intval);
            }   
        break;
      }
      addStringToQueue(buffer);
      addKeycodeToQueue(KC_ENTER);
      break;
    case PRINT_INFO:
      addStringToQueue("Keyboard Name  : " DEVICE_NAME " "); addKeycodeToQueue(KC_ENTER);
      addStringToQueue("Keyboard Model : " DEVICE_MODEL " "); addKeycodeToQueue(KC_ENTER);
      addStringToQueue("Keyboard Mfg   : " MANUFACTURER_NAME " "); addKeycodeToQueue(KC_ENTER);
      addStringToQueue("BSP Library    : " ARDUINO_BSP_VERSION " "); addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,"Bootloader     : %s", getBootloaderVersion());
      addStringToQueue(buffer); 
      addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,"Serial No      : %s", getMcuUniqueID());
      addStringToQueue(buffer);
      addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,"Device Power   : %f", DEVICE_POWER*1.0);
      addStringToQueue(buffer);
      break;      
  }
}

/**************************************************************************************************************************/
// Communication with computer and other boards
/**************************************************************************************************************************/
void sendKeyPresses() {
  uint8_t report[8] = {0, 0, 0 ,0, 0, 0, 0, 0}; ;
  uint16_t keyreport;
  uint16_t lookahead_keyreport;

   KeyScanner::getReport();                                            // get state data - Data is in KeyScanner::currentReport  
  if (KeyScanner::macro > 0){
      process_user_macros(KeyScanner::macro);
      KeyScanner::macro = 0;
  } 
  if (!stringbuffer.empty()) // if the macro buffer isn't empty, send the first character of the buffer... which is located at the back of the FIFO queue
  {
    keyreport = stringbuffer.back();
    stringbuffer.pop_back();
    
    report[0] = static_cast<uint8_t>((keyreport & 0xFF00) >> 8);// mods
    report[1] = static_cast<uint8_t>(keyreport & 0x00FF);
    sendKeys(report);
    delay(HIDREPORTINGINTERVAL);
    if (stringbuffer.empty()) // make sure to send an empty report when done...
    { 
      report[0] = 0;
      report[1] = 0;
      sendKeys(report);
      delay(HIDREPORTINGINTERVAL);
    }
    else
    {
      lookahead_keyreport = stringbuffer.back();
      if (lookahead_keyreport == keyreport) // if the next key is the same, make sure to send a key release before sending it again...
      {
        report[0] = 0;
        report[1] = 0;
        sendKeys(report);
        delay(HIDREPORTINGINTERVAL);
      }
    }
  }
  else if ((KeyScanner::reportChanged))  //any new key presses anywhere?
  {                                                                              
        sendKeys(KeyScanner::currentReport);
        LOG_LV1("MXSCAN","SEND: %i %i %i %i %i %i %i %i %i " ,millis(),KeyScanner::currentReport[0], KeyScanner::currentReport[1],KeyScanner::currentReport[2],KeyScanner::currentReport[3], KeyScanner::currentReport[4],KeyScanner::currentReport[5], KeyScanner::currentReport[6],KeyScanner::currentReport[7] );        
  } else if (KeyScanner::specialfunction > 0)
  {
    process_keyboard_function(KeyScanner::specialfunction);
    KeyScanner::specialfunction = 0; 
  } else if (KeyScanner::consumer > 0)
  {
    sendMediaKey(KeyScanner::consumer);
    KeyScanner::consumer = 0; 
  } else if (KeyScanner::mouse > 0)
  {
    KeyScanner::mouse = 0; 
  }
  

  #if BLE_PERIPHERAL ==1   | BLE_CENTRAL ==1                            /**************************************************/
    if(KeyScanner::layerChanged)                                               //layer comms
    {   
        sendlayer(KeyScanner::localLayer);
        LOG_LV1("MXSCAN","Layer %i  %i" ,millis(),KeyScanner::localLayer);
        KeyScanner::layerChanged = false;                                      // mark layer as "not changed" since last update
    } 
  #endif                                                                /**************************************************/
}
/**************************************************************************************************************************/
// put your main code here, to run repeatedly:
/**************************************************************************************************************************/
void loop() {};  // loop is now empty and no longer being called.

/**************************************************************************************************************************/
// put your key scanning code here, to run repeatedly:
/**************************************************************************************************************************/
void keyscantimer_callback(TimerHandle_t _handle) {
    #if MATRIX_SCAN == 1
    scanMatrix();
  #endif
  #if SEND_KEYS == 1
    sendKeyPresses();    // how often does this really run?
  #endif
   unsigned long timesincelastkeypress = millis() - KeyScanner::getLastPressed();

  #if SLEEP_ACTIVE == 1
    gotoSleep(timesincelastkeypress,Bluefruit.connected());
  #endif

  #if BLE_CENTRAL == 1  
    if ((timesincelastkeypress<10)&&(!Bluefruit.Central.connected()&&(!Bluefruit.Scanner.isRunning())))
    {
      Bluefruit.Scanner.start(0);                                                     // 0 = Don't stop scanning after 0 seconds  ();
    }
  #endif

  #if BACKLIGHT_PWM_ON == 1
    updatePWM(1, timesincelastkeypress);
  #endif

    #if WS2812B_LED_ON == 1 
     updateRGB(1, timesincelastkeypress);
    #endif

}
//********************************************************************************************//
//* Battery Monitoring Task - runs infrequently                                              *//
//********************************************************************************************//
void batterytimer_callback(TimerHandle_t _handle)
{
   
      Battery::updateBattery();
   
}

void RGBtimer_callback(TimerHandle_t _handle)
{
    #if WS2812B_LED_ON == 1 
      unsigned long timesincelastkeypress = millis() - KeyScanner::getLastPressed();
     updateRGB(0, timesincelastkeypress);
    #endif
}

//********************************************************************************************//
//* Idle Task - runs when there is nothing to do                                             *//
//* Any impact of placing code here on current consumption?                                  *//
//********************************************************************************************//
extern "C" void vApplicationIdleHook(void) {
  // Don't call any other FreeRTOS blocking API()
  // Perform background task(s) here
    sd_power_mode_set(NRF_POWER_MODE_LOWPWR);
    sd_app_evt_wait();  // puts the nrf52 to sleep when there is nothing to do.  You need this to reduce power consumption. (removing this will increase current to 8mA)
};
