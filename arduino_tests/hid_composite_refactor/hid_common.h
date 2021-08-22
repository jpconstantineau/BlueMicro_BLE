#include "Adafruit_TinyUSB.h"
#ifndef HID_COMMON
#define HID_COMMON

// Report ID
enum
{
  RID_KEYBOARD = 1,
  RID_MOUSE,
  RID_CONSUMER_CONTROL, // Media, volume etc ..
};

// HID report descriptor using TinyUSB's template
uint8_t const desc_hid_report[] =
{
  TUD_HID_REPORT_DESC_KEYBOARD( HID_REPORT_ID(RID_KEYBOARD) ),
  TUD_HID_REPORT_DESC_MOUSE   ( HID_REPORT_ID(RID_MOUSE) ),
  TUD_HID_REPORT_DESC_CONSUMER( HID_REPORT_ID(RID_CONSUMER_CONTROL) )
};

extern Adafruit_USBD_HID usb_hid;

        bool begin(void);
        bool ready(void);

        bool sendReport(uint8_t report_id, void const *report, uint8_t len);

  // Report helpers
  bool sendReport8(uint8_t report_id, uint8_t num);
  bool sendReport16(uint8_t report_id, uint16_t num);
  bool sendReport32(uint8_t report_id, uint32_t num);

  //------------- Keyboard API -------------//
  bool keyboardReport(uint8_t report_id, uint8_t modifier, uint8_t keycode[6]);
  bool keyboardPress(uint8_t report_id, char ch);
  bool keyboardRelease(uint8_t report_id);

  //------------- Mouse API -------------//
  bool mouseReport(uint8_t report_id, uint8_t buttons, int8_t x, int8_t y,
                   int8_t vertical, int8_t horizontal);
  bool mouseMove(uint8_t report_id, int8_t x, int8_t y);
  bool mouseScroll(uint8_t report_id, int8_t scroll, int8_t pan);
  bool mouseButtonPress(uint8_t report_id, uint8_t buttons);
  bool mouseButtonRelease(uint8_t report_id);



#endif
