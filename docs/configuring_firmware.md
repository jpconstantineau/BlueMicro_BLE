# Configuring BlueMicro

## Understanding nRF52 Modules and how GPIOs are numbered

### Adafruit Feather nRF52832

The __Adafruit Feather nRF52832__ uses the GPIO numbers in the IDE to call the specific pins.  This can be seen as the purple numbers in the following pinout image:
![Adafruit Feather nRF52832](https://cdn-learn.adafruit.com/assets/assets/000/046/248/original/microcontrollers_Feather_NRF52_Pinout_v1.2-1.png?1504885794)

Since there is a direct mapping between the Arduino IDE numbers and the GPIO number, the numbers used while programming are the same as the GPIOs.  __**This makes the Adafruit Feather nRF52832 compatible with most nRF52832 modules.**__

You can find a schematic of the Adafruit Feather nRF52832 [here](https://cdn-learn.adafruit.com/assets/assets/000/039/913/original/microcontrollers_BluefruitnRF52Feather_Rev-F.png).


### Adafruit Feather nRF52840 Express

Unlike for the nRF52832 Feather, Adafruit has opted to use the labels on the module itself as the numbers to use when programming the __Adafruit Feather nRF52840 Express__.  This means that there is no longer a direct representation between what's used while programming and the GPIO Port and Bit on the nRF52840 chip.  __**This makes the Adafruit Feather nRF52840 Express incompatible with other modules.**__

![Adafruit Feather nRF52840 Express](https://cdn-learn.adafruit.com/assets/assets/000/068/578/large1024/circuitpython_Screenshot_2019-01-02_at_12.04.27.png?1546446487)

For more details on the pinout of the Adafruit Feather nRF52840 Express, go to Adafruit's [documentation page](https://learn.adafruit.com/introducing-the-adafruit-nrf52840-feather/pinouts)

You can find a schematic of the Adafruit Feather nRF52840 Express [here](https://cdn-learn.adafruit.com/assets/assets/000/068/545/original/circuitpython_nRF52840_Schematic_REV-D.png).


### Nordic nRF52840DK (PCA10056)

Adafruit was very helpful when they included the __Nordic Semiconductor nRF52840 Development Kit__ in the Adafruit nRF52 Board Support Package. Unlike for the __Adafruit Feather nRF52840 Express__, the __PCA10056__ does not remap GPIO and Pin Numbers.  As such, we can use the GPIO number directly when programming.  __**This makes the Nordic nRF52840DK (PCA10056) compatible with most nRF52840 modules.**__

To find how to calculate the GPIO number, refer to the method described in the next section.

You can find more information on the PCA10056 [here](https://www.nordicsemi.com/Software-and-tools/Development-Kits/nRF52840-DK)

### Other nRF52832 and nRF52840 modules

This includes the BlueMicro, BlueMicro840, nRFMicro, Nice!Nano.  These modules reuse the __Adafruit Feather nRF52832__ or __Nordic nRF52840DK (PCA10056)__ boards in the Adafruit nRF52 Board Support Package.  As described above, the definition of these boards do not remap pins in code.

To find how to calculate the GPIO number, refer to the method described in the next section.

## Selecting GPIOs numbers

### Adafruit Feather nRF52840 Express

Use the Pin number as per what's written on the module itself. See picture in the  __Adafruit Feather nRF52840 Express__ section above.

### All other modules (nRF52832 or nRF52840)

The nRF52832 has 32 GPIOs on 1 port (Port 0) while the nRF52840 has 48 GPIOs on 2 ports (Port 0 and 1).  

To be able to address GPIOs on Port 1, we need to use this simple definition to convert port and bit to a single number.

``` c++
#define _PINNUM(port, bit)    ((port)*32 + (bit))

```
For __Port 0__, the GPIO number will be the same as the Bit number.

For __Port 1__, the GPIO number will be the Bit number plus 32.

| Port              | Bit        | GPIO Number to use       |
| ----------------- | ---------- | ---------- |
| 0                 | 0-31       | 0-31       |
| 1                 | 0-15       | 32-47      |



## Configuring your keyboard

### hardware_config.h

#### Matrix Definition

Most keyboards use a matrix of columns and rows to scan each key.  You will need to refer to the keyboard schematic to identify how many columns and rows your keyboard uses for it's scanning matrix.  The scanning matrix may differ from the keyboard layout.  For example, a 4x12 matrix uses 16 GPIOs and allows for 48 keys to be scanned.  A 8x8 matrix also uses 16 GPIOs but will allow 64 keys to be scanned.  The mapping of each key in the scanning matrix to the keyboard layout is done in the KEYMAP macro definition in keyboard_config.h.

![keyboard matrix](https://raw.githubusercontent.com/jpconstantineau/BlueMicro_BLE/develop/docs/images/keyboardmatrix.png)

In the image above, we see that this keyboard has a matrix of 4 rows, with 7 columns.  The direction of the diodes goes from the columns to the rows.  With this information, we can define the following:

``` c++

#define MATRIX_ROWS 4
#define MATRIX_COLS 7

#define DIODE_DIRECTION COL2ROW

```

Next, we need to identify how each row and column are mapped to the microntroller on board of the nRF52 module you use.  Since most DIY keyboards use the Arduino Pro Micro as its controller, we are using such an example.

![GPIO Mapping](https://raw.githubusercontent.com/jpconstantineau/BlueMicro_BLE/develop/docs/images/gpiomapping.png)

With the information from both the keyboard and controller schamatics, we can map each row and column to the GPIO and using the formula shown in the previous section, we can define the configuration needed: 

``` c++

#define MATRIX_ROW_PINS {13, 24, 9, 10 }
#define MATRIX_COL_PINS {26, 29, 2, 45, 3, 28, 43 }

```


#### Battery Monitoring

``` c++
#define BATTERY_TYPE BATT_LIPO
#define VBAT_PIN  31

```

#### External VCC Switching

``` c++
#define VCC_PIN 12
#define VCC_POLARITY_ON 1

```

#### LiPo Charger Switching

``` c++
     #define CHARGER_PIN  5
     #define CHARGER_POLARITY_ON 0
```

#### Backlight PWM LED Definition

``` c++
	#define BACKLIGHT_LED_PIN 23
	#define BACKLIGHT_PWM_ON 1 
    #define DEFAULT_PWM_VALUE 10000            // PWM intensity  max is 10000

```


#### RGB LED Definition

``` c++
	#define WS2812B_LED_PIN 15
	
	#define WS2812B_LED_COUNT 1
	#define WS2812B_LED_ON 1 

```


#### OLED Definition

To Do - Still being implemented.

``` c++
#define OLED_SDA_PIN        25
#define OLED_SCL_PIN        26
```


#### Rotary Encoder Definition

To Do - Still being implemented.

``` c++
#define ENCODERS_COUNT 1
#define ENCODERS_A_PIN { 26 }
#define ENCODERS_B_PIN { 30 }
```