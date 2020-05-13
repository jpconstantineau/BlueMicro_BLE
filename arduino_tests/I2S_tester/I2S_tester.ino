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

#include <bluefruit.h>
//#include "WS2812.h"
#include "I2S.h"

uint8_t rgbval=0;


rgb_led_t led_array[NLEDS];




/**************************************************************************************************************************/
// Battery Service and functions
BLEBas blebas;


/**************************************************************************************************************************/
// Start Advertizing Bluetooth Services 
void startAdv(void)
{
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
}


/**************************************************************************************************************************/
// Connect Callback
void connect_callback(uint16_t conn_handle)
{
 //connection_state = STATE_CONNECTED;
}


/**************************************************************************************************************************/
// Disconnect Callback
void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;

//  connection_state = STATE_DISCONNECTED;
}


//********************************************************************************************//
void setup()
{

Serial.begin(115200);
    // this code enables the NFC pins to be GPIO.
     if ((NRF_UICR->NFCPINS & UICR_NFCPINS_PROTECT_Msk) == (UICR_NFCPINS_PROTECT_NFC << UICR_NFCPINS_PROTECT_Pos)){
       // Serial.println("Fix NFC pins");
        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy);
        NRF_UICR->NFCPINS &= ~UICR_NFCPINS_PROTECT_Msk;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy);
        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy);
        //Serial.println("Done");
        delay(500);
        
        NVIC_SystemReset();
      } // end of NFC switch code.
  

  
  Bluefruit.begin();
  // Set max power. Accepted values are: -40, -30, -20, -16, -12, -8, -4, 0, 4
  Bluefruit.setTxPower(4);
  Bluefruit.setName("BlueMicroTester");
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);


  // Configure and Start Battery Service
  blebas.begin();
  blebas.write(100); // put the battery level at 100% - until it is updated by the battery monitoring loop.
    
  startAdv(); // Set up and start advertising

Serial.println("setup setup rgb");
   setuprgb();

}






//********************************************************************************************//
//* Main Loop Task - runs Display updates                                                    *//
//********************************************************************************************//
void loop()
{
  //Serial.println("loop");
  if(!rgbCheckStatus())
  {
   // Serial.println("update RGB");

    for(int i = 0; i < NLEDS; i++)
    {
      led_array[i].red = rgbval;
      led_array[i].green = rgbval;
      led_array[i].blue = rgbval;
    }
  
      copy_led_data(led_array);
      rgbval=rgbval+1;
      if (rgbval>128+64){rgbval=0;} 
      rgbstart();
     // delay(250);
  }
  
}
