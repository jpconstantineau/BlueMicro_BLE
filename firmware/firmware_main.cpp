// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

/**************************************************************************************************************************/

#include <bluemicro_hid.h>
#include "firmware.h"
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

#include "command_queues.h"


/**************************************************************************************************************************/
// Keyboard Matrix
// byte rows[] MATRIX_ROW_PINS;        // Contains the GPIO Pin Numbers defined in keyboard_config.h
// byte columns[] MATRIX_COL_PINS;     // Contains the GPIO Pin Numbers defined in keyboard_config.h  



PersistentState keyboardconfig;
DynamicState keyboardstate;

led_handler statusLEDs(&keyboardconfig, &keyboardstate);  /// Typically a Blue LED and a Red LED

KeyScanner keys(&keyboardconfig, &keyboardstate);

Battery batterymonitor;




/**************************************************************************************************************************/
// put your setup code here, to run once:
/**************************************************************************************************************************/
// cppcheck-suppress unusedFunction
void setup() {
  addsetupcommands();
  addkeyboardcommands();
  SORTCOMMANDS(commandList);
  RUNCOMMANDS(setupQueue, commandList);
  LOG_LV1("BLEMIC","Started %s" ,DEVICE_NAME); 
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
  

  // BACKLIGHT FUNCTIONS
  case BL_TOGG:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_TOGG");
    }
    //stepPWMMode();
    break;
  case BL_STEP: // step through modes
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_STEP");
    }
    //stepPWMMode();
    break;
  case BL_ON:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_ON");
    }
   // setPWMMode(3);
   // PWMSetMaxVal();
    break;
  case BL_OFF:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_OFF");
    }
   // setPWMMode(0);
    break;
  case BL_INC:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_INC");
    }
   // incPWMMaxVal();
    break;
  case BL_DEC:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_DEC");
    }
  //  decPWMMaxVal();
    break;
  case BL_BRTG:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_BRTG");
    }
   // setPWMMode(2);
    break;
  case BL_REACT:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_REACT");
    }
   // setPWMMode(1);
  //  PWMSetMaxVal();
    break;
  case BL_STEPINC:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_STEPINC");
    }
 //   incPWMStepSize();
    break;
  case BL_STEPDEC:
    if (keyboardstate.helpmode) {
      addStringToQueue("BL_STEPDEC");
    }
  //  decPWMStepSize();
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
//    updateRGBmode(RGB_MODE_PLAIN);
    break;
    case RGB_MODE_BREATHE:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_BREATHE");}
    //  updateRGBmode(RGB_MODE_BREATHE);
      break;
    case RGB_MODE_RAINBOW:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_RAINBOW");}
   //   updateRGBmode(RGB_MODE_RAINBOW);
      break;
    case RGB_MODE_SWIRL:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_SWIRL");}
    //  updateRGBmode(RGB_MODE_SWIRL);
      break;   
    case RGB_MODE_SNAKE:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_SNAKE");}
     // updateRGBmode(RGB_MODE_SNAKE);
      break;
    case RGB_MODE_KNIGHT:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_KNIGHT");}
   //   updateRGBmode(RGB_MODE_KNIGHT);
      break;
    case RGB_MODE_XMAS:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_XMAS");}
    //  updateRGBmode(RGB_MODE_XMAS);
      break;   
    case RGB_MODE_GRADIENT:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_GRADIENT");}
     // updateRGBmode(RGB_MODE_GRADIENT);
      break;
    case RGB_MODE_RGBTEST:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_MODE_RGBTEST");}
    //  updateRGBmode(RGB_MODE_RGBTEST);
      break;
    case RGB_SPI:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_SPI");}
      break;   
    case RGB_SPD:
      if ( keyboardstate.helpmode) {addStringToQueue("RGB_SPD");}
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
    HIDKeyboard reportarray = {0, {0, 0 ,0, 0, 0, 0}};
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
    bluemicro_hid.keyboardReport(0, reportarray.keycode);
    
    
    if (reportbuffer.empty()) // make sure to send an empty report when done...
    { 
        bluemicro_hid.keyboardRelease();
    }
   // KeyScanner::processingmacros=0;
  }
  else if ((KeyScanner::reportChanged))  //any new key presses anywhere?
  {     

      bluemicro_hid.keyboardReport(0, KeyScanner::currentReport.keycode);
                                                                      
        LOG_LV1("MXSCAN","SEND: %i %i %i %i %i %i %i %i %i " ,keyboardstate.timestamp,KeyScanner::currentReport.modifier, KeyScanner::currentReport.keycode[0],KeyScanner::currentReport.keycode[1],KeyScanner::currentReport.keycode[2], KeyScanner::currentReport.keycode[3],KeyScanner::currentReport.keycode[4], KeyScanner::currentReport.keycode[5],KeyScanner::currentReport.layer);        
  } else if (KeyScanner::specialfunction > 0)
  {
    process_keyboard_function(KeyScanner::specialfunction);
    KeyScanner::specialfunction = 0; 
  } else if (KeyScanner::consumer > 0)
  {
    // send consumeer code
    KeyScanner::consumer = 0; 
  } else if (KeyScanner::mouse > 0)
  {
    // send mouse code
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
void loop() {  // has task priority TASK_PRIO_LOW     
  updateWDT();

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

      case CONNECTION_BLE:
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

  bluemicro_hid.processQueues(CONNECTION_MODE_AUTO);

  // TODO: check for battery filtering when switching USB in/out
  // none of these things can be done in the timer event callbacks
  if (keyboardstate.needUnpair)
  {
   // bt_disconnect();
    char filename[33] = { 0 };
    sprintf(filename, "/adafruit/bond_prph/%04x", keyboardconfig.BLEProfileEdiv[keyboardconfig.BLEProfile]);
    InternalFS.remove(filename);

    sprintf(filename, "/adafruit/bond_prph/%02X%02X%02X%02X%02X%02X", keyboardconfig.BLEProfileAddr[keyboardconfig.BLEProfile][0],
                                                                      keyboardconfig.BLEProfileAddr[keyboardconfig.BLEProfile][1],
                                                                      keyboardconfig.BLEProfileAddr[keyboardconfig.BLEProfile][2],
                                                                      keyboardconfig.BLEProfileAddr[keyboardconfig.BLEProfile][3],
                                                                      keyboardconfig.BLEProfileAddr[keyboardconfig.BLEProfile][4],
                                                                      keyboardconfig.BLEProfileAddr[keyboardconfig.BLEProfile][5]);
     InternalFS.remove(filename);

    keyboardconfig.BLEProfileEdiv[keyboardconfig.BLEProfile] = 0xFFFF;
    memset(keyboardconfig.BLEProfileAddr[keyboardconfig.BLEProfile], 0, 6);
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

  
  backgroundTaskID toprocess = BACKGROUND_TASK_NONE;
  

   keyboardstate.lastuseractiontime = max(KeyScanner::getLastPressed(),keyboardstate.lastuseractiontime); // use the latest time to check for sleep...
//   unsigned long timesincelastkeypress = keyboardstate.timestamp - KeyScanner::getLastPressed();

 // updateBLEStatus(); TODO replace this
  
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
    break;
  case BACKGROUND_TASK_STATUSLED: 
    keyboardstate.statusledtimer = keyboardstate.timestamp;
    statusLEDs.update();
    break;
  case BACKGROUND_TASK_PWMLED: 
    keyboardstate.pwmledtimer = keyboardstate.timestamp;
   // updatePWM(timesincelastkeypress);
    break;
  case BACKGROUND_TASK_RGBLED: 
    keyboardstate.rgbledtimer = keyboardstate.timestamp;
   // updateRGB(timesincelastkeypress);
    break;
}
  delay(keyboardconfig.lowpriorityloopinterval);              // wait not too long  
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
