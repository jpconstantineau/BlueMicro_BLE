#include "hid_common.h"
const int pin = 7; // UserSw
bool activeState = false;


// the setup function runs once when you press reset or power the board
void setup()
{

  // Set up button, pullup opposite to active state
  pinMode(pin, activeState ? INPUT_PULLDOWN : INPUT_PULLUP);
  
  hid_start();// THIS MUST BE CALLED FIRST!
  Serial.begin(115200);
  while ( !Serial ) delay(10); // for nrf52840 with native usb
  Serial.println("Adafruit USB/BLE HID Composite example");
startAdv();
  // wait until device mounted
  //while( !USBDevice.mounted() ) delay(1);
}

//The function that runs over and over again...
void loop()
{
  // poll gpio once each 10 ms
  bool pendingrelease = false;
  delay(10);
  Serial.println("In Loop");

  // Whether button is pressed
  bool btn_pressed = (digitalRead(pin) == activeState);

 /* // Remote wakeup
  if ( USBDevice.suspended() && btn_pressed )
  {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    USBDevice.remoteWakeup();
  }*/

  
  if ( hid_ready() )
  {
    if ( btn_pressed )
    {
      int8_t const delta = 5;
      uint8_t keycode[6] = { 0 };
      keycode[0] = HID_KEY_A;
      hid_send_reports(0,  keycode, 0, delta, delta, 0,0, HID_USAGE_CONSUMER_VOLUME_DECREMENT );
      pendingrelease = true;
    }else
    {
      // send empty key report if previously has key pressed  
     // if (pendingrelease)
     {
        Serial.println("not btn_pressed");
        uint8_t keycode[6] = { 0 }; 
        hid_send_reports(0,  keycode, 0, 0, 0, 0, 0 , 0 );
        pendingrelease = false;
      }
    }
  }

  
}
