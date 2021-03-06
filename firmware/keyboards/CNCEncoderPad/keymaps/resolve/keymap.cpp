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
    {KEYMAP( LCTL(KC_B),    KC_NO,    LAYER_1, KC_J,    KC_K,    KC_L,  KC_DEL,    KC_NO,    KC_NO  )};

 
void setupKeymap() {
    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
     KEYMAP( MODE0,  KC_NO  ,    LAYER_1, MODE1,    MODE2,    MODE3,  MODE4,    MODE5,    KC_NO  );

    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_L1, Method::PRESS, layer1[row][col]);
        }
    }

// Code below makes sure that the encoder gets configured.
  keyboardstate.user1=0;
  keyboardstate.encoder1pos = 0; 
  RotaryEncoder.begin(ENCODER_PAD_A, ENCODER_PAD_B);    // Initialize Encoder
  RotaryEncoder.setCallback(encoder_callback);    // Set callback
  RotaryEncoder.start();    // Start encoder

resetleds();

}

    void resetleds ()
    {
        pinMode(LEDCOL0, OUTPUT);
        pinMode(LEDCOL1, OUTPUT);
        pinMode(LEDCOL2, OUTPUT);
        pinMode(LEDROW0, OUTPUT);
        pinMode(LEDROW1, OUTPUT);
        pinMode(LEDROW2, OUTPUT);
        digitalWrite(LEDCOL0, LOW);    
        digitalWrite(LEDCOL1, LOW); 
        digitalWrite(LEDCOL2, LOW); 
        digitalWrite(LEDROW0, LOW);
        digitalWrite(LEDROW1, LOW);
        digitalWrite(LEDROW2, LOW);
    } 

void encoder_callback(int step)
{
  keyboardstate.encoder1pos = keyboardstate.encoder1pos + step; 
  uint8_t layer = keyboardstate.layer;

  if (abs(keyboardstate.encoder1pos) > ENCODER_RESOLUTION)
  {
    if ( keyboardstate.encoder1pos < 0  )
    {
        switch(keyboardstate.user1)
        {
            case 0  : KeyScanner::add_to_encoderKeys(KC_VOLU); break;
            case 1  : KeyScanner::add_to_encoderKeys(LSFT(KC_RIGHT)); break;
            case 2  : KeyScanner::add_to_encoderKeys(KC_RIGHT); break;
            case 3  : KeyScanner::add_to_encoderKeys(KC_DOT); break;
            case 4  : KeyScanner::add_to_encoderKeys(LCTL(KC_PLUS)); break;
            default: ;
        }
    }else { 
        switch(keyboardstate.user1)
        {
            case 0  : KeyScanner::add_to_encoderKeys(KC_VOLD); break;
            case 1  : KeyScanner::add_to_encoderKeys(LSFT(KC_LEFT)); break;
            case 2  : KeyScanner::add_to_encoderKeys(KC_LEFT);break;
            case 3  : KeyScanner::add_to_encoderKeys(KC_COMMA);break;
            case 4  : KeyScanner::add_to_encoderKeys(LCTL(KC_MINUS)); break;
            default: ;
        }
    } 
    keyboardstate.encoder1pos = 0; 
  }
}

void process_user_macros(uint16_t macroid)
{
    switch ((macroid))
    { 
        case MODE0:
            keyboardstate.user1 = 0;
            resetleds();
        break;
        case MODE1:
            keyboardstate.user1 = 1;
            resetleds();
            pinMode(LEDCOL0, INPUT);
            pinMode(LEDCOL2, INPUT);            
            digitalWrite(LEDROW0, HIGH); 
        break;
        case MODE2:
            keyboardstate.user1 = 2;
            resetleds();
            pinMode(LEDCOL0, INPUT);
            pinMode(LEDCOL2, INPUT);            
            digitalWrite(LEDROW1, HIGH); 
        break;
        case MODE3:
            keyboardstate.user1 = 3;
            resetleds();
            pinMode(LEDCOL0, INPUT);
            pinMode(LEDCOL2, INPUT);            
            digitalWrite(LEDROW2, HIGH); 
        break;
        case MODE4:
            keyboardstate.user1 = 4;
            resetleds();
            pinMode(LEDCOL0, INPUT);
            pinMode(LEDCOL1, INPUT);            
            digitalWrite(LEDROW0, HIGH); 
        break;
        case MODE5:
            keyboardstate.user1 = 0;
            resetleds();
            pinMode(LEDCOL0, INPUT);
            pinMode(LEDCOL1, INPUT);            
            digitalWrite(LEDROW1, HIGH); 
        break;
    }
}