/*
Copyright 2018-2020 <Pierre Constantineau, Julian Komaromy>

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
#include "debug_cli.h"

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
void helpline(void)
{
         Serial.println("");
        Serial.println("Type 'h' to get a list of commands with descriptions");
}
//*************************************************************************
void matrix_key_init(bool singlekey)
{
  while (Serial.available() > 0)
  {
      Serial.read(); // clean up serial buffer
  }
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
  helpline();
}

//*************************************************************************
void matrix_key_test(bool singlekey)
{
    #ifdef NRF52840_XXAA
    // below tests all nrf52840 GPIOs except 32kHz xtal and reset
    #ifdef NICENANO // 14 and 16 are connected to 18 - reset line
      uint8_t pins[]    = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 17, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47   };
    #else
      uint8_t pins[]    = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,  19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47   };
    #endif
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


/**************************************************************************************************************************/
void gpiotester(){
    keyscantimer.stop();
  batterytimer.stop();
    #ifdef NRF52840_XXAA
    // below tests all nrf52840 GPIOs except 32kHz xtal and reset
    #ifdef NICENANO // 14 and 16 are connected to 18 - reset line
      uint8_t pins[]    = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 17, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47   };
    #else
      uint8_t pins[]    = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,  19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47   };
    #endif
    #else
    // below tests all nrf52832 GPIOs except 32kHz xtal and reset
    uint8_t pins[]    = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    #endif
uint8_t pincount = sizeof(pins)/sizeof(pins[0]);
  Serial.println("GPIO TESTER");
  Serial.println("-------------------------------\n");
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
    keyscantimer.start();
  batterytimer.start();
}
/**************************************************************************************************************************/
void handleSerial() {
    char buffer [50];
  uint8_t intval;
 while (Serial.available() > 0) {
   char incomingCharacter = Serial.read();
   switch (incomingCharacter) {
     case 'd':
        enterSerialDfu();
      break;
 

     case 'b':
        Serial.println("Clear Bonds");
        Serial.println("-------------------------------\n");

        Serial.println();
        Serial.println("----- Before -----\n");
        bond_print_list(BLE_GAP_ROLE_PERIPH);
        bond_print_list(BLE_GAP_ROLE_CENTRAL);
        #ifndef ARDUINO_NRF52_COMMUNITY
        Bluefruit.clearBonds();
        #endif
        Bluefruit.Central.clearBonds();

        Serial.println();
        Serial.println("----- After  -----\n");
        
        bond_print_list(BLE_GAP_ROLE_PERIPH);
        bond_print_list(BLE_GAP_ROLE_CENTRAL);
      break;

     case 'r':
           NVIC_SystemReset();
      break;
    case 'e':
      InternalFS.format();
      break;
    case 'u':
      enterUf2Dfu();
      break;
     case 'i':
          Serial.println("Bluefruit 52 HW Info");
          Serial.println("");
          // Unique Device ID
          Serial.print("Device ID  : ");
          Serial.print(DEVICE_ID_HIGH, HEX);
          Serial.println(DEVICE_ID_LOW, HEX);

          // MCU Variant;
          Serial.printf("MCU Variant: nRF%X 0x%08X\n",NRF_FICR->INFO.PART, NRF_FICR->INFO.VARIANT);
          Serial.printf("Memory     : Flash = %d KB, RAM = %d KB\n", NRF_FICR->INFO.FLASH, NRF_FICR->INFO.RAM);

      Serial.println("Keyboard Name  : " DEVICE_NAME " "); 
      Serial.println("Keyboard Model : " DEVICE_MODEL " "); 
      Serial.println("Keyboard Mfg   : " MANUFACTURER_NAME " "); 

      Serial.println("");

      sprintf(buffer,"Device Power   : %f", DEVICE_POWER*1.0);
      Serial.println(buffer);
      sprintf(buffer,"Filter RSSI  : %i", FILTER_RSSI_BELOW_STRENGTH); Serial.println(buffer);  
      Serial.println("Type\t RSSI\t name"); 
      sprintf(buffer,"cent\t %i\t %s",keyboardstate.rssi_cent, keyboardstate.peer_name_cent);Serial.println(buffer);  
      sprintf(buffer,"prph\t %i\t %s",keyboardstate.rssi_prph, keyboardstate.peer_name_prph);Serial.println(buffer); 
      sprintf(buffer,"cccd\t %i\t %s",keyboardstate.rssi_cccd, keyboardstate.peer_name_cccd);Serial.println(buffer); 
      Serial.println("");
          dbgPrintVersion();
          dbgMemInfo();
      break;
      case ' ':
        Serial.println(" ____  _            __  __ _                   ____  _     _____ ");
        Serial.println("| __ )| |_   _  ___|  \\/  (_) ___ _ __ ___    | __ )| |   | ____|");
        Serial.println("|  _ \\| | | | |/ _ \\ |\\/| | |/ __| '__/ _ \\   |  _ \\| |   |  _|  ");
        Serial.println("| |_) | | |_| |  __/ |  | | | (__| | | (_) |  | |_) | |___| |___ ");
        Serial.println("|____/|_|\\__,_|\\___|_|  |_|_|\\___|_|  \\___/___|____/|_____|_____|");
        Serial.println("                                         |_____|                 ");
        helpline();
      break;
      case 'h':
              Serial.println("");
        Serial.println("b  Clear Bonds - Warning! Disconnects BLE from Computer!");
        Serial.println("d  Enter Serial DFU - Warning! Disconnects BLE from Computer!");
        Serial.println("u  Enter UF2 DFU - Warning! Disconnects BLE from Computer!");
        Serial.println("e  flash reset - Warning! Disconnects BLE from Computer!");
        Serial.println("r  reboot - Warning! Disconnects BLE from Computer!");



        Serial.println("i  Show Device Information");
        Serial.println("p  Show Battery Information");
        Serial.println("g  run GPIO Tester");
        Serial.println("m  full matrix gpio tester");
        Serial.println("k  single key matrix gpio tester");
                Serial.println("");
      break;
      case 'p':
            intval = batterymonitor.vbat_per;

      switch (batterymonitor.batt_type)
      {
        case BATT_UNKNOWN:
            snprintf (buffer, sizeof(buffer), "VDD = %.0f mV, VBatt = %.0f mV", batterymonitor.vbat_vdd*1.0, batterymonitor.vbat_mv*1.0);
        break;
        case BATT_CR2032:
            if (intval>99)
            {
              snprintf (buffer, sizeof(buffer), "VDD = %.0f mV (%4d %%)", batterymonitor.vbat_mv*1.0, intval);
            }
            else
            {
              snprintf (buffer, sizeof(buffer), "VDD = %.0f mV (%3d %%)", batterymonitor.vbat_mv*1.0, intval);
            }
            
        break;
        case BATT_LIPO:
            if (intval>99)
            {
              sprintf (buffer, "LIPO = %.0f mV (%4d %%)", batterymonitor.vbat_mv*1.0, intval);
            }
            else
            {
              sprintf (buffer, "LIPO = %.0f mV (%3d %%)", batterymonitor.vbat_mv*1.0, intval);
            }   
        break;
      }
      Serial.println(buffer);
      break;
      case 'g':
        gpiotester();
      break;
     case 'm':
            keyscantimer.stop();
            batterytimer.stop();
            matrix_key_init(false);
            matrix_key_test(false);
            matrix_key_end(false);
            keyscantimer.start();
            batterytimer.start();
      break;
     case 'k':
            keyscantimer.stop();
            batterytimer.stop();
            matrix_key_init(true);
            matrix_key_test(true);
            matrix_key_end(true);
            keyscantimer.start();
            batterytimer.start();
      break;
    }
 }
}