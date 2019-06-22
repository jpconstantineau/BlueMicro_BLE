#include "I2S.h"
#include <Arduino.h>
#include <bluefruit.h>

    // This array cannot be allocated on stack (hence "static") and it must
    // be in RAM.
static uint32_t m_buffer_tx[I2S_BUFFER_SIZE];


void setuprgb(void)
{
   //Serial.println("setuprgb");
  NRF_I2S->CONFIG.TXEN = (I2S_CONFIG_TXEN_TXEN_ENABLE << I2S_CONFIG_TXEN_TXEN_Pos);                       // Enable transmission
  NRF_I2S->CONFIG.MCKEN = (I2S_CONFIG_MCKEN_MCKEN_ENABLE << I2S_CONFIG_MCKEN_MCKEN_Pos);                  // Enable MCK generator
  NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV10  << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;       // MCKFREQ = 3.2 MHz
  NRF_I2S->CONFIG.RATIO = I2S_CONFIG_RATIO_RATIO_32X << I2S_CONFIG_RATIO_RATIO_Pos;                       // Ratio = 32
  NRF_I2S->CONFIG.MODE = I2S_CONFIG_MODE_MODE_MASTER << I2S_CONFIG_MODE_MODE_Pos;                         // Master mode, 16Bit, left aligned
  NRF_I2S->CONFIG.SWIDTH = I2S_CONFIG_SWIDTH_SWIDTH_16BIT << I2S_CONFIG_SWIDTH_SWIDTH_Pos;
  NRF_I2S->CONFIG.ALIGN = I2S_CONFIG_ALIGN_ALIGN_LEFT << I2S_CONFIG_ALIGN_ALIGN_Pos;
  NRF_I2S->CONFIG.FORMAT = I2S_CONFIG_FORMAT_FORMAT_I2S << I2S_CONFIG_FORMAT_FORMAT_Pos;                  // Format = I2S 
  NRF_I2S->CONFIG.CHANNELS = I2S_CONFIG_CHANNELS_CHANNELS_STEREO << I2S_CONFIG_CHANNELS_CHANNELS_Pos;     // Use stereo
  

  NRF_I2S->PSEL.MCK = 0xFF;//(PIN_MCK << I2S_PSEL_MCK_PIN_Pos)|   (I2S_PSEL_MCK_CONNECT_Disconnected   << I2S_PSEL_MCK_CONNECT_Pos);        // Configure pins   //                                
  NRF_I2S->PSEL.SCK = (PIN_SCK << I2S_PSEL_SCK_PIN_Pos)|   (I2S_PSEL_SCK_CONNECT_Connected  << I2S_PSEL_SCK_CONNECT_Pos);                      /// must be connected - however we don't need it for RGB LEDs.  recommend using p0.23 when we have these pins unused
  NRF_I2S->PSEL.LRCK = (PIN_LRCK << I2S_PSEL_LRCK_PIN_Pos)|   (I2S_PSEL_LRCK_CONNECT_Connected  << I2S_PSEL_LRCK_CONNECT_Pos);                   /// must be connected - however we don't need it for RGB LEDs. recommend using p0.24 when we have these pins unused
  NRF_I2S->PSEL.SDOUT = (PIN_SDOUT << I2S_PSEL_SDOUT_PIN_Pos)|    (I2S_PSEL_SDOUT_CONNECT_Connected   << I2S_PSEL_SDOUT_CONNECT_Pos);                /// must be connected - this is the data line for the RGB LEDs
  NRF_I2S->INTENSET = I2S_INTENSET_TXPTRUPD_Msk;
  NRF_I2S->ENABLE = 0;
  //  NVIC_ClearPendingIRQ(I2S_IRQn); 

   // NVIC_EnableIRQ(I2S_IRQn);


  // Since we are not updating the TXD pointer, the sine wave will play over and over again.
  // The TXD pointer can be updated after the EVENTS_TXPTRUPD arrives. 
}



void set_led_data(uint8_t rval,uint8_t gval,uint8_t bval)
{
  //Serial.println(val);
    for(int i = 0; i < 3*NLEDS; i += 3) {
                    m_buffer_tx[i] = calcChannelValue(gval);;
                    m_buffer_tx[i+1] = calcChannelValue(rval);
                    m_buffer_tx[i+2] = calcChannelValue(bval);

    }
    
    // reset 
                    m_buffer_tx[3*NLEDS] = 0;
                    m_buffer_tx[3*NLEDS+1] = 0;
                    m_buffer_tx[3*NLEDS+2] = 0;
                    m_buffer_tx[3*NLEDS+3] = 0;
                    m_buffer_tx[3*NLEDS+4] = 0;
                    m_buffer_tx[3*NLEDS+5] = 0;
                    m_buffer_tx[3*NLEDS+6] = 0;
                    m_buffer_tx[3*NLEDS+7] = 0;
                    m_buffer_tx[3*NLEDS+8] = 0;
                    m_buffer_tx[3*NLEDS+9] = 0;
                    m_buffer_tx[3*NLEDS+10] = 0;
                    m_buffer_tx[3*NLEDS+11] = 0;

}

void copy_led_data(rgb_led_t values[])
{
    for(int i = 0; i < NLEDS; i++) {
                    m_buffer_tx[i*3] =   values[i].green;
                    m_buffer_tx[i*3+1] = values[i].red;
                    m_buffer_tx[i*3+2] = values[i].blue;
    }
    
    // reset 
                    m_buffer_tx[3*NLEDS] = 0;
                    m_buffer_tx[3*NLEDS+1] = 0;
                    m_buffer_tx[3*NLEDS+2] = 0;
                    m_buffer_tx[3*NLEDS+3] = 0;
                    m_buffer_tx[3*NLEDS+4] = 0;
                    m_buffer_tx[3*NLEDS+5] = 0;
                    m_buffer_tx[3*NLEDS+6] = 0;
                    m_buffer_tx[3*NLEDS+7] = 0;
                    m_buffer_tx[3*NLEDS+8] = 0;
                    m_buffer_tx[3*NLEDS+9] = 0;
                    m_buffer_tx[3*NLEDS+10] = 0;
                    m_buffer_tx[3*NLEDS+11] = 0;

}

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

bool rgbCheckStatus(void) {
  bool status = NRF_I2S->ENABLE;
 if (NRF_I2S->EVENTS_TXPTRUPD != 0)
  {
     NRF_I2S->EVENTS_TXPTRUPD = 0;
     NRF_I2S->ENABLE = 0;
  }
  
  return status;
}

void rgbstart(void)
{
  // Configure data pointer
  NRF_I2S->EVENTS_TXPTRUPD = 0;
  NRF_I2S->EVENTS_RXPTRUPD = 0;
  NRF_I2S->EVENTS_STOPPED = 0;
  NRF_I2S->TXD.PTR = (uint32_t)&m_buffer_tx[0];
  NRF_I2S->RXTXD.MAXCNT = sizeof(m_buffer_tx) / sizeof(uint32_t);
  NRF_I2S->ENABLE = 1;
  NRF_I2S->TASKS_START = 1;       // Start transmitting I2S data
}
