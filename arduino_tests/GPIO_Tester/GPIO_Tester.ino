

        #define D3      6  
        #define D2      8   
        #define D1      15  
        #define D0      17  
        #define D4      20
        #define C6      13
        #define D7      24
        #define E6      9
        #define B4      10
        #define B5      38 //1.06 = 32+6

        #define F4      30
        #define F5      26  
        #define F6      29
        #define F7      2
        #define B1      45 //1.13  = 32+13
        #define B3      3
        #define B2      28
        #define B6      43 //1.11 = 32+11
        #define BLUE_LED 32+10
        #define RED_LED 32+4
        #define LED_RED 32+4

// below tests mapped GPIOs in order above
//uint8_t pins[]    = { D3, D2, D1, D0, D4, C6, D7, E6, B4, B5, F4, F5, F6, F7, B1, B3, B2, B6   };


// below tests all nrf52840 GPIOs except 32kHz xtal and reset
uint8_t pins[]    = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,  19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47   };

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
delay(10);

    

}
