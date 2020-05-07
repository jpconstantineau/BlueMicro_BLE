#ifndef I2S_H
#define I2S_H

#include <bluefruit.h>

#define PIN_MCK    (11) //MOSI = B2   // 24 = WS2812B
#define PIN_SCK    (22) //MISO = B3     // 22 = factory reset
#define PIN_LRCK   (20) // = B4         // 20 = DFU
#define PIN_SDOUT  (24) // = B          // 11 = COL10

#define NLEDS 1
#define RESET_BITS 12
#define I2S_BUFFER_SIZE 3*NLEDS + RESET_BITS

//uint32_t m_buffer_tx[I2S_BUFFER_SIZE];

typedef struct
{
    uint8_t   green; // Brightness of green (0 to 255)
    uint8_t   red;   // Brightness of red   (0 to 255)
    uint8_t   blue;  // Brightness of blue  (0 to 255)
} rgb_led_t;

void setuprgb(void);
void rgbstart(void);
bool rgbCheckStatus(void) ;
uint32_t calcChannelValue(uint8_t level);

void copy_led_data(rgb_led_t values[]);
void set_led_data(uint8_t rval,uint8_t gval,uint8_t bval);
void I2S_IRQHandler(void);

#endif /* I2S_H */
