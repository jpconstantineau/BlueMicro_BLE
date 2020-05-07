
//#include <stdint.h>
//#include <cstddef>
//#include <bluefruit.h>
#include <arduino.h>
#include "WS2812.h"

#define NLEDS 6
/**************************************************************************************************************************/
// WS2812B I2S Functions

//volatile uint8_t  i2s_ws2812b_drive_m_blocks_transferred     = 0;
//volatile bool     i2s_ws2812b_drive_flag_first_buffer = false;
//rgb_led_t *i2s_ws2812b_drive_tx_led_array;


/*void i2s_ws2812b_drive_set_buff(rgb_led_t * rgb_led, uint8_t *p_xfer, uint16_t xbuff_length)
{
  rgb_led_t* p_led = rgb_led; 
  int8_t offset = 1;
  
  for(uint16_t i_led=0;i_led<(xbuff_length/I2S_WS2812B_DRIVE_BUF_SIZE_PER_LED);i_led++)
  {
    uint32_t rgb_data = (p_led->green << 16) | (p_led->red << 8 ) | p_led->blue;
    for(uint8_t i_rgb=0;i_rgb<I2S_WS2812B_DRIVE_BUF_SIZE_PER_LED;i_rgb++)
    {
      switch(rgb_data & 0x00c00000 )
      {
        case ( 0x00400000 ):
          *(p_xfer + offset)  = (uint8_t)(( I2S_WS2812B_DRIVE_PATTERN_0 << 4 ) | I2S_WS2812B_DRIVE_PATTERN_1);
          break;
        case ( 0x00800000 ):
          *(p_xfer + offset)  = (uint8_t)(( I2S_WS2812B_DRIVE_PATTERN_1 << 4 ) | I2S_WS2812B_DRIVE_PATTERN_0);
          break;
        case ( 0x00c00000 ):
          *(p_xfer + offset)  = (uint8_t)(( I2S_WS2812B_DRIVE_PATTERN_1 << 4 ) | I2S_WS2812B_DRIVE_PATTERN_1);
          break;
        default:
          *(p_xfer + offset)  = (uint8_t)(( I2S_WS2812B_DRIVE_PATTERN_0 << 4 ) | I2S_WS2812B_DRIVE_PATTERN_0);
      }
      p_xfer++;
      offset = -offset;
      rgb_data <<= (24 / I2S_WS2812B_DRIVE_BUF_SIZE_PER_LED);
    }
    p_led++;
  }
}*/

/*
static void i2s_ws2812b_drive_handler(uint32_t const * p_data_received,
                         uint32_t       * p_data_to_send,
                         uint16_t         number_of_words)
{
    // Only first transfer is necessary for WS2812B drive, so, 

    if (p_data_to_send != NULL)
    {
      if ( i2s_ws2812b_drive_flag_first_buffer == true )
      {
        i2s_ws2812b_drive_set_buff(i2s_ws2812b_drive_tx_led_array, (uint8_t *)p_data_to_send, number_of_words*4);
        i2s_ws2812b_drive_flag_first_buffer = false;
      }
      else
      {
        ++i2s_ws2812b_drive_m_blocks_transferred;
      }
    }
}*/

/*
void i2s_ws2812b_drive_xfer(rgb_led_t *led_array, uint16_t num_leds, uint8_t drive_pin)
{
//  ret_code_t err_code;
  
  /* define configs
  nrf_drv_i2s_config_t config = NRF_DRV_I2S_DEFAULT_CONFIG;
  config.sck_pin      = 22; // Don't set NRF_DRV_I2S_PIN_NOT_USED for I2S_CONFIG_SCK_PIN. (The program will stack.) 
  config.lrck_pin     = NRF_DRV_I2S_PIN_NOT_USED;
  config.mck_pin      = NRF_DRV_I2S_PIN_NOT_USED;
  config.sdout_pin    = drive_pin;
  config.sdin_pin     = NRF_DRV_I2S_PIN_NOT_USED;

  config.irq_priority = APP_IRQ_PRIORITY_HIGH;
  config.mode         = NRF_I2S_MODE_MASTER;
  config.format       = NRF_I2S_FORMAT_I2S;
  config.alignment    = NRF_I2S_ALIGN_LEFT;
  config.sample_width = NRF_I2S_SWIDTH_16BIT;
  config.channels     = NRF_I2S_CHANNELS_STEREO;
  config.mck_setup    = NRF_I2S_MCK_32MDIV10;
  config.ratio        = NRF_I2S_RATIO_32X;//
  
  // initialize i2s


  // start transfer
  uint16_t tx_buffer_size = num_leds * I2S_WS2812B_DRIVE_BUF_SIZE_PER_LED / 4;
  uint32_t m_buffer_tx[tx_buffer_size];
  i2s_ws2812b_drive_tx_led_array = led_array;

  i2s_ws2812b_drive_m_blocks_transferred = 0;
  i2s_ws2812b_drive_flag_first_buffer = true;
  


//  nrf_delay_us((num_leds+20) * (24*5/4));

  // stop transfer
 // nrf_drv_i2s_stop();//

  // un-initialize i2s
//  nrf_drv_i2s_uninit();//
  
 // return NRF_SUCCESS;
}

*/


/**************************************************************************************************************************/
// WS2812B Drive Functions

/*
void ws2812b_drive_set_blank(rgb_led_t * rgb_led, uint16_t num_leds)
{
  rgb_led_t * p = rgb_led;
  for(uint16_t i=0;i<num_leds;i++)
  {
    p->green = 0;
    p->red   = 0;
    p->blue  = 0;
    p++;
  }
}

void ws2812b_drive_current_cap(rgb_led_t * led_array, uint16_t num_leds, uint32_t limit)
{
  uint32_t sum0 = ws2812b_drive_calc_current(led_array, num_leds);
  if ( sum0 > limit ) {
    // fact = (limit - num_leds) / (sum0 - num_leds);
    int32_t factn = limit - num_leds;
    if ( factn < 0 )
    {
      factn = 1;
    }
    int32_t factd = sum0 - num_leds;
    if ( factd < 0 )
    {
      factd = 1;
    }

    rgb_led_t * p = led_array;  
    rgb_led_t dnext;
    for(uint16_t i=0;i<num_leds;i++)
    {
      dnext.green = p->green * factn / factd;
      dnext.red   = p->red   * factn / factd;
      dnext.blue  = p->blue  * factn / factd;

      if ( dnext.green == 0 && p->green > 0 )
      {
        dnext.green = 1;
      }
      if ( dnext.red   == 0 && p->red   > 0 ) 
      {
        dnext.red   = 1;
      }
      if ( dnext.blue  == 0 && p->blue  > 0 )
      {
        dnext.blue  = 1;
      }
      *p = dnext;
      p++;
    } // i
  } 
}

uint32_t ws2812b_drive_calc_current(rgb_led_t * led_array, uint16_t num_leds)
{
  uint32_t sum = 0;
  rgb_led_t * p = led_array;
  for(uint16_t i=0;i<num_leds;i++)
  {
    sum += p->green + p->red + p->blue;
    p++;
  }
  
  return(num_leds + (sum*45)/(255*3)); // mA
}

void ws2812b_drive_dim(rgb_led_t * led_array, uint16_t num_leds, float dim )
{
    rgb_led_t * p = led_array;  
    for(uint16_t i=0;i<num_leds;i++)
    {
      p->green *= dim;
      p->red   *= dim;
      p->blue  *= dim;

      p++;
    } // i

}
*/
/**************************************************************************************************************************/
// RGB Color Functions

//static rgb_led_t [NLEDS] led_array_base;
/*
void flashing_random_init(rgb_led_t * led_array_base, uint16_t num_leds)
{


    // initialize led_array (base color array)
    for(uint16_t i=0;i<NLEDS;i++)
    {
      int c = (i % 7) + 1;
        led_array_base[i].green = (MAX_INTENSE+MIN_INTENSE)/2 * ((c&4)>>2);
        led_array_base[i].red   = (MAX_INTENSE+MIN_INTENSE)/2 * ((c&2)>>1);
        led_array_base[i].blue  = (MAX_INTENSE+MIN_INTENSE)/2 * ((c&1)>>0);
    }


}



void flashing_random(rgb_led_t * led_array_out)
{
  int16_t nextc;
  {
    for(uint16_t i=0;i<NLEDS;i++) {
      nextc = led_array_out[i].green + rand()%3 -1;
      if ( nextc < MIN_INTENSE )
      {
        nextc = MIN_INTENSE;
      }
        
      if ( nextc > MAX_INTENSE )
      {
        nextc = MAX_INTENSE;
      }
      led_array_out[i].green = nextc;
        
      nextc = led_array_out[i].red + rand()%3 -1;
      if ( nextc < MIN_INTENSE )
      {
        nextc = MIN_INTENSE;
      }
        
      if ( nextc > MAX_INTENSE )
      {
        nextc = MAX_INTENSE;
      }
      led_array_out[i].red = nextc;

      nextc = led_array_out[i].blue + rand()%3 -1;
      if ( nextc < MIN_INTENSE )
      {
        nextc = MIN_INTENSE;
      }
        
      if ( nextc > MAX_INTENSE )
      {
        nextc = MAX_INTENSE;
      }
      led_array_out[i].blue = nextc;
    }

  }
}*/
