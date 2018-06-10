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
#include <bluefruit.h>
#undef min
#undef max
#include "Key.h"

BLEDis bledis;

#if BLE_PERIPHERAL == 1
BLEUart bleuart;
#endif

#if BLE_HID == 1
BLEHidAdafruit blehid;
#endif

#if BLE_CENTRAL == 1
//BLEUart bleuart;
BLEClientUart clientUart;
#endif

byte rows[] MATRIX_ROW_PINS;        // defined in keyboard_config.h
byte columns[] MATRIX_COL_PINS;     // defined in keyboard_config.h

Key keys;

std::array<uint8_t, 6> nullReport {0, 0,0,0 ,0,0};

bool isReportedReleased = true;

/****************************************************************************************************/
// put your main code here, to run repeatedly:
/****************************************************************************************************/
void setup() {
  #if DEBUG_SERIAL == 1
  Serial.begin(115200);
  #endif
   //inits all the columns as INPUT
   for (const auto& column : columns) {
  #if DEBUG_SERIAL == 1
      Serial.print("column ");
      Serial.print(column);
      Serial.println(" set to INPUT");
  #endif

      pinMode(column, INPUT);
    }

   //inits all the rows as INPUT_PULLUP
   for (const auto& row : rows) {
#if DEBUG_SERIAL == 1
      Serial.print("row ");
      Serial.print(row);
      Serial.println(" set to INPUT_PULLUP");
#endif
    pinMode(row, INPUT_PULLUP);
    }

  Bluefruit.begin(PERIPHERAL_COUNT,CENTRAL_COUNT);                            // (1,1) vs () PERIPHERAL_COUNT,CENTRAL_COUNT
  Bluefruit.setTxPower(DEVICE_POWER);
  Bluefruit.setName(DEVICE_NAME);

  // Configure and Start Device Information Service
  bledis.setManufacturer(MANUFACTURER_NAME);
  bledis.setModel(DEVICE_MODEL);
  bledis.begin();
  
 #if BLE_PERIPHERAL == 1
  bleuart.begin();
  bleuart.setRxCallback(prph_bleuart_rx_callback);   
  #endif
  
 #if BLE_CENTRAL == 1 
    // Init BLE Central Uart Serivce
  clientUart.begin();
  clientUart.setRxCallback(cent_bleuart_rx_callback);
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
  Bluefruit.setConnInterval(9, 12);

#if BLE_CENTRAL == 1
  Bluefruit.setConnectCallback(prph_connect_callback);
  Bluefruit.setDisconnectCallback(prph_disconnect_callback);  

  Bluefruit.Scanner.setRxCallback(scan_callback);
  Bluefruit.Scanner.restartOnDisconnect(true);
  Bluefruit.Scanner.setInterval(160, 80); // in unit of 0.625 ms
  Bluefruit.Scanner.useActiveScan(false);
  Bluefruit.Scanner.start(0);                   // // 0 = Don't stop scanning after 0 seconds

  Bluefruit.Central.setConnectCallback(cent_connect_callback);
  Bluefruit.Central.setDisconnectCallback(cent_disconnect_callback);

#endif
  
  // Set up and start advertising
  startAdv(); 
};
/****************************************************************************************************/

#if BLE_CENTRAL == 1
void scan_callback(ble_gap_evt_adv_report_t* report)
{
  // Check if advertising contain BleUart service3
  if ( Bluefruit.Scanner.checkReportForService(report, clientUart) )
  {
    #if DEBUG_SERIAL == 1

    Serial.print("BLE UART service detected. Connecting ... ");
#endif 
    // Connect to device with bleuart service in advertising
    Bluefruit.Central.connect(report);
  }
}
/****************************************************************************************************/
void prph_connect_callback(uint16_t conn_handle)
{
  char peer_name[32] = { 0 };
  Bluefruit.Gap.getPeerName(conn_handle, peer_name, sizeof(peer_name));
 #if DEBUG_SERIAL == 1

  Serial.print("[Prph] Connected to ");
  Serial.println(peer_name);
  #endif
}
/****************************************************************************************************/ 
void prph_disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;

#if DEBUG_SERIAL ==1
  Serial.println();
  Serial.println("[Prph] Disconnected");
#endif
  
}
/****************************************************************************************************/
void cent_bleuart_rx_callback(BLEClientUart& cent_uart)
    {
      uint8_t str[20+1] = { 0 };
      cent_uart.read(str, 20);
#if DEBUG_SERIAL ==1
      Serial.print("cent_bleuart_rx_callback: ");
      Serial.print(str[0]);
      Serial.print(str[1]);
      Serial.print(str[2]);
      Serial.print(str[3]);
      Serial.print(str[4]);
      Serial.print(str[5]);
      Serial.print(str[6]);
      Serial.print(str[7]);
      Serial.print(str[8]);
      Serial.println(str[9]);
#endif
      if (str[0] == 0)
      {
        Key::updateRemoteReport(str[1],str[2],str[3],str[4],str[5],str[6],str[7],str[8],str[9]);        
      }
      if (str[0] == 1)
      {
        Key::updateRemoteLayer(str[1]);        
      }
      
    }
/****************************************************************************************************/
void cent_connect_callback(uint16_t conn_handle)
{
  char peer_name[32] = { 0 };
  Bluefruit.Gap.getPeerName(conn_handle, peer_name, sizeof(peer_name));
#if DEBUG_SERIAL ==1 
  Serial.print("[Cent] Connected to ");
  Serial.println(peer_name);;
#endif
  if ( clientUart.discover(conn_handle) )
  {
    // Enable TXD's notify
    clientUart.enableTXD();
  }else
  {
    // disconect since we couldn't find bleuart service
    Bluefruit.Central.disconnect(conn_handle);
  }  
}
/****************************************************************************************************/
void cent_disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;
  #if DEBUG_SERIAL == 1

  Serial.println("[Cent] Disconnected");
#endif
}
#endif
/****************************************************************************************************/
#if BLE_PERIPHERAL == 1
void prph_bleuart_rx_callback(void)
    {
      // Forward data from Mobile to our peripheral
      uint8_t  str[20+1] = { 0 };
      bleuart.read(str, 20);
      #if DEBUG_SERIAL ==1 
      Serial.print("prph_bleuart_rx_callback: ");
      Serial.print(str[0]);
      Serial.print(str[1]);
      Serial.print(str[2]);
      Serial.print(str[3]);
      Serial.print(str[4]);
      Serial.print(str[5]);
      Serial.print(str[6]);
      Serial.print(str[7]);
      Serial.print(str[8]);
      Serial.println(str[9]);
      #endif
      if (str[0] == 0)
      {
        Key::updateRemoteReport(str[1],str[2],str[3],str[4],str[5],str[6],str[7],str[8],str[9]);        
      }
      if (str[0] == 1)
      {
        Key::updateRemoteLayer(str[1]);        
      }
      }
#endif
/****************************************************************************************************/
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
  Bluefruit.Advertising.addService(bleuart);
  #endif
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
/****************************************************************************************************/
void readMatrix() {
std::array<uint8_t, 9> data;
uint8_t keycode[6];
  
  for(int j = 0; j < MATRIX_ROWS; ++j) {
    //set the current row as OUPUT and LOW
    pinMode(rows[j], OUTPUT);                                         
    digitalWrite(rows[j], LOW);                                       // 'enables' a specific row to be "low" 
    //loops thru all of the columns
    for (int i = 0; i < MATRIX_COLS; ++i) {
      pinMode(columns[i], INPUT_PULLUP);                              // 'enables' the column High Value on the diode; becomes "LOW" when pressed
      delay(1);
      Key::scanMatrix(digitalRead(columns[i]), millis(), j, i);
      pinMode(columns[i], INPUT);                                     //'disables' the column that just got looped thru
     }
    pinMode(rows[j], INPUT);                                          //'disables' the row that was just scanned
   }                                                                  // done scanning the matrix
   
    data = Key::getReport();
         #if BLE_PERIPHERAL ==1   | BLE_CENTRAL ==1 
        uint8_t str[10] = {0};
        
        str[0]= 0; 
        str[1]= data[0];
        str[2]= data[1];
        str[3]=data[2];
        str[4]=data[3];
        str[5]=data[4];
        str[6]=data[5];
        str[7]=data[6];
        str[8]=data[7];
        str[9]=data[8];
        #endif  
         
   if ((data[0] != 0) | (data[1] != 0)| (data[2] != 0)| (data[3] != 0)| (data[4] != 0)| (data[5] != 0)| (data[6] != 0))
   {
        #if BLE_HID == 1  
        keycode[0] = data[1];
        keycode[1] = data[2];
        keycode[2] = data[3];
        keycode[3] = data[4];
        keycode[4] = data[5];
        keycode[5] = data[6];       
        blehid.keyboardReport(data[0],  keycode); 
        #endif
        #if BLE_PERIPHERAL ==1  
 
          bleuart.write(str, 10);
          #if DEBUG_SERIAL ==1
                    Serial.print(str[0]);
      Serial.print(str[1]);
      Serial.print(str[2]);
      Serial.print(str[3]);
      Serial.print(str[4]);
      Serial.print(str[5]);
      Serial.print(str[6]);
      Serial.print(str[7]);
      Serial.print(str[8]);
      Serial.println(str[9]);
        #endif
        #endif
        #if BLE_CENTRAL ==1
        if ( clientUart.discovered() ){
          clientUart.write(str,10);
        }
        #endif 
        isReportedReleased = false;
#if DEBUG_SERIAL ==1
        Serial.print("SEND: ");
        Serial.print(millis());
        Serial.print(' ');
        Serial.print(data[0]);
        Serial.print(' ');
        Serial.print(data[1]);
        Serial.print(' ');
        Serial.print(data[2]);
        Serial.print(' ');
        Serial.print(data[3]);
        Serial.print(' ');
        Serial.print(data[4]);
        Serial.print(' ');
        Serial.print(data[5]);
        Serial.print(' ');
        Serial.print(data[6]);
        Serial.print(' ');
        Serial.print(data[7]);
        Serial.print(' ');
        Serial.println(data[8]);
#endif        
    }
   else
   {
    if ((!isReportedReleased)){
     #if BLE_HID == 1
      blehid.keyRelease();
      #endif
#if BLE_PERIPHERAL ==1
    bleuart.write(str, 10);
    #if DEBUG_SERIAL ==1
          Serial.print(str[0]);
      Serial.print(str[1]);
      Serial.print(str[2]);
      Serial.print(str[3]);
      Serial.print(str[4]);
      Serial.print(str[5]);
      Serial.print(str[6]);
      Serial.print(str[7]);
      Serial.print(str[8]);
      Serial.println(str[9]);
    #endif
    #endif
        #if BLE_CENTRAL ==1
        if ( clientUart.discovered() ){
          clientUart.write(str,10);
        }
        #endif
      isReportedReleased = true;
      #if DEBUG_SERIAL ==1
        Serial.print("RELS: ");
        Serial.print(millis());
        Serial.print(' ');
        Serial.print(data[0]);
        Serial.print(' ');
        Serial.print(data[1]);
        Serial.print(' ');
        Serial.print(data[2]);
        Serial.print(' ');
        Serial.print(data[3]);
        Serial.print(' ');
        Serial.print(data[4]);
        Serial.print(' ');
        Serial.print(data[5]);
        Serial.print(' ');
        Serial.print(data[6]);
        Serial.print(' ');
        Serial.print(data[7]);
        Serial.print(' ');
        Serial.println(data[8]);
      #endif 
    }
    }
    #if BLE_PERIPHERAL ==1   | BLE_CENTRAL ==1 
if(Key::layerChanged)//layer comms
    {
        str[0]= 1; 
        str[1]= Key::localLayer;
        #if BLE_PERIPHERAL ==1  
          bleuart.write(str, 2);
        #endif
        #if BLE_CENTRAL ==1
        if ( clientUart.discovered() ){
          clientUart.write(str,2);
        }
        #endif 
        #if DEBUG_SERIAL == 1
        Serial.print("Layer: ");
        Serial.print(millis());
        Serial.print(' ');
        Serial.print(str[0]);
        Serial.println(str[1]);
        #endif
        Key::layerChanged = false;
    } 
    #endif
}

/****************************************************************************************************/
// put your main code here, to run repeatedly:
/****************************************************************************************************/
void loop() {
  // put your main code here, to run repeatedly:
  readMatrix(); 
  waitForEvent();  // Request CPU to enter low-power mode until an event/interrupt occurs
}

/****************************************************************************************************/
void rtos_idle_callback(void)
{
  // Don't call any other FreeRTOS blocking API()
  // Perform background task(s) here
}

