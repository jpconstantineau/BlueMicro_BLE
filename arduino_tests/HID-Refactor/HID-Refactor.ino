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
#include "keypad.h"
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


bool activeState = false;
std::vector<uint8_t> pins{7, 5, 6};

Keys thekeys;

std::vector<KeyEventMap> keymap;

void setupBLE()
{
  Bluefruit.begin();
  Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather 52");
  bledis.begin();
  blehid.begin();
  blehid.setKeyboardLedCallback(set_keyboard_led);
  
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



void kpa()
{
          uint8_t keycode[6] = { 0 };
        keycode[0] = HID_KEY_A;
  
        hid.keyboardReport(0, keycode);
}

void kra()
{
  hid.keyboardRelease();  
}

void kpb()
{
         int8_t const delta = 5;
        hid.mouseMove(delta, delta); // right + down
}

void krb()
{
  ;
}



void kpc()
{
  hid.consumerKeyPress(HID_USAGE_CONSUMER_VOLUME_DECREMENT);
}

void krc()
{
  hid.consumerKeyRelease();;
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
  

  Serial.begin(115200);
  Serial.println("Adafruit TinyUSB HID Composite example");
  thekeys.setupPins(pins,activeState);
  KeyEventMap km;
  km.key_number = 0;
  km.pressed_cb = kpa;
  km.released_cb = kra;
  keymap.push_back(km);
    km.key_number = 1;
  km.pressed_cb = kpb;
  km.released_cb = krb;
     km.key_number = 2;
  km.pressed_cb = kpc;
  km.released_cb = krc;
  keymap.push_back(km);
  thekeys.setupKeymap(keymap);

}

void loop()
{
  // poll gpio once each 10 ms
  delay(10);
  thekeys.scan(millis());
  thekeys.process();

/*  while (thekeys.anyEvent())
  {
    KeyEvent data = thekeys.getEvent();
    if (data.key_number == 0)
    {
      if (data.pressed)
      {
          kpa();
      }
      else
      {
        kra();
      }
    }
  
    if (data.key_number == 1)
    {
      if (data.pressed)
      {
        kpb();
      }
      else
      {
        krb();
      }
    }
  
    if (data.key_number == 2)
    {
      if (data.pressed)
      {
        kpc();
      }
      else
      {
        krc();
      }
    }
  }*/
    
  hid.processQueues(CONNECTION_MODE_AUTO);
}
