/*********************************************************************
 This is an example for our nRF52 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

#include <Arduino.h>
#include "RotaryEncoder.h"



#define PIN_A     30 //ROW 1
#define PIN_B     26 //ROW 2



SwRotaryEncoder swEncoder;

void setup()
{
  Serial.begin(115200);
  while ( !Serial ) delay(10);   // for nrf52840 with native usb

  Serial.println("Bluefruit52 SW Rotary Encoder Callback Example");
  Serial.println("----------------------------------------------\n");

  // Initialize Encoder
  swEncoder.begin(PIN_A, PIN_B);
  swEncoder.setCallback(encoder_callback);

}

void loop()
{
  // do nothing
}

void encoder_callback(int step)
{
  if ( step > 0 )
  {
    Serial.print(step);
    Serial.println("Right");
  }else
  {
    Serial.print(step);
    Serial.println("Left");
  }
}
