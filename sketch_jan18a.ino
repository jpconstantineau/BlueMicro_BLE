
#include <bluefruit.h>

class Key {
  public:
    Key() {
      pressed = false;
      pressedTime = 400;
      previousMillis = 0;
      }

    bool update(const int& currentState) {
        unsigned long currentMillis = millis();

        //if currently being pressed and delta t is larger than the amount of time that the key shouldn't be pressed for
        if (currentState == 0 && (currentMillis - previousMillis) >= pressedTime) {
          previousMillis = currentMillis;
          pressedTime = 300;
          
          return true;
          }

        else if (currentState == 1) {
          pressedTime = 50;
          
          return false;
        }  
        else 
          return false;
      } 
  private:
    unsigned long pressedTime;
    unsigned long previousMillis;
    bool pressed;  
};

int row1 = 26;
int row2 = 27;
int row3 = 28;
int row4 = 21;
int val;

BLEDis bledis;
BLEHidAdafruit blehid;

byte rows[] { 12, 13, 14, 16 };
byte columns[] { 2, 3, 4, 5, 28, 29};

byte COLS = 6;
byte ROWS = 4;

/*int firstLayer[4][6] = {
  {0, 113, 119, 101, 114, 116},
  {0, 97, 115, 100, 102, 103},
  {0, 122, 120, 99, 118, 98},
  {0, 0, 0, 0, 0, 0}
  };*/

int firstLayer[4][6] {
  {116, 114, 101, 119, 113, 27}, 
  {103, 102, 100, 115, 97, 9}, 
  {98, 118, 99, 120, 122, 15},
  {0, 0, 0, 0, 0, 0}
  };

Key keys[4][6];
  
void setup() {
  // put your setup code here, to run once:
  
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
  Bluefruit.setName("Bluefruit52");

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
  blehid.begin();

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
  for(int j(0); j < ROWS; ++j) {

    //set the current row as OUPUT and LOW
    pinMode(rows[j], OUTPUT);
    digitalWrite(rows[j], LOW);

    //loops thru all of the columns
    for (int i(0); i < COLS; ++i) {
      pinMode(columns[i], INPUT_PULLUP);
      
      //just a testing to see if a button was pressed
      /*if (digitalRead(columns[i]) == LOW) {
        Serial.print("LOW: "); Serial.print(columns[i]); Serial.print(", "); Serial.println(rows[j]);
        Serial.println(firstLayer[j][i]);
        
      }*/
      if (keys[j][i].update(digitalRead(columns[i]))) {

        char entered = firstLayer[j][i];
        Serial.print("Pressed: "); Serial.println(entered);
        blehid.keyPress(entered);

        delay(5);

        blehid.keyRelease();
        }

      //'disables' the column that just got looped thru
      pinMode(columns[i], INPUT);
      }

    //'disables' the row that was just pressed
    pinMode(rows[j], INPUT);
    }  
}

void loop() {
  // put your main code here, to run repeatedly:
  readMatrix(); 

  
  /*if ( hasKeyPressed )
  {
    hasKeyPressed = false;
    blehid.keyRelease();
    
    // Delay a bit after a report
    delay(5);
  }
    
  if (Serial.available())
  {
    char ch = (char) Serial.read();

    // echo
    Serial.write(ch); 

    blehid.keyPress(ch);
    hasKeyPressed = true;
    
    // Delay a bit after a report
    delay(5);
  }

  // Request CPU to enter low-power mode until an event/interrupt occurs
void rtos_idle_callback(void)
{
  // Don't call any other FreeRTOS blocking API()
  // Perform background task(s) here
}  waitForEvent();*/  
  waitForEvent();
}
void rtos_idle_callback(void)
{
  // Don't call any other FreeRTOS blocking API()
  // Perform background task(s) here
}
  
