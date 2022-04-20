// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

// To learn more about BLE, refer to https://learn.adafruit.com/introduction-to-bluetooth-low-energy/introduction

#include "bluetooth.h"

BLEDis bledis;                                                                    // Device Information Service
extern KeyScanner keys;
extern PersistentState keyboardconfig;
extern DynamicState keyboardstate;
extern Battery batterymonitor;

 #if BLE_HID == 1
 uint16_t hid_conn_hdl;
 #endif 
 
extern BLEBas blebas; 


#if BLE_HID == 1                                                                    // THIS IS USUALLY ON THE MASTER/CENTRAL BOARD
  BLEHidAdafruit blehid;                                                            // HID Service
#endif

/**************************************************************************************************************************/
void bt_setup(uint8_t BLEProfile)
{
  //TODO review what can be extracted for single boards

  //TODO review what is needed for split boards and provide in separate module
ble_gap_conn_params_t _ppcp;
  _ppcp = ((ble_gap_conn_params_t) {
    .min_conn_interval = 6,
    .max_conn_interval = 12,
    .slave_latency     = 5,
    .conn_sup_timeout  = 2000 / 10 // in 10ms unit
  });
  
  //Bluefruit.configPrphBandwidth(BANDWIDTH_MAX); // OK for nrf52840
//  Bluefruit.configPrphBandwidth(BANDWIDTH_HIGH);
 // Bluefruit.configCentralBandwidth(BANDWIDTH_HIGH);
  Bluefruit.begin(PERIPHERAL_COUNT,CENTRAL_COUNT);                            // Defined in firmware_config.h

  
  Bluefruit.autoConnLed(false);                                               // make sure the BlueFruit connection LED is not toggled.
  Bluefruit.setTxPower(DEVICE_POWER);                                         // Defined in bluetooth_config.h
  Bluefruit.setName(DEVICE_NAME);                                             // Defined in keyboard_config.h
  Bluefruit.configUuid128Count(UUID128_COUNT);                                // Defined in bluetooth_config.h
  Bluefruit.configServiceChanged(true);                                       // helps troubleshooting...
  Bluefruit.setAppearance(BLE_APPEARANCE_HID_KEYBOARD);                       // How the device appears once connected
  Bluefruit.setRssiCallback(rssi_changed_callback);
  //********Bluefruit.setConnInterval(9, 12);                                 // 0.10.1: not needed for master...
  //https://devzone.nordicsemi.com/nordic/power/w/opp/2/online-power-profiler-for-ble
 // Bluefruit.Periph.setConnInterval(6, 12); // 7.5 - 15 ms
 // Bluefruit.Periph.setConnSlaveLatency(10); // TODO: add this when 0.22.0 gets released!  This will reduce power consumption significantly.
 
//sd_ble_gap_ppcp_get(&_ppcp);
//_ppcp.slave_latency = 30;
sd_ble_gap_ppcp_set(&_ppcp);

  Bluefruit.Periph.setConnectCallback(prph_connect_callback);
  Bluefruit.Periph.setDisconnectCallback(prph_disconnect_callback);  

  // Set MAC address based on active BLE profile
  if (BLEProfile > 0)
  {
    ble_gap_addr_t gap_addr;
    gap_addr = Bluefruit.getAddr();
    gap_addr.addr[0] += BLEProfile;
    Bluefruit.setAddr(&gap_addr);
  }

  // Configure and Start Device Information Service
  bledis.setManufacturer(MANUFACTURER_NAME);                                  // Defined in keyboard_config.h
  bledis.setModel(DEVICE_MODEL);                                              // Defined in keyboard_config.h
  bledis.begin();

  //TODO Split Battery Reporting Service into separate module.
  // Configure and Start Battery Service
  blebas.begin();
  blebas.write(100); // put the battery level at 100% - until it is updated by the battery monitoring loop.
  batterymonitor.readVBAT(); // Get a single ADC sample and throw it away
  

//TODO Get Peripheral into separate module

 
    /* Start BLE HID
   * Note: Apple requires BLE device must have min connection interval >= 20m
   * ( The smaller the connection interval the faster we could send data).
   * However for HID and MIDI device, Apple could accept min connection interval 
   * up to 11.25 ms. Therefore BLEHidAdafruit::begin() will try to set the min and max
   * connection interval to 11.25  ms and 15 ms respectively for best performance.
   */
  //TODO setup LED feedback for both USB and BLE
#if BLE_HID == 1
  blehid.begin();
  // Set callback for set LED from central
  blehid.setKeyboardLedCallback(set_keyboard_led);
#endif

  /* Set connection interval (min, max) to your perferred value.
   * Note: It is already set by BLEHidAdafruit::begin() to 11.25ms - 15ms
   * min = 9*1.25=11.25 ms, max = 12*1.25= 15 ms 
   */

}

ble_gap_addr_t bt_getMACAddr(void)
{
  ble_gap_addr_t gap_addr;
  gap_addr = Bluefruit.getAddr();
  return gap_addr;
}

/**************************************************************************************************************************/
//
/**************************************************************************************************************************/

//TODO setup advertising setup group of tasks
void bt_startAdv(void)
{  
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();

  #if BLE_HID == 1
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);  // Include BLE HID service
  #endif
  

  // There is no other service for Central 
  
  // There is probably not enough room for the dev name in the advertising packet. Putting it in the ScanResponse Packet
  //Bluefruit.ScanResponse.addName();
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
  
  Bluefruit.Advertising.setSlowCallback(advertizing_slow_callback);
  Bluefruit.Advertising.setStopCallback(advertizing_stop_callback);
}



 // typedef void (*stop_callback_t) (void);
  //typedef void (*slow_callback_t) (void);
  void advertizing_slow_callback(void)
  {
     // drop fast
     keyboardstate.statusble = keyboardstate.statusble & (~1); // bitwise AND NOT
     // add is_running
     keyboardstate.statusble = keyboardstate.statusble | (4); // bitwise OR
     // add slow
     keyboardstate.statusble = keyboardstate.statusble | (2); // bitwise OR
  }
  void advertizing_stop_callback(void)
  {
     // drop slow
     keyboardstate.statusble = keyboardstate.statusble & (~2); // bitwise AND NOT
     // drop is_running
     keyboardstate.statusble = keyboardstate.statusble & (~4); // bitwise AND NOT
  }

void rssi_changed_callback(uint16_t conn_hdl, int8_t rssi)
{
  if (conn_hdl == keyboardstate.conn_handle_prph)
  {
    keyboardstate.rssi_prph = rssi;
    keyboardstate.rssi_prph_updated = true;
  } else
  if (conn_hdl == keyboardstate.conn_handle_cent)
  {
    keyboardstate.rssi_cent = rssi;
    keyboardstate.rssi_cent_updated = true;
  } else
  if (conn_hdl == keyboardstate.conn_handle_cccd)
  {
    keyboardstate.rssi_cccd = rssi;
    keyboardstate.rssi_cccd_updated = true;
  }  
     
}



/**************************************************************************************************************************/
// This callback is called when the master connects to a slave
/**************************************************************************************************************************/
void prph_connect_callback(uint16_t conn_handle)
{
char peer_name[32] = { 0 };
BLEConnection* connection = Bluefruit.Connection(conn_handle);
connection->getPeerName(peer_name, sizeof(peer_name));
LOG_LV1("PRPH","Connected to %i %s",conn_handle,peer_name  );
connection->monitorRssi(6);
strcpy (keyboardstate.peer_name_prph,peer_name);

  if (strncmp(peer_name, keyboardconfig.BLEProfileName[keyboardconfig.BLEProfile], sizeof(peer_name)))
  {
    strncpy(keyboardconfig.BLEProfileName[keyboardconfig.BLEProfile], peer_name, sizeof(peer_name));
    keyboardstate.save2flash = true;
  }

#ifdef ARDUINO_NRF52_ADAFRUIT
  ble_gap_addr_t peerAddr;
  peerAddr = connection->getPeerAddr();
  if (memcmp(peerAddr.addr, keyboardconfig.BLEProfileAddr[keyboardconfig.BLEProfile], 6) != 0)
  {
    memcpy(keyboardconfig.BLEProfileAddr[keyboardconfig.BLEProfile], peerAddr.addr, 6);
    keyboardstate.save2flash = true;
  }
#endif


keyboardstate.conn_handle_prph = conn_handle;

keyboardstate.statusble = keyboardstate.statusble | (8); // bitwise OR

     // drop fast
     keyboardstate.statusble = keyboardstate.statusble & (~1); // bitwise AND NOT
     // drop slow
     keyboardstate.statusble = keyboardstate.statusble & (~2); // bitwise AND NOT
     // drop is_running
     keyboardstate.statusble = keyboardstate.statusble & (~4); // bitwise AND NOT

// if HID then save connection handle to HID_connection handle
#if BLE_HID == 1
hid_conn_hdl = conn_handle;
#endif
}
/**************************************************************************************************************************/
// This callback is called when the master disconnects from a slave
/**************************************************************************************************************************/
void prph_disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;
  LOG_LV1("PRPH","Disconnected"  );

//keyboardstate.statusble = keyboardstate.statusble & (~8); // bitwise AND NOT
keyboardstate.statusble = 0;
// if HID then save connection handle to HID_connection handle
#if BLE_HID == 1
hid_conn_hdl = 0;
#endif
}


/**************************************************************************************************************************/
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
/*  if ( led_bitmap )
  {
    ledOn( STATUS_KB_LED_PIN );
  }
  else
  {
    ledOff( STATUS_KB_LED_PIN );
  }*/

  keyboardstate.statuskb = led_bitmap;
  //KeyScanner::ledStatus = led_bitmap;
}
