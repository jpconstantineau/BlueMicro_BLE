/*
Copyright 2018-2021 <Pierre Constantineau, Julian Komaromy>

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
#include <Arduino.h>
#include <bluefruit.h>
#include "firmware.h"
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

/**************************************************************************************************************************/
// Keyboard Matrix
byte rows[] MATRIX_ROW_PINS;        // Contains the GPIO Pin Numbers defined in keyboard_config.h
byte columns[] MATRIX_COL_PINS;     // Contains the GPIO Pin Numbers defined in keyboard_config.h  

SoftwareTimer keyscantimer, batterytimer;

using namespace Adafruit_LittleFS_Namespace;
#define SETTINGS_FILE "/settings"
File file(InternalFS);
PersistentState keyboardconfig;
DynamicState keyboardstate;

#ifdef ENABLE_AUDIO
  BlueMicro_tone speaker(&keyboardconfig, &keyboardstate);  /// A speaker to play notes and tunes...
#endif
led_handler statusLEDs(&keyboardconfig, &keyboardstate);  /// Typically a Blue LED and a Red LED



#ifdef BLUEMICRO_CONFIGURED_DISPLAY
  BlueMicro_Display OLED(&keyboardconfig, &keyboardstate);  /// Typically a Blue LED and a Red LED
#endif

KeyScanner keys(&keyboardconfig, &keyboardstate);
Battery batterymonitor;

static std::vector<uint16_t> stringbuffer; // buffer for macros to type into...
static std::vector<HIDKeyboard> reportbuffer; 

/**************************************************************************************************************************/
void setupConfig() {
  InternalFS.begin();
  loadConfig();

  keyboardstate.statusble=0;  //initialize to a known state.
  keyboardstate.statuskb=0;   //initialize to a known state.

  keyboardstate.user1=0;   //initialize to a known state.  
  keyboardstate.user2=0;   //initialize to a known state. 
  keyboardstate.user3=0;   //initialize to a known state.

  keyboardstate.helpmode = false;
  keyboardstate.timestamp = millis();
  keyboardstate.lastupdatetime = keyboardstate.timestamp;
  keyboardstate.lastreporttime = 0;
  keyboardstate.lastuseractiontime = 0;

  keyboardstate.connectionState = CONNECTION_NONE;
  keyboardstate.needReset = false;
  keyboardstate.needUnpair = false;
  keyboardstate.needFSReset = false;
  keyboardstate.save2flash = false;

}

/**************************************************************************************************************************/
void loadConfig()
{
  file.open(SETTINGS_FILE, FILE_O_READ);

  if(file)
  {
    file.read(&keyboardconfig, sizeof(keyboardconfig));
    file.close();
  }
  else
  {
    resetConfig();
    saveConfig();
  }

 if (keyboardconfig.version != BLUEMICRO_CONFIG_VERSION) // SETTINGS_FILE format changed. we need to reset and re-save it.
 {
    resetConfig();
    saveConfig();
 }
}

/**************************************************************************************************************************/
void resetConfig()
{
  keyboardconfig.version=BLUEMICRO_CONFIG_VERSION;
  keyboardconfig.pinPWMLED=BACKLIGHT_LED_PIN;
  keyboardconfig.pinRGBLED=WS2812B_LED_PIN;
  keyboardconfig.pinBLELED=STATUS_BLE_LED_PIN;  
  keyboardconfig.pinKBLED=STATUS_KB_LED_PIN;

  keyboardconfig.enablePWMLED=BACKLIGHT_PWM_ON;
  keyboardconfig.enableRGBLED=WS2812B_LED_ON;
  keyboardconfig.enableBLELED=BLE_LED_ACTIVE;
  keyboardconfig.enableKBLED=STATUS_KB_LED_ACTIVE;

  keyboardconfig.polarityBLELED=BLE_LED_POLARITY;
  keyboardconfig.polarityKBLED=STATUS_KB_LED_POLARITY;

  keyboardconfig.enableVCCSwitch=VCC_ENABLE_GPIO;
  keyboardconfig.polarityVCCSwitch=VCC_DEFAULT_ON;

  keyboardconfig.enableChargerControl=VCC_ENABLE_CHARGER;
  keyboardconfig.polarityChargerControl=true;

  #ifdef BLUEMICRO_CONFIGURED_DISPLAY
    keyboardconfig.enableDisplay = true;// enabled if it's compiled with one...
  #else
    keyboardconfig.enableDisplay = false;// disabled if it's not compiled with one...
  #endif

  #ifdef SPEAKER_PIN
    keyboardconfig.enableAudio = true;// enabled if it's compiled with one...
  #else
    keyboardconfig.enableAudio = false;// disabled if it's not compiled with one...
  #endif

  keyboardconfig.enableSerial = SERIAL_DEBUG_CLI_DEFAULT_ON;   

  keyboardconfig.mode = 0; 
  keyboardconfig.user1 = 0;  
  keyboardconfig.user2 = 0; 

  keyboardconfig.matrixscaninterval=HIDREPORTINGINTERVAL;
  keyboardconfig.batteryinterval=BATTERYINTERVAL;
  keyboardconfig.keysendinterval=HIDREPORTINGINTERVAL;
  keyboardconfig.lowpriorityloopinterval=LOWPRIORITYLOOPINTERVAL;
  keyboardconfig.lowestpriorityloopinterval = HIDREPORTINGINTERVAL*2;
  keyboardconfig.connectionMode  = CONNECTION_MODE_AUTO;
  keyboardconfig.BLEProfile = 0;
  keyboardconfig.BLEProfileEdiv[0] = 0xFFFF;
  keyboardconfig.BLEProfileEdiv[1] = 0xFFFF;
  keyboardconfig.BLEProfileEdiv[2] = 0xFFFF;
  strcpy(keyboardconfig.BLEProfileName[0], "unpaired");
  strcpy(keyboardconfig.BLEProfileName[1], "unpaired");
  strcpy(keyboardconfig.BLEProfileName[2], "unpaired");


}

/**************************************************************************************************************************/
void saveConfig()
{
  InternalFS.remove(SETTINGS_FILE);

  if (file.open(SETTINGS_FILE, FILE_O_WRITE))
  {
    file.write((uint8_t*)&keyboardconfig, sizeof(keyboardconfig));
    file.close();
  }
}




/**************************************************************************************************************************/
// put your setup code here, to run once:
/**************************************************************************************************************************/
// cppcheck-suppress unusedFunction
void setup() {

  setupGpio();                                                                // checks that NFC functions on GPIOs are disabled.
  setupWDT();
  #ifdef BLUEMICRO_CONFIGURED_DISPLAY
     OLED.begin();
  #endif
 
  setupConfig();
#ifdef ENABLE_AUDIO
 #ifdef SPEAKER_PIN
 speaker.setSpeakerPin(SPEAKER_PIN);
 #endif
 #endif

  if (keyboardconfig.enableSerial) 
  {
  Serial.begin(115200);
        Serial.println(" ____  _            __  __ _                   ____  _     _____ ");
        Serial.println("| __ )| |_   _  ___|  \\/  (_) ___ _ __ ___    | __ )| |   | ____|");
        Serial.println("|  _ \\| | | | |/ _ \\ |\\/| | |/ __| '__/ _ \\   |  _ \\| |   |  _|  ");
        Serial.println("| |_) | | |_| |  __/ |  | | | (__| | | (_) |  | |_) | |___| |___ ");
        Serial.println("|____/|_|\\__,_|\\___|_|  |_|_|\\___|_|  \\___/___|____/|_____|_____|");
        Serial.println("                                         |_____|                 ");
        Serial.println("");
        Serial.println("Type 'h' to get a list of commands with descriptions");
  }
 
  LOG_LV1("BLEMIC","Starting %s" ,DEVICE_NAME);

  if(keyboardconfig.enableVCCSwitch)
  {
    switchVCC(keyboardconfig.polarityVCCSwitch); // turn on VCC when starting up if needed.
  }

  if(keyboardconfig.enableChargerControl)
  {
    switchCharger(keyboardconfig.polarityChargerControl); // turn on Charger when starting up if needed.
  }

  keyscantimer.begin(keyboardconfig.matrixscaninterval, keyscantimer_callback);
  //batterytimer.begin(keyboardconfig.batteryinterval, batterytimer_callback);
  
  usb_setup(); // does nothing for 832 - see usb.cpp
  bt_setup(keyboardconfig.BLEProfile);
  // Set up keyboard matrix and start advertising
  setupKeymap(); // this is where we can change the callback for our LEDs...
  setupMatrix();
  bt_startAdv(); 
  keyscantimer.start();
  //batterytimer.start();

  stringbuffer.clear();
  reportbuffer.clear();

  if(keyboardconfig.enablePWMLED)
  {
    setupPWM(keyboardconfig.pinPWMLED); //PWM contributes 500uA to the bottom line on a 840 device. see https://devzone.nordicsemi.com/f/nordic-q-a/40912/pwm-power-consumption-nrf52840 (there is no electrical specification)
  }

  if(keyboardconfig.enableRGBLED)
  {
    setupRGB();//keyboardconfig.pinRGBLED
  }

  statusLEDs.enable();
  statusLEDs.hello();  // blinks Status LEDs a couple as last step of setup.
  Scheduler.startLoop(LowestPriorityloop, 1024, TASK_PRIO_LOWEST, "l1"); // this loop contains LED,RGB & PWM and Display updates.
  //Scheduler.startLoop(NormalPriorityloop, 1024, TASK_PRIO_NORMAL, "n1"); // this has nothing in it...
  #ifdef BLUEMICRO_CONFIGURED_DISPLAY
    if(keyboardconfig.enableDisplay)
    {
      OLED.changeUpdateMode(DISPLAY_UPDATE_STATUS);
    }
    else
    {
      OLED.sleep();
    }
  #endif
#ifdef ENABLE_AUDIO
  speaker.playTone(TONE_STARTUP);
  speaker.playTone(TONE_BLE_PROFILE);
  #endif

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

#if DIODE_DIRECTION == COL2ROW
#define writeRow(r) digitalWrite(r,LOW)
#define modeCol(c) pinMode(c, INPUT_PULLUP)
#ifdef NRF52840_XXAA
#define gpioIn (((uint64_t)(NRF_P1->IN)^0xffffffff)<<32)|(NRF_P0->IN)^0xffffffff
#else
#define gpioIn (NRF_GPIO->IN)^0xffffffff
#endif
#else
#define writeRow(r) digitalWrite(r,HIGH)
#define modeCol(c) pinMode(c, INPUT_PULLDOWN)
#ifdef NRF52840_XXAA
#define gpioIn (((uint64_t)NRF_P1->IN)<<32)|(NRF_P0->IN)
#else
#define gpioIn NRF_GPIO->IN
#endif
#endif
#ifdef NRF52840_XXAA
#define PINDATATYPE uint64_t
#else
#define PINDATATYPE uint32_t
#endif
/**************************************************************************************************************************/
// THIS FUNCTION TAKES CARE OF SCANNING THE MATRIX AS WELL AS DEBOUNCING THE KEY PRESSES
// IF YOU ARE USING A DIFFERENT METHOD TO READ/WRITE TO GPIOS (SUCH AS SHIFT REGISTERS OR GPIO EXPANDERS), YOU WILL
// NEED TO RE-WORK THIS ROUTINE.  IDEALLY WE SHOULD HAVE THIS AS A COMPILE-TIME OPTION TO SWITCH BETWEEN ROUTINES.
/**************************************************************************************************************************/
void scanMatrix() {

    keyboardstate.timestamp  = millis();   // lets call it once per scan instead of once per key in the matrix
    
    static PINDATATYPE pindata[MATRIX_ROWS][DEBOUNCETIME];

    static uint8_t head = 0; // points us to the head of the debounce array;

    for (int i = 0; i < MATRIX_COLS; ++i){
        modeCol(columns[i]);
    }

    for (int j = 0; j < MATRIX_ROWS; ++j){
        // set the current row as OUPUT and LOW
        PINDATATYPE pinreg = 0;

        pinMode(rows[j], OUTPUT);
        writeRow(rows[j]);

        nrfx_coredep_delay_us(1);   // need for the GPIO lines to settle down electrically before reading.
        pindata[j][head] = gpioIn;  // press is active high regardless of diode dir

        //debounce happens here - we want to press a button as soon as possible, and release it only when all bounce has left
        for (int d = 0; d < DEBOUNCETIME; ++d)
            pinreg |= pindata[j][d];
        
        for (int i = 0; i < MATRIX_COLS; ++i){
            int ulPin = g_ADigitalPinMap[columns[i]]; 
            if((pinreg>>ulPin)&1)  KeyScanner::press(keyboardstate.timestamp, j, i);
            else                   KeyScanner::release(keyboardstate.timestamp, j, i);
        }

        pinMode(rows[j], INPUT);                                                   // 'disables' the row that was just scanned
    }
    for (int i = 0; i < MATRIX_COLS; ++i) {                             //Scanning done, disabling all columns
        pinMode(columns[i], INPUT);                                     
    }

    head++;
    if(head >= DEBOUNCETIME) head = 0; // reset head to 0 when we reach the end of our buffer
}


/**************************************************************************************************************************/
// THIS IS THE DEFAULT process_user_macros FUNCTION WHICH IS OVERRIDEN BY USER ONE.
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

void UpdateQueue()
{
  #ifdef ENABLE_COMBOS
     stringbuffer.insert(stringbuffer.end(), combos.keycodebuffertosend.rbegin(),combos.keycodebuffertosend.rend());
     combos.keycodebuffertosend.clear();
  #endif

}

/**************************************************************************************************************************/
// macro string queue management
/**************************************************************************************************************************/
void addStringToQueue(const char* str)
{
  auto it = stringbuffer.begin();
  char ch;
  while( (ch = *str++) != 0 )
  {
    uint8_t modifier = ( hid_ascii_to_keycode[(uint8_t)ch][0] ) ? KEYBOARD_MODIFIER_LEFTSHIFT : 0;
    uint8_t keycode = hid_ascii_to_keycode[(uint8_t)ch][1];
    uint16_t keyreport = MOD( modifier << 8 , keycode);
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

void addKeycodeToQueue(const uint16_t keycode, const uint8_t modifier)
{
  auto it = stringbuffer.begin();
  auto hidKeycode = static_cast<uint8_t>(keycode & 0x00FF);
     //  auto extraModifiers = static_cast<uint8_t>((keycode & 0xFF00) >> 8);

        if (hidKeycode >= KC_A && hidKeycode <= KC_EXSEL)  // only insert keycodes if they are valid keyboard codes...
        {
                uint16_t keyreport = MOD( modifier << 8 , hidKeycode);
                it = stringbuffer.insert(it, keyreport);
        }
  }  
/**************************************************************************************************************************/
/**************************************************************************************************************************/
void process_keyboard_function(uint16_t keycode)
{
  char buffer [50];
  uint8_t intval;
  switch (keycode) {
  case RESET:
    NVIC_SystemReset();
    break;
  case DEBUG:
    keyboardconfig.enableSerial = !keyboardconfig.enableSerial;
    keyboardstate.save2flash = true;
    keyboardstate.needReset = true;
    break;
  case EEPROM_RESET:
    keyboardstate.needFSReset = true;
    break;
  case CLEAR_BONDS:
    // Bluefruit.clearBonds(); //removed in next BSP?
    if (keyboardstate.connectionState == CONNECTION_BT)
      keyboardstate.needUnpair = true;
    // Bluefruit.Central.clearBonds();
    break;
  case DFU:
  #ifdef ENABLE_AUDIO
    speaker.playTone(TONE_SLEEP);
    speaker.playAllQueuedTonesNow();
    #endif
    enterOTADfu();
    break;
  case SERIAL_DFU:
  #ifdef ENABLE_AUDIO
    speaker.playTone(TONE_SLEEP);
    speaker.playAllQueuedTonesNow();
    #endif
    enterSerialDfu();
    break;
  case UF2_DFU:
  #ifdef ENABLE_AUDIO
    speaker.playTone(TONE_SLEEP);
    speaker.playAllQueuedTonesNow();
    #endif
    enterUf2Dfu();
    break;
  case HELP_MODE:
    keyboardstate.helpmode = !keyboardstate.helpmode;
    break;
  case OUT_AUTO:
    keyboardconfig.connectionMode = CONNECTION_MODE_AUTO;
    if (keyboardstate.helpmode) {
      addStringToQueue("Automatic USB/BLE - Active");
      addKeycodeToQueue(KC_ENTER);
      addStringToQueue("USB Only");
      addKeycodeToQueue(KC_ENTER);
      addStringToQueue("BLE Only");
      addKeycodeToQueue(KC_ENTER);
    }
    break;
  case OUT_USB:
#ifdef NRF52840_XXAA // only the 840 has USB available.
    keyboardconfig.connectionMode = CONNECTION_MODE_USB_ONLY;
    if (keyboardstate.helpmode) {
      addStringToQueue("Automatic USB/BLE");
      addKeycodeToQueue(KC_ENTER);
      addStringToQueue("USB Only - Active");
      addKeycodeToQueue(KC_ENTER);
      addStringToQueue("BLE Only");
      addKeycodeToQueue(KC_ENTER);
    }
#else
    if (keyboardstate.helpmode) {
      addStringToQueue("USB not available on NRF52832");
      addKeycodeToQueue(KC_ENTER);
    }
#endif
    break;
  case OUT_BT:
    keyboardconfig.connectionMode = CONNECTION_MODE_BLE_ONLY;
    if (keyboardstate.helpmode) {
      addStringToQueue("Automatic USB/BLE");
      addKeycodeToQueue(KC_ENTER);
      addStringToQueue("USB Only");
      addKeycodeToQueue(KC_ENTER);
      addStringToQueue("BLE Only - Active");
      addKeycodeToQueue(KC_ENTER);
    }
    break;

  // BACKLIGHT FUNCTIONS
  case BL_TOGG:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_TOGG");
    }
    stepPWMMode();
    break;
  case BL_STEP: // step through modes
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_STEP");
    }
    stepPWMMode();
    break;
  case BL_ON:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_ON");
    }
    setPWMMode(3);
    PWMSetMaxVal();
    break;
  case BL_OFF:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_OFF");
    }
    setPWMMode(0);
    break;
  case BL_INC:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_INC");
    }
    incPWMMaxVal();
    break;
  case BL_DEC:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_DEC");
    }
    decPWMMaxVal();
    break;
  case BL_BRTG:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_BRTG");
    }
    setPWMMode(2);
    break;
  case BL_REACT:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_REACT");
    }
    setPWMMode(1);
    PWMSetMaxVal();
    break;
  case BL_STEPINC:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_STEPINC");
    }
    incPWMStepSize();
    break;
  case BL_STEPDEC:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_STEPDEC");
    }
    decPWMStepSize();
    break;
  case RGB_TOG:
    if (keyboardstate.helpmode) {
      addStringToQueue("RGB_TOG");
    }
    break;
  case RGB_MODE_FORWARD:
    if (keyboardstate.helpmode) {
      addStringToQueue("RGB_MODE_FORWARD");
    }
    break;
  case RGB_MODE_REVERSE:
    if (keyboardstate.helpmode) {
      addStringToQueue("RGB_MODE_REVERSE");
    }
    break;
  case RGB_HUI:
    if (keyboardstate.helpmode) {
      addStringToQueue("RGB_HUI");
    }
    break;
  case RGB_HUD:
    if (keyboardstate.helpmode) {
      addStringToQueue("RGB_HUD");
    }
    break;
  case RGB_SAI:
    if (keyboardstate.helpmode) {
      addStringToQueue("RGB_SAI");
    }
    break;
  case RGB_SAD:
    if (keyboardstate.helpmode) {
      addStringToQueue("RGB_SAD");
    }
    break;
  case RGB_VAI:
    if (keyboardstate.helpmode) {
      addStringToQueue("RGB_VAI");
    }
    break;
  case RGB_VAD:
    if (keyboardstate.helpmode) {
      addStringToQueue("RGB_VAD");
    }
    break;
  case RGB_MODE_PLAIN:
    if (keyboardstate.helpmode) {
      addStringToQueue("RGB_MODE_PLAIN");
    }
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
        case BATT_VDDH:
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
      addStringToQueue(buffer); addKeycodeToQueue(KC_ENTER);
        switch (keyboardconfig.connectionMode)
        {
          case CONNECTION_MODE_AUTO:
          addStringToQueue("CONNECTION_MODE_AUTO"); addKeycodeToQueue(KC_ENTER);
          break;
          case CONNECTION_MODE_USB_ONLY:
          addStringToQueue("CONNECTION_MODE_USB_ONLY"); addKeycodeToQueue(KC_ENTER);
          break;
          case CONNECTION_MODE_BLE_ONLY:
          addStringToQueue("CONNECTION_MODE_BLE_ONLY"); addKeycodeToQueue(KC_ENTER);
          break;
        }
            switch (keyboardstate.connectionState)
            {
              case CONNECTION_USB:
                addStringToQueue("CONNECTION_USB"); addKeycodeToQueue(KC_ENTER);
              break;

              case CONNECTION_BT:
                addStringToQueue("CONNECTION_BLE"); addKeycodeToQueue(KC_ENTER);
              break;

              case CONNECTION_NONE:
                addStringToQueue("CONNECTION_NONE"); addKeycodeToQueue(KC_ENTER);
              break;
            }
      break;  
    case PRINT_BLE:
      addStringToQueue("Keyboard Name: " DEVICE_NAME " "); addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,"Device Power : %i", DEVICE_POWER); addStringToQueue(buffer);  addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,"Filter RSSI  : %i", FILTER_RSSI_BELOW_STRENGTH); addStringToQueue(buffer);  addKeycodeToQueue(KC_ENTER); 
      addStringToQueue("Type\t RSSI\t name"); addKeycodeToQueue(KC_ENTER); 
      sprintf(buffer,"cent\t %i\t %s",keyboardstate.rssi_cent, keyboardstate.peer_name_cent);addStringToQueue(buffer); addKeycodeToQueue(KC_ENTER); 
      sprintf(buffer,"prph\t %i\t %s",keyboardstate.rssi_prph, keyboardstate.peer_name_prph);addStringToQueue(buffer); addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,"cccd\t %i\t %s",keyboardstate.rssi_cccd, keyboardstate.peer_name_cccd);addStringToQueue(buffer); addKeycodeToQueue(KC_ENTER);
       sprintf(buffer,  "Profile 1:   %s", keyboardconfig.BLEProfileName[0]);
      addStringToQueue(buffer);
      if (keyboardconfig.BLEProfile == 0) addStringToQueue(" (active)");
      addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,  "Profile 2:   %s", keyboardconfig.BLEProfileName[1]);
      addStringToQueue(buffer);
      if (keyboardconfig.BLEProfile == 1) addStringToQueue(" (active)");
      addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,  "Profile 3:   %s", keyboardconfig.BLEProfileName[2]);
      addStringToQueue(buffer);
      if (keyboardconfig.BLEProfile == 2) addStringToQueue(" (active)");
      addKeycodeToQueue(KC_ENTER);
      addKeycodeToQueue(KC_ENTER);
      ble_gap_addr_t gap_addr;
      gap_addr = bt_getMACAddr();
      sprintf(buffer,  "BT MAC Addr: %02X:%02X:%02X:%02X:%02X:%02X", gap_addr.addr[5], gap_addr.addr[4], gap_addr.addr[3], gap_addr.addr[2], gap_addr.addr[1], gap_addr.addr[0]);
      addStringToQueue(buffer);
      addKeycodeToQueue(KC_ENTER);
      addKeycodeToQueue(KC_ENTER);
      break;
    case PRINT_HELP:
      break;
    case SLEEP_NOW:
      if (keyboardstate.connectionState != CONNECTION_USB) sleepNow();
    break;
    case VCC_ON:
      keyboardconfig.enableVCCSwitch = true;
      keyboardstate.save2flash = true;
      keyboardstate.needReset = true;
      break;
    case VCC_OFF:
      keyboardconfig.enableVCCSwitch = false;
      keyboardstate.save2flash = true;
      keyboardstate.needReset = true;
      break;
    case VCC_TOGGLE:
      keyboardconfig.enableVCCSwitch = !keyboardconfig.enableVCCSwitch;
      keyboardstate.save2flash = true;
      keyboardstate.needReset = true;
      break;
    case CHARGER_ON:
      keyboardconfig.enableChargerControl = true;
      keyboardstate.save2flash = true;
      keyboardstate.needReset = true;
      break;
    case CHARGER_OFF:
      keyboardconfig.enableChargerControl = false;
      keyboardstate.save2flash = true;
      keyboardstate.needReset = true;
      break;
    case CHARGER_TOGGLE:
      keyboardconfig.enableChargerControl = ! keyboardconfig.enableChargerControl;
      keyboardstate.save2flash = true;
      keyboardstate.needReset = true;
      break;


    case WIN_A_GRAVE: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_2, KC_KP_4) break; //Alt 0224 a grave
    case WIN_A_ACUTE: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_2, KC_KP_5) break;//Alt 0225 a acute
    case WIN_A_CIRCU: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_2, KC_KP_6) break; //Alt 0226 a circumflex
    case WIN_A_TILDE: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_2, KC_KP_7) break; //Alt 0227 a tilde
    case WIN_A_UMLAU: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_2, KC_KP_8) break; //Alt 0228 a umlaut

    case WIN_A_GRAVE_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_9, KC_KP_2) break; //Alt 0192 A grave
    case WIN_A_ACUTE_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_9, KC_KP_3) break; //Alt 0193 A acute
    case WIN_A_CIRCU_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_9, KC_KP_4) break; //Alt 0194 A circumflex
    case WIN_A_TILDE_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_9, KC_KP_5) break; //Alt 0195 A tilde
    case WIN_A_UMLAU_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_9, KC_KP_6) break; //Alt 0196 A umlaut

    case WIN_C_CEDIL: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_1) break; //Alt 0231 c cedilla
    case WIN_C_CEDIL_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_9, KC_KP_9) break;//Alt 0199 C cedilla

    case WIN_E_GRAVE: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_2) break;
    case WIN_E_ACUTE: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_3) break;
    case WIN_E_CIRCU: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_4) break;
    case WIN_E_UMLAU: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_5) break;

    case  WIN_I_GRAVE: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_6) break;//Alt 0236 i grave
    case  WIN_I_ACUTE: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_7) break;//Alt 0237 i acute
    case  WIN_I_CIRCU: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_8) break;//Alt 0238 i circumflex
    case  WIN_I_UMLAU: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_9) break; //Alt 0239 i umlaut

    case  WIN_I_GRAVE_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_0, KC_KP_4) break;//Alt 0204 I grave
    case  WIN_I_ACUTE_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_0, KC_KP_5) break; //Alt 0205 I acute
    case  WIN_I_CIRCU_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_0, KC_KP_6) break; //Alt 0206 I circumflex
    case  WIN_I_UMLAU_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_0, KC_KP_7) break;//Alt 0207 I umlaut

    case  WIN_N_TILDE: EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_6, KC_KP_4) break;//Alt 164 n tilde
    case  WIN_N_TILDE_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_6, KC_KP_5) break; //Alt 165 N tilde

    case  WIN_O_GRAVE: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_4, KC_KP_2) break; //Alt 0242 o grave
    case  WIN_O_ACUTE: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_4, KC_KP_3) break; //Alt 0243 o acute
    case  WIN_O_CIRCU: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_4, KC_KP_4) break; //Alt 0244 o circumflex
    case  WIN_O_TILDE: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_4, KC_KP_5) break;  //Alt 0245 o tilde
    case  WIN_O_UMLAU: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_4, KC_KP_6) break;  //Alt 0246 o umlaut

    case  WIN_O_GRAVE_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_0) break; //Alt 0210 O grave
    case  WIN_O_ACUTE_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_1) break; //Alt 0211 O acute
    case  WIN_O_CIRCU_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_2) break;//Alt 0212 O circumflex
    case  WIN_O_TILDE_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_3) break; //Alt 0213 O tilde
    case  WIN_O_UMLAU_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_4) break; //Alt 0214 O umlaut

    case  WIN_S_CARON: EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_5, KC_KP_4) break; //Alt 0154 s caron
    case  WIN_S_CARON_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_3, KC_KP_8) break;  //Alt 0138 S caron

    case WIN_U_GRAVE: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_4, KC_KP_9) break;  //Alt 0249 u grave
    case WIN_U_ACUTE: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_5, KC_KP_0) break; //Alt 0250 u acute
    case WIN_U_CIRCU: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_5, KC_KP_1) break; //Alt 0251 u circumflex
    case WIN_U_UMLAU: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_5, KC_KP_2) break;//Alt 0252 u umlaut

    case WIN_U_GRAVE_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_1) break; //Alt 0217 U grave
    case WIN_U_ACUTE_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_8) break;//Alt 0218  U acute
    case WIN_U_CIRCU_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_9) break;//Alt 0219 U circumflex
    case WIN_U_UMLAU_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_2, KC_KP_0) break; //Alt 0220 U umlaut

    case  WIN_Y_ACUTE: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_5, KC_KP_3) break; //Alt 0253 y acute
    case  WIN_Y_UMLAU: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_5, KC_KP_5) break; //Alt 0255 y umlaut

    case  WIN_Y_ACUTE_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_2, KC_KP_1) break; //Alt 0221 Y tilde
    case  WIN_Y_UMLAU_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_5, KC_KP_9) break;  //Alt 0159 Y umlaut

    case  WIN_Z_CARON: EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_5, KC_KP_4) break; //Alt 0154 z caron
    case  WIN_Z_CARON_CAP: EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_3, KC_KP_8) break;  //Alt 0138 Z caron

    case SYM_DEGREE: EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_7, KC_KP_6) break; // Alt 0176 degree symbol

    case BLEPROFILE_1:
     // if (keyboardstate.connectionState != CONNECTION_USB) // reseting/rebooting KB when BLE Profile switching on USB would be ennoying...
        {
        #ifdef ARDUINO_NRF52_COMMUNITY
          keyboardconfig.BLEProfile = 0;
          keyboardstate.save2flash = true;
          keyboardstate.needReset = true;
        #endif
        #ifdef ARDUINO_NRF52_ADAFRUIT
          ; // do nothing since the Adafruit BSP doesn't support ediv.
        #endif
      }
    break;

    case BLEPROFILE_2:
     // if (keyboardstate.connectionState != CONNECTION_USB) // reseting/rebooting KB when BLE Profile switching on USB would be ennoying...
      {
        #ifdef ARDUINO_NRF52_COMMUNITY
          keyboardconfig.BLEProfile = 1;
          keyboardstate.save2flash = true;
          keyboardstate.needReset = true;
        #endif
        #ifdef ARDUINO_NRF52_ADAFRUIT
          ; // do nothing since the Adafruit BSP doesn't support ediv.
        #endif
      }
    break;

    case BLEPROFILE_3:
    //  if (keyboardstate.connectionState != CONNECTION_USB) // reseting/rebooting KB when BLE Profile switching on USB would be ennoying...
      {
        #ifdef ARDUINO_NRF52_COMMUNITY
          keyboardconfig.BLEProfile = 2;
          keyboardstate.save2flash = true;
          keyboardstate.needReset = true;
        #endif
        #ifdef ARDUINO_NRF52_ADAFRUIT
          ; // do nothing since the Adafruit BSP doesn't support ediv.
        #endif
      }
    break;

    case BATTERY_CALC_DEFAULT:
      batterymonitor.setmvToPercentCallback(mvToPercent_default);
      batterymonitor.updateBattery(); // force an update
    break;
    case BATTERY_CALC_TEST:
      batterymonitor.setmvToPercentCallback(mvToPercent_test);
      batterymonitor.updateBattery(); // force an update
    break;     
     
  }
}

/**************************************************************************************************************************/
/**************************************************************************************************************************/
void process_user_special_keys()
{
  uint8_t mods = KeyScanner::currentReport.modifier ;
          LOG_LV1("SPECIAL","PROCESS: %i %i %i %i %i %i %i %i %i" ,KeyScanner::special_key,mods, KeyScanner::currentReport.keycode[0],KeyScanner::currentReport.keycode[1],KeyScanner::currentReport.keycode[2], KeyScanner::currentReport.keycode[3],KeyScanner::currentReport.keycode[4], KeyScanner::currentReport.keycode[5],KeyScanner::bufferposition );  
   switch(KeyScanner::special_key)
  {
    case KS(KC_ESC):
        switch (mods)
        {
          case 0:          KeyScanner::currentReport.keycode[KeyScanner::bufferposition] = KC_ESC;   KeyScanner::reportChanged = true; break;
          case BIT_LCTRL:  KeyScanner::currentReport.keycode[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport.modifier  = 0; break;
          case BIT_LSHIFT: KeyScanner::currentReport.keycode[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport.modifier  = BIT_LSHIFT; break;
          case BIT_LALT:   KeyScanner::currentReport.keycode[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport.modifier  = 0; break;
          case BIT_LGUI:   KeyScanner::currentReport.keycode[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport.modifier  = 0; break;
          case BIT_RCTRL:  KeyScanner::currentReport.keycode[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport.modifier  = 0; break;
          case BIT_RSHIFT: KeyScanner::currentReport.keycode[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport.modifier  = 0; break;
          case BIT_RALT:   KeyScanner::currentReport.keycode[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport.modifier  = 0; break;
          case BIT_RGUI:   KeyScanner::currentReport.keycode[KeyScanner::bufferposition] = KC_GRAVE; KeyScanner::reportChanged = true; KeyScanner::currentReport.modifier  = 0; break;
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

   KeyScanner::getReport();                                         // get state data - Data is in KeyScanner::currentReport 

  if (KeyScanner::special_key > 0){
      process_user_special_keys();
      KeyScanner::special_key = 0;
  }

  if (KeyScanner::macro > 0){
      process_user_macros(KeyScanner::macro);
      KeyScanner::macro = 0;
      
  } 
  UpdateQueue();
  if (!stringbuffer.empty()) // if the macro buffer isn't empty, send the first character of the buffer... which is located at the back of the queue
  {  
    HIDKeyboard reportarray = {0, {0, 0 ,0, 0, 0, 0}, 0};
    uint16_t keyreport = stringbuffer.back();
    stringbuffer.pop_back();
    
    reportarray.modifier = static_cast<uint8_t>((keyreport & 0xFF00) >> 8);// mods
    reportarray.keycode[0] = static_cast<uint8_t>(keyreport & 0x00FF);

    auto buffer_iterator = reportbuffer.begin();
    buffer_iterator = reportbuffer.insert(buffer_iterator, reportarray);

      uint16_t lookahead_keyreport = stringbuffer.back();
      if (lookahead_keyreport == keyreport) // if the next key is the same, make sure to send a key release before sending it again... but keep the mods.
      {
        reportarray.modifier = static_cast<uint8_t>((keyreport & 0xFF00) >> 8);// mods;
        reportarray.keycode[0] = 0;
        buffer_iterator = reportbuffer.begin();
        buffer_iterator = reportbuffer.insert(buffer_iterator, reportarray);
      }
  }  


 
  if (!reportbuffer.empty()) // if the report buffer isn't empty, send the first character of the buffer... which is located at the end of the queue
  {  
    HIDKeyboard reportarray  = reportbuffer.back();
    reportbuffer.pop_back();
    switch (keyboardstate.connectionState)
    {
      case CONNECTION_USB: usb_sendKeys(reportarray); delay(keyboardconfig.keysendinterval*2); break;
      case CONNECTION_BT: bt_sendKeys(reportarray); delay(keyboardconfig.keysendinterval*2); break;
      case CONNECTION_NONE: // save the report for when we reconnect
              auto it = reportbuffer.end();
              it = reportbuffer.insert(it, reportarray);
      break; 
    }
    
    if (reportbuffer.empty()) // make sure to send an empty report when done...
    { 
      HIDKeyboard emptyReport = {0, {0, 0 ,0, 0, 0, 0}, 0}; 
      switch (keyboardstate.connectionState)
      {
        case CONNECTION_USB: usb_sendKeys(emptyReport); delay(keyboardconfig.keysendinterval*2); break;
        case CONNECTION_BT: bt_sendKeys(emptyReport); delay(keyboardconfig.keysendinterval*2); break;
        case CONNECTION_NONE: // save the report for when we reconnect
                      auto it = reportbuffer.end();
                      it = reportbuffer.insert(it, emptyReport);
        break; 
      } 
    }
   // KeyScanner::processingmacros=0;
  }
  else if ((KeyScanner::reportChanged))  //any new key presses anywhere?
  {                                                                              
    switch (keyboardstate.connectionState)
    {
      case CONNECTION_USB: usb_sendKeys(KeyScanner::currentReport); break;
      case CONNECTION_BT: bt_sendKeys(KeyScanner::currentReport); break;
      case CONNECTION_NONE: // save the report for when we reconnect
                      auto it = reportbuffer.begin();
                      it = reportbuffer.insert(it, KeyScanner::currentReport);    
      break; 
    }
        LOG_LV1("MXSCAN","SEND: %i %i %i %i %i %i %i %i %i " ,keyboardstate.timestamp,KeyScanner::currentReport.modifier, KeyScanner::currentReport.keycode[0],KeyScanner::currentReport.keycode[1],KeyScanner::currentReport.keycode[2], KeyScanner::currentReport.keycode[3],KeyScanner::currentReport.keycode[4], KeyScanner::currentReport.keycode[5],KeyScanner::currentReport.layer);        
  } else if (KeyScanner::specialfunction > 0)
  {
    process_keyboard_function(KeyScanner::specialfunction);
    KeyScanner::specialfunction = 0; 
  } else if (KeyScanner::consumer > 0)
  {
    switch (keyboardstate.connectionState)
    {
      case CONNECTION_USB: usb_sendMediaKey(KeyScanner::consumer); break;
      case CONNECTION_BT: bt_sendMediaKey(KeyScanner::consumer); break;
      case CONNECTION_NONE: 
      #ifdef ENABLE_AUDIO
      speaker.playTone(TONE_BLE_DISCONNECT);
      #endif
       break; // we have lost a report!
    }
    KeyScanner::consumer = 0; 
  } else if (KeyScanner::mouse > 0)
  {
    switch (keyboardstate.connectionState)
    {
      case CONNECTION_USB: usb_sendMouseKey(KeyScanner::mouse); break;
      case CONNECTION_BT: bt_sendMouseKey(KeyScanner::mouse); break;
      case CONNECTION_NONE: 
      #ifdef ENABLE_AUDIO
      speaker.playTone(TONE_BLE_DISCONNECT); 
      #endif
      break; // we have lost a report!
    }
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

// keyscantimer is being called instead
/**************************************************************************************************************************/
void keyscantimer_callback(TimerHandle_t _handle) {
  // timers have NORMAL priorities (HIGHEST>HIGH>NORMAL>LOW>LOWEST)
  // since timers are repeated non stop, we dont want the duration of code running within the timer to vary and potentially
  // go longer than the interval time.

  #if MATRIX_SCAN == 1
    scanMatrix();
  #endif
  #if SEND_KEYS == 1
    sendKeyPresses();  
  #endif
   keyboardstate.lastuseractiontime = max(KeyScanner::getLastPressed(),keyboardstate.lastuseractiontime); // use the latest time to check for sleep...
   unsigned long timesincelastkeypress =  (keyboardstate.timestamp > keyboardstate.lastuseractiontime) ? keyboardstate.timestamp - keyboardstate.lastuseractiontime : 0;

  #if SLEEP_ACTIVE == 1
    switch (keyboardstate.connectionState)
    {
      case CONNECTION_USB:
        // never sleep in this case
      break;

      case CONNECTION_BT:
        gotoSleep(timesincelastkeypress, true);
      break;

      case CONNECTION_NONE:
        gotoSleep(timesincelastkeypress, false);
      break;
    }
  #endif

  #if BLE_CENTRAL == 1  // this is for the master half...
    if ((timesincelastkeypress<10)&&(!Bluefruit.Central.connected()&&(!Bluefruit.Scanner.isRunning())))
    {
      Bluefruit.Scanner.start(0);                                             // 0 = Don't stop scanning after 0 seconds  ();
    }
  #endif

}
//********************************************************************************************//
//* Battery Monitoring Task - runs infrequently                                              *//
//********************************************************************************************//
// TODO: move to lower priority loop.  updating battery infomation isnt critical
// timers have NORMAL priorities (HIGHEST>HIGH>NORMAL>LOW>LOWEST)
//void batterytimer_callback(TimerHandle_t _handle)
//{ 
//      batterymonitor.updateBattery();
//}

//********************************************************************************************//
//* Loop to send keypresses - moved to loop instead of timer due to delay() in processing macros *//
//********************************************************************************************//
// this loop has NORMAL priority(HIGHEST>HIGH>NORMAL>LOW>LOWEST)
//void NormalPriorityloop(void)
//{
//  delay (keyboardconfig.keysendinterval);
//}

/**************************************************************************************************************************/
// put your main code here, to run repeatedly:
/**************************************************************************************************************************/
// cppcheck-suppress unusedFunction
void loop() {  // has task priority TASK_PRIO_LOW     
  updateWDT();
#ifdef ENABLE_AUDIO
  speaker.processTones();
#endif
  if (keyboardconfig.enableSerial)
  {
    handleSerial();
  }

  switch (keyboardconfig.connectionMode)
  {
    case CONNECTION_MODE_AUTO:  // automatically switch between BLE and USB when connecting/disconnecting USB
        if (usb_isConnected())  
        {
          if (keyboardstate.connectionState != CONNECTION_USB)
          {
            if (bt_isConnected()) bt_disconnect();
            bt_stopAdv();
            keyboardstate.connectionState = CONNECTION_USB;
            keyboardstate.lastuseractiontime = millis(); // a USB connection will reset sleep timer... 
            //speaker.playTone(TONE_BLE_CONNECT);
          }
        }
      else if (bt_isConnected())
        {
          if (keyboardstate.connectionState != CONNECTION_BT)
          {
            keyboardstate.connectionState = CONNECTION_BT;
            keyboardstate.lastuseractiontime = millis(); // a BLE connection will reset sleep timer...
            //speaker.playTone(TONE_BLE_CONNECT);
          }
        }
        else
        {
          if (keyboardstate.connectionState != CONNECTION_NONE)
          {
            bt_startAdv();
            keyboardstate.connectionState = CONNECTION_NONE;
            //speaker.playTone(TONE_BLE_DISCONNECT);
            // disconnecting won't reset sleep timer.
          }
        }
      break;
    case CONNECTION_MODE_USB_ONLY:
        if (usb_isConnected())  
        {
          if (keyboardstate.connectionState != CONNECTION_USB)
          {
            if (bt_isConnected()) bt_disconnect();
            bt_stopAdv();
            keyboardstate.connectionState = CONNECTION_USB;
          }
        }
        else // if USB not connected but we are in USB Mode only...
        {
          keyboardstate.connectionState = CONNECTION_NONE;
        }
      break;
    case CONNECTION_MODE_BLE_ONLY:
        if (bt_isConnected())
        {
            keyboardstate.connectionState = CONNECTION_BT;
        }
        else
        {
          if (keyboardstate.connectionState != CONNECTION_NONE)
          {
            bt_startAdv();
            keyboardstate.connectionState = CONNECTION_NONE;
          }
        }
      break;
  }

  // TODO: check for battery filtering when switching USB in/out
  // none of these things can be done in the timer event callbacks
  if (keyboardstate.needUnpair)
  {
    bt_disconnect();
    char filename[32] = { 0 };
    sprintf(filename, "/adafruit/bond_prph/%04x", keyboardconfig.BLEProfileEdiv[keyboardconfig.BLEProfile]);
    InternalFS.remove(filename);

    keyboardconfig.BLEProfileEdiv[keyboardconfig.BLEProfile] = 0xFFFF;
    strcpy(keyboardconfig.BLEProfileName[keyboardconfig.BLEProfile], "unpaired");
    keyboardstate.save2flash = true;
    keyboardstate.needReset = true;
  }
  if (keyboardstate.save2flash)
  {
    saveConfig();
    keyboardstate.save2flash = false;
  }
  if (keyboardstate.needFSReset)
  {
    InternalFS.format();
    keyboardstate.needReset = true;
  }
  if (keyboardstate.needReset) NVIC_SystemReset(); // this reboots the keyboard.

  delay (keyboardconfig.lowpriorityloopinterval);
  
};  // loop is called for serials comms and saving to flash.
/**************************************************************************************************************************/
void LowestPriorityloop()
{ // this loop has LOWEST priority (HIGHEST>HIGH>NORMAL>LOW>LOWEST)
  // it's setup to do 1 thing every call.  This way, we won't take too much time from keyboard functions.
  
  backgroundTaskID toprocess = BACKGROUND_TASK_NONE;
  

   keyboardstate.lastuseractiontime = max(KeyScanner::getLastPressed(),keyboardstate.lastuseractiontime); // use the latest time to check for sleep...
   unsigned long timesincelastkeypress = keyboardstate.timestamp - KeyScanner::getLastPressed();

  updateBLEStatus();
  
  if ((keyboardstate.timestamp - keyboardstate.batterytimer) > keyboardconfig.batteryinterval)  // this is typically every 30 seconds...
  {
    if (timesincelastkeypress > 1000) // update if we haven't typed for 1 second
    {
      toprocess = BACKGROUND_TASK_BATTERY;
    }
  }
    if ((keyboardstate.timestamp - keyboardstate.displaytimer) > 250)  // update even if we type but update 4 times a second. 
    { // TODO check if there is new data to display too!
      toprocess = BACKGROUND_TASK_DISPLAY;
    }

    if ((keyboardstate.timestamp - keyboardstate.audiotimer) > 500)  
    { // TODO: check if there is new audio to play!
      toprocess = BACKGROUND_TASK_AUDIO;
    }
      if(keyboardconfig.enableRGBLED)
      {
          if ((keyboardstate.timestamp - keyboardstate.rgbledtimer) > 50)  
          { 
            toprocess = BACKGROUND_TASK_RGBLED;
          }      
      }

      if(keyboardconfig.enablePWMLED)
      {
          if ((keyboardstate.timestamp - keyboardstate.pwmledtimer) > 50)  
          { 
            toprocess = BACKGROUND_TASK_PWMLED;
          }
      }
    
     if ((keyboardstate.timestamp - keyboardstate.statusledtimer) > 100)  
    { // TODO: check if there is new audio to play!
      toprocess = BACKGROUND_TASK_STATUSLED;
    }

switch (toprocess)
{
  case BACKGROUND_TASK_NONE: 
    break;
  case BACKGROUND_TASK_AUDIO: 
    keyboardstate.audiotimer = keyboardstate.timestamp;
    break;
  case BACKGROUND_TASK_BATTERY: 
      batterymonitor.updateBattery(); 
      keyboardstate.batterytimer = keyboardstate.timestamp;
      keyboardstate.batt_type = batterymonitor.batt_type;
      keyboardstate.vbat_mv = batterymonitor.vbat_mv;
      keyboardstate.vbat_per = batterymonitor.vbat_per;
      keyboardstate.vbat_vdd = batterymonitor.vbat_vdd;
    break;
  case BACKGROUND_TASK_DISPLAY: 
       keyboardstate.displaytimer = keyboardstate.timestamp;
       #ifdef BLUEMICRO_CONFIGURED_DISPLAY
       if(keyboardconfig.enableDisplay)
        {
          OLED.update(); 
        }
        else
        {
          OLED.sleep();
        }
      #endif
    break;
  case BACKGROUND_TASK_STATUSLED: 
    keyboardstate.statusledtimer = keyboardstate.timestamp;
    statusLEDs.update();
    break;
  case BACKGROUND_TASK_PWMLED: 
    keyboardstate.pwmledtimer = keyboardstate.timestamp;
    updatePWM(timesincelastkeypress);
    break;
  case BACKGROUND_TASK_RGBLED: 
    keyboardstate.rgbledtimer = keyboardstate.timestamp;
    updateRGB(timesincelastkeypress);
    break;
}
  delay(keyboardconfig.lowestpriorityloopinterval);              // wait not too long  
}



//********************************************************************************************//
//* Idle Task - runs when there is nothing to do                                             *//
//* Any impact of placing code here on current consumption?                                  *//
//********************************************************************************************//
// cppcheck-suppress unusedFunction  
extern "C" void vApplicationIdleHook(void) {
  // Don't call any other FreeRTOS blocking API()
  // Perform background task(s) here
  // this task has LOWEST priority (HIGHEST>HIGH>NORMAL>LOW>LOWEST)
    sd_power_mode_set(NRF_POWER_MODE_LOWPWR); // 944uA
    //sd_power_mode_set(NRF_POWER_MODE_CONSTLAT); // 1.5mA
    sd_app_evt_wait();  // puts the nrf52 to sleep when there is nothing to do.  You need this to reduce power consumption. (removing this will increase current to 8mA)
};
