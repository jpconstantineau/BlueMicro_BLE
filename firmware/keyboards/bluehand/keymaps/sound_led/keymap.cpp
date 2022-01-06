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

/*
Sample keymap for demonstrating sound output and LED control.

In order to use sound in other keymaps, add the following to keymap.h:
    #define ENABLE_AUDIO
    #include "BlueMicro_tone.h"
    extern BlueMicro_tone speaker;

SPEAKER_PIN must also be defined in hardware_config.h For bluehand the pin is 45:
    #define SPEAKER_PIN 45

For LED control, LED pins should be defined in hardware_config.h, For bluehand those pins are:
    #define LED_G 42 //Green
    #define LED_R 36 //Red

As a one time setup, enable the LED pins for output:
    pinMode(LED_G, OUTPUT);
    pinMode(LED_R, OUTPUT);

Then turned on with
    digitalWrite(LED_G, HIGH);
and off with
    digitalWrite(LED_G, LOW);

*/

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {{
        MC0,    MC1,    MC2,    MC3,
        MC4,    MC5,    MC6,    MC7
    }};

 
void setupKeymap() {
    pinMode(LED_G, OUTPUT);
    pinMode(LED_R, OUTPUT);
}

void process_user_macros(uint16_t macroid) {
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_R, LOW);

    switch(macroid) {
        case MC0: 
            digitalWrite(LED_G, HIGH);
            speaker.playTone(TONE_STARTUP);
            speaker.playAllQueuedTonesNow();
        break;
        case MC1: 
            digitalWrite(LED_R, HIGH);
            speaker.playNoteNow(NOTE_A4, EIGHTH_TRIPLE, true);
            speaker.playNoteNow(NOTE_B4, EIGHTH_TRIPLE);
            speaker.playNoteNow(NOTE_D5, EIGHTH_TRIPLE, true);
            speaker.playNoteNow(NOTE_B4, EIGHTH_TRIPLE);
            speaker.playNoteNow(NOTE_FS5, QUARTER);
            speaker.playNoteNow(NOTE_FS5, QUARTER);
            speaker.playNoteNow(NOTE_E5, EIGHTH);
        break;
        case MC2: 
            digitalWrite(LED_G, HIGH);
            speaker.playNoteNow(NOTE_A4, HALF);
        break;
        case MC3: 
            digitalWrite(LED_R, HIGH);
            speaker.playNoteNow(NOTE_A4, SIXTEENTH);
        break;
        case MC4: 
            // Play a little charge melody, from:
            // https://en.wikipedia.org/wiki/Charge_(fanfare)
            speaker.playNoteNow(NOTE_G4, EIGHTH_TRIPLE, true);
            speaker.playNoteNow(NOTE_C5, EIGHTH_TRIPLE, true);
            speaker.playNoteNow(NOTE_E5, EIGHTH_TRIPLE, false);
            speaker.playNoteNow(NOTE_G5, EIGHTH, true);
            speaker.playNoteNow(NOTE_E5, SIXTEENTH, false);
            speaker.playNoteNow(NOTE_G5, HALF, false);
        break;
        case MC5:  
            digitalWrite(LED_G, HIGH);
            speaker.playNoteNow(NOTE_G5, QUARTER, true);
            digitalWrite(LED_G, LOW);
            speaker.playNoteNow(NOTE_FS5, EIGHTH);
            digitalWrite(LED_G, HIGH);
            speaker.playNoteNow(NOTE_G5, QUARTER, true);
            digitalWrite(LED_G, LOW);
            speaker.playNoteNow(NOTE_D5, EIGHTH);
            digitalWrite(LED_G, HIGH);
            speaker.playNoteNow(NOTE_E5, EIGHTH_TRIPLE);
            digitalWrite(LED_G, LOW);
            speaker.playNoteNow(NOTE_E5, EIGHTH_TRIPLE);
        break;
        case MC6:
            digitalWrite(LED_G, HIGH);
            digitalWrite(LED_R, HIGH);
        break;
        case MC7: 
            // Play happy birthday tune, from:
            // http://www.irish-folk-songs.com/happy-birthday-tin-whistle-sheet-music.html#.WXFJMtPytBw
            digitalWrite(LED_G, HIGH);
            speaker.playNoteNow(NOTE_D4, EIGHTH, true);
            speaker.playNoteNow(NOTE_D4, EIGHTH);
            digitalWrite(LED_G, LOW);
            digitalWrite(LED_R, HIGH);
            speaker.playNoteNow(NOTE_E4, QUARTER);       // Bar 1
            speaker.playNoteNow(NOTE_D4, QUARTER);
            speaker.playNoteNow(NOTE_G4, QUARTER);
            digitalWrite(LED_G, HIGH);
            digitalWrite(LED_R, LOW);
            speaker.playNoteNow(NOTE_FS4, HALF);         // Bar 2
            speaker.playNoteNow(NOTE_D4, EIGHTH, true);
            speaker.playNoteNow(NOTE_D4, EIGHTH);
            digitalWrite(LED_G, LOW);
            digitalWrite(LED_R, HIGH);
            speaker.playNoteNow(NOTE_E4, QUARTER);       // Bar 3
            speaker.playNoteNow(NOTE_D4, QUARTER);
            speaker.playNoteNow(NOTE_A4, QUARTER);
            digitalWrite(LED_G, HIGH);
            digitalWrite(LED_R, LOW);
            speaker.playNoteNow(NOTE_G4, HALF);          // Bar 4
            speaker.playNoteNow(NOTE_D4, EIGHTH, true);
            speaker.playNoteNow(NOTE_D4, EIGHTH);
            digitalWrite(LED_G, LOW);
            digitalWrite(LED_R, HIGH);
            speaker.playNoteNow(NOTE_D5, QUARTER);       // Bar 5
            speaker.playNoteNow(NOTE_B4, QUARTER);
            speaker.playNoteNow(NOTE_G4, QUARTER);
            digitalWrite(LED_G, HIGH);
            digitalWrite(LED_R, LOW);
            speaker.playNoteNow(NOTE_FS4, QUARTER);      // Bar 6
            speaker.playNoteNow(NOTE_E4, QUARTER);
            speaker.playNoteNow(NOTE_C5, EIGHTH, true);
            speaker.playNoteNow(NOTE_C5, EIGHTH);
            digitalWrite(LED_G, LOW);
            digitalWrite(LED_R, HIGH);
            speaker.playNoteNow(NOTE_B4, QUARTER);       // Bar 7
            speaker.playNoteNow(NOTE_G4, QUARTER);
            speaker.playNoteNow(NOTE_A4, QUARTER);
            digitalWrite(LED_G, HIGH);
            digitalWrite(LED_R, LOW);
            speaker.playNoteNow(NOTE_G4, HALF);          // Bar 8
            digitalWrite(LED_G, LOW);
        break;
    }

}

