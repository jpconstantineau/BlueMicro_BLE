

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

  Serial.println("GPIO TESTER");
  Serial.println("-------------------------------\n");

}


void loop()
{

 Serial.println(); 
Serial.println("i\tGPIO\tGPIO\tFloat \tP.Up \tP.Down\tstatus"); 
  


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
  #ifdef NRF52840_XXAA
delay(200);
#else
delay(1000);
#endif

}
