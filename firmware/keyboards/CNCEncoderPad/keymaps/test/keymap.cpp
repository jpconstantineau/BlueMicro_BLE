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
    {KEYMAP( KC_1,    KC_2,    KC_3, KC_4,    KC_5,    KC_6,  KC_7,    KC_8,    KC_9  )};

 
void setupKeymap() {
;

  // Code below makes sure that the encoder gets configured.
  RotaryEncoder.begin(ENCODER_PAD_A, ENCODER_PAD_B);    // Initialize Encoder
  RotaryEncoder.setCallback(encoder_callback);    // Set callback
  RotaryEncoder.start();    // Start encoder 

  // flash the leds in sequence to make sure they run fine...
  setled(1); delay(100);
  setled(2); delay(100);
  setled(3); delay(100);
  setled(4); delay(100);
  setled(5); delay(100);
  setled(6); delay(100);
  setled(7); delay(100);
  setled(8); delay(100);
  setled(9); delay(100);
  resetleds();

  // Play an obvious tune to check that speaker/buzzer works fine...
  speaker.playNoteNow(NOTE_G4, EIGHTH_TRIPLE, true);
  speaker.playNoteNow(NOTE_C5, EIGHTH_TRIPLE, true);
  speaker.playNoteNow(NOTE_E5, EIGHTH_TRIPLE, false);
  speaker.playNoteNow(NOTE_G5, EIGHTH, true);
  speaker.playNoteNow(NOTE_E5, SIXTEENTH, false);
  speaker.playNoteNow(NOTE_G5, HALF, false);

}

void encoder_callback(int step)
{
  keyboardstate.encoder1pos = keyboardstate.encoder1pos + step; 
  uint8_t layer = keyboardstate.layer;

  if (abs(keyboardstate.encoder1pos) > ENCODER_RESOLUTION)
  {
    if ( keyboardstate.encoder1pos < 0  )
    {
            switch(layer)
        {
            case _L0: KeyScanner::add_to_encoderKeys(LSFT(KC_DOT)); break;
            case _L1: KeyScanner::add_to_encoderKeys(KC_RIGHT); break;
            case _L2: KeyScanner::add_to_encoderKeys(LSFT(KC_RIGHT)); break;
            default: ;
        }
    }
    else 
    {
        switch(layer)
        {
            case _L0: KeyScanner::add_to_encoderKeys(LSFT(KC_COMMA)); break;
            case _L1: KeyScanner::add_to_encoderKeys(KC_LEFT);break;
            case _L2: KeyScanner::add_to_encoderKeys(LSFT(KC_LEFT));break;
            default: ;
        }
    } 
    keyboardstate.encoder1pos = 0; 
  } 
}

// Utility functions to handle LEDs
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

    void setled(int lednumber)
    {
    switch ((lednumber))
        { 
            case 0:
                resetleds();
            break;
            case 1:
                resetleds();
                pinMode(LEDCOL0, INPUT);
                pinMode(LEDCOL2, INPUT);            
                digitalWrite(LEDROW0, HIGH); 
            break;
            case 2:
                resetleds();
                pinMode(LEDCOL0, INPUT);
                pinMode(LEDCOL2, INPUT);            
                digitalWrite(LEDROW1, HIGH); 
            break;
            case 3:
                resetleds();
                pinMode(LEDCOL0, INPUT);
                pinMode(LEDCOL2, INPUT);            
                digitalWrite(LEDROW2, HIGH); 
            break;
            case 4:
                resetleds();
                pinMode(LEDCOL0, INPUT);
                pinMode(LEDCOL1, INPUT);            
                digitalWrite(LEDROW0, HIGH); 
            break;
            case 5:
                resetleds();
                pinMode(LEDCOL0, INPUT);
                pinMode(LEDCOL1, INPUT);            
                digitalWrite(LEDROW1, HIGH); 
            break;
            case 6:
                resetleds();
                pinMode(LEDCOL0, INPUT);
                pinMode(LEDCOL1, INPUT);            
                digitalWrite(LEDROW2, HIGH); 
            break;
            case 7:
                resetleds();
                pinMode(LEDCOL1, INPUT);
                pinMode(LEDCOL2, INPUT);            
                digitalWrite(LEDROW0, HIGH); 
            break;
            case 8:
                resetleds();
                pinMode(LEDCOL1, INPUT);
                pinMode(LEDCOL2, INPUT);            
                digitalWrite(LEDROW1, HIGH); 
            break;
            case 9:
                resetleds();
                pinMode(LEDCOL1, INPUT);
                pinMode(LEDCOL2, INPUT);            
                digitalWrite(LEDROW2, HIGH); 
            break;
        }
    }