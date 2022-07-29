// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

/**************************************************************************************************************************/
#include "firmware_setup.h"

commandlist_t commandList; 
commandqueue_t setupQueue;
commandqueue_t commandQueue;
commandqueue_t loopQueue;

PersistentState keyboardconfig;
DynamicState keyboardstate;

//led_handler statusLEDs(&keyboardconfig, &keyboardstate);  /// Typically a Blue LED and a Red LED
KeyScanner keys(&keyboardconfig, &keyboardstate);
//Battery batterymonitor;


using namespace Adafruit_LittleFS_Namespace;
#define SETTINGS_FILE "/settings"
File file(InternalFS);

/**************************************************************************************************************************/
// Keyboard Matrix
byte rows[] MATRIX_ROW_PINS;        // Contains the GPIO Pin Numbers defined in keyboard_config.h
byte columns[] MATRIX_COL_PINS;     // Contains the GPIO Pin Numbers defined in keyboard_config.h  



/**************************************************************************************************************************/
//todo setup save to flash as module.
void setupConfig() {
  LOG_LV1("SETUP","setupConfig");
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
  LOG_LV1("SETUP","loadConfig");
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
  LOG_LV1("SETUP","resetConfig");
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
  memset(keyboardconfig.BLEProfileAddr[0], 0, 6);
  memset(keyboardconfig.BLEProfileAddr[1], 0, 6);
  memset(keyboardconfig.BLEProfileAddr[2], 0, 6);
  strcpy(keyboardconfig.BLEProfileName[0], "unpaired");
  strcpy(keyboardconfig.BLEProfileName[1], "unpaired");
  strcpy(keyboardconfig.BLEProfileName[2], "unpaired");

}

/**************************************************************************************************************************/
void saveConfig()
{
  LOG_LV1("SETUP","saveConfig");
  InternalFS.remove(SETTINGS_FILE);

  if (file.open(SETTINGS_FILE, FILE_O_WRITE))
  {
    file.write((uint8_t*)&keyboardconfig, sizeof(keyboardconfig));
    file.close();
  }
}


void setuphid()
{
  LOG_LV1("SETUP","setuphid");
  bluemicro_hid.setBLEManufacturer(MANUFACTURER_NAME);
  bluemicro_hid.setBLETxPower(DEVICE_POWER);
  bluemicro_hid.setBLEModel(DEVICE_NAME);
  bluemicro_hid.setHIDMessageDelay(HIDREPORTINGINTERVAL);
  bluemicro_hid.setUSBPollInterval(HIDREPORTINGINTERVAL/2);
  bluemicro_hid.setUSBStringDescriptor(DEVICE_NAME);
  bluemicro_hid.begin(); 
}


//todo re-install debug CLI as module
void serialsplash()
{
  LOG_LV1("SETUP","serialsplash");
  Serial.begin(115200);
        Serial.println(" ____  _            __  __ _                   ____  _     _____ ");
        Serial.println("| __ )| |_   _  ___|  \\/  (_) ___ _ __ ___    | __ )| |   | ____|");
        Serial.println("|  _ \\| | | | |/ _ \\ |\\/| | |/ __| '__/ _ \\   |  _ \\| |   |  _|  ");
        Serial.println("| |_) | | |_| |  __/ |  | | | (__| | | (_) |  | |_) | |___| |___ ");
        Serial.println("|____/|_|\\__,_|\\___|_|  |_|_|\\___|_|  \\___/___|____/|_____|_____|");
        Serial.println("                                         |_____|                 ");
        Serial.println("");
}

/**************************************************************************************************************************/
//
/**************************************************************************************************************************/
void setupMatrix(void) {
  LOG_LV1("SETUP","setupMatrix");
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

void addsetupcommands()
{
  LOG_LV1("SETUP","addsetupcommands");
  SETUPCOMMAND(commandList, SETUP_HID , setuphid());
  ADDCOMMAND(setupQueue, SETUP_HID );
  SETUPCOMMAND(commandList, SETUP_GPIO , setupGpio());
  ADDCOMMAND(setupQueue, SETUP_GPIO );
  SETUPCOMMAND(commandList, SETUP_WDT , setupWDT());
  ADDCOMMAND(setupQueue, SETUP_WDT );
  SETUPCOMMAND(commandList, SETUP_SERIAL, serialsplash());
  if (keyboardconfig.enableSerial) 
  {
    ADDCOMMAND(setupQueue, SETUP_SERIAL);
  }
//  SETUPCOMMAND(commandList, SETUP_VCCSWITCH, switchVCC(keyboardconfig.polarityVCCSwitch)); // turn on VCC when starting up if needed.
  if(keyboardconfig.enableVCCSwitch)
  {
 ///   ADDCOMMAND(setupQueue, SETUP_VCCSWITCH);
  }
//  SETUPCOMMAND(commandList, SETUP_CHARGER, switchCharger(keyboardconfig.polarityChargerControl)); // turn on Charger when starting up if needed.
  if(keyboardconfig.enableChargerControl)
  {
//    ADDCOMMAND(setupQueue, SETUP_CHARGER);
  }

  SETUPCOMMAND(commandList, SETUP_KEYMAP , setupKeymap());
  ADDCOMMAND(setupQueue, SETUP_KEYMAP );
  SETUPCOMMAND(commandList, SETUP_MATRIX , setupMatrix());
  ADDCOMMAND(setupQueue, SETUP_MATRIX );
  



//  SETUPCOMMAND(commandList, LED_ENABLE , statusLEDs.enable());
//  ADDCOMMAND(setupQueue, LED_ENABLE );
//  SETUPCOMMAND(commandList, LED_HELLO , statusLEDs.hello()); // blinks Status LEDs a couple as last step of setup.
 // ADDCOMMAND(setupQueue, LED_HELLO);
}

void toggleserial()
{
  keyboardconfig.enableSerial = !keyboardconfig.enableSerial; 
  keyboardstate.save2flash = true; 
  keyboardstate.needReset = true;
}

void togglehelpmode()
{
    keyboardstate.helpmode = !keyboardstate.helpmode;
}

void clearbonds()
{
    if (keyboardstate.connectionState == CONNECTION_BLE)
      keyboardstate.needUnpair = true;
}

void automode()
{
    keyboardconfig.connectionMode = CONNECTION_MODE_AUTO;
    if (keyboardstate.helpmode) {
      addStringToQueue("Automatic USB/BLE - Active");
      addKeycodeToQueue(KC_ENTER);
      addStringToQueue("USB Only");
      addKeycodeToQueue(KC_ENTER);
      addStringToQueue("BLE Only");
      addKeycodeToQueue(KC_ENTER);
  }
}

void usbmode()
{
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
    if (keyboardstate.helpmode) [&](){
      addStringToQueue("USB not available on NRF52832");
      addKeycodeToQueue(KC_ENTER);
    }
#endif
}

void blemode()
{
    keyboardconfig.connectionMode = CONNECTION_MODE_BLE_ONLY;
    if (keyboardstate.helpmode) {
      addStringToQueue("Automatic USB/BLE");
      addKeycodeToQueue(KC_ENTER);
      addStringToQueue("USB Only");
      addKeycodeToQueue(KC_ENTER);
      addStringToQueue("BLE Only - Active");
      addKeycodeToQueue(KC_ENTER);
    }  
}


void printbattery()
{
 /*   char buffer [50];
  uint8_t intval;
  //    intval = batterymonitor.vbat_per;
      switch (batterymonitor.batt_type)
      {
        case BATT_UNKNOWN:
   //         snprintf (buffer, sizeof(buffer), "VDD = %.0f mV, VBatt = %.0f mV", batterymonitor.vbat_vdd*1.0, batterymonitor.vbat_mv*1.0);
        break;
        case BATT_CR2032:
            if (intval>99)
            {
      //        snprintf (buffer, sizeof(buffer), "VDD = %.0f mV (%4d %%)", batterymonitor.vbat_mv*1.0, intval);
            }
            else
            {
    //          snprintf (buffer, sizeof(buffer), "VDD = %.0f mV (%3d %%)", batterymonitor.vbat_mv*1.0, intval);
            }    
        break;
        case BATT_LIPO:
            if (intval>99)
            {
        //      sprintf (buffer, "LIPO = %.0f mV (%4d %%)", batterymonitor.vbat_mv*1.0, intval);
            }
            else
            {
       //       sprintf (buffer, "LIPO = %.0f mV (%3d %%)", batterymonitor.vbat_mv*1.0, intval);
            }   
        break;
        case BATT_VDDH:
            if (intval>99)
            {
      //        sprintf (buffer, "LIPO = %.0f mV (%4d %%)", batterymonitor.vbat_mv*1.0, intval);
            }
            else
            {
        //      sprintf (buffer, "LIPO = %.0f mV (%3d %%)", batterymonitor.vbat_mv*1.0, intval);
            }   
        break;
      } 
    addStringToQueue(buffer);
    addKeycodeToQueue(KC_ENTER);*/
}

void printinfo()
{
    char buffer [50];
  uint8_t intval;
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

              case CONNECTION_BLE:
                addStringToQueue("CONNECTION_BLE"); addKeycodeToQueue(KC_ENTER);
              break;

              case CONNECTION_NONE:
                addStringToQueue("CONNECTION_NONE"); addKeycodeToQueue(KC_ENTER);
              break;
            }
}

  void printble()
  {
  char buffer [50];
  uint8_t intval;
      addStringToQueue("Keyboard Name: " DEVICE_NAME " "); addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,"Device Power : %i", DEVICE_POWER); addStringToQueue(buffer);  addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,"Filter RSSI  : %i", FILTER_RSSI_BELOW_STRENGTH); addStringToQueue(buffer);  addKeycodeToQueue(KC_ENTER); 
      addStringToQueue("Type\t RSSI\t name"); addKeycodeToQueue(KC_ENTER); 
      sprintf(buffer,"cent\t %i\t %s",keyboardstate.rssi_cent, keyboardstate.peer_name_cent);addStringToQueue(buffer); addKeycodeToQueue(KC_ENTER); 
      sprintf(buffer,"prph\t %i\t %s",keyboardstate.rssi_prph, keyboardstate.peer_name_prph);addStringToQueue(buffer); addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,"cccd\t %i\t %s",keyboardstate.rssi_cccd, keyboardstate.peer_name_cccd);addStringToQueue(buffer); addKeycodeToQueue(KC_ENTER);
       sprintf(buffer,  "Profile 1:   %s", keyboardconfig.BLEProfileName[0]);
      addStringToQueue(buffer);
      sprintf(buffer,  "Profile 1: %02X:%02X:%02X:%02X:%02X:%02X - %s", keyboardconfig.BLEProfileAddr[0][5],
                                                                        keyboardconfig.BLEProfileAddr[0][4],
                                                                        keyboardconfig.BLEProfileAddr[0][3],
                                                                        keyboardconfig.BLEProfileAddr[0][2],
                                                                        keyboardconfig.BLEProfileAddr[0][1],
                                                                        keyboardconfig.BLEProfileAddr[0][0],
                                                                        keyboardconfig.BLEProfileName[0]);
      addStringToQueue(buffer);
      if (keyboardconfig.BLEProfile == 0) addStringToQueue(" (active)");
      addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,  "Profile 2:   %s", keyboardconfig.BLEProfileName[1]);
      addStringToQueue(buffer);
      sprintf(buffer,  "Profile 2: %02X:%02X:%02X:%02X:%02X:%02X - %s", keyboardconfig.BLEProfileAddr[1][5],
                                                                        keyboardconfig.BLEProfileAddr[1][4],
                                                                        keyboardconfig.BLEProfileAddr[1][3],
                                                                        keyboardconfig.BLEProfileAddr[1][2],
                                                                        keyboardconfig.BLEProfileAddr[1][1],
                                                                        keyboardconfig.BLEProfileAddr[1][0],
                                                                        keyboardconfig.BLEProfileName[1]);
      addStringToQueue(buffer);
      if (keyboardconfig.BLEProfile == 1) addStringToQueue(" (active)");
      addKeycodeToQueue(KC_ENTER);
      sprintf(buffer,  "Profile 3:   %s", keyboardconfig.BLEProfileName[2]);
      addStringToQueue(buffer);
      sprintf(buffer,  "Profile 3: %02X:%02X:%02X:%02X:%02X:%02X - %s", keyboardconfig.BLEProfileAddr[2][5],
                                                                        keyboardconfig.BLEProfileAddr[2][4],
                                                                        keyboardconfig.BLEProfileAddr[2][3],
                                                                        keyboardconfig.BLEProfileAddr[2][2],
                                                                        keyboardconfig.BLEProfileAddr[2][1],
                                                                        keyboardconfig.BLEProfileAddr[2][0],
                                                                        keyboardconfig.BLEProfileName[2]);
      addStringToQueue(buffer);
      if (keyboardconfig.BLEProfile == 2) addStringToQueue(" (active)");
      addKeycodeToQueue(KC_ENTER);
      addKeycodeToQueue(KC_ENTER);
      ble_gap_addr_t gap_addr;
     // gap_addr = bt_getMACAddr(); // TODO MOVE THIS FUNCTION TO BE ACCESSIBLE IN LIBRARY
      sprintf(buffer,  "BT MAC Addr: %02X:%02X:%02X:%02X:%02X:%02X", gap_addr.addr[5], gap_addr.addr[4], gap_addr.addr[3], gap_addr.addr[2], gap_addr.addr[1], gap_addr.addr[0]);
      addStringToQueue(buffer);
      addKeycodeToQueue(KC_ENTER);
      addKeycodeToQueue(KC_ENTER);
  }
  void printhelp()
  {
    ;
  }

  void sleepnow()
  {
    // if (keyboardstate.connectionState != CONNECTION_USB) sleepNow();
  }



void setdefaultbatterycalc()
{
  //    batterymonitor.setmvToPercentCallback(mvToPercent_default);
  //    batterymonitor.updateBattery(); // force an update
}
void settestbatterycalc()
{
   //   batterymonitor.setmvToPercentCallback(mvToPercent_test);
   //   batterymonitor.updateBattery(); // force an update
} 

void setbleprofile1()
{
     // if (keyboardstate.connectionState != CONNECTION_USB) // reseting/rebooting KB when BLE Profile switching on USB would be ennoying...
        {
          keyboardconfig.BLEProfile = 0;
          keyboardstate.save2flash = true;
          keyboardstate.needReset = true;
      }
}

void setbleprofile2()
{
     // if (keyboardstate.connectionState != CONNECTION_USB) // reseting/rebooting KB when BLE Profile switching on USB would be ennoying...
      {
          keyboardconfig.BLEProfile = 1;
          keyboardstate.save2flash = true;
          keyboardstate.needReset = true;
      }
}

void setbleprofile3()
{
    //  if (keyboardstate.connectionState != CONNECTION_USB) // reseting/rebooting KB when BLE Profile switching on USB would be ennoying...
      {
          keyboardconfig.BLEProfile = 2;
          keyboardstate.save2flash = true;
          keyboardstate.needReset = true;
      }
}





void process_user_special_keys_command()
{
LOG_LV1("LOOP","process_user_special_keys_command");
  //todo update special keys
////  uint8_t mods = KeyScanner::currentReport.modifier ;
       ;//   LOG_LV1("SPECIAL","PROCESS: %i %i %i %i %i %i %i %i %i" ,KeyScanner::special_key,mods, KeyScanner::currentReport.keycode[0],KeyScanner::currentReport.keycode[1],KeyScanner::currentReport.keycode[2], KeyScanner::currentReport.keycode[3],KeyScanner::currentReport.keycode[4], KeyScanner::currentReport.keycode[5],KeyScanner::bufferposition );  

 /*       switch (mods)
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
        }  */
}





void addkeyboardcommands()
{
  LOG_LV1("SETUP","addkeyboardcommands");
    SETUPCOMMAND(commandList,  RESET, NVIC_SystemReset() );
    SETUPCOMMAND(commandList,  DEBUG, toggleserial() );
    SETUPCOMMAND(commandList,  EEPROM_RESET, {keyboardstate.needFSReset = true;} );
    SETUPCOMMAND(commandList,  CLEAR_BONDS,clearbonds());
    SETUPCOMMAND(commandList,  DFU, enterOTADfu());
    SETUPCOMMAND(commandList,  SERIAL_DFU, enterSerialDfu());
    SETUPCOMMAND(commandList,  UF2_DFU, enterUf2Dfu() );
    SETUPCOMMAND(commandList,  HELP_MODE, togglehelpmode());
    SETUPCOMMAND(commandList,  OUT_AUTO,automode());
    SETUPCOMMAND(commandList,  OUT_USB, usbmode());
    SETUPCOMMAND(commandList,  OUT_BT,blemode());
    SETUPCOMMAND(commandList,  PRINT_BATTERY, printbattery());
    SETUPCOMMAND(commandList,  PRINT_INFO, printinfo());
    SETUPCOMMAND(commandList,  PRINT_BLE, printble());
    SETUPCOMMAND(commandList,  PRINT_HELP, printhelp());
 //   SETUPCOMMAND(commandList,  SLEEP_NOW, sleepnow());
    SETUPCOMMAND(commandList,  BATTERY_CALC_DEFAULT, setdefaultbatterycalc());
    SETUPCOMMAND(commandList,  BATTERY_CALC_TEST, settestbatterycalc());
    SETUPCOMMAND(commandList,  BLEPROFILE_1, setbleprofile1());
    SETUPCOMMAND(commandList,  BLEPROFILE_2, setbleprofile2());
    SETUPCOMMAND(commandList,  BLEPROFILE_3, setbleprofile3());

    SETUPCOMMAND(commandList,  WIN_A_GRAVE, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_2, KC_KP_4));  //Alt 0224 a grave

    SETUPCOMMAND(commandList,   WIN_A_ACUTE, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_2, KC_KP_5) ); //Alt 0225 a acute
    SETUPCOMMAND(commandList,   WIN_A_CIRCU, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_2, KC_KP_6) );  //Alt 0226 a circumflex
    SETUPCOMMAND(commandList,   WIN_A_TILDE, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_2, KC_KP_7) );  //Alt 0227 a tilde
    SETUPCOMMAND(commandList,   WIN_A_UMLAU, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_2, KC_KP_8) );  //Alt 0228 a umlaut

    SETUPCOMMAND(commandList,   WIN_A_GRAVE_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_9, KC_KP_2) );  //Alt 0192 A grave
    SETUPCOMMAND(commandList,   WIN_A_ACUTE_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_9, KC_KP_3) );  //Alt 0193 A acute
    SETUPCOMMAND(commandList,   WIN_A_CIRCU_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_9, KC_KP_4) );  //Alt 0194 A circumflex
    SETUPCOMMAND(commandList,   WIN_A_TILDE_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_9, KC_KP_5) );  //Alt 0195 A tilde
    SETUPCOMMAND(commandList,   WIN_A_UMLAU_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_9, KC_KP_6) );  //Alt 0196 A umlaut

    SETUPCOMMAND(commandList,   WIN_C_CEDIL, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_1) );  //Alt 0231 c cedilla
    SETUPCOMMAND(commandList,   WIN_C_CEDIL_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_9, KC_KP_9) ); //Alt 0199 C cedilla

    SETUPCOMMAND(commandList,   WIN_E_GRAVE, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_2) ); 
    SETUPCOMMAND(commandList,   WIN_E_ACUTE, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_3) ); 
    SETUPCOMMAND(commandList,   WIN_E_CIRCU, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_4) ); 
    SETUPCOMMAND(commandList,   WIN_E_UMLAU, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_5) ); 

    SETUPCOMMAND(commandList,    WIN_I_GRAVE, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_6) ); //Alt 0236 i grave
    SETUPCOMMAND(commandList,    WIN_I_ACUTE, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_7) ); //Alt 0237 i acute
    SETUPCOMMAND(commandList,    WIN_I_CIRCU, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_8) ); //Alt 0238 i circumflex
    SETUPCOMMAND(commandList,    WIN_I_UMLAU, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_3, KC_KP_9) );  //Alt 0239 i umlaut

    SETUPCOMMAND(commandList,    WIN_I_GRAVE_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_0, KC_KP_4) ); //Alt 0204 I grave
    SETUPCOMMAND(commandList,    WIN_I_ACUTE_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_0, KC_KP_5) );  //Alt 0205 I acute
    SETUPCOMMAND(commandList,    WIN_I_CIRCU_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_0, KC_KP_6) );  //Alt 0206 I circumflex
    SETUPCOMMAND(commandList,    WIN_I_UMLAU_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_0, KC_KP_7) ); //Alt 0207 I umlaut

    SETUPCOMMAND(commandList,    WIN_N_TILDE, EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_6, KC_KP_4) ); //Alt 164 n tilde
    SETUPCOMMAND(commandList,    WIN_N_TILDE_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_6, KC_KP_5) );  //Alt 165 N tilde

    SETUPCOMMAND(commandList,    WIN_O_GRAVE, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_4, KC_KP_2) );  //Alt 0242 o grave
    SETUPCOMMAND(commandList,    WIN_O_ACUTE, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_4, KC_KP_3) );  //Alt 0243 o acute
    SETUPCOMMAND(commandList,    WIN_O_CIRCU, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_4, KC_KP_4) );  //Alt 0244 o circumflex
    SETUPCOMMAND(commandList,    WIN_O_TILDE, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_4, KC_KP_5) );   //Alt 0245 o tilde
    SETUPCOMMAND(commandList,    WIN_O_UMLAU, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_4, KC_KP_6) );   //Alt 0246 o umlaut

    SETUPCOMMAND(commandList,    WIN_O_GRAVE_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_0) );  //Alt 0210 O grave
    SETUPCOMMAND(commandList,    WIN_O_ACUTE_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_1) );  //Alt 0211 O acute
    SETUPCOMMAND(commandList,    WIN_O_CIRCU_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_2) ); //Alt 0212 O circumflex
    SETUPCOMMAND(commandList,    WIN_O_TILDE_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_3) );  //Alt 0213 O tilde
    SETUPCOMMAND(commandList,    WIN_O_UMLAU_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_4) );  //Alt 0214 O umlaut

    SETUPCOMMAND(commandList,    WIN_S_CARON, EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_5, KC_KP_4) );  //Alt 0154 s caron
    SETUPCOMMAND(commandList,    WIN_S_CARON_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_3, KC_KP_8) );   //Alt 0138 S caron

    SETUPCOMMAND(commandList,   WIN_U_GRAVE, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_4, KC_KP_9) );   //Alt 0249 u grave
    SETUPCOMMAND(commandList,   WIN_U_ACUTE, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_5, KC_KP_0) );  //Alt 0250 u acute
    SETUPCOMMAND(commandList,   WIN_U_CIRCU, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_5, KC_KP_1) );  //Alt 0251 u circumflex
    SETUPCOMMAND(commandList,   WIN_U_UMLAU, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_5, KC_KP_2) ); //Alt 0252 u umlaut

    SETUPCOMMAND(commandList,   WIN_U_GRAVE_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_1) );  //Alt 0217 U grave
    SETUPCOMMAND(commandList,   WIN_U_ACUTE_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_8) ); //Alt 0218  U acute
    SETUPCOMMAND(commandList,   WIN_U_CIRCU_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_1, KC_KP_9) ); //Alt 0219 U circumflex
    SETUPCOMMAND(commandList,   WIN_U_UMLAU_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_2, KC_KP_0) );  //Alt 0220 U umlaut

    SETUPCOMMAND(commandList,    WIN_Y_ACUTE, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_5, KC_KP_3) );  //Alt 0253 y acute
    SETUPCOMMAND(commandList,    WIN_Y_UMLAU, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_5, KC_KP_5) );  //Alt 0255 y umlaut

    SETUPCOMMAND(commandList,    WIN_Y_ACUTE_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_2, KC_KP_2, KC_KP_1) );  //Alt 0221 Y tilde
    SETUPCOMMAND(commandList,    WIN_Y_UMLAU_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_5, KC_KP_9) );   //Alt 0159 Y umlaut

    SETUPCOMMAND(commandList,    WIN_Z_CARON, EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_5, KC_KP_4) );  //Alt 0154 z caron
    SETUPCOMMAND(commandList,    WIN_Z_CARON_CAP, EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_3, KC_KP_8) );   //Alt 0138 Z caron

    SETUPCOMMAND(commandList,   SYM_DEGREE, EXPAND_ALT_CODE(KC_KP_0, KC_KP_1, KC_KP_7, KC_KP_6) ); // Alt 0176 degree symbol   
    SETUPCOMMAND(commandList,   KS(KC_ESC), process_user_special_keys_command());
}


void run_setup_commands(void)
{
    SORTCOMMANDS(commandList);
    RUNCOMMANDS(setupQueue, commandList);
}
