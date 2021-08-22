#include <arduino.h>
#include "hid_common.h"

// USB HID object


bool  begin() {

//  LOG_LV1(" begin","end begin()");
    usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
usb_hid.begin();
}

bool  ready()
{
  return usb_hid.ready();
}

  // Report helpers
  bool  sendReport8(uint8_t report_id, uint8_t num)
  {
    return usb_hid.sendReport8(report_id,num);
}

  bool  sendReport16(uint8_t report_id, uint16_t num)
  {
    return usb_hid.sendReport16( report_id,  num);
}

  bool  sendReport32(uint8_t report_id, uint32_t num)
  {
    return usb_hid.sendReport32( report_id,  num);
}

  //------------- Keyboard API -------------//
  bool  keyboardReport(uint8_t report_id, uint8_t modifier, uint8_t keycode[6])
  {
    return usb_hid.keyboardReport( report_id,  modifier,  keycode);
}

  bool  keyboardPress(uint8_t report_id, char ch)
  {
    return usb_hid.keyboardPress( report_id,  ch);
}

  bool  keyboardRelease(uint8_t report_id)
  {
    return usb_hid.keyboardRelease( report_id);
}

  //------------- Mouse API -------------//
  bool  mouseReport(uint8_t report_id, uint8_t buttons, int8_t x, int8_t y,
                   int8_t vertical, int8_t horizontal)
  {
    return usb_hid.mouseReport( report_id,  buttons,  x,  y, vertical,  horizontal);
}

  bool  mouseMove(uint8_t report_id, int8_t x, int8_t y)
  {
    return usb_hid.mouseMove( report_id,  x,  y);
}

  bool  mouseScroll(uint8_t report_id, int8_t scroll, int8_t pan)
  {
    return usb_hid.mouseScroll( report_id, scroll,  pan);
}

  bool  mouseButtonPress(uint8_t report_id, uint8_t buttons)
  {
    return usb_hid.mouseButtonPress( report_id,  buttons);
}

  bool  mouseButtonRelease(uint8_t report_id)
  {
    return usb_hid.mouseButtonRelease( report_id);
}
