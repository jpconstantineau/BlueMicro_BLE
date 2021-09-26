#include <bluefruit.h>

void hid_start(void);
void startAdv(void);

bool hid_ready(void);

 // bool hid_sendReport(uint8_t report_id, void const *report, uint8_t len);

  //------------- Keyboard API -------------//
  bool hid_keyboardReport( uint8_t modifier, uint8_t keycode[6]);
  bool hid_keyboardPress(char ch);
  bool hid_keyboardRelease(void);

  //------------- Mouse API -------------//
  bool hid_mouseReport( uint8_t buttons, int8_t x, int8_t y,
                       int8_t vertical, int8_t horizontal);
  bool hid_mouseMove(int8_t x, int8_t y);
  bool hid_mouseScroll(int8_t scroll, int8_t pan);
  bool hid_mouseButtonPress(uint8_t buttons);
  bool hid_mouseButtonRelease(void);

  //------------- Consumer API -------------//

  bool hid_consumerKeyPress(uint16_t usage_code);
  bool hid_consumerKeyRelease(void);

//------------- Common HID API -------------//
  bool hid_send_reports(uint8_t modifier, uint8_t keycode[6], uint8_t buttons, int8_t x, int8_t y,
                         int8_t vertical, int8_t horizontal , uint16_t consumer_code );

 //------------- CALLBACK LED API -------------//
  void set_keyboard_led(uint16_t conn_handle, uint8_t led_bitmap);
