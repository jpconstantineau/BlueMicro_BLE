
typedef struct
{
    uint8_t   green; // Brightness of green (0 to 255)
    uint8_t   red;   // Brightness of red   (0 to 255)
    uint8_t   blue;  // Brightness of blue  (0 to 255)
} rgb_led_t;


#define NLEDS 6
#define RESET_BITS 6
#define I2S_BUFFER_SIZE 3*NLEDS + RESET_BITS

#define I2S_WS2812B_DRIVE_PATTERN_0 ((uint8_t)0x08)      // Bit pattern for data "0" is "HLLL".
#define I2S_WS2812B_DRIVE_PATTERN_1 ((uint8_t)0x0e)      // Bit pattern for data "1" is "HHHL".
#define I2S_WS2812B_DRIVE_BUF_SIZE_PER_LED  (12)         // buffer size for each LED (8bit * 4 * 3 )

#define NUM_LEDS      (6)   // Number of LEDs (LED総数）
#define MAX_INTENSE   (64)    // Max intense of random LEDs for "flashing_random" (flashing_random用のランダム色LEDの最大輝度)
#define MAX_INTENSE2  (255)   // Max intense of "shooting start" running bright LEDs for all demos.
#define MAX_INTENSE3  (64)    // Max intense of "rainbow LEDs" for "running_rainbow" and "running_rainbowv" demos. 
#define MIN_INTENSE   (1)     // Minimum intense of randaom LEDs for "flashing_random" (flashing_random用のランダム色LEDの最小輝度)
#define ROW_SIZE      (17)    // Count of LEDs for each line (1巻き分のLEDの数)
#define CURRENT_LIMIT (1500)  // Current limit of LEDs (mA) (総電流制限値)
#define FADE_IN_MS    (6000)  // Fade in/out period (フェードイン・アウトの秒数）




void i2s_ws2812b_drive_set_buff(rgb_led_t * rgb_led, uint8_t *p_xfer, uint16_t xbuff_length);
static void i2s_ws2812b_drive_handler(uint32_t const * p_data_received,uint32_t       * p_data_to_send,uint16_t         number_of_words);
void i2s_ws2812b_drive_xfer(rgb_led_t *led_array, uint16_t num_leds, uint8_t drive_pin);
void ws2812b_drive_set_blank(rgb_led_t * rgb_led, uint16_t num_leds);
void ws2812b_drive_current_cap(rgb_led_t * led_array, uint16_t num_leds, uint32_t limit);
uint32_t ws2812b_drive_calc_current(rgb_led_t * led_array, uint16_t num_leds);

void ws2812b_drive_dim(rgb_led_t * led_array, uint16_t num_leds, float dim );
void flashing_random_init(rgb_led_t * led_array_base, uint16_t num_leds);
void flashing_random(rgb_led_t * led_array_out);
