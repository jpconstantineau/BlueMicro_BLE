---
id: configure_hardware
title: Configuring hardware_config.h
slug: /configure_hardware
---

## Configuring your keyboard - Part 1: Hardware Definition

### Matrix Definition

Most keyboards use a matrix of columns and rows to scan each key.  You will need to refer to the keyboard schematic to identify how many columns and rows your keyboard uses for it's scanning matrix.  The scanning matrix may differ from the keyboard layout.  For example, a 4x12 matrix uses 16 GPIOs and allows for 48 keys to be scanned.  A 8x8 matrix also uses 16 GPIOs but will allow 64 keys to be scanned.  The mapping of each key in the scanning matrix to the keyboard layout is done in the KEYMAP macro definition in keyboard_config.h.

![keyboard matrix](http://bluemicro.jpconstantineau.com/img/keyboardmatrix.png)

In the image above, we see that this keyboard has a matrix of 4 rows, with 7 columns.  The direction of the diodes goes from the columns to the rows.  With this information, we can define the following:

``` c++
#define MATRIX_ROWS 4
#define MATRIX_COLS 7

#define DIODE_DIRECTION COL2ROW
```

Next, we need to identify how each row and column are mapped to the microntroller on board of the nRF52 module you use.  Since most DIY keyboards use the Arduino Pro Micro as its controller, we are using such an example.

![GPIO Mapping](http://bluemicro.jpconstantineau.com/img/gpiomapping.png)

With the information from both the keyboard and controller schamatics, we can map each row and column to the GPIO and using the formula shown in the previous section, we can define the configuration needed: 

``` c++
#define MATRIX_ROW_PINS {13, 24, 9, 10 }
#define MATRIX_COL_PINS {26, 29, 2, 45, 3, 28, 43 }
```

### Status LEDs

Most controllers will have 1 or 2 LEDs to let the user know of the status of the board.  To configure the firmware to use these LEDs, you need to set at least the PIN definition for the LED. 
By default, when `STATUS_BLE_LED_PIN` or `STATUS_KB_LED_PIN` are defined, both the `ACTIVE` and `POLARITY` settings will default to 1.

``` c++
	#define  STATUS_BLE_LED_PIN  19  //blue = 0.19
	#define  BLE_LED_ACTIVE 1
	#define  BLE_LED_POLARITY 1

	#define  STATUS_KB_LED_PIN 17  //red = 0.17
	#define  STATUS_KB_LED_ACTIVE 1
	#define  STATUS_KB_LED_POLARITY 1
```
If you want to keep the definition of the PIN but want to disable the use of the specific status LED, you need to set the `ACTIVE` to `0`.  

By default, setting a `1` on the GPIO will turn on the LED.  If this logic is reversed, set `POLARITY` to `0`.

If your board does not have the LED defined but it's status does not change, you need to configure the PIN so that it can be updated to match the state of the keyboard.

Note that when going to sleep, the enabled pins will go in a low power mode (INPUT) and will turn off the LEDs.


### Battery Monitoring

Battery Monitoring is a function that's specific to the controller you use.  Most controllers implement an on-board battery charger and battery monitoring voltage divider and connect this divider to an analog input.  Such a configuration is shown below:

![Battery Monitoring](http://bluemicro.jpconstantineau.com/img/batterymonitoring.png)

From the schematic, we identify that the connection point of the voltage divider is connected to 0.31. This leads to this definition:

``` c++
#define BATTERY_TYPE BATT_LIPO
#define VBAT_PIN  31
```

If a non-rechargeable CR2032 (3V) powers your keyboard and the battery is directly connected to the nRF52 chip, you still need to define a `VBATT_PIN`  but since the nrf52 chip can measure its own supply voltage, it will not use this configuration. All you need to do is to use this definition:

``` c++
#define BATTERY_TYPE BATT_CR2032
```

### External VCC Switching

Some controllers implement switching of external VCC to ensure low power consumption.  Polarity of switching will depend on the hardware implementation.  Refer to the controller documentation and/or schematic to identify if VCC switching is available, which GPIO it is connected to and polarity of the switch.

``` c++
#define VCC_PIN 12
#define VCC_POLARITY_ON 1
```
If `VCC_PIN` is left undefined, VCC switching functionality will not be enabled in the firmware.

By default, `VCC_POLARITY_ON` is defined with 1. You only need to define it if polarity is reversed. (replace 1 with 0)

By default, the firmware will turn on external VCC when booting up and will turn off External VCC when going to sleep.  If you want to force external VCC to be off at bootup, you can add this definition to your __hardware_config.h__ file.

``` c++
#define VCC_DEFAULT_ON 0
```

### LiPo Charger Switching

Some controllers implement turning off the LiPo Charger to allow for a more precise battery level measurement.  Switching polarity will depend on the hardware implementation.  Refer to the controller documentation and/or schematic to identify if charger switching is available, which GPIO it is connected to and polarity to enable charging.

``` c++
     #define CHARGER_PIN  5
     #define CHARGER_POLARITY_ON 0
```
If `CHARGER_PIN` is left undefined, charger switching functionality will not be enabled in the firmware. By default, the firmware will turn on charger when booting up and will not change it at any time.


### Backlight PWM LED Definition

Some keyboards have backlit keys using LEDs controlled by a central mosfet.  The brightness of these LEDs can be modulated using Pulse Width Modulation (PWM). When referring to the keyboard and controller schematics above, we see that GPIO 1.06 is connected to the LED Backlight.

 ![GPIO Mapping](http://bluemicro.jpconstantineau.com/img/gpiomapping.png)

This enables setting up the following configuration:

``` c++
	#define BACKLIGHT_LED_PIN 38
	#define BACKLIGHT_PWM_ON 1 
    #define DEFAULT_PWM_VALUE 10000  // Reduce max PWM to 10000 out of 63351 (0x7FFF)
```
If `BACKLIGHT_LED_PIN` is left undefined, LED functionality will not be enabled in the firmware.
`BACKLIGHT_PWM_ON` is optional. If `BACKLIGHT_LED_PIN` is defined, but you want to turn off LED functionality, you can do so by setting `BACKLIGHT_PWM_ON` to 0.
If `DEFAULT_PWM_VALUE` is left undefined, the default value will be that of maximum PWM value of 63351 (0x7FFF).  This will turn on LEDs on fully.

Turning on the PWM peripheral on the nRF52 chip uses approximately 0.5mA, not including the power used by the LED themselves.  As such, when the PWM value is set to 0, the firmware turns off the PWM peripheral it uses for controlling the brightness of the LEDs. It does the same prior to going to sleep. 


### RGB LED Definition

Some keyboards have RGB LEDs.  These LEDs are controlled through a single data line. When referring to the keyboard and controller schematics above, we see that GPIO 0.06 is connected to the RGB WS2812 LEDs.

 ![GPIO Mapping](http://bluemicro.jpconstantineau.com/img/gpiomapping.png)

This enables setting up the following configuration:

``` c++
	#define WS2812B_LED_PIN 6
	#define WS2812B_LED_COUNT 1
	#define WS2812B_LED_ON 1 
```
If `WS2812B_LED_PIN` is left undefined, LED functionality will not be enabled in the firmware.
If `WS2812B_LED_ON` is set to 0, RGB functionality will not be enabled in the firmware. Note that this will not power down VCC power to the RGB LEDs, impacting power consumption of your keyboard.  External VCC to the RGB LEDs is controlled through the __External VCC Switch__ functionality described above.

### OLED Definition

To Do - Still being implemented.

``` c++
#define OLED_SDA_PIN        25
#define OLED_SCL_PIN        26
```


### Rotary Encoder Definition

Currently implemented for a single Rotary encoder per side/half.

Add these lines to your `hardware_config.h`

``` c++
#define ENCODER_A_PIN  26 
#define ENCODER_B_PIN  30 
```

From a hardware point of view, the A an B lines of the encoder should be wired directly to the nRF52 GPIO. The C (or common) line should be wired to ground. By default, the configuration uses the hardware QDEC peripheral (Quadrature Decoder) that's part of the nRF52 SoC and uses callbacks to handle rotation.  The Adafruit library supports sofware interrupts for 4 encoders but this has not been fully tested.  This limit on the number of encoders supported can be modified in the [library](https://github.com/jpconstantineau/Adafruit_nRF52_Arduino/blob/master/libraries/RotaryEncoder/SwRotaryEncoder.cpp).  Refer to the examples in the library if you want to implement multiple encoders.

You will need to add a few things to your keymap.h file.

``` c++
#include "KeyScanner.h"  // include at the top with the other includes

void encoder_callback(int step); // add right after void setupKeymap();

```

You will also need to add a few things to your keymap.cpp file.  For example, you will need to add the following 3 lines in the `setupKeymap()` function:

``` c++
// Code below makes sure that the encoder gets configured.

  RotaryEncoder.begin(ENCODER_PAD_A, ENCODER_PAD_B);    // Initialize Encoder
  RotaryEncoder.setCallback(encoder_callback);    // Set callback
  RotaryEncoder.start();    // Start encoder

```

You will need to add the  `encoder_callback()` function:

``` c++
void encoder_callback(int step)
{
  if ( step > 0 )
  {
      switch(KeyScanner::localLayer)
      {
         // case _L0: break;  // commented out to revert to default
          case _L1: break;    // in Layer 1, send nothing
          case _L2: break;    // in Layer 2, send nothing
          default: KeyScanner::add_to_encoderKeys(KC_AUDIO_VOL_UP);
      }
  }else
  {
      switch(KeyScanner::localLayer)
      {
         // case _L0: break;   // commented out to revert to default
          case _L1: break;     // in Layer 1, send nothing
          case _L2: break;     // in Layer 2, send nothing
          default: KeyScanner::add_to_encoderKeys(KC_AUDIO_VOL_DOWN);
      }
  }  
}

```

If you rotate in one direction and the keycodes are for the other direction, simply change the `if ( step > 0 )` statement to `if ( step < 0 )` or swap the keycodes around.