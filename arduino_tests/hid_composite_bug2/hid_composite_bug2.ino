/*********************************************************************
 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 Copyright (c) 2019 Ha Thach for Adafruit Industries
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

#include "Adafruit_TinyUSB.h"
#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

bool hasKeyPressed = false;

#if defined ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS
  const int pin = 4; // Left Button
  bool activeState = true;
#elif defined ARDUINO_NRF52840_FEATHER
  const int pin = 7; // UserSw
  bool activeState = false;
#else
  const int pin = 12;
  bool activeState = false;
#endif


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

// USB HID object
Adafruit_USBD_HID usb_hid;

// the setup function runs once when you press reset or power the board
void setup()
{
// SETUP BLE BEFORE USB
  Bluefruit.begin();
  Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values

  // Configure and Start Device Information Service
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather 52");
  bledis.begin();
  blehid.begin();
  blehid.setKeyboardLedCallback(set_keyboard_led);
  startAdv();


// SETUP USB
  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  //usb_hid.setStringDescriptor("TinyUSB HID Composite");

  usb_hid.begin();

  // Set up button, pullup opposite to active state
  pinMode(pin, activeState ? INPUT_PULLDOWN : INPUT_PULLUP);


  // wait until device mounted
  while( !USBDevice.mounted() ) delay(1);
}

// Standard advert code from examples
void startAdv(void)
{  
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  // Include BLE HID service
  Bluefruit.Advertising.addService(blehid);

  // There is enough room for the dev name in the advertising packet
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}



void loop()
{
  // poll gpio once each 10 ms
  delay(10);

  // BLE first!
  // do nothing as setup is where the bug is...

  // USB second

  // Whether button is pressed
  bool btn_pressed = (digitalRead(pin) == activeState);

  // Remote wakeup
  if ( USBDevice.suspended() && btn_pressed )
  {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    USBDevice.remoteWakeup();
  }

  /*------------- Mouse -------------*/
  if ( usb_hid.ready() && btn_pressed )
  {
    int8_t const delta = 5;
    usb_hid.mouseMove(RID_MOUSE, delta, delta); // right + down

    // delay a bit before attempt to send keyboard report
    delay(10);
  }

  /*------------- Keyboard -------------*/
  if ( usb_hid.ready() )
  {
    // use to send key release report
    static bool has_key = false;

    if ( btn_pressed )
    {
      uint8_t keycode[6] = { 0 };
      keycode[0] = HID_KEY_A;

      usb_hid.keyboardReport(RID_KEYBOARD, 0, keycode);

      has_key = true;
    }else
    {
      // send empty key report if previously has key pressed
      if (has_key) usb_hid.keyboardRelease(RID_KEYBOARD);
      has_key = false;
    }

    // delay a bit before attempt to send consumer report
    delay(10);
  }

  /*------------- Consumer Control -------------*/
  if ( usb_hid.ready() )
  {
    // Consumer Control is used to control Media playback, Volume, Brightness etc ...
    // Consumer report is 2-byte containing the control code of the key
    // For list of control check out https://github.com/hathach/tinyusb/blob/master/src/class/hid/hid.h#L544

    // use to send consumer release report
    static bool has_consumer_key = false;

    if ( btn_pressed )
    {
      // send volume down (0x00EA)
      usb_hid.sendReport16(RID_CONSUMER_CONTROL, HID_USAGE_CONSUMER_VOLUME_DECREMENT);
      has_consumer_key = true;
    }else
    {
      // release the consume key by sending zero (0x0000)
      if (has_consumer_key) usb_hid.sendReport16(RID_CONSUMER_CONTROL, 0);
      has_consumer_key = false;
    }
  }
}


// Standard LED cb code from examples
void set_keyboard_led(uint16_t conn_handle, uint8_t led_bitmap)
{
  (void) conn_handle;
  
  // light up Red Led if any bits is set
  if ( led_bitmap )
  {
    ledOn( LED_RED );
  }
  else
  {
    ledOff( LED_RED );
  }
}
