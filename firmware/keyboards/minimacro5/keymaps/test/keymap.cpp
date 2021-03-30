/*
Copyright 2018 <Pierre Constantineau>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include "keymap.h"

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP( KC_1,    KC_2,    KC_3, KC_4,    KC_5 )};

SwRotaryEncoder RotaryEncoder1,RotaryEncoder2, RotaryEncoder3, RotaryEncoder4, RotaryEncoder5;

void setupKeymap() {
;
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


  //RotaryEncoder.start();    // Start encoder

}

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