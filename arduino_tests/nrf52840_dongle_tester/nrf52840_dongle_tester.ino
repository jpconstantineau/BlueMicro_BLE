/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN takes care 
  of use the correct LED pin whatever is the board used.
  If you want to know what pin the on-board LED is conn
  ected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
*/

// the setup function runs once when you press reset or power the board
void setup() {
// this is the code needed to change the default voltage from the on chip voltage regulator.
// see https://infocenter.nordicsemi.com/pdf/nRF52840_PS_v1.0.pdf page 45

if (NRF_UICR->REGOUT0 != UICR_REGOUT0_VOUT_3V3) {
    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
    NRF_UICR->REGOUT0 = UICR_REGOUT0_VOUT_3V3;

    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
        delay(500);
        NVIC_SystemReset();
      }

  
  pinMode(32+10, OUTPUT);
    pinMode(32+4, OUTPUT);
}
     
// the loop function runs over and over again forever
void loop() {
  digitalToggle(32+10); // turn the LED on (HIGH is the voltage level)
  digitalToggle(32+4); // turn the LED on (HIGH is the voltage level)
  delay(1000);                // wait for a second
}
