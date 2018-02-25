#include <bluefruit.h>
#undef min
#undef max
#include </home/julian/Arduino/sketch_jan18a/Key.h>

int row1 = 26;
int row2 = 27;
int row3 = 28;
int row4 = 21;
int val;

BLEDis bledis;
BLEHidAdafruit blehid;
BLEUart bleuart;

BLEClientUart clientUart;

byte rows[] { 12, 13, 14, 16 };
byte columns[] { 2, 3, 4, 5, 28, 29};

byte COLS = 6;
byte ROWS = 4;

Key keys[4][6];

char currentChar = ' ';
std::array<uint8_t, 2> nullReport {0, 0};

bool isReportedReleased = true;
bool isFirstLayer = true;

void setup() {

  // put your setup code here, to run once:
  Key::startCurrentLayer();

  //should be the shift key, which is then set to be the shift key 
  keys[2][5].setSpecial(Key::SpecialKey::SHIFT);
  keys[3][2].setSpecial(Key::SpecialKey::DOWN);
  keys[3][1].setSpecial(Key::SpecialKey::WIN);
  keys[3][0].setSpecial(Key::SpecialKey::CONTROL);
  
  Serial.begin(115200);
   pinMode(LED_BUILTIN, OUTPUT);

   //inits all the columns as INPUT
   for (const auto& column : columns) {
      Serial.print("column ");
      Serial.print(column);
      Serial.println(" set to INPUT");
      pinMode(column, INPUT);
    }

   //inits all the rows as INPUT_PULLUP
   for (const auto& row : rows) {
      Serial.print("row ");
      Serial.print(row);
      Serial.println(" set to INPUT_PULLUP");
    pinMode(row, INPUT_PULLUP);
    }

  Bluefruit.begin(1, 1);
  // Set max power. Accepted values are: -40, -30, -20, -16, -12, -8, -4, 0, 4
  Bluefruit.setTxPower(4);
  Bluefruit.setName("Airgo - dox (L)");

  // Configure and Start Device Information Service
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather 52");
  bledis.begin();


  bleuart.begin();
  bleuart.setRxCallback(prph_bleuart_rx_callback);   
    // Init BLE Central Uart Serivce
  clientUart.begin();
  clientUart.setRxCallback(cent_bleuart_rx_callback);

  /* Start BLE HID
   * Note: Apple requires BLE device must have min connection interval >= 20m
   * ( The smaller the connection interval the faster we could send data).
   * However for HID and MIDI device, Apple could accept min connection interval 
   * up to 11.25 ms. Therefore BLEHidAdafruit::begin() will try to set the min and max
   * connection interval to 11.25  ms and 15 ms respectively for best performance.
   */
  blehid.begin();

  /* Set connection interval (min, max) to your perferred value.
   * Note: It is already set by BLEHidAdafruit::begin() to 11.25ms - 15ms
   * min = 9*1.25=11.25 ms, max = 12*1.25= 15 ms 
   */
  Bluefruit.setConnInterval(9, 12);

  Bluefruit.Scanner.setRxCallback(scan_callback);
  Bluefruit.Scanner.restartOnDisconnect(true);
  Bluefruit.Scanner.setInterval(160, 80); // in unit of 0.625 ms
  Bluefruit.Scanner.useActiveScan(false);
  Bluefruit.Scanner.start(0);                   // // 0 = Don't stop scanning after 0 seconds

  Bluefruit.Central.setConnectCallback(cent_connect_callback);
  Bluefruit.Central.setDisconnectCallback(cent_disconnect_callback);

  Bluefruit.setConnectCallback(prph_connect_callback);
  Bluefruit.setDisconnectCallback(prph_disconnect_callback);  
  
  // Set up and start advertising
  startAdv(); 
};

void prph_connect_callback(uint16_t conn_handle)
{
  char peer_name[32] = { 0 };
  Bluefruit.Gap.getPeerName(conn_handle, peer_name, sizeof(peer_name));
 
  Serial.print("[Prph] Connected to ");
  Serial.println(peer_name);
}
 
void prph_disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;
 
  Serial.println();
  Serial.println("[Prph] Disconnected");
}


void cent_bleuart_rx_callback(BLEClientUart& cent_uart)
    {
      uint8_t str[3];
      cent_uart.read(str, 3);

      Serial.print(str[0]);
      Serial.print(str[1]);
      Serial.println(str[2]);

      if (str[0] == 0) {
        blehid.keyboardReport((str[1]+Key::currentReport[0]), str[2], 0, 0, 0, 0, 0);
        }
      else if (str[0] == 1){
        Serial.println("Pressed up");
        Key::aCurrentLayer = &Key::upBLELayer;
        }
      else {
        Serial.println("Released up");
        Key::aCurrentLayer = &Key::firstBLELayer;
        }
    }
 
void cent_connect_callback(uint16_t conn_handle)
{
  char peer_name[32] = { 0 };
  Bluefruit.Gap.getPeerName(conn_handle, peer_name, sizeof(peer_name));
 
  Serial.print("[Cent] Connected to ");
  Serial.println(peer_name);;
 
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
 
void cent_disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;
  
  Serial.println("[Cent] Disconnected");
}

void prph_bleuart_rx_callback(void)
    {
      // Forward data from Mobile to our peripheral
      char str[20+1] = { 0 };
      bleuart.read(str, 20);
     
      Serial.print("[Prph] RX: ");
      Serial.println(str);  
     
      if ( clientUart.discovered() )
      {
        clientUart.print(str);
      }else
      {
        bleuart.println("[Prph] Central role not connected");
      }
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

void readMatrix() {
  for(int j = 0; j < ROWS; ++j) {

    //set the current row as OUPUT and LOW
    pinMode(rows[j], OUTPUT);
    digitalWrite(rows[j], LOW);

    //loops thru all of the columns
    for (int i = 0; i < COLS; ++i) {
      pinMode(columns[i], INPUT_PULLUP);

      auto pair = keys[j][i].aUpdate(digitalRead(columns[i]), millis(), j, i);
      
      if (pair != nullReport) {
        Serial.print("Pressed: ");
        Serial.print(pair[0]);
        Serial.print(' ');
        Serial.println(pair[1]);
        
        blehid.keyboardReport(pair[0], pair[1], 0, 0, 0, 0, 0);  
        
        isReportedReleased = false;
      }
      else if (!isReportedReleased) {
        
        blehid.keyRelease();
        isReportedReleased = true;
      }
      
      //'disables' the column that just got looped thru
      pinMode(columns[i], INPUT);
     }

    //'disables' the row that was just pressed
    pinMode(rows[j], INPUT);
   }

   if (Key::downPressed) {
          Serial.println("Pressed down");
          clientUart.println('d');
          isFirstLayer = false;
        }
    else if (!isFirstLayer) {
        Serial.println("Released down");
          clientUart.println('n');
          isFirstLayer = true;
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  readMatrix(); 

  waitForEvent();
}
void rtos_idle_callback(void)
{
  // Don't call any other FreeRTOS blocking API()
  // Perform background task(s) here
}

void scan_callback(ble_gap_evt_adv_report_t* report)
{
  // Check if advertising contain BleUart service3
  if ( Bluefruit.Scanner.checkReportForService(report, clientUart) )
  {
    Serial.print("BLE UART service detected. Connecting ... ");
 
    // Connect to device with bleuart service in advertising
    Bluefruit.Central.connect(report);
  }
}


