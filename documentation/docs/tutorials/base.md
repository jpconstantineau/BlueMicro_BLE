---
id: tut_base
title: Setting up
sidebar_label: Basic setup
slug: /tut_base
---


<figure class="video-container">
 <iframe src="//www.youtube.com/embed/TD9BAB1R4jg" frameborder="0" allowfullscreen width="100%"></iframe>
 </figure>


 ### hardware_config.h

This file contains the basic hardware configuration of your keyboard. 
It will contain at the minimum these 5 lines:

``` c++
#define MATRIX_ROWS 4
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS {43, 3, 28, 45}
#define MATRIX_COL_PINS {2, 29, 30,  26}
#define DIODE_DIRECTION COL2ROW
```
Other lines can be added for other features like battery monitoring, RGB Underglow, Backlight LEDs and other hardware features that are connected to the microcontroller. For more information on the options available to add in __hardware_config.h__ refer [here](/docs/configure_hardware)

 ### keyboard_config.h

This file contains the basic firmware configuration of your keyboard. It will contain at the minimum these 4 lines and a KEYMAP macro definition:

 ``` c++
#define KEYBOARD_SIDE SINGLE
#define DEVICE_NAME                         "4x4Backpack"                          
#define DEVICE_MODEL                        "4x4Backpack_V1"                      
#define MANUFACTURER_NAME                   "keyboards.jpconstantineau.com"      


#define KEYMAP( \
	 K00,   K01,   K02,   K03,      \
	 K10,   K11,   K12,   K13,     \
	 K20,   K21,   K22,   K23,     \
	 K30,   K31,   K32,   K33 \
) { \
	{ K00,   K01,   K02,   K03,   }, \
	{ K10,   K11,   K12,   K13,   }, \
	{ K20,   K21,   K22,   K23,   }, \
	{ K30,   K31,   K32,   K33    } \
}
```

If you have a split keyboard, you will also need to define the name of the left and right halves.
 ``` c++
#define DEVICE_NAME_R                         "ErgoTravel_R"  
#define DEVICE_NAME_L                         "ErgoTravel_L"  
 ``` 

 ### keymap.h

The most basic keymap.h file will need the following two lines to declare the matrix of keys and a function to map keycodes to the keys.

  ``` c++
void setupKeymap();
extern std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix; 
 ``` 

 ### keymap.cpp

 The most basic keymap.cpp file will define what we declared above.

  ``` c++
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
        KEYMAP2ARRAY(KEYMAP(
        KC_7,    KC_8,    KC_9,    KC_KP_SLASH,
        KC_4,    KC_5,    KC_6,    KC_KP_ASTERISK,
        KC_1,    KC_2,    KC_3,    KC_KP_MINUS,
        KC_0,    KC_0,    KC_DOT,  KC_KP_PLUS 
        ));

void setupKeymap() {
    ;  // this function does nothing in this case.
}
 ```
