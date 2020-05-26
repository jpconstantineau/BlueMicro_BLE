/*
Copyright 2019 <Pierre Constantineau>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

/*
 GPIO extension files / library added by Coyt Barringer
*/

#include "gpioExtension.h"

//********************************************************************************************//
//* Helper functions for Keyboards using Shift Registers to drive columns high in order to   *//
//* save I/O on nrf52840                                                                     *//
//* Shift register code is currently setup to use                                            *//
//********************************************************************************************//

void setupShiftRegisters(){
    //inits the shift register pins as outputs and makes them low
    pinMode(SER_LATCH, OUTPUT);
    pinMode(SER_DATA, OUTPUT);
    pinMode(SER_CLK, OUTPUT);

    digitalWrite(SER_LATCH, HIGH);
    digitalWrite(SER_DATA, LOW);
    digitalWrite(SER_CLK, LOW);
}

//makes a specific "pin" high
void shiftOutToMakePinHigh(int pin){

    uint16_t shiftValue = pow(2, pin);
    uint8_t shiftValLow = shiftValue & 0xFF;
    uint8_t shiftValHigh = (shiftValue & 0xFF00) >> 8;

    digitalWrite(SER_LATCH, LOW);
    shiftOut(SER_DATA, SER_CLK, MSBFIRST, shiftValHigh); //first number to 255
    shiftOut(SER_DATA, SER_CLK, MSBFIRST, shiftValLow); //second number to 255
    digitalWrite(SER_LATCH, HIGH);
}

//makes a specific "pin" low
void shiftOutToMakePinLow(int pin){

    uint16_t shiftValue = pow(2, pin);
    uint8_t shiftValLow = shiftValue & 0xFF;
    uint8_t shiftValHigh = (shiftValue & 0xFF00) >> 8;

    digitalWrite(SER_LATCH, LOW);
    shiftOut(SER_DATA, SER_CLK, MSBFIRST, shiftValHigh); //first number to 255
    shiftOut(SER_DATA, SER_CLK, MSBFIRST, shiftValLow); //second number to 255
    digitalWrite(SER_LATCH, HIGH);
}

void shiftOutToMakeAllLow(){

    uint8_t shiftValLow = 0x00;
    uint8_t shiftValHigh = 0x00;

    digitalWrite(SER_LATCH, LOW);
    shiftOut(SER_DATA, SER_CLK, LSBFIRST, shiftValHigh); //first number to 255
    shiftOut(SER_DATA, SER_CLK, LSBFIRST, shiftValLow); //second number to 255
    digitalWrite(SER_LATCH, HIGH);
}

void shiftOutToMakeAllHigh(){

    uint8_t shiftValLow = 0xFF;
    uint8_t shiftValHigh = 0xFF;

    digitalWrite(SER_LATCH, LOW);
    shiftOut(SER_DATA, SER_CLK, LSBFIRST, shiftValHigh); //first number to 255
    shiftOut(SER_DATA, SER_CLK, LSBFIRST, shiftValLow); //second number to 255
    digitalWrite(SER_LATCH, HIGH);
}

