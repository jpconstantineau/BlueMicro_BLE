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
#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

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

// Modifier keys, only take cares of Shift
// ATL, CTRL, CMD keys are left for user excersie.
uint8_t shiftPin = 11;

bool keyPressedPreviously = false;

void setup() 
{
  Serial.begin(115200);
  //while ( !Serial ) delay(10);   // for nrf52840 with native usb

  Serial.println("Bluefruit52 HID Keyscan Example");
  Serial.println("-------------------------------\n");

  Serial.println();
  Serial.println("Go to your phone's Bluetooth settings to pair your device");
  Serial.println("then open an application that accepts keyboard input");

  Serial.println();
  Serial.println("Wire configured Pin to GND to send key");
  Serial.println("Wire Shift Keky to GND if you want to send it in upper case");
  Serial.println();  

  Bluefruit.begin();
  Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values
  Bluefruit.setName("Bluefruit52");

  // Configure and Start Device Information Service
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather 52");
  bledis.begin();

  // set up pin as input
  for (uint8_t i=0; i<pincount; i++)
  {
    pinMode(pins[i], INPUT_PULLUP);
  }

  // set up modifier key
  pinMode(shiftPin, INPUT_PULLUP);

  /* Start BLE HID
   * Note: Apple requires BLE device must have min connection interval >= 20m
   * ( The smaller the connection interval the faster we could send data).
   * However for HID and MIDI device, Apple could accept min connection interval 
   * up to 11.25 ms. Therefore BLEHidAdafruit::begin() will try to set the min and max
   * connection interval to 11.25  ms and 15 ms respectively for best performance.
   */
  blehid.begin();

  // Set callback for set LED from central
  blehid.setKeyboardLedCallback(set_keyboard_led);

  /* Set connection interval (min, max) to your perferred value.
   * Note: It is already set by BLEHidAdafruit::begin() to 11.25ms - 15ms
   * min = 9*1.25=11.25 ms, max = 12*1.25= 15 ms 
   */
  /* Bluefruit.Periph.setConnInterval(9, 12); */

  // Set up and start advertising
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

void loop()
{
  /*-------------- Scan Pin Array and send report ---------------------*/
  bool anyKeyPressed = false;

  uint8_t modifier = 0;
  uint8_t count=0;
  uint8_t keycode[6] = { 0 };

  // scan modifier key (only SHIFT), user implement ATL, CTRL, CMD if needed
  if ( 0 == digitalRead(shiftPin) )
  {
    modifier |= KEYBOARD_MODIFIER_LEFTSHIFT;
  }

  // scan normal key and send report
  for(uint8_t i=0; i < pincount; i++)
  {
    if ( 0 == digitalRead(pins[i]) )
    {
      // if pin is active (low), add its hid code to key report
      keycode[count++] = hidcode[i];

      // 6 is max keycode per report
      if ( count == 6)
      {
        blehid.keyboardReport(modifier, keycode);

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
    blehid.keyboardReport(modifier, keycode);
  }

  // Send All-zero report to indicate there is no keys pressed
  // Most of the time, it is, though we don't need to send zero report
  // every loop(), only a key is pressed in previous loop() 
  if ( !anyKeyPressed && keyPressedPreviously )
  {
    keyPressedPreviously = false;
    blehid.keyRelease();
  }  
  
  // Poll interval
  delay(10);
}

/**
 * Callback invoked when received Set LED from central.
 * Must be set previously with setKeyboardLedCallback()
 *
 * The LED bit map is as follows: (also defined by KEYBOARD_LED_* )
 *    Kana (4) | Compose (3) | ScrollLock (2) | CapsLock (1) | Numlock (0)
 */
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
