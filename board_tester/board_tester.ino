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

#define D3      17  //
#define D2      7   //
#define D1      25  //sda
#define D0      26  //scl
#define D4      27
#define C6      28
#define D7      29
#define E6      30
#define B4      15
#define B5      16

#define F4      5
#define F5      4
#define F6      3
#define F7      2
#define B1      12  //sck
#define B3      14  //miso
#define B2      13  //mosi
#define B6      11

#define PINCOUNT1 18
#define PINCOUNT2 18
#define PINCOUNT3 19

BLEDis bledis;
BLEHidAdafruit blehid;

int pinlist1 [PINCOUNT1] ={ D3, D2, D1, D0, D4, C6, D7, E6, B4, B5, F4, F5, F6, F7, B1, B3, B2, B6};
int pinlist2 [PINCOUNT2] ={ D3, F4, D2, F5, D1, F6, D0, F7, D4, B1, C6, B3, D7, B2, E6, B6, B4, B5};
int pinlist3 [PINCOUNT3] ={ D3, F4, D2, F5, D1, F6, D0, F7, D4, B1, C6, B3, D7, B2, E6, B6, B4,B6, B5};

void setup() 
{
  Serial.begin(115200);

  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("BlueMicroHID");
  bledis.setManufacturer("jpconstantineau.com");
  bledis.setModel("BlueMicro Tester");
  bledis.begin();
  blehid.begin();
  startAdv();
}

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
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds

  for (int i = 0; i< PINCOUNT1; i++ )
  {
    pinMode(pinlist1[i], OUTPUT);
  }
  
}

void flashpin(int pinno)
{
  digitalWrite(pinno, LOW); delay(100); digitalWrite(pinno, HIGH);  delay(100);digitalWrite(pinno, LOW); 
  }

void loop() 
{
sd_power_dcdc_mode_set(NRF_POWER_DCDC_DISABLE);
    for (int i = 0; i< PINCOUNT1; i++ )
  {
    flashpin(pinlist1[i]);
  }                        
/*      for (int i = 0; i< PINCOUNT2; i++ )
  {
    flashpin(pinlist2[i]);
  }*/ 
  for (int i = 0; i< PINCOUNT3; i++ )
  {
    flashpin(pinlist3[i]);
  } 


sd_power_dcdc_mode_set(NRF_POWER_DCDC_ENABLE);
    for (int i = 0; i< PINCOUNT1; i++ )
  {
    flashpin(pinlist1[i]);
  }                        
/*      for (int i = 0; i< PINCOUNT2; i++ )
  {
    flashpin(pinlist2[i]);
  }*/ 
  for (int i = 0; i< PINCOUNT3; i++ )
  {
    flashpin(pinlist3[i]);
  } 
 
}

/**
 * RTOS Idle callback is automatically invoked by FreeRTOS
 * when there are no active threads. E.g when loop() calls delay() and
 * there is no bluetooth or hw event. This is the ideal place to handle
 * background data.
 * 
 * NOTE: FreeRTOS is configured as tickless idle mode. After this callback
 * is executed, if there is time, freeRTOS kernel will go into low power mode.
 * Therefore waitForEvent() should not be called in this callback.
 * http://www.freertos.org/low-power-tickless-rtos.html
 * 
 * WARNING: This function MUST NOT call any blocking FreeRTOS API 
 * such as delay(), xSemaphoreTake() etc ... for more information
 * http://www.freertos.org/a00016.html
 */
void rtos_idle_callback(void)
{
  // Don't call any other FreeRTOS blocking API()
  // Perform background task(s) here
}
