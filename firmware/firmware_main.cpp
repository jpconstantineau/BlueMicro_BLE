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
#if READ_DIRECTION == READ_ON_COLS
  byte gpioBias[] MATRIX_ROW_PINS;       // Contains the GPIO Pin Numbers defined in keyboard_config.h
  byte gpioReadIn[] MATRIX_COL_PINS;     // Contains the GPIO Pin Numbers defined in keyboard_config.h 
#else //READ_DIRECTION == READ_ON_ROWS
  byte gpioReadIn[] MATRIX_ROW_PINS;     // Contains the GPIO Pin Numbers defined in keyboard_config.h
  byte gpioBias[] MATRIX_COL_PINS;       // Contains the GPIO Pin Numbers defined in keyboard_config.h
#endif

//uint32_t lastupdatetime =0;
SoftwareTimer keyscantimer, batterytimer;

static PersistentState keyboardconfig;
static DynamicState keyboardstate;

KeyScanner keys;
Battery batterymonitor;

static std::vector<uint16_t> stringbuffer; // buffer for macros to type into...
//static bool helpmode = false;

/**************************************************************************************************************************/
void setupConfig() {
  keyboardconfig.ledbacklight=BACKLIGHT_PWM_ON;
  keyboardconfig.ledrgb=WS2812B_LED_ON;
  keyboardconfig.ledunderglow=UNDERGLOW_LED_ON;
  keyboardconfig.audio=AUDIO_ON;
  keyboardconfig.timerkeyscaninterval=HIDREPORTINGINTERVAL;
  keyboardconfig.timerbatteryinterval=30*1000;

  keyboardstate.helpmode = false;
  keyboardstate.timestamp = millis();
}


/**************************************************************************************************************************/
// put your setup code here, to run once:
/**************************************************************************************************************************/
void setup() {
 setupConfig();
 Serial.begin(115200);
  //while ( !Serial ) delay(10);   // for nrf52840 with native usb this makes the nrf52840 stall and wait for a serial connection.  Something not wanted for a keyboard...

  LOG_LV1("BLEMIC","Starting %s" ,DEVICE_NAME);

  setupGpio();                                                                // checks that NFC functions on GPIOs are disabled.

  keyscantimer.begin(keyboardconfig.timerkeyscaninterval, keyscantimer_callback);
  batterytimer.begin(keyboardconfig.timerbatteryinterval, batterytimer_callback);

  setupBluetooth();

  if(keyboardconfig.audio)
  {
    setupAudio();
  }

  if(keyboardconfig.ledunderglow)
  {
    setupUnderglow();
  }

  if(keyboardconfig.ledbacklight)
  {
    setupPWM();
  }

  if(keyboardconfig.ledrgb)
  {
    setupRGB();
  }
  
  // Set up keyboard matrix and start advertising
  setupKeymap();

  setupMatrix();

  startAdv(); 

  keyscantimer.start();

  batterytimer.start();

  suspendLoop(); // this commands suspends the main loop.  We are no longer using the loop but scheduling things using the timers.
  stringbuffer.clear();
};

/**************************************************************************************************************************/
// setupMatrix fuc for keybards using shift registers as I/O expanders to drive columns high during the scanning of keys. 
/**************************************************************************************************************************/
void setupMatrix(void) {

  //inits gpio as INPUT
  for (const auto& gpioToRead : gpioReadIn) {
    LOG_LV2("BLEMIC","Setting to INPUT GPIO: %i" ,gpioToRead);
    pinMode(gpioToRead, INPUT);
  }

  #if defined(SHIFT_REGISTER_KEYBOARD)
    setupShiftRegisters();
  #else
    //inits gpio as INPUT_PULLUP
    for (const auto& gpioToBias : gpioBias) {
        LOG_LV2("BLEMIC","Setting to INPUT_PULLUP GPIO: %i" ,gpioToBias);
        pinMode(gpioToBias, INPUT_PULLUP);
    }
  #endif

};

/**************************************************************************************************************************/
// Keyboard Scanning
/**************************************************************************************************************************/
void scanMatrix() {
  uint32_t pindata0 = 0;
  uint32_t pindata1 = 0;
  keyboardstate.timestamp  = millis();   // lets call it once per scan instead of once per key in the matrix
  int matrixOutsideLoop; //holds number of pins scanned during outside loop
  int matrixInsideLoop;  //holds number of pins scanned during inside loop

  //handle read direction - we have option to read in / poll keypresses on either the cols or the rows
  #if READ_DIRECTION == READ_ON_COLS
    matrixOutsideLoop = MATRIX_ROWS;
    matrixInsideLoop = MATRIX_COLS;
  #else //READ_DIRECTION == READ_ON_ROWS
    matrixOutsideLoop = MATRIX_COLS;
    matrixInsideLoop = MATRIX_ROWS;
  #endif

  //sets all io used to "read in" a keypress value to an input & handles DIODE_DIRECTION
  for (int i = 0; i < matrixInsideLoop; ++i) {                               
          #if DIODE_DIRECTION == COL2ROW                                         
          pinMode(gpioReadIn[i], INPUT_PULLUP);                               
          #else
          pinMode(gpioReadIn[i], INPUT_PULLDOWN);                            
          #endif
  }

  //outside loop scans through either rows or cols - sets their 'BIAS' appropriately in preparation for inside loop which "gpio Reads" the pins
  for(int j = 0; j < matrixOutsideLoop; ++j) {    

      //set the current COL as OUPUT - handle each case thereafter
      #if DIODE_DIRECTION == COL2ROW && !defined(SHIFT_REGISTER_KEYBOARD)     
      pinMode(gpioBias[j], OUTPUT);                                   
      digitalWrite(gpioBias[j], LOW);                                         // 'enables' a specific pin to be "low" 
      #elif DIODE_DIRECTION == ROW2COL && !defined(SHIFT_REGISTER_KEYBOARD)
      pinMode(gpioBias[j], OUTPUT);
      digitalWrite(gpioBias[j], HIGH);                                        // 'enables' a specific pin to be "high"
      #elif DIODE_DIRECTION == COL2ROW && defined(SHIFT_REGISTER_KEYBOARD)                                        
      shiftOutToMakePinLow(j);                                                // 'enables' a specific pin to be "low" but using a shift register
      #else //DIODE_DIRECTION == ROW2COL && defined(SHIFT_REGISTER_KEYBOARD)
      shiftOutToMakePinHigh(j);                                               // 'enables' a specific pin to be "high" but using a shift register
      #endif   

      nrfx_coredep_delay_us(1);   // need for the GPIO lines to settle down electrically before reading.

          #ifdef NRF52840_XXAA        // This is chip dependent and not on the board.  As such, we need this to also support the nrf52840 feather which remaps the numbers of the GPIOs to Pins numbers.
              
              pindata0 = NRF_P0->IN;                                         // read all pins at once
              pindata1 = NRF_P1->IN;                                         // read all pins at once
              
              //loop that scans through "COLS"
              for (int i = 0; i < matrixInsideLoop; ++i) {
              int ulPin = g_ADigitalPinMap[gpioReadIn[i]];                               // This maps the Board Pin to the GPIO.
                if (ulPin<32)
                {
                  #if READ_DIRECTION == READ_ON_COLS
                    KeyScanner::scanMatrix((pindata0>>(ulPin))&1, keyboardstate.timestamp, j, i);       // This function processes the logic values and does the debouncing
                  #else
                    KeyScanner::scanMatrix((pindata0>>(ulPin))&1, keyboardstate.timestamp, i, j);       // This function processes the logic values and does the debouncing
                  #endif
                } else
                {
                  #if READ_DIRECTION == READ_ON_COLS
                    KeyScanner::scanMatrix((pindata1>>(ulPin-32))&1, keyboardstate.timestamp, j, i);    // This function processes the logic values and does the debouncing
                  #else
                    KeyScanner::scanMatrix((pindata1>>(ulPin-32))&1, keyboardstate.timestamp, i, j);    // This function processes the logic values and does the debouncing
                  #endif
                }
              }

          #else
              pindata0 = NRF_GPIO->IN;                                                // read all pins at once
              for (int i = 0; i < matrixInsideLoop; ++i) {
              int ulPin = g_ADigitalPinMap[gpioReadIn[i]];                             // This maps the Board Pin to the GPIO. Added to ensure compatibility with potential new nrf52832 boards
              KeyScanner::scanMatrix((pindata0>>(ulPin))&1, keyboardstate.timestamp, j, i);       // This function processes the logic values and does the debouncing
              }
          #endif

      #if !defined(SHIFT_REGISTER_KEYBOARD)
      pinMode(gpioBias[j], INPUT);                                          //'disables' the pin that was just scanned
      #elif DIODE_DIRECTION == COL2ROW && defined(SHIFT_REGISTER_KEYBOARD)                                        
      shiftOutToMakeAllLow();                                    
      #else //DIODE_DIRECTION == ROW2COL && defined(SHIFT_REGISTER_KEYBOARD)
      shiftOutToMakeAllHigh();                                     
      #endif

  }                                                                   // done scanning the matrix

  for (int i = 0; i < matrixInsideLoop; ++i) {                             //Scanning done, disabling all columns
      pinMode(gpioReadIn[i], INPUT);                                     
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

    case HELP_MODE:
       keyboardstate.helpmode = ! keyboardstate.helpmode;
      break;  

    case OUT_AUTO:
      break;
    case OUT_USB:
      break;
    case OUT_BT:
      break;  

    // BACKLIGHT FUNCTIONS
    case BL_TOGG:
    if ( keyboardstate.helpmode) {addStringToQueue("BL_TOGG");}
      stepPWMMode();
    break;
    case BL_STEP:  // step through modes
    if ( keyboardstate.helpmode) {addStringToQueue("BL_STEP");}
      stepPWMMode();
    break;
    case BL_ON:
   if ( keyboardstate.helpmode) { addStringToQueue("BL_ON");}
      setPWMMode(3);
      PWMSetMaxVal();
    break;
    case BL_OFF:
    if ( keyboardstate.helpmode) {addStringToQueue("BL_OFF");}
      setPWMMode(0);
    break;
    case BL_INC:
    if ( keyboardstate.helpmode) {addStringToQueue("BL_INC");}
      incPWMMaxVal();
    break;
    case BL_DEC:
    if ( keyboardstate.helpmode) {addStringToQueue("BL_DEC");}
      decPWMMaxVal();
    break;
    case BL_BRTG:
    if ( keyboardstate.helpmode) {addStringToQueue("BL_BRTG");}
      setPWMMode(2);
    break;
    case BL_REACT:
    if ( keyboardstate.helpmode) {addStringToQueue("BL_REACT");}
      setPWMMode(1);
      PWMSetMaxVal();
    break;
    case BL_STEPINC:
    if ( keyboardstate.helpmode) {addStringToQueue("BL_STEPINC");}
        incPWMStepSize();
      break;
    case BL_STEPDEC:
    if ( keyboardstate.helpmode) {addStringToQueue("BL_STEPDEC");}
        decPWMStepSize();
      break;

    case RGB_TOG:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_TOG");}
      break;
    case RGB_MODE_FORWARD:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_FORWARD");}
      break;
    case RGB_MODE_REVERSE:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_REVERSE");}
      break;
    case RGB_HUI:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_HUI");}
      
      break;      
    case RGB_HUD:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_HUD");}
      break;
    case RGB_SAI:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_SAI");}
      break;
    case RGB_SAD:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_SAD");}
      break;
    case RGB_VAI:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_VAI");}
      break;
    case RGB_VAD:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_VAD");}
      break;   
    case RGB_MODE_PLAIN:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_PLAIN");}
      updateRGBmode(RGB_MODE_PLAIN);
      break;
    case RGB_MODE_BREATHE:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_BREATHE");}
      updateRGBmode(RGB_MODE_BREATHE);
      break;
    case RGB_MODE_RAINBOW:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_RAINBOW");}
      updateRGBmode(RGB_MODE_RAINBOW);
      break;
    case RGB_MODE_SWIRL:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_SWIRL");}
      updateRGBmode(RGB_MODE_SWIRL);
      break;   
    case RGB_MODE_SNAKE:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_SNAKE");}
      updateRGBmode(RGB_MODE_SNAKE);
      break;
    case RGB_MODE_KNIGHT:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_KNIGHT");}
      updateRGBmode(RGB_MODE_KNIGHT);
      break;
    case RGB_MODE_XMAS:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_XMAS");}
      updateRGBmode(RGB_MODE_XMAS);
      break;   
    case RGB_MODE_GRADIENT:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_GRADIENT");}
      updateRGBmode(RGB_MODE_GRADIENT);
      break;
    case RGB_MODE_RGBTEST:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_RGBTEST");}
      updateRGBmode(RGB_MODE_RGBTEST);
      break;
    case RGB_SPI:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_SPI");}
      break;   
    case RGB_SPD:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_SPD");}
      break;    
    case PRINT_BATTERY:
      intval = batterymonitor.vbat_per;

      switch (batterymonitor.batt_type)
      {
        case BATT_UNKNOWN:
            snprintf (buffer, sizeof(buffer), "VDD = %.0f mV, VBatt = %.0f mV", batterymonitor.vbat_vdd*1.0, batterymonitor.vbat_mv*1.0);
        break;
        case BATT_CR2032:
            if (intval>99)
            {
              snprintf (buffer, sizeof(buffer), "VDD = %.0f mV (%4d %%)", batterymonitor.vbat_mv*1.0, intval);
            }
            else
            {
              snprintf (buffer, sizeof(buffer), "VDD = %.0f mV (%3d %%)", batterymonitor.vbat_mv*1.0, intval);
            }
            
        break;
        case BATT_LIPO:
            if (intval>99)
            {
              sprintf (buffer, "LIPO = %.0f mV (%4d %%)", batterymonitor.vbat_mv*1.0, intval);
            }
            else
            {
              sprintf (buffer, "LIPO = %.0f mV (%3d %%)", batterymonitor.vbat_mv*1.0, intval);
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
/**************************************************************************************************************************/
void process_user_special_keys()
{
  uint8_t mods = KeyScanner::currentReport[0] ;
          LOG_LV1("SPECIAL","PROCESS: %i %i %i %i %i %i %i %i %i" ,KeyScanner::special_key,mods, KeyScanner::currentReport[1],KeyScanner::currentReport[2],KeyScanner::currentReport[3], KeyScanner::currentReport[4],KeyScanner::currentReport[5], KeyScanner::currentReport[6],KeyScanner::bufferposition );  
   switch(KeyScanner::special_key)
  {
    case KS(KC_ESC):
        switch (mods)
        {
          case 0:          KeyScanner::currentReport[KeyScanner::bufferposition] = KC_ESC;   KeyScanner::reportChanged = true; break;
          case BIT_LCTRL:  KeyScanner::currentReport[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport[0]  = 0; break;
          case BIT_LSHIFT: KeyScanner::currentReport[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport[0]  = BIT_LSHIFT; break;
          case BIT_LALT:   KeyScanner::currentReport[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport[0]  = 0; break;
          case BIT_LGUI:   KeyScanner::currentReport[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport[0]  = 0; break;
          case BIT_RCTRL:  KeyScanner::currentReport[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport[0]  = 0; break;
          case BIT_RSHIFT: KeyScanner::currentReport[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport[0]  = 0; break;
          case BIT_RALT:   KeyScanner::currentReport[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport[0]  = 0; break;
          case BIT_RGUI:   KeyScanner::currentReport[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport[0]  = 0; break;
        }  
      break;
    default:
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

  if (KeyScanner::special_key > 0){
      process_user_special_keys();
      KeyScanner::special_key = 0;
  }

  if (KeyScanner::macro > 0){
      process_user_macros(KeyScanner::macro);
      KeyScanner::macro = 0;
  } 
  if (!stringbuffer.empty()) // if the macro buffer isn't empty, send the first character of the buffer... which is located at the back of the queue
  {
    keyreport = stringbuffer.back();
    stringbuffer.pop_back();
    
    report[0] = static_cast<uint8_t>((keyreport & 0xFF00) >> 8);// mods
    report[1] = static_cast<uint8_t>(keyreport & 0x00FF);
    sendKeys(report);
    delay(keyboardconfig.timerkeyscaninterval);
    if (stringbuffer.empty()) // make sure to send an empty report when done...
    { 
      report[0] = 0;
      report[1] = 0;
      sendKeys(report);
      delay(keyboardconfig.timerkeyscaninterval);
    }
    else
    {
      lookahead_keyreport = stringbuffer.back();
      if (lookahead_keyreport == keyreport) // if the next key is the same, make sure to send a key release before sending it again...
      {
        report[0] = 0;
        report[1] = 0;
        sendKeys(report);
        delay(keyboardconfig.timerkeyscaninterval);
      }
    }
  }
  else if ((KeyScanner::reportChanged))  //any new key presses anywhere?
  {                                                                              
        sendKeys(KeyScanner::currentReport);
        LOG_LV1("MXSCAN","SEND: %i %i %i %i %i %i %i %i %i " ,keyboardstate.timestamp,KeyScanner::currentReport[0], KeyScanner::currentReport[1],KeyScanner::currentReport[2],KeyScanner::currentReport[3], KeyScanner::currentReport[4],KeyScanner::currentReport[5], KeyScanner::currentReport[6],KeyScanner::currentReport[7] );        
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
    sendMouseKey(KeyScanner::mouse);
    KeyScanner::mouse = 0; 
  }
  

  #if BLE_PERIPHERAL ==1   | BLE_CENTRAL ==1                            /**************************************************/
    if(KeyScanner::layerChanged || (keyboardstate.timestamp-keyboardstate.lastupdatetime > 1000))     //layer comms
    {   
        keyboardstate.lastupdatetime = keyboardstate.timestamp;
        sendlayer(KeyScanner::localLayer);
        LOG_LV1("MXSCAN","Layer %i  %i" ,keyboardstate.timestamp,KeyScanner::localLayer);
        KeyScanner::layerChanged = false;                                      // mark layer as "not changed" since last update
    } 
  #endif                                                                /**************************************************/
}
/**************************************************************************************************************************/
// put your main code here, to run repeatedly:
/**************************************************************************************************************************/
void loop() {};  // loop is now empty and no longer being called.
// keyscantimer is being called instead
/**************************************************************************************************************************/
void keyscantimer_callback(TimerHandle_t _handle) {
    #if MATRIX_SCAN == 1
    scanMatrix();
  #endif
  #if SEND_KEYS == 1
    sendKeyPresses();    // how often does this really run?
  #endif
   unsigned long timesincelastkeypress = keyboardstate.timestamp - KeyScanner::getLastPressed();

  #if SLEEP_ACTIVE == 1
    gotoSleep(timesincelastkeypress,Bluefruit.connected());
  #endif

  #if BLE_CENTRAL == 1  
    if ((timesincelastkeypress<10)&&(!Bluefruit.Central.connected()&&(!Bluefruit.Scanner.isRunning())))
    {
      Bluefruit.Scanner.start(0);                                             // 0 = Don't stop scanning after 0 seconds  ();
    }
  #endif

  if(keyboardconfig.ledbacklight)
  {
    updatePWM(timesincelastkeypress);
  }

  if(keyboardconfig.ledrgb)
  {
     updateRGB(timesincelastkeypress);
  }

}
//********************************************************************************************//
//* Battery Monitoring Task - runs infrequently                                              *//
//********************************************************************************************//
void batterytimer_callback(TimerHandle_t _handle)
{ 
      batterymonitor.updateBattery();
      //Serial.println("***** LOOP STILL RUNNING ***** ");
    
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
