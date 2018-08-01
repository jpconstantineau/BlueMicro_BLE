/*
Copyright 2018 <Pierre Constantineau, Julian Komaromy>

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
/**************************************************************************************************************************/
#include <bluefruit.h>
#undef min
#undef max

#include "firmware.h"

/**************************************************************************************************************************/
// Bluetooth Services and Characteristics Definition

  BLEDis bledis;                                                                    // Device Information Service

#if BLE_PERIPHERAL == 1                                                             // PERIPHERAL IS THE SLAVE BOARD
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
// Keyboard Matrix
byte rows[] MATRIX_ROW_PINS;        // Contains the GPIO Pin Numbers defined in keyboard_config.h
byte columns[] MATRIX_COL_PINS;     // Contains the GPIO Pin Numbers defined in keyboard_config.h  

Key keys;
uint8_t Linkdata[7] = {0 ,0,0,0,0,0,0};

bool isReportedReleased = true;

/**************************************************************************************************************************/
// put your setup code here, to run once:
/**************************************************************************************************************************/
void setup() {

  Serial.begin(115200);

  LOG_LV1("BLEMIC","Starting %s" ,DEVICE_NAME);
 
  Bluefruit.begin(PERIPHERAL_COUNT,CENTRAL_COUNT);                            // Defined in firmware_config.h
  Bluefruit.setTxPower(DEVICE_POWER);                                         // Defined in bluetooth_config.h
  Bluefruit.setName(DEVICE_NAME);                                             // Defined in keyboard_config.h
  Bluefruit.configUuid128Count(UUID128_COUNT);                                // Defined in bluetooth_config.h
  Bluefruit.configServiceChanged(true);                                       // helps troubleshooting...
  Bluefruit.setConnInterval(9, 12);

  // Configure and Start Device Information Service
  bledis.setManufacturer(MANUFACTURER_NAME);                                  // Defined in keyboard_config.h
  bledis.setModel(DEVICE_MODEL);                                              // Defined in keyboard_config.h
  bledis.begin();
  
#if BLE_PERIPHERAL == 1
  // Configure Keyboard Link Service
  KBLinkService.begin();
  
  KBLinkChar_Layers.setProperties(CHR_PROPS_NOTIFY+ CHR_PROPS_READ);
  KBLinkChar_Layers.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
  KBLinkChar_Layers.setFixedLen(1);
  KBLinkChar_Layers.setUserDescriptor("Keyboard Layer");
  KBLinkChar_Layers.setCccdWriteCallback(cccd_callback);
  KBLinkChar_Layers.begin();
  KBLinkChar_Layers.write8(0);  // initialize with layer 0

  KBLinkChar_Layer_Request.setProperties(CHR_PROPS_WRITE + CHR_PROPS_WRITE_WO_RESP);
  KBLinkChar_Layer_Request.setPermission(SECMODE_NO_ACCESS, SECMODE_OPEN );
  KBLinkChar_Layer_Request.setFixedLen(1);
  KBLinkChar_Layer_Request.setUserDescriptor("Keyboard Layer Request");
  KBLinkChar_Layer_Request.setWriteCallback(layer_request_callback);
  KBLinkChar_Layer_Request.begin();
  KBLinkChar_Layer_Request.write8(0);  // initialize with layer 0
    
  KBLinkChar_Buffer.setProperties(CHR_PROPS_NOTIFY+ CHR_PROPS_READ);
  KBLinkChar_Buffer.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
  KBLinkChar_Buffer.setFixedLen(7);
  KBLinkChar_Buffer.setUserDescriptor("Keyboard HID Buffer");
  KBLinkChar_Buffer.setCccdWriteCallback(cccd_callback);
  KBLinkChar_Buffer.begin();
  KBLinkChar_Buffer.write(Linkdata, 7);  // initialize with empty buffer

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
#endif

  /* Set connection interval (min, max) to your perferred value.
   * Note: It is already set by BLEHidAdafruit::begin() to 11.25ms - 15ms
   * min = 9*1.25=11.25 ms, max = 12*1.25= 15 ms 
   */
 
 #if BLE_CENTRAL == 1 

  KBLinkClientService.begin();

  KBLinkClientChar_Layers.begin();
  KBLinkClientChar_Layers.setNotifyCallback(notify_callback);

  KBLinkClientChar_Buffer.begin();
  KBLinkClientChar_Buffer.setNotifyCallback(notify_callback);

  KBLinkClientChar_Layer_Request.begin();
  
  Bluefruit.setConnectCallback(prph_connect_callback);
  Bluefruit.setDisconnectCallback(prph_disconnect_callback);  

  Bluefruit.Scanner.setRxCallback(scan_callback);
  Bluefruit.Scanner.restartOnDisconnect(true);
  Bluefruit.Scanner.filterRssi(-80);                                              // limits very far away devices - reduces load
  Bluefruit.Scanner.filterUuid(BLEUART_UUID_SERVICE, UUID128_SVC_KEYBOARD_LINK);  // looks specifically for these 2 services (A OR B) - reduces load
  Bluefruit.Scanner.setInterval(160, 80);                                         // in unit of 0.625 ms  Interval = 100ms, Window = 50 ms
  Bluefruit.Scanner.useActiveScan(false);                                         // If true, will fetch scan response data
  Bluefruit.Scanner.start(30);                                                     // 0 = Don't stop scanning after 0 seconds

  Bluefruit.Central.setConnectCallback(cent_connect_callback);
  Bluefruit.Central.setDisconnectCallback(cent_disconnect_callback);

#endif
  
  // Set up keyboard matrix and start advertising
  setupMatrix();
  startAdv(); 
};
/**************************************************************************************************************************/
//
/**************************************************************************************************************************/
void setupMatrix(void)
{
    //inits all the columns as INPUT
   for (const auto& column : columns) {
      LOG_LV2("BLEMIC","Setting to INPUT Column: %i" ,column);
      pinMode(column, INPUT);
    }

   //inits all the rows as INPUT_PULLUP
   for (const auto& row : rows) {
      LOG_LV2("BLEMIC","Setting to INPUT_PULLUP Row: %i" ,row);
      pinMode(row, INPUT_PULLUP);
    }
}
/**************************************************************************************************************************/
//
/**************************************************************************************************************************/
void startAdv(void)
{  
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);

  #if BLE_HID == 1
  // Include BLE HID service
  Bluefruit.Advertising.addService(blehid);
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
  Bluefruit.ScanResponse.addName();
  
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

/**************************************************************************************************************************/
// This callback is called when a Notification update even occurs (This occurs on the client)
/**************************************************************************************************************************/
#if BLE_CENTRAL == 1
void notify_callback(BLEClientCharacteristic* chr, uint8_t* data, uint16_t len)
{
  LOG_LV1("CB NOT","notify_callback: Length %i data[0] %i" ,len, data[0]);
  if (len>0)  // check if there really is data...
  {
     if (chr->uuid == KBLinkClientChar_Layers.uuid){
      LOG_LV1("CB NOT","notify_callback: Layers Data");
          Key::updateRemoteLayer(data[0]);  // Layer is only a single uint8
      }

    if (chr->uuid == KBLinkClientChar_Buffer.uuid){
      LOG_LV1("CB NOT","notify_callback: Buffer Data");
          Key::updateRemoteReport(data[0],data[1],data[2], data[3],data[4], data[5], data[6]);
      }
      
  }
}
#endif
/**************************************************************************************************************************/
// This callback is called when a Notification subscription event occurs (This occurs on the server)
/**************************************************************************************************************************/
 #if BLE_PERIPHERAL == 1
void cccd_callback(BLECharacteristic& chr, uint16_t cccd_value)    
{
    LOG_LV1("CBCCCD","notify_callback: %i " ,cccd_value);
    
    // Check the characteristic this CCCD update is associated with in case
    // this handler is used for multiple CCCD records.
    if (chr.uuid == KBLinkChar_Layers.uuid) {
        if (chr.notifyEnabled()) {              
            LOG_LV1("CBCCCD","Layers 'Notify' enabled");
        } else {
            LOG_LV1("CBCCCD","Layers 'Notify' disabled");
        }
    }
      if (chr.uuid == KBLinkChar_Layer_Request.uuid) {
          if (chr.notifyEnabled()) {
            LOG_LV1("CBCCCD","KBLinkChar_Layer_Request 'Notify' enabled");
          } else {
            LOG_LV1("CBCCCD","KBLinkChar_Layer_Request 'Notify' disabled");
          }
      }
      if (chr.uuid == KBLinkChar_Buffer.uuid) {
          if (chr.notifyEnabled()) {
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
void layer_request_callback (BLECharacteristic& chr, uint8_t* data, uint16_t len, uint16_t offset)
{
LOG_LV1("CB_CHR","layer_request_callback: len %i offset %i  data %i" ,len, offset, data[0]);
      if (len>0)
      {
        // update state
        Key::updateRemoteLayer(data[offset]);
      }  
}
#endif

/**************************************************************************************************************************/
// This callback is called when the scanner finds a device. This happens on the Client/Central
/**************************************************************************************************************************/
#if BLE_CENTRAL == 1
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
  Bluefruit.Gap.getPeerName(conn_handle, peer_name, sizeof(peer_name));
  LOG_LV1("PRPH","Connected to %i %s",conn_handle,peer_name  );
}

/**************************************************************************************************************************/
// This callback is called when the master disconnects from a slave
/**************************************************************************************************************************/
void prph_disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;
  LOG_LV1("PRPH","Disconnected"  );
}


/**************************************************************************************************************************/
// This callback is called when the central connects to a peripheral
/**************************************************************************************************************************/
void cent_connect_callback(uint16_t conn_handle)
{
  char peer_name[32] = { 0 };
  Bluefruit.Gap.getPeerName(conn_handle, peer_name, sizeof(peer_name));
  LOG_LV1("CENTRL","Connected to %i %s",conn_handle,peer_name );
  if (KBLinkClientService.discover(conn_handle)) // validating that KBLink service is available to this connection
  {
    if (KBLinkClientChar_Layers.discover()) {
          KBLinkClientChar_Layers.enableNotify();      
      }
    if (KBLinkClientChar_Buffer.discover()) {
          KBLinkClientChar_Buffer.enableNotify();      
      }
  }
  else
  {
    LOG_LV1("CENTRL","No KBLink Service on this connection"  );
    // disconect since we couldn't find KBLink service
    Bluefruit.Central.disconnect(conn_handle);
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
}
#endif

/**************************************************************************************************************************/
// Keyboard Scanning
// ToDo: DIODE_DIRECTION COL2ROW and ROW2COL code
/**************************************************************************************************************************/
void scanMatrix() {
  uint32_t pindata = 0;
  for(int j = 0; j < MATRIX_ROWS; ++j) {                              
    //set the current row as OUPUT and LOW
    pinMode(rows[j], OUTPUT);                                         
    digitalWrite(rows[j], LOW);                                       // 'enables' a specific row to be "low" 
    //loops thru all of the columns
    for (int i = 0; i < MATRIX_COLS; ++i) {
      pinMode(columns[i], INPUT_PULLUP);                              // 'enables' the column High Value on the diode; becomes "LOW" when pressed
    }
      delay(1);                                                       // need for the GPIO lines to settle down electrically before reading.
      pindata = NRF_GPIO->IN;                                         // read all pins at once
     for (int i = 0; i < MATRIX_COLS; ++i) {
      Key::scanMatrix((pindata>>(columns[i]))&1, millis(), j, i);       // This function processes the logic values and does the debouncing
      pinMode(columns[i], INPUT);                                     //'disables' the column that just got looped thru
     }
    pinMode(rows[j], INPUT);                                          //'disables' the row that was just scanned
   }                                                                  // done scanning the matrix
}

/**************************************************************************************************************************/
// Communication with computer and other boards
/**************************************************************************************************************************/
void sendKeyPresses() {
uint8_t keycode[6];
uint8_t layer = 0;
uint8_t mods = 0;
  
        Key::getReport();                                            // get state data - Data is in Key::currentReport

        mods = Key::currentReport[0];                                                 // modifiers
        keycode[0] = Key::currentReport[1];                                           // Buffer 
        keycode[1] = Key::currentReport[2];                                           // Buffer 
        keycode[2] = Key::currentReport[3];                                           // Buffer 
        keycode[3] = Key::currentReport[4];                                           // Buffer 
        keycode[4] = Key::currentReport[5];                                           // Buffer 
        keycode[5] = Key::currentReport[6];                                           // Buffer 
        layer = Key::currentReport[7];                                                // Layer
 
         
   if (!(Key::reportEmpty))  //any key presses anywhere?
   {                                                                              // Note that HID standard only has a buffer of 6 keys (plus modifiers)
        #if BLE_HID == 1  
        blehid.keyboardReport(mods,  keycode); 

        #endif
        #if BLE_PERIPHERAL ==1  
          KBLinkChar_Buffer.notify(Key::currentReport,7);
        #endif
        #if BLE_CENTRAL ==1
         ; // Only send layer to slaves - send nothing here
        #endif 
        isReportedReleased = false;
        LOG_LV1("MXSCAN","SEND: %i %i %i %i %i %i %i %i %i %i" ,millis(),Key::currentReport[0], Key::currentReport[1],Key::currentReport[2],Key::currentReport[3], Key::currentReport[4],Key::currentReport[5], Key::currentReport[6],Key::currentReport[7] );        
    }
   else                                                                  //NO key presses anywhere
   {
    if ((!isReportedReleased)){
      #if BLE_HID == 1
        blehid.keyRelease();                                             // HID uses the standard blehid service
      #endif
      #if BLE_PERIPHERAL ==1     
        KBLinkChar_Buffer.notify(Key::currentReport,7);                              // Peripheral->central uses the subscribe/notify mechanism
      #endif
        #if BLE_CENTRAL ==1
          // Only send layer to slaves
          ;                                                              // Central does not need to send the buffer to the Peripheral.
        #endif
      isReportedReleased = true;                                         // Update flag so that we don't re-issue the message if we don't need to.
      LOG_LV1("MXSCAN","RELEASED: %i %i %i %i %i %i %i %i %i %i" ,millis(),Key::currentReport[0], Key::currentReport[1],Key::currentReport[2],Key::currentReport[3], Key::currentReport[4],Key::currentReport[5], Key::currentReport[6],Key::currentReport[7] ); 
    }
   }
    
    
  #if BLE_PERIPHERAL ==1   | BLE_CENTRAL ==1                            /**************************************************/
    if(Key::layerChanged)                                               //layer comms
    {   
        #if BLE_PERIPHERAL ==1  
          KBLinkChar_Layers.notify8(Key::localLayer);                   // Peripheral->central uses the subscribe/notify mechanism
        #endif
        
        #if BLE_CENTRAL ==1
        LOG_LV1("MXSCAN","Sending Layer %i  %i" ,millis(),Key::localLayer );
        if (KBLinkClientChar_Layer_Request.discover()) {
          uint16_t msg = KBLinkClientChar_Layer_Request.write8_resp(Key::localLayer);       // Central->Peripheral uses the write mechanism
          LOG_LV1("MXSCAN","Sending Layer results  %i" ,msg);
        }
        #endif 
        
        LOG_LV1("MXSCAN","Layer %i  %i" ,millis(),Key::localLayer );
        Key::layerChanged = false;                                      // mark layer as "not changed" since last update
    } 
  #endif                                                                /**************************************************/
}

/**************************************************************************************************************************/
// put your main code here, to run repeatedly:
/**************************************************************************************************************************/
void loop() {
  // put your main code here, to run repeatedly:
  #if MATRIX_SCAN == 1
  scanMatrix();
  #endif

  #if SEND_KEYS == 1
  sendKeyPresses();    // how often does this really run?
  #endif

 //  //

// Option 1: 6.7-6.8 mA
 //sd_power_mode_set(NRF_POWER_MODE_LOWPWR);
 //   waitForEvent();

// Option 2: 6.8 mA
//    waitForEvent();  // Request CPU to enter low-power mode until an event/interrupt occurs

// Option 3: 6.9-7.0 mA
// sd_app_evt_wait();

// option 4: 7.0 mA
//  __WFE();

// Option 5: 993-1001 uA
//    sd_power_mode_set(NRF_POWER_MODE_LOWPWR);
//    __WFI();

// Option 6: 990-1000 uA
 //  __WFI();

// option 7: 631-640 uA
delay(25);
}

/**************************************************************************************************************************/
void rtos_idle_callback(void)
{
  // Don't call any other FreeRTOS blocking API()
  // Perform background task(s) here
}

