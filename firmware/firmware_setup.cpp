// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

/**************************************************************************************************************************/
#include "firmware_setup.h"

commandlist_t commandList; 
commandqueue_t setupQueue;
commandqueue_t commandQueue;

using namespace Adafruit_LittleFS_Namespace;
#define SETTINGS_FILE "/settings"
File file(InternalFS);

/**************************************************************************************************************************/
// Keyboard Matrix
byte rows[] MATRIX_ROW_PINS;        // Contains the GPIO Pin Numbers defined in keyboard_config.h
byte columns[] MATRIX_COL_PINS;     // Contains the GPIO Pin Numbers defined in keyboard_config.h  
 std::vector<uint16_t> stringbuffer; // buffer for macros to type into...
 std::vector<HIDKeyboard> reportbuffer; 

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
  InternalFS.remove(SETTINGS_FILE);

  if (file.open(SETTINGS_FILE, FILE_O_WRITE))
  {
    file.write((uint8_t*)&keyboardconfig, sizeof(keyboardconfig));
    file.close();
  }
}


void setuphid()
{
  bluemicro_hid.setBLEManufacturer(MANUFACTURER_NAME);
  bluemicro_hid.setBLETxPower(DEVICE_POWER);
  bluemicro_hid.setBLEModel(DEVICE_NAME);
  bluemicro_hid.setHIDMessageDelay(HIDREPORTINGINTERVAL);
  bluemicro_hid.setUSBPollInterval(HIDREPORTINGINTERVAL/2);
  bluemicro_hid.setUSBStringDescriptor(DEVICE_NAME);
  bluemicro_hid.begin(); 
}

void setupnrf52()
{
  setupGpio();                                                                // checks that NFC functions on GPIOs are disabled.
  setupWDT();
}

void serialsplash()
{
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
  SETUPCOMMAND(commandList, COMMANDID(0) , setuphid());
  ADDCOMMAND(setupQueue, COMMANDID(0));
  SETUPCOMMAND(commandList, COMMANDID(1) , setupnrf52());
  ADDCOMMAND(setupQueue, COMMANDID(1));
  SETUPCOMMAND(commandList, COMMANDID(2) , serialsplash());
  if (keyboardconfig.enableSerial) 
  {
    ADDCOMMAND(setupQueue, COMMANDID(2));
  }
  SETUPCOMMAND(commandList, COMMANDID(3) , switchVCC(keyboardconfig.polarityVCCSwitch)); // turn on VCC when starting up if needed.
  if(keyboardconfig.enableVCCSwitch)
  {
    ADDCOMMAND(setupQueue, COMMANDID(3));
  }
  SETUPCOMMAND(commandList, COMMANDID(4) , switchCharger(keyboardconfig.polarityChargerControl)); // turn on Charger when starting up if needed.
  if(keyboardconfig.enableChargerControl)
  {
    ADDCOMMAND(setupQueue, COMMANDID(4));
  }

  SETUPCOMMAND(commandList, COMMANDID(5) , setupKeymap());
  ADDCOMMAND(setupQueue, COMMANDID(5));
  SETUPCOMMAND(commandList, COMMANDID(6) , setupMatrix());
  ADDCOMMAND(setupQueue, COMMANDID(6));
  
  SETUPCOMMAND(commandList, COMMANDID(7) , stringbuffer.clear());
  ADDCOMMAND(setupQueue, COMMANDID(7));
  SETUPCOMMAND(commandList, COMMANDID(8) , reportbuffer.clear());
  ADDCOMMAND(setupQueue, COMMANDID(8));

  SETUPCOMMAND(commandList, COMMANDID(9) , statusLEDs.enable());
  ADDCOMMAND(setupQueue, COMMANDID(9));
  SETUPCOMMAND(commandList, COMMANDID(10) , statusLEDs.hello()); // blinks Status LEDs a couple as last step of setup.
  ADDCOMMAND(setupQueue, COMMANDID(10));
}
