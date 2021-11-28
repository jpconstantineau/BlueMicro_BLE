#ifndef HID_DATA_STRUCTURES_H
#define HID_DATA_STRUCTURES_H
#include <cstdint>

// Report ID
enum
{
  RID_KEYBOARD = 1,
  RID_MOUSE,
  RID_CONSUMER_CONTROL, // Media, volume etc ..
};

enum connectionState { CONNECTION_NONE, CONNECTION_USB, CONNECTION_BLE };

enum connectionMode { CONNECTION_MODE_AUTO, CONNECTION_MODE_USB_ONLY, CONNECTION_MODE_BLE_ONLY };

struct HIDKeyboard {
    uint8_t modifier;
    uint8_t keycode[6];

    bool operator!= (const HIDKeyboard &c2)
    {
          return !(*this == c2); 
    }

    inline bool operator== (const HIDKeyboard &c2)
    {
          return  (keycode[0]==c2.keycode[0]) &&
                  (modifier==c2.modifier    ) &&
                  (keycode[1]==c2.keycode[1]) &&
                  (keycode[2]==c2.keycode[2]) &&
                  (keycode[3]==c2.keycode[3]) &&
                  (keycode[4]==c2.keycode[4]) &&
                  (keycode[5]==c2.keycode[5]) ;
              
    }
  } ;


struct HIDMouse {
    uint8_t buttons;
    int8_t x;
    int8_t y; 
    int8_t wheel; 
    int8_t pan;

    bool operator!= (const HIDMouse &c2)
    {
          return !(*this == c2); 
    }

    inline bool operator== (const HIDMouse &c2)
    {
          return  (buttons==c2.buttons) &&
                  (x==c2.x) &&
                  (y==c2.y) &&
                  (wheel==c2.wheel) &&
                  (pan==c2.pan) ;       
    }    
  } ;


struct HIDConsumer {
    uint16_t usage_code;

    bool operator!= (const HIDConsumer &c2)
    {
          return !(*this == c2); 
    }

    inline bool operator== (const HIDConsumer &c2)
    {
          return  (usage_code==c2.usage_code);       
    }    
  } ;


struct HIDGamepad {
    int8_t x; 
    int8_t y;
    int8_t z;
    int8_t rz;
    int8_t rx;
    int8_t r;

    bool operator!= (const HIDGamepad &c2)
    {
          return !(*this == c2); 
    }

    inline bool operator== (const HIDGamepad &c2)
    {
          return  (x==c2.x) &&
                  (y==c2.y) &&
                  (z==c2.z) &&
                  (rz==c2.rz) &&
                  (rx==c2.rx) &&
                  (r==c2.r) ;       
    }    
  } ;

#endif /* HID_DATA_STRUCTURES_H */
