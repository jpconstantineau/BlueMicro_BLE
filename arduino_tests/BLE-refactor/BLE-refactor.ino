/*********************************************************************
 This is an example for our nRF52 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

/* This sketch demonstate how to use BLE HID to scan an array of pin
 * and send its keycode. It is essentially an implementation of hid keyboard,
 * useful reference if you want to make an BLE keyboard.
 */
#include "hid_common.h"

const int pin = 7; // UserSw
bool activeState = false;

void setup() 
{
  hid_start();// THIS MUST BE CALLED FIRST!
  Serial.begin(115200);
  Serial.println("BLE HID Composite example");
 // Set up button, pullup opposite to active state
  pinMode(pin, activeState ? INPUT_PULLDOWN : INPUT_PULLUP);
 
  startAdv(); // Set up and start BLE advertising
}

void loop()
{
    // Poll interval
   delay(10);
    bool pendingrelease = false;
  /*-------------- Scan Pin Array and send report ---------------------*/
  // Whether button is pressed
  bool btn_pressed = (digitalRead(pin) == activeState);
  if ( hid_ready() )
  {
  if ( btn_pressed )
    {
      int8_t const delta = 5;
      uint8_t modifier = 0;
      uint8_t keycode[6] = { 0 };
      keycode[0] = HID_KEY_A;
      hid_send_reports(modifier,  keycode, 0, delta, delta, 0,0, HID_USAGE_CONSUMER_VOLUME_DECREMENT );
      pendingrelease = true;
    }else
    {
      // send empty key report if previously has key pressed  
     // if (pendingrelease)
     {
        uint8_t keycode[6] = { 0 }; 
        hid_send_reports(0,  keycode, 0, 0, 0, 0, 0 , 0 );
        pendingrelease = false;
      }
    }
  }
}
