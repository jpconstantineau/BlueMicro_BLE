/*********************************************************************
 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/
#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

bool hasKeyPressed = false;
int stringcounter = 0;

void setup() 
{
 

  Bluefruit.begin();
  Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values
  Bluefruit.setName("BlueMicroHID");

  // Configure and Start Device Information Service
  bledis.setManufacturer("jpconstantineau.com");
  bledis.setModel("BlueMicroNRF52832");
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
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}

void loop() 
{
  if ( millis() > 10000)
  {
    switch (stringcounter )
    {
      case 0: blehid.keySequence("BlueMicro HID Keyboard Tester\n"); break;
      case 1: blehid.keySequence("--------------------------------\n");break;
      case 2: blehid.keySequence("testing string 2\n");break;
      case 3: blehid.keySequence("testing string 3\n");break;
      case 4: blehid.keySequence("testing string 4\n");break;
      case 5: blehid.keySequence("testing string 5\n");break;
      case 6: blehid.keySequence("testing string 6\n");break;
      case 7: blehid.keySequence("testing string 7\n");break;
      case 8: blehid.keySequence("testing string 8\n");break;
      case 9: blehid.keySequence("testing string 9\n");break;
      case 10: blehid.keySequence("testing string 10\n");break;
      case 11: blehid.keySequence("testing string 11\n");break;
      case 12: blehid.keySequence("testing string 12\n");break;
      case 13: blehid.keySequence("testing string 13\n");break;
      case 14: blehid.keySequence("testing string 14\n");break;
      case 15: blehid.keySequence("testing string 15\n");break;
      case 16: blehid.keySequence("--------------------------------\n\n"); stringcounter = -1; break;
      default: 
      break;
    }

    delay(5);
    stringcounter++;
  }
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
