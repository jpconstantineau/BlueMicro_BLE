/*
Copyright 2018-2020 <Pierre Constantineau>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
// To learn more about BLE, refer to https://learn.adafruit.com/introduction-to-bluetooth-low-energy/introduction

#include "bluetooth.h"

BLEDis bledis;                                                                    // Device Information Service
extern KeyScanner keys;
extern DynamicState keyboardstate;
extern Battery batterymonitor;

 #if BLE_HID == 1
 uint16_t hid_conn_hdl;
 #endif 
 
extern BLEBas blebas; 
StatePayload  statedata;

#if BLE_PERIPHERAL == 1                                                             // PERIPHERAL IS THE SLAVE BOARD
  Payload Linkdata;
  BLEService KBLinkService = BLEService(UUID128_SVC_KEYBOARD_LINK);                 // Keyboard Link Service - Slave/Server Side                 
  BLECharacteristic KBLinkChar_Layers        = BLECharacteristic(UUID128_CHR_KEYBOARD_LAYERS);
  BLECharacteristic KBLinkChar_Layer_Request = BLECharacteristic(UUID128_CHR_KEYBOARD_LAYER_REQUEST);      
  BLECharacteristic KBLinkChar_Buffer        = BLECharacteristic(UUID128_CHR_KEYBOARD_BUFFER); 
#endif

#if BLE_HID == 1                                                                    // THIS IS USUALLY ON THE MASTER/CENTRAL BOARD
  BLEHidAdafruit blehid;                                                            // HID Service
#endif

// ToDo: provision for multiple master/slave links
#if BLE_CENTRAL == 1                                                                // CENTRAL IS THE MASTER BOARD
  BLEClientService KBLinkClientService = BLEClientService(UUID128_SVC_KEYBOARD_LINK);     // Keyboard Link Service Client - Master/Client Side  
  BLEClientCharacteristic KBLinkClientChar_Layers        = BLEClientCharacteristic(UUID128_CHR_KEYBOARD_LAYERS);
  BLEClientCharacteristic KBLinkClientChar_Layer_Request = BLEClientCharacteristic(UUID128_CHR_KEYBOARD_LAYER_REQUEST);
  BLEClientCharacteristic KBLinkClientChar_Buffer        = BLEClientCharacteristic(UUID128_CHR_KEYBOARD_BUFFER); 
#endif
/**************************************************************************************************************************/
void setupBluetooth(void)
{
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

  
  Bluefruit.autoConnLed(BLE_LED_ACTIVE);                                      // make sure the BlueFruit connection LED is not toggled.
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

  // Configure and Start Device Information Service
  bledis.setManufacturer(MANUFACTURER_NAME);                                  // Defined in keyboard_config.h
  bledis.setModel(DEVICE_MODEL);                                              // Defined in keyboard_config.h
  bledis.begin();

 
  // Configure and Start Battery Service
  blebas.begin();
  blebas.write(100); // put the battery level at 100% - until it is updated by the battery monitoring loop.
  Battery::readVBAT(); // Get a single ADC sample and throw it away
  
  statedata.command =0;
  statedata.layer =0;
  statedata.timesync=0;

#if BLE_PERIPHERAL == 1      // PERIPHERAL IS THE SLAVE BOARD

  Linkdata.report[0] =0;  // initialize the slave to master link data...
  Linkdata.report[1] =0;
  Linkdata.report[2] =0;
  Linkdata.report[3] =0;
  Linkdata.report[4] =0;
  Linkdata.report[5] =0;
  Linkdata.report[6] =0;
  Linkdata.report[7] =0;
  Linkdata.command = 0;
  Linkdata.timesync = 0;
  Linkdata.specialkeycode = 0;
  Linkdata.batterylevel = 0;

  // Configure Keyboard Link Service
  KBLinkService.begin();
  
  KBLinkChar_Layers.setProperties(CHR_PROPS_NOTIFY+ CHR_PROPS_READ);
  KBLinkChar_Layers.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
  KBLinkChar_Layers.setFixedLen(sizeof(statedata));
  KBLinkChar_Layers.setUserDescriptor("Keyboard Layer");
  KBLinkChar_Layers.setCccdWriteCallback(cccd_callback,true);     /// 0.10.1 - second parameter is the "use adafruit calback" to call adafruit's method before ours.  Not sure what it does.
  KBLinkChar_Layers.begin();
  KBLinkChar_Layers.write(&statedata, sizeof(statedata));  // initialize with layer 0

  KBLinkChar_Layer_Request.setProperties(CHR_PROPS_WRITE + CHR_PROPS_WRITE_WO_RESP);
  KBLinkChar_Layer_Request.setPermission(SECMODE_NO_ACCESS, SECMODE_OPEN );
  KBLinkChar_Layer_Request.setFixedLen(sizeof(statedata));
  KBLinkChar_Layer_Request.setUserDescriptor("Keyboard Layer Request");
  KBLinkChar_Layer_Request.setWriteCallback(layer_request_callback);
  KBLinkChar_Layer_Request.begin();
  KBLinkChar_Layer_Request.write(&statedata, sizeof(statedata));  // initialize with empty buffer
    
  KBLinkChar_Buffer.setProperties(CHR_PROPS_NOTIFY+ CHR_PROPS_READ);
  KBLinkChar_Buffer.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
  KBLinkChar_Buffer.setFixedLen(sizeof(Linkdata));
  KBLinkChar_Buffer.setUserDescriptor("Keyboard Master/Slave Payload");
  KBLinkChar_Buffer.setCccdWriteCallback(cccd_callback,true);     /// 0.10.1 - second parameter is the "use adafruit calback" to call adafruit's method before ours.  Not sure what it does.
  KBLinkChar_Buffer.begin();
  KBLinkChar_Buffer.write(&Linkdata, sizeof(Linkdata));  // initialize with empty buffer

 #endif
 
    /* Start BLE HID
   * Note: Apple requires BLE device must have min connection interval >= 20m
   * ( The smaller the connection interval the faster we could send data).
   * However for HID and MIDI device, Apple could accept min connection interval 
   * up to 11.25 ms. Therefore BLEHidAdafruit::begin() will try to set the min and max
   * connection interval to 11.25  ms and 15 ms respectively for best performance.
   */
   
#if BLE_HID == 1
  blehid.begin();
  // Set callback for set LED from central
  blehid.setKeyboardLedCallback(set_keyboard_led);
#endif

  /* Set connection interval (min, max) to your perferred value.
   * Note: It is already set by BLEHidAdafruit::begin() to 11.25ms - 15ms
   * min = 9*1.25=11.25 ms, max = 12*1.25= 15 ms 
   */

 #if BLE_CENTRAL == 1                                   // CENTRAL IS THE MASTER BOARD

  KBLinkClientService.begin();
  KBLinkClientChar_Layers.begin();
  KBLinkClientChar_Layers.setNotifyCallback(notify_callback);
  KBLinkClientChar_Buffer.begin();
  KBLinkClientChar_Buffer.setNotifyCallback(notify_callback);
  KBLinkClientChar_Layer_Request.begin(); 
  Bluefruit.Periph.setConnectCallback(prph_connect_callback);
  Bluefruit.Periph.setDisconnectCallback(prph_disconnect_callback);  
  Bluefruit.Scanner.setRxCallback(scan_callback);
  Bluefruit.Scanner.restartOnDisconnect(true);
  Bluefruit.Scanner.filterRssi(FILTER_RSSI_BELOW_STRENGTH);                                              // limits very far away devices - reduces load
  Bluefruit.Scanner.filterUuid(BLEUART_UUID_SERVICE, UUID128_SVC_KEYBOARD_LINK);  // looks specifically for these 2 services (A OR B) - reduces load
  Bluefruit.Scanner.setInterval(160, 80);                                         // in unit of 0.625 ms  Interval = 100ms, Window = 50 ms
  Bluefruit.Scanner.useActiveScan(false);                                         // If true, will fetch scan response data
  Bluefruit.Scanner.start(0);                                                     // 0 = Don't stop scanning after 0 seconds
  Bluefruit.Central.setConnectCallback(cent_connect_callback);
  Bluefruit.Central.setDisconnectCallback(cent_disconnect_callback);

#endif

}


/**************************************************************************************************************************/
//
/**************************************************************************************************************************/
void startAdv(void)
{  
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();

  #if BLE_HID == 1
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);  // Include BLE HID service
  #endif
  
  #if BLE_PERIPHERAL ==1
   Bluefruit.Advertising.addUuid(UUID128_SVC_KEYBOARD_LINK);
   Bluefruit.Advertising.addUuid(UUID128_CHR_KEYBOARD_LAYERS);
   Bluefruit.Advertising.addUuid(UUID128_CHR_KEYBOARD_LAYER_REQUEST);
   Bluefruit.Advertising.addUuid(UUID128_CHR_KEYBOARD_BUFFER); 
   Bluefruit.Advertising.addService(KBLinkService);  /// Advertizing Keyboard Link Service
  #endif

  // There is no other service for Central 
  // ToDo: Consider Configuration Service... Save config to board, reset to default values, go to DFU, etc...
  
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
}

void rssi_changed_callback(uint16_t conn_hdl, int8_t rssi)
{
  if (conn_hdl == keyboardstate.conn_handle_prph)
  {
    keyboardstate.rssi_prph = rssi;
  } else
  if (conn_hdl == keyboardstate.conn_handle_cent)
  {
    keyboardstate.rssi_cent = rssi;
  } else
  if (conn_hdl == keyboardstate.conn_handle_cccd)
  {
    keyboardstate.rssi_cccd = rssi;
  }  
     
}

/**************************************************************************************************************************/
// This callback is called when a Notification update even occurs (This occurs on the client)
/**************************************************************************************************************************/
#if BLE_CENTRAL == 1    // CENTRAL IS THE MASTER BOARD
void notify_callback(BLEClientCharacteristic* chr, uint8_t* data, uint16_t len)
{

  Payload remotedata; 

  LOG_LV1("CB NOT","notify_callback: want %i got %i [0] %i [1] %i [2] %i [3] %i [4] %i [5] %i [6] %i" , sizeof(remotedata),len, data[0], data[1], data[2], data[3], data[4], data[5], data[6]);
  if (len>0)  // check if there really is data...
  {
     if (chr->uuid == KBLinkClientChar_Layers.uuid){
      LOG_LV1("CB NOT","notify_callback: Layers Data");
          KeyScanner::updateRemoteLayer(data[0]);  // Layer is only a single uint8
      }

    if (chr->uuid == KBLinkClientChar_Buffer.uuid){
      LOG_LV1("CB NOT","notify_callback: Buffer Data");
      if (len >= sizeof(remotedata))
        {
          remotedata=*(Payload*) data;
          KeyScanner::updateRemoteReport(remotedata.report[0],remotedata.report[1],remotedata.report[2], remotedata.report[3],remotedata.report[4], remotedata.report[5], remotedata.report[6]);
          KeyScanner::updateRemoteLayer(remotedata.report[7]);
          KeyScanner::remotespecialkeycode = remotedata.specialkeycode;
        }      
      }
      
  }
}
#endif
/**************************************************************************************************************************/
// This callback is called when a Notification subscription event occurs (This occurs on the server)
/**************************************************************************************************************************/
 #if BLE_PERIPHERAL == 1
void cccd_callback(uint16_t conn_hdl, BLECharacteristic* chr, uint16_t cccd_value)    
{
// this is called on the slave board...
  char peer_name[32] = { 0 };
  BLEConnection* connection = Bluefruit.Connection(conn_hdl);
  connection->getPeerName(peer_name, sizeof(peer_name));
  LOG_LV1("CENTRL","Connected to %i %s",conn_hdl,peer_name );
  connection->monitorRssi(6);
  strcpy (keyboardstate.peer_name_cccd,peer_name);
  keyboardstate.conn_handle_cccd = conn_hdl;
    LOG_LV1("CBCCCD","notify_callback: %i " ,cccd_value);
    
    // Check the characteristic this CCCD update is associated with in case
    // this handler is used for multiple CCCD records.
    if (chr->uuid == KBLinkChar_Layers.uuid) {
        if (chr->notifyEnabled()) {              
            LOG_LV1("CBCCCD","Layers 'Notify' enabled");
        } else {
            LOG_LV1("CBCCCD","Layers 'Notify' disabled");
        }
    }
      if (chr->uuid == KBLinkChar_Layer_Request.uuid) {
          if (chr->notifyEnabled()) {
            LOG_LV1("CBCCCD","KBLinkChar_Layer_Request 'Notify' enabled");
         } else {
            LOG_LV1("CBCCCD","KBLinkChar_Layer_Request 'Notify' disabled");
          }
      }
      if (chr->uuid == KBLinkChar_Buffer.uuid) {
          if (chr->notifyEnabled()) {
            LOG_LV1("CBCCCD","KBLinkChar_Buffer 'Notify' enabled");
          } else {
            LOG_LV1("CBCCCD","KBLinkChar_Buffer 'Notify' disabled");
          }
      }
      
}
/**************************************************************************************************************************/
// This callback is called layer_request when characteristic is being written to.  This occurs on the server (Peripheral)
// Called by KBLinkChar_Layer_Request
/**************************************************************************************************************************/
void layer_request_callback (uint16_t conn_hdl, BLECharacteristic* chr, uint8_t* data, uint16_t len)
{
LOG_LV1("CB_CHR","layer_request_callback: len %i offset %i  data %i" ,len, data[0]);
      if (len >= sizeof(statedata))
      {
        statedata=*(StatePayload*) data; // update state
        KeyScanner::updateRemoteLayer(statedata.layer);
      }  
}
#endif

/**************************************************************************************************************************/
// This callback is called when the scanner finds a device. This happens on the Client/Central
/**************************************************************************************************************************/
#if BLE_CENTRAL == 1    // CENTRAL IS THE MASTER BOARD
void scan_callback(ble_gap_evt_adv_report_t* report)
{
  if ( Bluefruit.Scanner.checkReportForService(report, KBLinkClientService) )
  {
    LOG_LV1("KBLINK","KBLink service detected. Connecting ... ");
    Bluefruit.Central.connect(report);
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
keyboardstate.conn_handle_prph = conn_handle;

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

// if HID then save connection handle to HID_connection handle
#if BLE_HID == 1
hid_conn_hdl = 0;
#endif
}

/**************************************************************************************************************************/
// This callback is called when the central connects to a peripheral
/**************************************************************************************************************************/
void cent_connect_callback(uint16_t conn_handle)
{// this runs on the master but when connecting to a slave.
  char peer_name[32] = { 0 };
  BLEConnection* connection = Bluefruit.Connection(conn_handle);
  connection->getPeerName(peer_name, sizeof(peer_name));
  LOG_LV1("CENTRL","Connected to %i %s",conn_handle,peer_name );
  connection->monitorRssi(6);
strcpy (keyboardstate.peer_name_cent,peer_name);
keyboardstate.conn_handle_cent = conn_handle;

  if (KBLinkClientService.discover(conn_handle )) // validating that KBLink service is available to this connection
  {
    if (KBLinkClientChar_Layers.discover()) {
          KBLinkClientChar_Layers.enableNotify();      
      }
    if (KBLinkClientChar_Buffer.discover()) {
          KBLinkClientChar_Buffer.enableNotify();      
      }

      if (KBLinkClientChar_Layer_Request.discover()) {
          LOG_LV1("CENTRL","Connected and KBLinkClientChar_Layer_Request.discover() successful");     
      }
  }
  else 
  {
    LOG_LV1("CENTRL","No KBLink Service on this connection"  );
    // disconect since we couldn't find KBLink service
    Bluefruit.disconnect(conn_handle);
  }   
}
/**************************************************************************************************************************/
// This callback is called when the central disconnects from a peripheral
/**************************************************************************************************************************/
void cent_disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;
  LOG_LV1("CENTRL","Disconnected"  );
  // if the half disconnects, we need to make sure that the received buffer is set to empty.
            KeyScanner::updateRemoteLayer(0);  // Layer is only a single uint8
           KeyScanner::updateRemoteReport(0,0,0, 0,0, 0, 0);
}
#endif

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
  if ( led_bitmap )
  {
    ledOn( STATUS_KB_LED_PIN );
  }
  else
  {
    ledOff( STATUS_KB_LED_PIN );
  }
}
/**************************************************************************************************************************/
void sendlayer(uint8_t layer)
{     
        #if BLE_CENTRAL ==1
        LOG_LV1("CENTRAL","Sending Layer %i  %i" ,millis(),layer );
        if (KBLinkClientChar_Layer_Request.discovered()) {
          statedata.layer =layer;
          uint16_t msg = KBLinkClientChar_Layer_Request.write_resp(&statedata, sizeof(statedata));       // Central->Peripheral uses the write mechanism
          LOG_LV1("CENTRAL","Sending Layer results  %i" ,msg);
        } else
        {
          LOG_LV1("CENTRAL","Sending Layer failed KBLinkClientChar_Layer_Request.discover() not true ");
        }
        #endif 
}
/**************************************************************************************************************************/
void sendKeys(uint8_t currentReport[8])
{
    #if BLE_HID == 1  
        uint8_t keycode[6];
     //   uint8_t layer = 0;
        uint8_t mods = 0;
        mods = currentReport[0];                                                 // modifiers
        keycode[0] = currentReport[1];                                           // Buffer 
        keycode[1] = currentReport[2];                                           // Buffer 
        keycode[2] = currentReport[3];                                           // Buffer 
        keycode[3] = currentReport[4];                                           // Buffer 
        keycode[4] = currentReport[5];                                           // Buffer 
        keycode[5] = currentReport[6];                                           // Buffer 
    //    layer = currentReport[7];                                                // Layer
        blehid.keyboardReport(hid_conn_hdl,mods,  keycode); 
        LOG_LV2("HID","Sending blehid.keyboardReport " );
    #endif
    #if BLE_PERIPHERAL ==1    // PERIPHERAL IS THE SLAVE BOARD
          Linkdata.report[0] =currentReport[0];  // initialize the slave to master link data...
          Linkdata.report[1] =currentReport[1];
          Linkdata.report[2] =currentReport[2];
          Linkdata.report[3] =currentReport[3];
          Linkdata.report[4] =currentReport[4];
          Linkdata.report[5] =currentReport[5];
          Linkdata.report[6] =currentReport[6];
          Linkdata.report[7] =currentReport[7];
          Linkdata.command = 0;
          Linkdata.timesync = 0;
          Linkdata.specialkeycode = 0;
          Linkdata.batterylevel = batterymonitor.vbat_per;
          LOG_LV1("KB-P2C"," KBLinkChar_Buffer.notify sendKeys sending %i [1] %i",sizeof(Linkdata),Linkdata.report[1]);
          KBLinkChar_Buffer.notify(&Linkdata, sizeof(Linkdata));    
    #endif
    #if BLE_CENTRAL ==1      // CENTRAL IS THE MASTER BOARD
         ; // Don't send keys to slaves
    #endif 
}
#ifndef MOVE_STEP
  #define MOVE_STEP   8
#endif
void sendMouseKey(uint16_t keycode)
{
  static uint8_t movestep = MOVE_STEP;

  #if BLE_HID == 1
  switch (keycode) 
  {
    case KC_MS_OFF:   blehid.mouseButtonRelease(hid_conn_hdl); break;
    case KC_MS_UP:    blehid.mouseMove(hid_conn_hdl, 0, -movestep); break;
    case KC_MS_DOWN:  blehid.mouseMove(hid_conn_hdl, 0,  movestep); break;
    case KC_MS_LEFT:  blehid.mouseMove(hid_conn_hdl, -movestep, 0); break;
    case KC_MS_RIGHT: blehid.mouseMove(hid_conn_hdl,  movestep, 0); break;

    case KC_MS_ACCEL0: movestep = MOVE_STEP/MOVE_STEP; break;
    case KC_MS_ACCEL1: movestep = MOVE_STEP; break;
    case KC_MS_ACCEL2: movestep = MOVE_STEP+MOVE_STEP; break;

    case KC_MS_BTN1:  blehid.mouseButtonPress(hid_conn_hdl, MOUSE_BUTTON_LEFT); break;
    case KC_MS_BTN2:  blehid.mouseButtonPress(hid_conn_hdl, MOUSE_BUTTON_RIGHT); break;
    case KC_MS_BTN3:  blehid.mouseButtonPress(hid_conn_hdl, MOUSE_BUTTON_MIDDLE); break;
    case KC_MS_BTN4:  blehid.mouseButtonPress(hid_conn_hdl, MOUSE_BUTTON_BACKWARD); break;
    case KC_MS_BTN5:  blehid.mouseButtonPress(hid_conn_hdl, MOUSE_BUTTON_FORWARD); break;

    case KC_MS_WH_UP: blehid.mouseScroll(hid_conn_hdl,  -1); break;
    case KC_MS_WH_DOWN: blehid.mouseScroll(hid_conn_hdl, 1); break;
    case KC_MS_WH_LEFT: blehid.mousePan(hid_conn_hdl,   -1); break;
    case KC_MS_WH_RIGHT: blehid.mousePan(hid_conn_hdl,   1); break;
  }
  #endif
      #if BLE_PERIPHERAL ==1    // PERIPHERAL IS THE SLAVE BOARD
          Linkdata.report[0] = 0;  // initialize the slave to master link data...
          Linkdata.report[1] = 0;
          Linkdata.report[2] = 0;
          Linkdata.report[3] = 0;
          Linkdata.report[4] = 0;
          Linkdata.report[5] = 0;
          Linkdata.report[6] = 0;
          Linkdata.report[7] = 0;
          Linkdata.command = 0;
          Linkdata.timesync = 0;
          Linkdata.specialkeycode = keycode;
          Linkdata.batterylevel = batterymonitor.vbat_per;
          LOG_LV1("KB-P2C"," KBLinkChar_Buffer.notify sendMouseKey");
          KBLinkChar_Buffer.notify(&Linkdata, sizeof(Linkdata));    
    #endif
    #if BLE_CENTRAL ==1      // CENTRAL IS THE MASTER BOARD
         ; // Don't send keys to slaves
    #endif 
}
void sendMediaKey(uint16_t keycode)
{
uint16_t usagecode = 0;
#if BLE_HID == 1
  switch (keycode) 
  {
    case KC_SYSTEM_POWER: usagecode = HID_USAGE_CONSUMER_POWER; break;
    case KC_SYSTEM_RESET: usagecode = HID_USAGE_CONSUMER_RESET; break;
    case KC_SYSTEM_SLEEP: usagecode = HID_USAGE_CONSUMER_SLEEP; break;
    case KC_DISPLAY_BRIGHTI: usagecode = HID_USAGE_CONSUMER_BRIGHTNESS_INCREMENT; break;
    case KC_DISPLAY_BRIGHTD: usagecode = HID_USAGE_CONSUMER_BRIGHTNESS_DECREMENT; break;
    case KC_RADIO_CONTROL: usagecode = HID_USAGE_CONSUMER_WIRELESS_RADIO_CONTROLS; break;
    case KC_RADIO_BUTTONS: usagecode = HID_USAGE_CONSUMER_WIRELESS_RADIO_BUTTONS; break;
    case KC_RADIO_LED: usagecode = HID_USAGE_CONSUMER_WIRELESS_RADIO_LED; break;
    case KC_RADIO_SWITCH: usagecode = HID_USAGE_CONSUMER_WIRELESS_RADIO_SLIDER_SWITCH; break;
    case KC_MEDIA_PLAY_PAUSE: usagecode = HID_USAGE_CONSUMER_PLAY_PAUSE; break;
    case KC_MEDIA_NEXT_TRACK: usagecode = HID_USAGE_CONSUMER_SCAN_NEXT; break;
    case KC_MEDIA_PREV_TRACK: usagecode = HID_USAGE_CONSUMER_SCAN_PREVIOUS; break;
    case KC_MEDIA_STOP: usagecode = HID_USAGE_CONSUMER_STOP; break;
    case KC_AUDIO_VOL: usagecode = HID_USAGE_CONSUMER_VOLUME; break;
    case KC_AUDIO_MUTE: usagecode = HID_USAGE_CONSUMER_MUTE; break;
    case KC_AUDIO_BASS: usagecode = HID_USAGE_CONSUMER_BASS; break;
    case KC_AUDIO_TREBLE: usagecode = HID_USAGE_CONSUMER_TREBLE; break;
    case KC_AUDIO_BASS_BOOST: usagecode = HID_USAGE_CONSUMER_BASS_BOOST; break;
    case KC_AUDIO_VOL_UP: usagecode = HID_USAGE_CONSUMER_VOLUME_INCREMENT; break;
    case KC_AUDIO_VOL_DOWN: usagecode = HID_USAGE_CONSUMER_VOLUME_DECREMENT; break;
    case KC_AUDIO_BASS_UP: usagecode = HID_USAGE_CONSUMER_BASS_INCREMENT; break;
    case KC_AUDIO_BASS_DOWN: usagecode = HID_USAGE_CONSUMER_BASS_DECREMENT; break;
    case KC_AUDIO_TREBLE_UP: usagecode = HID_USAGE_CONSUMER_TREBLE_INCREMENT; break;
    case KC_AUDIO_TREBLE_DOWN: usagecode = HID_USAGE_CONSUMER_TREBLE_DECREMENT; break;
    case KC_MSEL: usagecode = HID_USAGE_CONSUMER_AL_CONSUMER_CONTROL_CONFIGURATION; break;
    case KC_WWW: usagecode = HID_USAGE_CONSUMER_AL_EMAIL_READER; break;
    case KC_CALCULATOR: usagecode = HID_USAGE_CONSUMER_AL_CALCULATOR; break;
    case KC_MYCM: usagecode = HID_USAGE_CONSUMER_AL_LOCAL_BROWSER; break;

    case KC_WWW_SEARCH: usagecode = HID_USAGE_CONSUMER_AC_SEARCH; break;
    case KC_WWW_HOME: usagecode = HID_USAGE_CONSUMER_AC_HOME; break;
    case KC_WWW_BACK: usagecode = HID_USAGE_CONSUMER_AC_BACK; break;
    case KC_WWW_FORWARD: usagecode = HID_USAGE_CONSUMER_AC_FORWARD; break;
    case KC_WWW_STOP: usagecode = HID_USAGE_CONSUMER_AC_STOP; break;
    case KC_WWW_REFRESH: usagecode = HID_USAGE_CONSUMER_AC_REFRESH; break;
    case KC_WWW_FAVORITES: usagecode = HID_USAGE_CONSUMER_AC_BOOKMARKS; break;
    case KC_AC_PAN: usagecode = HID_USAGE_CONSUMER_AC_PAN; break;
  }
  
    blehid.consumerKeyPress(hid_conn_hdl, usagecode);
    delay(HIDREPORTINGINTERVAL);
    blehid.consumerKeyRelease();
  #endif 
        #if BLE_PERIPHERAL ==1    // PERIPHERAL IS THE SLAVE BOARD
          Linkdata.report[0] = 0;  // initialize the slave to master link data...
          Linkdata.report[1] = 0;
          Linkdata.report[2] = 0;
          Linkdata.report[3] = 0;
          Linkdata.report[4] = 0;
          Linkdata.report[5] = 0;
          Linkdata.report[6] = 0;
          Linkdata.report[7] = 0;
          Linkdata.command = 0;
          Linkdata.timesync = 0;
          Linkdata.specialkeycode = keycode;
          Linkdata.batterylevel = batterymonitor.vbat_per;
          LOG_LV1("KB-P2C"," KBLinkChar_Buffer.notify sendMediaKey");
          KBLinkChar_Buffer.notify(&Linkdata, sizeof(Linkdata));    
    #endif
    #if BLE_CENTRAL ==1      // CENTRAL IS THE MASTER BOARD
         ; // Don't send keys to slaves
    #endif 
}
/**************************************************************************************************************************/
