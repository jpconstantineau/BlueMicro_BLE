
#include <utility>
#include <cstdint>
#include <vector>
#include <algorithm>


namespace std {
  void __throw_length_error(char const*) {
  }
}



//*************************************************************************
uint8_t testlink(uint8_t setpin, uint8_t readpin)
{
  uint8_t result = 0;
  pinMode(setpin, OUTPUT);
  pinMode(readpin, INPUT_PULLDOWN);
  digitalWrite(setpin, LOW);
  uint8_t initial = digitalRead(readpin);
  digitalWrite(setpin, HIGH);
  uint8_t final = digitalRead(readpin);
  pinMode(setpin, INPUT);
  pinMode(readpin, INPUT);
  if (!initial)
  {
    result =final*1;
  }
  return result;
  
}
//*************************************************************************
void matrix_key_init_separator(bool singlekey)
{
  Serial.println("-----------------------------------------------------------------");
}
//*************************************************************************
void matrix_key_init(bool singlekey)
{
  matrix_key_init_separator(singlekey);
  if (singlekey)
  {
    Serial.println("                  KEY in a MATRIX GPIO TESTER");
  }
  else
  {
    Serial.println("                       MATRIX GPIO TESTER");
  }
  matrix_key_init_separator(singlekey);
  Serial.println("Press each key for 1 second, one at a time");
  if(!singlekey)
  {
      Serial.println("GPIO Data will only be updated when new rows/columns are detected");
      Serial.println("The order shown will be depend on the sequence of keys you press");
  }
  Serial.println("Diode Pins: Cathode = Positive, Anode = Negative");
  matrix_key_init_separator(singlekey);
  Serial.println("   if DIODE_DIRECTION = COL2ROW");
  Serial.println("      POS = MATRIX_COL_PINS"); 
  Serial.println("      NEG = MATRIX_ROW_PINS");  
  Serial.println("   else // DIODE_DIRECTION = ROW2COL");
  Serial.println("      POS = MATRIX_ROW_PINS");
  Serial.println("      NEG = MATRIX_COL_PINS"); 
  matrix_key_init_separator(singlekey);
  Serial.println("If GPIOs are shown on both POS and NEG, ");
  Serial.println("you have a wire/short between these GPIOs and not a diode");
  matrix_key_init_separator(singlekey);
  Serial.println("Send a key through serial to end test");
  Serial.println("If you are in the Serial Monitor of the Arduino IDE, press Send");
  matrix_key_init_separator(singlekey);
}

void matrix_key_end(bool singlekey)
{
  matrix_key_init_separator(singlekey);
  Serial.println("Done");
  matrix_key_init_separator(singlekey);
}

//*************************************************************************
void matrix_key_test(bool singlekey)
{
    #ifdef NRF52840_XXAA
    // below tests all nrf52840 GPIOs except 32kHz xtal and reset
    uint8_t pins[]    = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,  19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47   };
    
    #else
    // below tests all nrf52832 GPIOs except 32kHz xtal and reset
    uint8_t pins[]    = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31   };
    #endif

    uint8_t pincount = sizeof(pins)/sizeof(pins[0]);
    
    static  std::vector<uint8_t> pospins; 
    static  std::vector<uint8_t> negpins; 
  while (Serial.available() == 0)
  {
    if(singlekey){
      pospins.clear();
      negpins.clear();    
    }
    
    bool updated = false;
      for (uint8_t i=0; i<pincount; i++)
      {
        for (uint8_t j=0; j<pincount; j++)
        {
        if (testlink(pins[i],pins[j]))
          {
             auto it = std::find(pospins.begin(), pospins.end(), pins[i]);
                        if (it != pospins.end())
                        {
                            // do nothing
                        }
                        else
                        {
                          pospins.push_back(pins[i]);
                          updated = true;
                        }
                     it = std::find(negpins.begin(), negpins.end(), pins[j]);
                        if (it != negpins.end())
                        {
                            // do nothing
                        }
                        else
                        {
                          negpins.push_back(pins[j]);
                          updated = true;
                        }      
          }
        }
      }

      if (updated)
      {
        Serial.print("POS: {"); 
        for (uint8_t gpio : pospins) 
        {
          Serial.print(gpio);
          Serial.print(","); 
        }
        Serial.println("}"); 
        Serial.print("NEG: {");
        for (uint8_t gpio : negpins) 
        {
          Serial.print(gpio);
          Serial.print(","); 
        }
        Serial.println("}");  
      }
  }
  while (Serial.available() > 0)
  {
      Serial.read();
  }
      pospins.clear();//clear up the buffers in case we test again
      negpins.clear(); 
}


//*************************************************************************
void setup() 
{
  Serial.begin(115200);
  while ( !Serial ) delay(10);   // for nrf52840 with native usb



}
//*************************************************************************
void loop()
{
  matrix_key_init(true);
matrix_key_test(true);
matrix_key_end(true);

delay(2000);
}
