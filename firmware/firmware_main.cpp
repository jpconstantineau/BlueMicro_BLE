/*
Copyright 2018-2020 <Pierre Constantineau, Julian Komaromy>

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
//uint32_t lastupdatetime =0;
SoftwareTimer keyscantimer, batterytimer;

PersistentState keyboardconfig;
DynamicState keyboardstate;

KeyScanner keys;
Battery batterymonitor;

static std::vector<uint16_t> stringbuffer; // buffer for macros to type into...
//static bool helpmode = false;

/**************************************************************************************************************************/
void setupConfig() {
  keyboardconfig.ledbacklight=BACKLIGHT_PWM_ON;
  keyboardconfig.ledrgb=WS2812B_LED_ON;
  keyboardconfig.timerkeyscaninterval=HIDREPORTINGINTERVAL;
  keyboardconfig.timerbatteryinterval=BATTERYINTERVAL;
  keyboardconfig.VCCSwitchAvailable=(VCC_ENABLE_GPIO==1);
  keyboardconfig.VCCSwitchEnabled=(VCC_DEFAULT_ON==1);;
  keyboardconfig.ChargerControlAvailable=(VCC_ENABLE_CHARGER==1);
  keyboardconfig.ChargerControlEnabled=true;

  keyboardconfig.WakeUpBLELED=true;
  keyboardconfig.WakeUpKBLED=true;

  keyboardstate.helpmode = false;
  keyboardstate.timestamp = millis();
  keyboardstate.lastupdatetime = keyboardstate.timestamp;
}


/**************************************************************************************************************************/
// put your setup code here, to run once:
/**************************************************************************************************************************/
// cppcheck-suppress unusedFunction
void setup() {
 setupConfig();

 Serial.begin(115200);

  LOG_LV1("BLEMIC","Starting %s" ,DEVICE_NAME);

  setupGpio();                                                                // checks that NFC functions on GPIOs are disabled.
  if(keyboardconfig.VCCSwitchAvailable)
  {
    switchVCC(keyboardconfig.VCCSwitchEnabled); // turn on VCC when starting up if needed.
  }
  if(keyboardconfig.ChargerControlAvailable)
  {
    switchCharger(keyboardconfig.ChargerControlEnabled); // turn on Charger when starting up if needed.
  }
  setupStatusLEDs(keyboardconfig.WakeUpBLELED,keyboardconfig.WakeUpKBLED); 
   
  keyscantimer.begin(keyboardconfig.timerkeyscaninterval, keyscantimer_callback);
  batterytimer.begin(keyboardconfig.timerbatteryinterval, batterytimer_callback);
  setupBluetooth();

  if(keyboardconfig.ledbacklight)
  {
    setupPWM(BACKLIGHT_LED_PIN); //PWM contributes 500uA to the bottom line on a 840 device. see https://devzone.nordicsemi.com/f/nordic-q-a/40912/pwm-power-consumption-nrf52840 (there is no electrical specification)
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
 // suspendLoop(); // this commands suspends the main loop.  We are no longer using the loop but scheduling things using the timers.
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
// Better scanning with debounce Keyboard Scanning
/**************************************************************************************************************************/
void scanMatrix() {

    keyboardstate.timestamp  = millis();   // lets call it once per scan instead of once per key in the matrix
    //take care when selecting debouncetime - each row has a delay of 1ms inbetween - so if you have 5 rows, setting debouncetime to 2 is at least 5ms...
    
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
       // Bluefruit.clearBonds(); //removed in next BSP?
        Bluefruit.Central.clearBonds();
      break;      
    case DFU:
      enterOTADfu();
      break;
    case SERIAL_DFU:
      enterSerialDfu();
      break;
    case UF2_DFU:
      enterUf2Dfu();
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
      addStringToQueue(buffer); addKeycodeToQueue(KC_ENTER);
      break;  
    case PRINT_BLE:
      addStringToQueue("Keyboard Name: " DEVICE_NAME " "); addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,"Device Power : %i", DEVICE_POWER); addStringToQueue(buffer);  addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,"Filter RSSI  : %i", FILTER_RSSI_BELOW_STRENGTH); addStringToQueue(buffer);  addKeycodeToQueue(KC_ENTER); 
      addStringToQueue("Type\t RSSI\t name"); addKeycodeToQueue(KC_ENTER); 
      sprintf(buffer,"cent\t %i\t %s",keyboardstate.rssi_cent, keyboardstate.peer_name_cent);addStringToQueue(buffer); addKeycodeToQueue(KC_ENTER); 
      sprintf(buffer,"prph\t %i\t %s",keyboardstate.rssi_prph, keyboardstate.peer_name_prph);addStringToQueue(buffer); addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,"cccd\t %i\t %s",keyboardstate.rssi_cccd, keyboardstate.peer_name_cccd);addStringToQueue(buffer); addKeycodeToQueue(KC_ENTER);
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
    uint8_t report[8] = {0, 0, 0 ,0, 0, 0, 0, 0}; ;
    uint16_t keyreport = stringbuffer.back();
    stringbuffer.pop_back();
    
    report[0] = static_cast<uint8_t>((keyreport & 0xFF00) >> 8);// mods
    report[1] = static_cast<uint8_t>(keyreport & 0x00FF);
    sendKeys(report);
    delay(keyboardconfig.timerkeyscaninterval*3);
    if (stringbuffer.empty()) // make sure to send an empty report when done...
    { 
      report[0] = 0;
      report[1] = 0;
      sendKeys(report);
      delay(keyboardconfig.timerkeyscaninterval*3);
    }
    else
    {
      
      uint16_t lookahead_keyreport = stringbuffer.back();
      if (lookahead_keyreport == keyreport) // if the next key is the same, make sure to send a key release before sending it again... but keep the mods.
      {
        report[0] = static_cast<uint8_t>((keyreport & 0xFF00) >> 8);// mods;
        report[1] = 0;
        sendKeys(report);
        delay(keyboardconfig.timerkeyscaninterval*3);
      }
    }
   // KeyScanner::processingmacros=0;
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
// cppcheck-suppress unusedFunction
void loop() {
  handleSerial();
  delay(1000);
  
};  // loop is called for serials comms and saving to flash.
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
}


//********************************************************************************************//
//* Idle Task - runs when there is nothing to do                                             *//
//* Any impact of placing code here on current consumption?                                  *//
//********************************************************************************************//
// cppcheck-suppress unusedFunction  
extern "C" void vApplicationIdleHook(void) {
  // Don't call any other FreeRTOS blocking API()
  // Perform background task(s) here
    sd_power_mode_set(NRF_POWER_MODE_LOWPWR); // 944uA
    //sd_power_mode_set(NRF_POWER_MODE_CONSTLAT); // 1.5mA
    sd_app_evt_wait();  // puts the nrf52 to sleep when there is nothing to do.  You need this to reduce power consumption. (removing this will increase current to 8mA)
};
