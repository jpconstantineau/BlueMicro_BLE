#include <arduino.h>
#include "hid_common.h"

BLEDis bledis;
BLEHidAdafruit ble_hid;


 /*bool hid_sendReport(uint8_t report_id, void const *report, uint8_t len){
    return ble_hid.sendReport( report_id,  report, len);
  }*/

  //------------- Keyboard API -------------//
  bool hid_keyboardReport(uint8_t modifier, uint8_t keycode[6]){
    return ble_hid.keyboardReport( modifier,  keycode);
  }
  bool hid_keyboardPress(char ch){
    return ble_hid.keyPress(ch);
  }
  bool hid_keyboardRelease(){
    return ble_hid.keyRelease();
  }

  //------------- Mouse API -------------//
  bool hid_mouseReport( uint8_t buttons, int8_t x, int8_t y,
                   int8_t vertical, int8_t horizontal){
    return ble_hid.mouseReport(buttons,  x,  y, vertical, horizontal);
  }
  bool hid_mouseMove( int8_t x, int8_t y){
    return ble_hid.mouseMove(  x,  y);
  }
  bool hid_mouseScroll( int8_t scroll, int8_t pan){
    return ble_hid.mouseScroll(  scroll,  pan);
  }
  bool hid_mouseButtonPress( uint8_t buttons){
    return ble_hid.mouseButtonPress(buttons);
  }
  bool hid_mouseButtonRelease(){
    return ble_hid.mouseButtonRelease();
  }


  bool hid_consumerKeyPress(uint16_t usage_code)
  {
    return ble_hid.consumerKeyPress(usage_code);
  }
  
  bool hid_consumerKeyRelease(void)
  {
    return ble_hid.consumerKeyRelease();
  }

  bool hid_send_reports(uint8_t modifier, uint8_t keycode[6], uint8_t buttons, int8_t x, int8_t y,
                   int8_t vertical, int8_t horizontal , uint16_t consumer_code ){
        hid_mouseReport(buttons,  x,  y, vertical,  horizontal); 
        delay(10);
        hid_keyboardReport(modifier, keycode);
        delay(10);
        hid_consumerKeyPress(consumer_code);  
        return true;                
  }



void hid_start(void)
{
  Bluefruit.begin();
  Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values

  // Configure and Start Device Information Service
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather 52");
  bledis.begin();
  /* Start BLE HID
   * Note: Apple requires BLE device must have min connection interval >= 20m
   * ( The smaller the connection interval the faster we could send data).
   * However for HID and MIDI device, Apple could accept min connection interval 
   * up to 11.25 ms. Therefore ble_hidAdafruit::begin() will try to set the min and max
   * connection interval to 11.25  ms and 15 ms respectively for best performance.
   */
  ble_hid.begin();

  // Set callback for set LED from central
  ble_hid.setKeyboardLedCallback(set_keyboard_led);

  /* Set connection interval (min, max) to your perferred value.
   * Note: It is already set by ble_hidAdafruit::begin() to 11.25ms - 15ms
   * min = 9*1.25=11.25 ms, max = 12*1.25= 15 ms 
   */
  /* Bluefruit.Periph.setConnInterval(9, 12); */
  }

void startAdv(void)
{  
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  // Include BLE HID service
  Bluefruit.Advertising.addService(ble_hid);

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



bool hid_ready(void)
{
  return (Bluefruit.connected()>0);
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
