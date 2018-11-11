/*
Copyright 2018 <Pierre Constantineau>

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
These defines map the AVR-based ports of the Arduino Pro to the NRF52832 GPIO pins.
This makes it simpler to migrate from the Arduino Pro Micro to the BlueMicro.
*/

#ifndef AVR_MAPPING_H
#define AVR_MAPPING_H

#define D3      17  //
#define D2      7   //
#define D1      25  //sda
#define D0      26  //scl
#define D4      27
#define C6      28
#define D7      29
#define E6      30
#define B4      15
#define B5      16

#define F4      5
#define F5      4
#define F6      3
#define F7      2
#define B1      12  //sck
#define B3      14  //miso
#define B2      13  //mosi
#define B6      11

#define BLUEMICRO 0
#define BLUEMACRO 1

/*
Common Defines.
*/
// ToDo: Move these defines to a more logical location.

#define COL2ROW       0
#define ROW2COL       1

#define TEST 0
#define LEFT 1
#define RIGHT 2
#define MASTER 3

#endif /* AVR_MAPPING_H */
