
#include <utility>
#include <cstdint>
#include <vector>
#include <algorithm>

 std::vector<uint8_t> pospins; 
 std::vector<uint8_t> negpins; 
namespace std {
  void __throw_length_error(char const*) {
  }
}
#ifdef NRF52840_XXAA
  #ifdef ARDUINO_NICE_NANO
  //Use this for nicenano - 14 and 16 are connected to 18 - reset line
  uint8_t pins[]    = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,  15,  17,  19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47   };
  #else
  // below tests all nrf52840 GPIOs except 32kHz xtal and reset
  uint8_t pins[]    = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,  19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47   };
  #endif
#else
  // below tests all nrf52832 GPIOs except 32kHz xtal and reset
  uint8_t pins[]    = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31   };
#endif

uint8_t pincount = sizeof(pins)/sizeof(pins[0]);



void setup() 
{
  Serial.begin(115200);
  while ( !Serial ) delay(10);   // for nrf52840 with native usb
  Serial.println("-----------------------------------------------------------------");
  Serial.println("                       MATRIX GPIO TESTER");
  Serial.println("-----------------------------------------------------------------");
  Serial.println("Press each key for 1 second, one at a time");
  Serial.println("GPIO Data will only be updated when new rows/columns are detected");
  Serial.println("The order shown will be depend on the sequence of keys you press");
  Serial.println("Diode Pins: Cathode = Positive, Anode = Negative");
  Serial.println("-----------------------------------------------------------------");
  Serial.println("   if DIODE_DIRECTION = COL2ROW");
  Serial.println("      POS = MATRIX_COL_PINS"); 
  Serial.println("      NEG = MATRIX_ROW_PINS");  
  Serial.println("   else // DIODE_DIRECTION = ROW2COL");
  Serial.println("      POS = MATRIX_ROW_PINS");
  Serial.println("      NEG = MATRIX_COL_PINS"); 
  Serial.println("-----------------------------------------------------------------");
  Serial.println("If GPIOs are shown on both POS and NEG, ");
  Serial.println("you have a wire/short between these GPIOs and not a diode");
  Serial.println("-----------------------------------------------------------------");
  


}

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

void loop()
{

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

 

/*
  // set up pin as input
  for (uint8_t i=0; i<pincount; i++)
  {
    pinMode(pins[i], INPUT);
    Serial.print(i);
    Serial.print("\t"); 
    Serial.print(pins[i]);
    Serial.print("\t");
    if (pins[i]<32)
    {
      Serial.print("P0.");
      Serial.print(pins[i]);
    }else
    {
            Serial.print("P1.");
      Serial.print(pins[i]-32);
     }
    Serial.print("\t");
    uint8_t rinfloat = digitalRead(pins[i]);
    Serial.print(rinfloat);
    Serial.print("\t"); 
    pinMode(pins[i], INPUT_PULLUP);
    uint8_t rinup = digitalRead(pins[i]);
    Serial.print(rinup);
    Serial.print("\t"); 
    pinMode(pins[i], INPUT_PULLDOWN);
    uint8_t rindown = digitalRead(pins[i]);
    Serial.print(rindown);
    Serial.print("\t");
    if (rinup == 0)
    {
      Serial.print("GND\t");
    }
    else
    {
      if (rindown == 1)
     {
        Serial.print("VCC\t");
     }
     else
     {
      Serial.print(".\t");
     }
    }
    if (pins[i]<2) {Serial.print("XTAL\t");}
    if (pins[i]==9) {Serial.print("NFC1\t");}
    if (pins[i]==10) {Serial.print("NFC2\t");}
    #ifdef NRF52840_XXAA
    if (pins[i]==32) {Serial.print("SWO(840)\t");}
    if (pins[i]==18) {Serial.print("RESET(840)\t");}
    #else
    if (pins[i]==21) {Serial.print("RESET(832)\t");}
    if (pins[i]==18) {Serial.print("SWO(832)\t");}
    #endif
    Serial.println("\t"); 
    
  }
*/


delay(200);


}
