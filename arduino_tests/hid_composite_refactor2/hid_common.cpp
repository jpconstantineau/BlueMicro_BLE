
#include <arduino.h>
#include "hid_common.h"

// USB HID object
Adafruit_USBD_HID usb_hid;

void hid_start()
{
    usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  //usb_hid.setStringDescriptor("TinyUSB HID Composite");

  usb_hid.begin();
}


bool hid_ready(void)
{
  return usb_hid.ready();
}

  bool hid_sendReport(uint8_t report_id, void const *report, uint8_t len){
    return usb_hid.sendReport( report_id,  report, len);
  }

  // Report helpers
  bool hid_sendReport8(uint8_t report_id, uint8_t num){
    return usb_hid.sendReport8( report_id,  num);
  }
  bool hid_sendReport16(uint8_t report_id, uint16_t num){
    return usb_hid.sendReport16( report_id, num);
  }
  bool hid_sendReport32(uint8_t report_id, uint32_t num){
    return usb_hid.sendReport32( report_id,  num);
  }

  //------------- Keyboard API -------------//
  bool hid_keyboardReport(uint8_t report_id, uint8_t modifier, uint8_t keycode[6]){
    return usb_hid.keyboardReport( report_id,  modifier,  keycode);
  }
  bool hid_keyboardPress(uint8_t report_id, char ch){
    return usb_hid.keyboardPress( report_id, ch);
  }
  bool hid_keyboardRelease(uint8_t report_id){
    return usb_hid.keyboardRelease( report_id);
  }

  //------------- Mouse API -------------//
  bool hid_mouseReport(uint8_t report_id, uint8_t buttons, int8_t x, int8_t y,
                   int8_t vertical, int8_t horizontal){
    return usb_hid.mouseReport( report_id,  buttons,  x,  y, vertical, horizontal);
  }
  bool hid_mouseMove(uint8_t report_id, int8_t x, int8_t y){
    return usb_hid.mouseMove( report_id,  x,  y);
  }
  bool hid_mouseScroll(uint8_t report_id, int8_t scroll, int8_t pan){
    return usb_hid.mouseScroll( report_id,  scroll,  pan);
  }
  bool hid_mouseButtonPress(uint8_t report_id, uint8_t buttons){
    return usb_hid.mouseButtonPress( report_id,  buttons);
  }
  bool hid_mouseButtonRelease(uint8_t report_id){
    return usb_hid.mouseButtonRelease( report_id);
  }

  bool hid_send_reports(uint8_t modifier, uint8_t keycode[6], uint8_t buttons, int8_t x, int8_t y,
                   int8_t vertical, int8_t horizontal , uint16_t consumer_code ){
        hid_mouseReport(RID_MOUSE, buttons,  x,  y, vertical,  horizontal); 
        delay(10);
        hid_keyboardReport(RID_KEYBOARD, modifier, keycode);
        delay(10);
        hid_sendReport16(RID_CONSUMER_CONTROL, consumer_code);  
        return true;                
  }
