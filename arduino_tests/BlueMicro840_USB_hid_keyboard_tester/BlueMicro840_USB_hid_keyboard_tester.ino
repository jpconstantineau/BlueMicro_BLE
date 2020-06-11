// make sure you get the Adafruit TinyUSB Library.
// to install the Adafruit TinyUSB Library, to to Tools -> Manage Libraries... and search for TinyUSB

// select the following board: "Nordic nRF52840DK (PCA10056)"
// select the programmer "Bootloader DFU for Bluefruit nrf52"
// double-reset the BlueMicro840
// Select the serial port shown in Tools -> Port
// compile and upload
// once flashed, disconnect and reconnect the USB cable.
// the board should now show up as a USB keyboard
// go to the following website to test it
// https://config.qmk.fm/#/test
// using a wire, ground each GPIO, one pin at a time and see if a key is "pressed"



#include "Adafruit_TinyUSB.h"

// HID report descriptor using TinyUSB's template
// Single Report (no ID) descriptor
uint8_t const desc_hid_report[] =
{
  TUD_HID_REPORT_DESC_KEYBOARD(),
};

Adafruit_USBD_HID usb_hid;
        #define D3      6  
        #define D2      8   
        #define D1      15  
        #define D0      17  
        #define D4      20
        #define C6      13
        #define D7      24
        #define E6      9
        #define B4      10
        #define B5      38 //1.06 = 32+6

        #define F4      30
        #define F5      26  
        #define F6      29
        #define F7      2
        #define B1      45 //1.13  = 32+13
        #define B3      3
        #define B2      28
        #define B6      43 //1.11 = 32+11
        #define BLUE_LED 32+10
        #define RED_LED 32+4
        #define LED_RED 32+4

// Array of pins and its keycode
// For keycode definition see BLEHidGeneric.h
uint8_t pins[]    = { D3, D2, D1, D0, D4, C6, D7, E6, B4, B5, F4, F5, F6, F7, B1, B3, B2, B6   };
uint8_t hidcode[] = { HID_KEY_0, HID_KEY_1, HID_KEY_2, HID_KEY_3, HID_KEY_4, HID_KEY_5, HID_KEY_6, HID_KEY_7, HID_KEY_8, HID_KEY_9, HID_KEY_A, HID_KEY_B, HID_KEY_C, HID_KEY_D, HID_KEY_E, HID_KEY_F, HID_KEY_G, HID_KEY_H};

uint8_t pincount = sizeof(pins)/sizeof(pins[0]);

// the setup function runs once when you press reset or power the board
void setup()
{
  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.setReportCallback(NULL, hid_report_callback);

  usb_hid.begin();

  // led pin
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);

  // Set up pin as input
  for (uint8_t i=0; i<pincount; i++)
  {
    pinMode(pins[i], INPUT_PULLUP);
  }

  // wait until device mounted
  while( !USBDevice.mounted() ) delay(1);
}


void loop()
{
  // poll gpio once each 2 ms
  delay(2);

//  // Remote wakeup
//  if ( USBDevice.suspended() && btn )
//  {
//    // Wake up host if we are in suspend mode
//    // and REMOTE_WAKEUP feature is enabled by host
//    USBDevice.remoteWakeup();
//  }

  if ( !usb_hid.ready() ) return;

  static bool keyPressedPreviously = false;
  bool anyKeyPressed = false;

  uint8_t count=0;
  uint8_t keycode[6] = { 0 };

  // scan normal key and send report
  for(uint8_t i=0; i < pincount; i++)
  {
    if ( 0 == digitalRead(pins[i]) )
    {
      // if pin is active (low), add its hid code to key report
      keycode[count++] = hidcode[i];

      // 6 is max keycode per report
      if (count == 6)
      {
        usb_hid.keyboardReport(0, 0, keycode);
        delay(2); // delay for report to send out

        // reset report
        count = 0;
        memset(keycode, 0, 6);
      }

      // used later
      anyKeyPressed = true;
      keyPressedPreviously = true;
    }
  }

  // Send any remaining keys (not accumulated up to 6)
  if ( count )
  {
    usb_hid.keyboardReport(0, 0, keycode);
  }

  // Send All-zero report to indicate there is no keys pressed
  // Most of the time, it is, though we don't need to send zero report
  // every loop(), only a key is pressed in previous loop()
  if ( !anyKeyPressed && keyPressedPreviously )
  {
    keyPressedPreviously = false;
    usb_hid.keyboardRelease(0);
  }
}

// Output report callback for LED indicator such as Caplocks
void hid_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  // LED indicator is output report with only 1 byte length
  if ( report_type != HID_REPORT_TYPE_OUTPUT ) return;

  // The LED bit map is as follows: (also defined by KEYBOARD_LED_* )
  // Kana (4) | Compose (3) | ScrollLock (2) | CapsLock (1) | Numlock (0)
  uint8_t ledIndicator = buffer[0];

  // turn on LED if caplock is set
  digitalWrite(RED_LED, ledIndicator & KEYBOARD_LED_CAPSLOCK);
}
