/*********************************************************************
 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 Copyright (c) 2019 Ha Thach for Adafruit Industries
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/
#ifdef NRF52840_XXAA  // only the 840 has USB available.
  #include "Adafruit_TinyUSB.h"
#endif
#include "hid_queues.h"
#include "std_fix.h"
#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;


#ifdef NRF52840_XXAA  // only the 840 has USB available.
  // USB HID object. For ESP32 these values cannot be changed after this declaration
  // desc report, desc len, protocol, interval, use out endpoint
  Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_NONE, 2, false);

  HID_Queues hid (&usb_hid,&blehid);
#else
  HID_Queues hid (&blehid);
#endif

const int pin = 7; // UserSw
bool activeState = false;

void setupBLE()
{
  Bluefruit.begin();
  Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather 52");
  bledis.begin();
  blehid.begin();
  blehid.setKeyboardLedCallback(set_keyboard_led);
  startAdv();
}

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
  
  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   * 
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html   
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}

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

// the setup function runs once when you press reset or power the board
void setup()
{
  // Notes: following commented-out functions has no affect on ESP32
  // usb_hid.setPollInterval(2);
  // usb_hid.setReportDescriptor();
  // usb_hid.setStringDescriptor("TinyUSB HID Composite");

#ifdef NRF52840_XXAA  // only the 840 has USB available.
  usb_hid.begin();
#endif
  setupBLE();
  // Set up button, pullup opposite to active state
  pinMode(pin, activeState ? INPUT_PULLDOWN : INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("Adafruit TinyUSB HID Composite example");
}

void loop()
{
  // poll gpio once each 10 ms
  delay(10);

  // Whether button is pressed
  bool btn_pressed = (digitalRead(pin) == activeState);

  /*------------- Mouse -------------*/
  if (btn_pressed )
  {
    int8_t const delta = 5;
    hid.mouseMove(delta, delta); // right + down
  }

  /*------------- Keyboard -------------*/
    // use to send key release report
    static bool has_key = false;

    if ( btn_pressed )
    {
      uint8_t keycode[6] = { 0 };
      keycode[0] = HID_KEY_A;

      hid.keyboardReport(0, keycode);

      has_key = true;
    }else
    {
      // send empty key report if previously has key pressed
      if (has_key) hid.keyboardRelease();
      has_key = false;
    }

    // Consumer Control is used to control Media playback, Volume, Brightness etc ...
    // Consumer report is 2-byte containing the control code of the key
    // For list of control check out https://github.com/hathach/tinyusb/blob/master/src/class/hid/hid.h

    // use to send consumer release report
    static bool has_consumer_key = false;

    if ( btn_pressed )
    {
      // send volume down (0x00EA)
      hid.consumerKeyPress(HID_USAGE_CONSUMER_VOLUME_DECREMENT);
      has_consumer_key = true;
    }else
    {
      // release the consume key by sending zero (0x0000)
      if (has_consumer_key) hid.consumerKeyRelease();
      has_consumer_key = false;
    }
    
  hid.processQueues(CONNECTION_MODE_AUTO);
}
