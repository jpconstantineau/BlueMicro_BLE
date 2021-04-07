---
id: configure_keymap
title: Configuring keymap.h.cpp
slug: /configure_keymap
---

## Configuring your keyboard - Part 3: Keymap Definition


### The default layer
The default layer is the layer which you will most often use. Generally this is the "QWERTY" Layer.
For example for the gherkin 3x10:

``` c++
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    KEYMAP2ARRAY(KEYMAP(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ESC,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_SPC,  KC_BKSPC,KC_B,    KC_N,    KC_M,    KC_NO 
        ));
        
```

Notice the 2 macros being used: `KEYMAP2ARRAY` and `KEYMAP`. Since the `matrix` variable is a c++ array, we need to convert the output of the `KEYMAP` macro from a C array to a c ++ array. 

### Further layers

For additional layers, you will need to programatically add the layers and the keycodes.  This is done in the function `setupKeymap()`.

``` c++
void setupKeymap() {

    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_Z,     KC_X,     KC_C,     KC_V,     KC_SPC,    KC_BSPC,  KC_B,     KC_N,     KC_M,     KC_ENT );

    ADDLAYER(_L1, Method::PRESS , layer1);

}

```

Notice that in the `setupKeymap()` function, we use c arrays that only need the `KEYMAP2ARRAY` macro to help you with your keymap.

The `ADDLAYER` macro simplifies the process of adding your layer and has the following arguments:

* **LAYER NUMBER**: The first argument is the layer number.  Unlike the layer keycode, this is a simple number from 0 to 6 (up to 15 may be supported; depending on memory availability and matrix size).
* **ACTIVATION METHOD**: Generally, you will use the `Method::PRESS` method. Other methods are `Method::MT_TAP`, `Method::MT_HOLD`, `Method::DT_TAP` and `Method::DT_DOUBLETAP`. If a key keys triggered using multiple methods, all methods will "fire" and send a keycode.  As such, it's useful to use the `KC_NO` keycode to avoid sending anything for a specific activation.
* **KEYMAP ARRAY**: This is the C array to load.

The `ADDLAYER` macro wraps the Key::addActivation with a loop for all rows and columns of the key matrix. 

Note that when using `KC_NO` as the keycode within a layer, the firmware will automatically bypass this keycode for this specific key and it won't be added to its mapping.  As such, having lots of `KC_NO` keycodes in a layer won't affect the performance of the keyboard.


### Rotary Encoder Definition (1 encoder)

You can refer to the configuration of the solfle keyboard - default configuration for a working example for a single encoder.

 This configuration uses the hardware QDEC peripheral (Quadrature Decoder) that's part of the nRF52 SoC and uses callbacks to handle rotation.

You will need to add a few things to your keymap.h file.

``` c++
#include "KeyScanner.h"  // include at the top with the other includes
extern DynamicState keyboardstate;
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
  uint8_t layer = keyboardstate.layer;
  if ( step > 0 )
  {
      switch(layer)
      {
          case _L0: KeyScanner::add_to_encoderKeys(KC_AUDIO_VOL_UP); break;
          case _L1: KeyScanner::add_to_encoderKeys(KC_RIGHT); break;
          case _L2: KeyScanner::add_to_encoderKeys(LSFT(KC_RIGHT)); break;
          default: ;
      }
  }else
  {
      switch(layer)
      {
          case _L0: KeyScanner::add_to_encoderKeys(KC_AUDIO_VOL_DOWN); break;
          case _L1: KeyScanner::add_to_encoderKeys(KC_LEFT);break;
          case _L2: KeyScanner::add_to_encoderKeys(LSFT(KC_LEFT));break;
          default: ;
      }
  }  
}

```

If you rotate in one direction and the keycodes are for the other direction, simply change the `if ( step > 0 )` statement to `if ( step < 0 )` or swap the keycodes around.

You can change the rotary encoder callback to a different function by calling a macro.  This will enable changing the behavior of the rotary encoder at runtime.

### Rotary Encoder Definition (Up to 8 encoders)

You can refer to the configuration of the miniMACRO5 keyboard - default configuration for a working example for 5 encoders.

 This configuration uses the software interrupts and uses callbacks to handle rotation.  This limit on the number of encoders supported using software interrupts can be modified in the [library](https://github.com/jpconstantineau/Adafruit_nRF52_Arduino/blob/master/libraries/RotaryEncoder/SwRotaryEncoder.cpp).  The Community BSP has a limit of 8 encoders while the adafruit BSP is set to a maximum of 4.

You will need to add a few things to your keymap.h file.  The example below is from the miniMACRO5 which supports up to 5 encoders.

``` c++
#include "KeyScanner.h"  // include at the top with the other includes
extern DynamicState keyboardstate;
void encoder_callback1(int step);
void encoder_callback2(int step);
void encoder_callback3(int step);
void encoder_callback4(int step);
void encoder_callback5(int step);

```

You need to instantiate the software encoders in your keymap.cpp.  Add the following before your `setupKeymap()` function:

``` c++
SwRotaryEncoder RotaryEncoder1,RotaryEncoder2, RotaryEncoder3, RotaryEncoder4, RotaryEncoder5;

```

You will also need to add a few things to your keymap.cpp file.  For example, you will need to add the following lines in the `setupKeymap()` function:

``` c++
byte encoder_pins_a[] ENCODER_PAD_A;
byte encoder_pins_b[] ENCODER_PAD_B;
// Code below makes sure that the encoder gets configured.

  RotaryEncoder1.begin(encoder_pins_a[0], encoder_pins_b[0]);    // Initialize Encoder
  RotaryEncoder1.setCallback(encoder_callback1);    // Set callback

  RotaryEncoder2.begin(encoder_pins_a[1], encoder_pins_b[1]);    // Initialize Encoder
  RotaryEncoder2.setCallback(encoder_callback2);    // Set callback

  RotaryEncoder3.begin(encoder_pins_a[2], encoder_pins_b[2]);    // Initialize Encoder
  RotaryEncoder3.setCallback(encoder_callback3);    // Set callback

  RotaryEncoder4.begin(encoder_pins_a[3], encoder_pins_b[3]);    // Initialize Encoder
  RotaryEncoder4.setCallback(encoder_callback4);    // Set callback

#ifdef ARDUINO_NRF52_COMMUNITY  // if you want to initialize more than 4, you need to compile on the Community BSP
    RotaryEncoder5.begin(encoder_pins_a[4], encoder_pins_b[4]);    // Initialize Encoder
  RotaryEncoder5.setCallback(encoder_callback5);    // Set callback
#endif

```

You will need to add the  `encoder_callback()` functions (one per encoder):

``` c++

void encoder_callback1(int step)
{
  keyboardstate.encoder1pos = keyboardstate.encoder1pos + step; 

  if (abs(keyboardstate.encoder1pos) > ENCODER_RESOLUTION)
  {
    if ( keyboardstate.encoder1pos < 0  )
    {
      KeyScanner::add_to_encoderKeys(KC_AUDIO_VOL_UP); 
    }
    else 
    {
      KeyScanner::add_to_encoderKeys(KC_AUDIO_VOL_DOWN); 
    } 
    keyboardstate.encoder1pos = 0; 
  } 
}

void encoder_callback2(int step)
{
  keyboardstate.encoder2pos = keyboardstate.encoder2pos + step; 

  if (abs(keyboardstate.encoder2pos) > ENCODER_RESOLUTION)
  {
    if ( keyboardstate.encoder2pos < 0  )
    {
  
      KeyScanner::add_to_encoderKeys(KC_RIGHT); 
    }
    else 
    {
      KeyScanner::add_to_encoderKeys(KC_LEFT);
    } 
    keyboardstate.encoder2pos = 0; 
  } 
}

void encoder_callback3(int step)
{
  keyboardstate.encoder3pos = keyboardstate.encoder3pos + step; 

  if (abs(keyboardstate.encoder3pos) > ENCODER_RESOLUTION)
  {
    if ( keyboardstate.encoder3pos < 0  )
    {
  
      KeyScanner::add_to_encoderKeys(KC_L); 
    }
    else 
    {
      KeyScanner::add_to_encoderKeys(KC_J);
    } 
    keyboardstate.encoder3pos = 0; 
  } 
}

void encoder_callback4(int step)
{
  keyboardstate.encoder4pos = keyboardstate.encoder4pos + step; 

  if (abs(keyboardstate.encoder4pos) > ENCODER_RESOLUTION)
  {
    if ( keyboardstate.encoder4pos < 0  )
    {
  
      KeyScanner::add_to_encoderKeys(KC_COMMA); 
    }
    else 
    {
      KeyScanner::add_to_encoderKeys(KC_DOT);
    } 
    keyboardstate.encoder4pos = 0; 
  } 
}

void encoder_callback5(int step)
{
  keyboardstate.encoder5pos = keyboardstate.encoder5pos + step; 

  if (abs(keyboardstate.encoder5pos) > ENCODER_RESOLUTION)
  {
    if ( keyboardstate.encoder5pos < 0  )
    {
  
      KeyScanner::add_to_encoderKeys(KC_UP); 
    }
    else 
    {
      KeyScanner::add_to_encoderKeys(KC_DOWN);
    } 
    keyboardstate.encoder5pos = 0; 
  } 
}

```

If you rotate in one direction and the keycodes are for the other direction, simply change the `if ( step > 0 )` statement to `if ( step < 0 )` or swap the keycodes around.

You can change the rotary encoder callback to a different function by calling a macro.  This will enable changing the behavior of the rotary encoder at runtime.


### OLED Definition

The default screens can be overriden by assigning a new callback.

You will need to add a few things to your keymap.h file.

``` c++
#include "BlueMicro_display.h"

#ifdef BLUEMICRO_CONFIGURED_DISPLAY
extern BlueMicro_Display OLED;        // needed to assign the update display callback
extern DISPLAY_U8G2_CONSTRUCTOR u8g2; // needed to call the display functions
#endif

void updateDisplay(PersistentState* cfg, DynamicState* stat);

```

You will also need to add a few things to your keymap.cpp file.  For example, you will need to add the following 3 lines in the `setupKeymap()` function:

``` c++

    #ifdef BLUEMICRO_CONFIGURED_DISPLAY
    OLED.setStatusDisplayCallback(updateDisplay);
    #endif

```

You will then need to define the `updateDisplay()` function with your own requirements.  The following is an example that provides a battery icon, the computer or half it is connected to and the currently active layer. 

``` c++
void updateDisplay(PersistentState* cfg, DynamicState* stat)
{
    #ifdef BLUEMICRO_CONFIGURED_DISPLAY
    u8g2.setFontMode(1);	// Transparent
    u8g2.setFontDirection(0);
    battery(22,19,stat->vbat_per);
    printline(0,28,stat->peer_name_prph);

    char buffer [50];
    u8g2.setFont(u8g2_font_helvB12_tf);	// choose a suitable font
    switch(stat->layer)
    {
        case _QWERTY:     u8g2.drawStr(0,128,""); break;
        case _LOWER:      u8g2.drawStr(0,128,"L");break;
        case _RAISE:     u8g2.drawStr(0,128,"R");break;
        case _ADJUST:     u8g2.drawStr(0,128,"A");break;
        case _EXTRAL:     u8g2.drawStr(0,128,"EL");break;
        case _EXTRAR:     u8g2.drawStr(0,128,"ER");break; 
        case _MACROL:     u8g2.drawStr(0,128,"ML");break;
        case _MACROR:     u8g2.drawStr(0,128,"MR");break; 
        case _MACRO:     u8g2.drawStr(0,128,"M");break;    
    }
    #endif
}
```


### Speaker/Buzzer/Audio Definition

If you want to add additional audio feedback to your macros or user functions, you will need to add a few lines to your keymap.h file:

``` c++
#define ENABLE_AUDIO
#include "BlueMicro_tone.h"
extern BlueMicro_tone speaker; 
```

Refer to the Luddite, default keymap for an example how to add music to your macros.
