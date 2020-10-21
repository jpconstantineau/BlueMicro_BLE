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




//BlueMacro
uint8_t pins[]    = {43, 3,28,45,30,2,29,26,6,5,8,41,4,12   ,38,10,9,20,17,15,13,22,24,32,7 , 36, 42  };
uint8_t pincount = sizeof(pins)/sizeof(pins[0]);

BLEDis bledis;
BLEHidAdafruit blehid;

void setup() 
{
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

  Serial.begin(115200);
 // while ( !Serial ) delay(10);   // for nrf52840 with native usb
  
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("BlueMicro840");
  bledis.setManufacturer("jpconstantineau.com");
  bledis.setModel("BlueMicro Tester");
  bledis.begin();
  blehid.begin();
  startAdv();




    for (int i = 0; i< pincount; i++ )
  {
    pinMode(pins[i], OUTPUT);
  }
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

  
}

void flashpin(int pinno)
{
  digitalWrite(pinno, LOW); delay(100); digitalWrite(pinno, HIGH);  delay(100);digitalWrite(pinno, LOW); 
  }

void loop() 
{

    for (int i = 0; i< pincount; i++ )
  {
    flashpin(pins[i]);
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
    Serial.println("\t"); 
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
