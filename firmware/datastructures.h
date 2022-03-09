// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H
#include <array>

#define BLUEMICRO_CONFIG_VERSION 6
// this should be incremented every time the PersistentState structure definition is updated.
// This will ensure that the SETTINGS_FILE file is reset when the structure is updated.

    typedef union {
        struct { 
        uint8_t  version;
        uint8_t    mode;
        uint8_t    user1;  
        uint8_t    user2; 
        
        uint32_t matrixscaninterval; // timer interval = normal priority
        uint32_t batteryinterval;  // timer interval = normal priority
        uint32_t keysendinterval; //   normal priority
        uint32_t lowpriorityloopinterval;
        uint32_t lowestpriorityloopinterval;

        uint8_t    pinBLELED;  
        uint8_t    pinKBLED; 
        uint8_t    pinPWMLED;
        uint8_t    pinRGBLED;

        uint8_t    pinVCCSwitch;
        uint8_t    pinChargerControl;

        bool    enableBLELED; 
        bool    enableKBLED; 
        bool    enablePWMLED;  
        bool    enableRGBLED;

        bool    polarityBLELED; 
        bool    polarityKBLED; 
        bool    polarityPWMLED;  
        bool    enableVCCSwitch;  

        bool    polarityVCCSwitch;  
        bool    enableChargerControl;  
        bool    polarityChargerControl;    
        bool    enableDisplay;

        bool    enableSerial;
        bool    enableAudio;
        bool    dummy1;
        bool    dummy2;

        uint8_t connectionMode;
        uint8_t BLEProfile;
        uint16_t BLEProfileEdiv[3];
        uint8_t BLEProfileAddr[3][6];
        char BLEProfileName[3][32];
  
       };
       char data[160]; } PersistentState;  // meant for configuration and things that we want to store in flash so that we can pick it up on the next reboot.




typedef struct {
  uint32_t timestamp;
  uint32_t lastupdatetime;
  uint32_t lastreporttime;
  uint32_t lastuseractiontime;

  uint16_t layer;
  uint8_t statuskb;
  uint8_t statusble;

  uint32_t vbat_raw;
  uint32_t vbat_mv;
  uint32_t vbat_vdd;
  uint32_t vbat_vddh;

  uint32_t batterytimer;
  uint32_t displaytimer;
  uint32_t audiotimer;
  uint32_t rgbledtimer;
  uint32_t pwmledtimer;
  uint32_t statusledtimer;

  char peer_name_prph[32];

  uint16_t conn_handle_prph;
  int8_t rssi_prph;

  uint8_t vbat_per;

  char peer_name_cent[32];

  uint16_t conn_handle_cent;
  int8_t rssi_cent;

  uint8_t batt_type;

  char peer_name_cccd[32];

  uint16_t conn_handle_cccd;
  int8_t rssi_cccd;

  uint8_t connectionState;

  bool rssi_prph_updated;
  bool rssi_cent_updated;
  bool rssi_cccd_updated;
  bool helpmode;
  bool needReset;
  bool needUnpair;
  bool needFSReset;
  bool save2flash;

  uint8_t user1;
  uint8_t user2;
  uint8_t user3;
  int8_t encoder1pos;
  int8_t encoder2pos;
  int8_t encoder3pos;
  int8_t encoder4pos;
  int8_t encoder5pos;
  int8_t encoder6pos;
  int8_t encoder7pos;
  int8_t encoder8pos;

} DynamicState; // meant for keyboard and BLE status and things that are dynamic and should not be stored in flash.

// TODO: Add the structures and function definitions for keycode buffer for user processing

typedef void (*ledupdateCallback)(PersistentState *config, DynamicState *status);
typedef void (*updateDisplay_cb_t)(PersistentState *cfg, DynamicState *stat);

//enum connectionState { CONNECTION_NONE, CONNECTION_USB, CONNECTION_BT };

//enum connectionMode { CONNECTION_MODE_AUTO, CONNECTION_MODE_USB_ONLY, CONNECTION_MODE_BLE_ONLY };

enum backgroundTaskID {
  BACKGROUND_TASK_NONE,
  BACKGROUND_TASK_AUDIO,
  BACKGROUND_TASK_BATTERY,
  BACKGROUND_TASK_DISPLAY,
  BACKGROUND_TASK_STATUSLED,
  BACKGROUND_TASK_PWMLED,
  BACKGROUND_TASK_RGBLED
};
/*
struct HIDKeyboard {
    uint8_t modifier;
    uint8_t keycode[6];
    uint16_t layer; 

    bool operator!= (const HIDKeyboard &c2)
    {
          return !(*this == c2); 
    }

    inline bool operator== (const HIDKeyboard &c2)
    {
          return  (keycode[0]==c2.keycode[0]) &&
                  (modifier==c2.modifier    ) &&
                  (layer==c2.layer          ) &&
                  (keycode[1]==c2.keycode[1]) &&
                  (keycode[2]==c2.keycode[2]) &&
                  (keycode[3]==c2.keycode[3]) &&
                  (keycode[4]==c2.keycode[4]) &&
                  (keycode[5]==c2.keycode[5]) ;
              
    }

  } ;

*/


/*
typedef struct {
    uint8_t buttons; 
    int8_t x; 
    int8_t y;
    int8_t wheel; 
    int8_t pan;
  } HIDMouse;

typedef struct {
    uint16_t usage_code;
  } HIDConsumer;

typedef struct {
  HIDKeyboard keyboard;
  HIDMouse mouse;
  HIDConsumer consumer;
  } HIDMessages; 
*/
#endif
