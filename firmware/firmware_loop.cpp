// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

/**************************************************************************************************************************/
#include "firmware_loop.h"

/**************************************************************************************************************************/
// Keyboard Scanning
/**************************************************************************************************************************/
//todo get scanning code into separate module
//todo get generic code scanning module for non-nrf52 boards.
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
LOG_LV1("BLEMIC","scanMatrix" ); 
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

/**************************************************************************************************************************/
// macro string queue management
/**************************************************************************************************************************/
void addStringToQueue(const char* str)
{
  bluemicro_hid.keySequence(str);
   LOG_LV1("QUEUE","addStringToQueue" );        

}
/**************************************************************************************************************************/
/**************************************************************************************************************************/


void addKeycodeToQueue(const uint16_t keycode, const uint8_t modifier)
{
  LOG_LV1("QUEUE","addKeycodeToQueue km" ); 
  auto hidKeycode = static_cast<uint8_t>(keycode & 0x00FF);
        if (hidKeycode >= KC_A && hidKeycode <= KC_EXSEL)  // only insert keycodes if they are valid keyboard codes...
        {
            HIDKeyboard reportarray = {modifier, {hidKeycode, 0 ,0, 0, 0, 0}};
            bluemicro_hid.keyboardReport(reportarray.modifier , reportarray.keycode);
        }
  }  

void addKeycodeToQueue(const uint16_t keycode)
{
  LOG_LV1("QUEUE","addKeycodeToQueue k" ); 
  auto hidKeycode = static_cast<uint8_t>(keycode & 0x00FF);
     auto extraModifiers = static_cast<uint8_t>((keycode & 0xFF00) >> 8);

        if (hidKeycode >= KC_A && hidKeycode <= KC_EXSEL)  // only insert keycodes if they are valid keyboard codes...
        {
            HIDKeyboard reportarray = {extraModifiers, {hidKeycode, 0 ,0, 0, 0, 0}};
            bluemicro_hid.keyboardReport(reportarray.modifier , reportarray.keycode);
        }
  }  


/**************************************************************************************************************************/
// Communication with computer and other boards
/**************************************************************************************************************************/
void sendKeyPresses() {

   KeyScanner::getReport();                                         // get state data - Data is in KeyScanner::currentReport 

  if (KeyScanner::special_key > 0){
      ADDCOMMAND(commandQueue, KS(KC_ESC) );
      KeyScanner::special_key = 0;
  }

  if (KeyScanner::macro > 0){
      process_user_macros(KeyScanner::macro);
      KeyScanner::macro = 0; 
  } 

  #ifdef ENABLE_COMBOS
     std::for_each(combos.keycodebuffertosend.rbegin(), combos.keycodebuffertosend.rend(), [](uint16_t keycode){addKeycodeToQueue(keycode);} );
     combos.keycodebuffertosend.clear();
  #endif

  if ((KeyScanner::reportChanged))  //any new key presses anywhere?
  {     

      bluemicro_hid.keyboardReport(KeyScanner::currentReport.modifier, KeyScanner::currentReport.keycode);
                                                                      
    //    LOG_LV1("MXSCAN","SEND: %i %i %i %i %i %i %i %i %i " ,keyboardstate.timestamp,KeyScanner::currentReport.modifier, KeyScanner::currentReport.keycode[0],KeyScanner::currentReport.keycode[1],KeyScanner::currentReport.keycode[2], KeyScanner::currentReport.keycode[3],KeyScanner::currentReport.keycode[4], KeyScanner::currentReport.keycode[5],KeyScanner::currentReport.layer);        
  } 
  if (KeyScanner::specialfunction > 0)
  {
    
    ADDCOMMAND(commandQueue, KeyScanner::specialfunction);
    KeyScanner::specialfunction = 0; 
  } 
  if (KeyScanner::consumer > 0)
  {
    // TODO send consumeer code
    KeyScanner::consumer = 0; 
  } 
  if (KeyScanner::mouse > 0)
  {
    // TODO  send mouse code
    KeyScanner::mouse = 0; 
  }
  
}

//TODO re-implement sleep as module
void checkforsleep()
{
    
    switch (keyboardstate.connectionState)
    {
      case CONNECTION_USB:
        // never sleep in this case
      break;

      case CONNECTION_BLE:
      //  gotoSleep(timesincelastkeypress, true);
      break;

      case CONNECTION_NONE:
     //   gotoSleep(timesincelastkeypress, false);
      break;
    }
  
}

void checkforunpair()
{
  if (keyboardstate.needUnpair)
  {
      ADDCOMMAND(commandQueue, RENDER_UNPAIR);
  }
}

void unpaircommand()
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

void checkforsave2flash()
{
  if (keyboardstate.save2flash)
  { 
    ADDCOMMAND(commandQueue, RENDER_SAVE );
    keyboardstate.save2flash = false;
  }

}

void checkforformat()
{
  if (keyboardstate.needFSReset)
  {  
    ADDCOMMAND(commandQueue, RENDER_FORMAT );
    keyboardstate.needReset = true;
  }
}

void checkforreboot()
{
    if (keyboardstate.needReset)  ADDCOMMAND(commandQueue, RENDER_REBOOT );
}
  


void updatebattery()
{
      batterymonitor.updateBattery(); 
      keyboardstate.batterytimer = keyboardstate.timestamp;
      keyboardstate.batt_type = batterymonitor.batt_type;
      keyboardstate.vbat_mv = batterymonitor.vbat_mv;
      keyboardstate.vbat_per = batterymonitor.vbat_per;
      keyboardstate.vbat_vdd = batterymonitor.vbat_vdd;
}


//todo Implement LEDs as module
void updateleds()
{
    keyboardstate.statusledtimer = keyboardstate.timestamp;
    statusLEDs.update();
}


void addloopcommands(void)
{
    SETUPCOMMAND(commandList, PROCESSS_WDT , updateWDT());
    SETUPCOMMAND(commandList, PROCESSS_MATRIX , scanMatrix());
    SETUPCOMMAND(commandList, UPDATE_KEYS , sendKeyPresses() );
    SETUPCOMMAND(commandList, RENDER_HID , bluemicro_hid.processQueues(CONNECTION_MODE_AUTO) );
    SETUPCOMMAND(commandList, RENDER_SLEEP , checkforsleep() );
    SETUPCOMMAND(commandList, UPDATE_UNPAIR , checkforunpair() );
    SETUPCOMMAND(commandList, RENDER_UNPAIR , unpaircommand() );
    SETUPCOMMAND(commandList, UPDATE_SAVE , checkforsave2flash() );
    SETUPCOMMAND(commandList, RENDER_SAVE , saveConfig() );
    SETUPCOMMAND(commandList, UPDATE_FORMAT , checkforformat() );
    SETUPCOMMAND(commandList, RENDER_FORMAT, InternalFS.format() );
    SETUPCOMMAND(commandList, UPDATE_REBOOT, checkforreboot() );
    SETUPCOMMAND(commandList, RENDER_REBOOT, NVIC_SystemReset() );   // this reboots the keyboard.
    SETUPCOMMAND(commandList, BATTERY_UPDATE, updatebattery() );
    SETUPCOMMAND(commandList, LED_UPDATE , updateleds() );

    ADDCOMMAND(loopQueue, PROCESSS_WDT );
    ADDCOMMAND(loopQueue, PROCESSS_MATRIX );
    ADDCOMMAND(loopQueue, UPDATE_KEYS );   
    ADDCOMMAND(loopQueue, RENDER_HID);
    ADDCOMMAND(loopQueue, RENDER_SLEEP ); 
    ADDCOMMAND(loopQueue, UPDATE_UNPAIR ); 
    ADDCOMMAND(loopQueue, UPDATE_SAVE ); 
    ADDCOMMAND(loopQueue, UPDATE_FORMAT ); 
    ADDCOMMAND(loopQueue, UPDATE_REBOOT ); 
    ADDCOMMAND(loopQueue, BATTERY_UPDATE );
    ADDCOMMAND(loopQueue, LED_UPDATE );

    SETUPCOMMAND(commandList, RUN_COMMAND_QUEUE, RUNCOMMANDS(commandQueue, commandList) );  // second to command is to run the command queue
    SETUPCOMMAND(commandList, CLEAR_COMMAND_QUEUE, commandQueue.clear());  // last command to run is to clear the command queue
    ADDCOMMAND(loopQueue, RUN_COMMAND_QUEUE );
    ADDCOMMAND(loopQueue, CLEAR_COMMAND_QUEUE ); 

}
