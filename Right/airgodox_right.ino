#include <bluefruit.h>
#undef min
#undef max
#include </home/julian/Arduino/sketch_feb20a/Key.h>

int row1 = 26;
int row2 = 27;
int row3 = 28;
int row4 = 21;
int val;

BLEUart bleuart;
BLEDis bledis;

byte rows[] { 16, 14, 13, 29 };
byte columns[] { 2, 3, 4, 5, 28, 12};

byte COLS = 6;
byte ROWS = 4;

Key keys[4][6];

bool isFirstLayer = true;

char currentChar = ' ';
char output[2] = {'0', '0'};
std::array<uint8_t, 2> nullReport {0, 0};

bool isReportedReleased = true;

void setup() {

  // put your setup code here, to run once:
  Key::startCurrentLayer();

  //should be the shift key, which is then set to be the shift key 
  keys[3][3].setSpecial(Key::SpecialKey::UP);
  keys[2][0].setSpecial(Key::SpecialKey::ALT);
  
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

  Bluefruit.begin();
  // Set max power. Accepted values are: -40, -30, -20, -16, -12, -8, -4, 0, 4
  Bluefruit.setTxPower(4);
  Bluefruit.setName("Airgo - dox (R)");

  // Configure and Start Device Information Service
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather 52");
  bledis.begin();

  /* Start BLE HID
   * Note: Apple requires BLE device must have min connection interval >= 20m
   * ( The smaller the connection interval the faster we could send data).
   * However for HID and MIDI device, Apple could accept min connection interval 
   * up to 11.25 ms. Therefore BLEHidAdafruit::begin() will try to set the min and max
   * connection interval to 11.25  ms and 15 ms respectively for best performance.
   */
  bleuart.begin();
  
  bleuart.setRxCallback(prph_bleuart_rx_callback);   

  /* Set connection interval (min, max) to your perferred value.
   * Note: It is already set by BLEHidAdafruit::begin() to 11.25ms - 15ms
   * min = 9*1.25=11.25 ms, max = 12*1.25= 15 ms 
   */
  Bluefruit.setConnInterval(9, 12);

  // Set up and start advertising
  startAdv(); 
};

void startAdv(void)
{  
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  // Include BLE HID service
  // Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addService(bleuart);

  // There is enough room for the dev name in the advertising packet
  //Bluefruit.Advertising.addName();
  
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

  std::array<uint8_t, 7> currentReport = {0, 0, 0, 0, 0, 0, 0};
  
  for(int j = 0; j < ROWS; ++j) {

    //set the current row as OUPUT and LOW
    pinMode(rows[j], OUTPUT);
    digitalWrite(rows[j], LOW);

    //loops thru all of the columns
    for (int i = 0; i < COLS; ++i) {
      pinMode(columns[i], INPUT_PULLUP);

      /*currentChar = keys[j][i].update(digitalRead(columns[i]), millis(), j, i);
      if ( currentChar != ' ' ) {
        //char entered = firstLayer.keyAt(j, i);
        Serial.print("Pressed: "); Serial.println(currentChar);
        blehid.keyPress(currentChar);
        //delay(2000);

        blehid.keyRelease();
        }*/

      auto pair = keys[j][i].aUpdate(digitalRead(columns[i]), millis(), j, i);

      /*Serial.print( (int) pair.second[0]); Serial.print(' ');
      Serial.print((int)pair.second[1]); Serial.print(' ');
      Serial.print((int)pair.second[2]); Serial.print(' ');
      Serial.print((int)pair.second[3]); Serial.print(' ');
      Serial.print((int)pair.second[4]); Serial.print(' ');
      Serial.println((int)pair.second[5]);
      //delay(2000);*/
      uint8_t str[3] = {0, pair[0], pair[1]};
      
      if (pair != nullReport) {
        Serial.print("Pressed: ");
        Serial.print(pair[0]);
        Serial.print(' ');
        Serial.println(pair[1]);
        
        Serial.print(str[0]);
        Serial.print(str[1]);
        Serial.println(str[2]);
          
        bleuart.write(str, 3);

        isReportedReleased = false;
      }
      else if (!isReportedReleased) {
        bleuart.write(str, 3);

        isReportedReleased = true;
      }
      //'disables' the column that just got looped thru
      pinMode(columns[i], INPUT);
     }

    //'disables' the row that was just pressed
    pinMode(rows[j], INPUT);

    if (Key::upPressed) {
          Serial.println("Pressed up");
          bleuart.write(1);
          isFirstLayer = false;
        }
    else if (!isFirstLayer) {
        Serial.println("Released up");
          bleuart.write(2);
          isFirstLayer = true;
    }
   }  
}

void loop() {
  // put your main code here, to run repeatedly:
  readMatrix(); 

  waitForEvent();
}
void rtos_idle_callback(void)
{
  // Don't call any other FreeRTOS blocking API()Serial.println("Set down layer");
  // Perform background task(s) here
}

void prph_bleuart_rx_callback(void)
    {
      // Forward data from Mobile to our peripheral
      char str[20+1] = { 0 };
      bleuart.read(str, 20);
     
      Serial.print("[Prph] RX: ");
      Serial.print(str);      

      if (*str == 'd') {
        Serial.println("Set down layer");
        Key::aCurrentLayer = &Key::downBLELayer;
        }
      else if (*str == 'n') {
        Serial.println("Set normal layer");
        Key::aCurrentLayer = &Key::firstBLELayer;
        }
      }
