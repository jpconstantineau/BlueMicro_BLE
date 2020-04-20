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

#ifndef HARDWAREVARIANTS_H
#define HARDWAREVARIANTS_H

/*
The following can be selected from the Tools->Boards Arduino Menu when compiling
NRF52832_FEATHER
NRF52840_FEATHER
NRF52840_ITSYBITSY
NRF52840_CIRCUITPLAY
NRF52840_METRO
NRF52840_PCA10056
*/

#define FEATHERNRF52832 0  // don't do any avr mapping
#define FEATHERNRF52840 0  // don't do any avr mapping

#define BLUEMICROV1_0   1
#define BLUEMICROV1_1   2
#define BLUEMICROV2_0   3
#define BLUEMICROV2_0B  4
#define BLUEMICROV2_0C  5
#define BLUENANO1_0     6
#define BLUENANO2_0     7
#define BLUEMICROV2_1A  8
#define BLUEMICRO840V1_0 9  // Needs ARDUINO_NRF52840_PCA10056 on the Arduino IDE
#define NICE_NANOV0_2 10


#define COL2ROW       0
#define ROW2COL       1

#define TEST 0
#define LEFT 1
#define RIGHT 2
#define MASTER 3

#endif  /*HARDWAREVARIANTS_H*/