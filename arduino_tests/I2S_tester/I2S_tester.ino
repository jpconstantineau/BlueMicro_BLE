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
#include "WS2812.h"









static uint32_t m_buffer_tx[I2S_BUFFER_SIZE];
static volatile int nled = 1;
SoftwareTimer keyscanTimer;

  // Sine table (stereo, so every value is duplicated)
  int16_t sine_table[] = { 0, 0, 23170, 23170, 32767, 32767, 23170, 23170, 0, 0, -23170, -23170, -32768, -32768, -23170, -23170};

    // This array cannot be allocated on stack (hence "static") and it must
    // be in RAM.
volatile uint8_t g_demo_mode = 0;
//volatile bool g_i2s_start = true;
//volatile bool g_i2s_running = false;

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
  

  // Create additional loops using Scheduler to run in 'parallel' with loop()
  Scheduler.startLoop(backgroundloop);
  Scheduler.startLoop(monitoringloop);
  keyscanTimer.begin(1, keyscan_timer_callback); // runs the keyscan every millisecond.
  keyscanTimer.start(); // Start the timer


  
  Bluefruit.begin();
  // Set max power. Accepted values are: -40, -30, -20, -16, -12, -8, -4, 0, 4
  Bluefruit.setTxPower(4);
  Bluefruit.setName("BlueMicroTester");
  Bluefruit.setConnectCallback(connect_callback);
  Bluefruit.setDisconnectCallback(disconnect_callback);


  // Configure and Start Battery Service
  blebas.begin();
  blebas.write(100); // put the battery level at 100% - until it is updated by the battery monitoring loop.
    
  startAdv(); // Set up and start advertising
  

//g_i2s_start = true;
 setuprgb();
 rgb();
}


//********************************************************************************************//
//* High Priority Task - runs key scanning - called every ms (timing not guaranteed)         *//
//********************************************************************************************//
void keyscan_timer_callback(TimerHandle_t xTimerID)
{
  // freeRTOS timer ID, ignored if not used
  (void) xTimerID;

}

//#define PIN_MCK    (24) //MOSI = B2
#define PIN_SCK    (22) //MISO = B3
#define PIN_LRCK   (20) // = B4
#define PIN_SDOUT  (11) // = B
uint32_t calcChannelValue(uint8_t level)
{
    uint32_t val = 0;

    // 0 
    if(level == 0) {
        val = 0x88888888;
    }
    // 255
    else if (level == 255) {
        val = 0xeeeeeeee;
    }
    else {
        // apply 4-bit 0xe HIGH pattern wherever level bits are 1.
        val = 0x88888888;
        for (uint8_t i = 0; i < 8; i++) {
            if((1 << i) & level) {
                uint32_t mask = ~(0x0f << 4*i);
                uint32_t patt = (0x0e << 4*i);
                val = (val & mask) | patt;
            }
        }

        // swap 16 bits
        val = (val >> 16) | (val << 16);
    }

    return val;
}
void set_led_data(uint8_t val)
{
    for(int i = 0; i < 3*NLEDS; i += 3) {
        if (i == 3*nled) {
            switch(g_demo_mode) 
            {
                case 0:
                {
                    m_buffer_tx[i] = 0x88888888;
                    m_buffer_tx[i+1] = calcChannelValue(val);
                    m_buffer_tx[i+2] = 0x88888888;
                }
                break;
                case 1:
                {
                    m_buffer_tx[i] = calcChannelValue(val);;
                    m_buffer_tx[i+1] = 0x88888888;
                    m_buffer_tx[i+2] = 0x88888888;
                }
                break;
                case 2:
                {
                    m_buffer_tx[i] = 0x88888888;
                    m_buffer_tx[i+1] = 0x88888888;
                    m_buffer_tx[i+2] = calcChannelValue(val);
                }
                break;
                default:
                break;
            }
        }
        else {
            m_buffer_tx[i] = 0x88888888;
            m_buffer_tx[i+1] = 0x88888888;
            m_buffer_tx[i+2] = 0x88888888;
        }
    }

    // reset 
    for(int i = 3*NLEDS; i < I2S_BUFFER_SIZE; i++) {
        m_buffer_tx[i] = 0;
    }
    //rgb();
}


void setuprgb(void)
{
  NRF_I2S->CONFIG.TXEN = (I2S_CONFIG_TXEN_TXEN_ENABLE << I2S_CONFIG_TXEN_TXEN_Pos);                       // Enable transmission
  NRF_I2S->CONFIG.MCKEN = (I2S_CONFIG_MCKEN_MCKEN_ENABLE << I2S_CONFIG_MCKEN_MCKEN_Pos);                  // Enable MCK generator
  NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV10  << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;       // MCKFREQ = 3.2 MHz
  NRF_I2S->CONFIG.RATIO = I2S_CONFIG_RATIO_RATIO_32X << I2S_CONFIG_RATIO_RATIO_Pos;                       // Ratio = 32
  NRF_I2S->CONFIG.MODE = I2S_CONFIG_MODE_MODE_MASTER << I2S_CONFIG_MODE_MODE_Pos;                         // Master mode, 16Bit, left aligned
  NRF_I2S->CONFIG.SWIDTH = I2S_CONFIG_SWIDTH_SWIDTH_16BIT << I2S_CONFIG_SWIDTH_SWIDTH_Pos;
  NRF_I2S->CONFIG.ALIGN = I2S_CONFIG_ALIGN_ALIGN_LEFT << I2S_CONFIG_ALIGN_ALIGN_Pos;
  NRF_I2S->CONFIG.FORMAT = I2S_CONFIG_FORMAT_FORMAT_I2S << I2S_CONFIG_FORMAT_FORMAT_Pos;                  // Format = I2S 
  NRF_I2S->CONFIG.CHANNELS = I2S_CONFIG_CHANNELS_CHANNELS_STEREO << I2S_CONFIG_CHANNELS_CHANNELS_Pos;     // Use stereo
  

  NRF_I2S->PSEL.MCK = 0xFF;//(PIN_MCK << I2S_PSEL_MCK_PIN_Pos)|                                           // Configure pins   //(I2S_PSEL_MCK_CONNECT_Disconnected   << I2S_PSEL_MCK_CONNECT_Pos);                
  NRF_I2S->PSEL.SCK = (PIN_SCK << I2S_PSEL_SCK_PIN_Pos)| 
                      (I2S_PSEL_SCK_CONNECT_Connected  << I2S_PSEL_SCK_CONNECT_Pos);                      /// must be connected - however we don't need it for RGB LEDs.  recommend using p0.23 when we have these pins unused
  NRF_I2S->PSEL.LRCK = (PIN_LRCK << I2S_PSEL_LRCK_PIN_Pos)| 
                       (I2S_PSEL_LRCK_CONNECT_Connected  << I2S_PSEL_LRCK_CONNECT_Pos);                   /// must be connected - however we don't need it for RGB LEDs. recommend using p0.24 when we have these pins unused
  NRF_I2S->PSEL.SDOUT = (PIN_SDOUT << I2S_PSEL_SDOUT_PIN_Pos)| 
                       (I2S_PSEL_SDOUT_CONNECT_Connected   << I2S_PSEL_SDOUT_CONNECT_Pos);                /// must be connected - this is the data line for the RGB LEDs
  NRF_I2S->ENABLE = 1;
  // Since we are not updating the TXD pointer, the sine wave will play over and over again.
  // The TXD pointer can be updated after the EVENTS_TXPTRUPD arrives. 
}



void rgb(void)
{

  // Configure data pointer
  NRF_I2S->TXD.PTR = (uint32_t)&m_buffer_tx[0];
  NRF_I2S->RXTXD.MAXCNT = sizeof(m_buffer_tx) / sizeof(uint32_t);
  NRF_I2S->TASKS_START = 1;       // Start transmitting I2S data
}
//********************************************************************************************//
//* Main Loop Task - runs Display updates                                                    *//
// for some reason, oled functions only work from the main loop.
//********************************************************************************************//

void loop()
{
 
g_demo_mode = 0;
//delay(100);
//g_demo_mode = 1;
//delay(10000);
//g_demo_mode = 2;
//delay(10000);
               
            

if(NRF_I2S->EVENTS_TXPTRUPD  != 0)
{
  rgbval++;
  nled = (nled + 1) % NLEDS; 
  set_led_data(rgbval);
    NRF_I2S->TXD.PTR = (uint32_t)&m_buffer_tx[0];
    NRF_I2S->EVENTS_TXPTRUPD = 0;
    NRF_I2S->TASKS_START = 1;
}
if (rgbval>200){rgbval=0;}
            

        
}

//********************************************************************************************//
//* Background Task - runs  *//
//********************************************************************************************//
void backgroundloop()
{
  
}

//********************************************************************************************//
//* Battery Monitoring Task - runs infrequently - except in boot mode                        *//
//********************************************************************************************//
void monitoringloop()
{

}

//********************************************************************************************//
//* Idle Task - runs when there is nothing to do                                             *//
//* Any impact of placing code here on current consumption?                                  *//
//********************************************************************************************//
void rtos_idle_callback(void)
{
  // Don't call any other FreeRTOS blocking API()
  // Perform background task(s) here
}
