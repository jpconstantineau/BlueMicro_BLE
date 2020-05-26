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
Working keyboard config for LOST60 V1.0 hardware (no shift registers)
and for LOST60 V2.0 hardware (shift registers for scanning columns)
NOTE: uses modified "Variant.cpp" for adafruit_feather_nrf52840 to fix pin mappings
*/


#ifndef KEYBOARD_CONFIG_H
#define KEYBOARD_CONFIG_H
#include "hardware_variants.h"
#define HARDWARE_MAPPING  BLUEMICRO840V1_0  // note only the BlueMicro840 fits on the corne.
#include "avr_mapping.h"


//********** START CORE Configuration Selection **********
// COMMENT OUT ALL EXCEPT ONE OF THE FOLLOWING:

#define LOST60_VER_ONE    //this selects code for version 1 of the LOST60 with much less features - used for legacy systems
//#define LOST60_VER_TWO    //this selects code for version 2 of the LOST60 with significant updates in features.

//just for testing pin mappings quickly - comment out all except one
//#define PCA10056_MAPPING
//#define FEATHER_MAPPING

//********** END CORE Configuration Selection ************


//Selector for config based on version of keyboard
#if defined(LOST60_VER_TWO) 							//for LOST60 V2.0

 	//#define SHIFT_REGISTER_KEYBOARD

	#if defined(PCA10056_MAPPING)
		//setup pins for shift register / i/o expander if this is what we're using
		#define SER_DATA        45 // is P1.13
		#define SER_CLK         46 // is P1.14
		#define SER_LATCH       47 // is P1.15
	#else 
		//setup pins for shift register / i/o expander if this is what we're using
		#define SER_DATA        42      // D42 is P1.13
		#define SER_CLK         43      // D43 is P1.14
		#define SER_LATCH       3       // D3  is P1.15
	#endif 

	#define DEVICE_NAME_R                         	"LOST60 V2 RIGHT"                          	/**< Name of device. Will be included in the advertising data. */
	#define DEVICE_NAME_L                        	"LOST60 V2 LEFT"                          	/**< Name of device. Will be included in the advertising data. */
	#define DEVICE_NAME_M                         	"LOST60 V2"                          		/**< Name of device. Will be included in the advertising data. */
	#define DEVICE_MODEL                        	"LOST60 V2"                          		/**< Name of device. Will be included in the advertising data. */
	#define MANUFACTURER_NAME                   	"Lizard Power Systems"                      /**< Manufacturer. Will be passed to Device Information Service. */

	//HARDWARE DEFINITION
	// key matrix size 
	#define MATRIX_ROWS 5
	#define MATRIX_COLS 14

	//pin definitions for rows
	#if defined(PCA10056_MAPPING)
		#define MATRIX_ROW_PINS {43, 9, 27, 28, 8}
	#else 
		#define MATRIX_ROW_PINS {40, 33, 10, 17, 12}
	#endif 

	//these colums do nothing now, but are needed for code to compile - because we haven't tackled full integration
	//into power optimization code yet. 
	#define MATRIX_COL_PINS {1} //remove this somehow? / not used if a shift register keyboard is used

	// if keyboard hardware uses shift registers for I/O expansion within the matrix itself
	// NOTE: only Shifting Out (I.E. driving shift register pins high) is supported. We can't read from shift registers yet
	#define SHIFT_REGISTER_KEYBOARD

	/* READ_ON_ROWS or READ_ON_COLS */
	#define READ_DIRECTION READ_ON_ROWS

	/* COL2ROW or ROW2COL */
	#define DIODE_DIRECTION ROW2COL //LOST60 V2.0 (shift registers)

	//led pin definition
	#if defined(PCA10056_MAPPING)
		#define MYLED           7 // is on P0.07
	#else 
		#define MYLED           6       //D6 is on P0.07
	#endif 

	//QSPI Pins
	//already defined and wired as the default in Variant.cpp

	//for switch backlighting leds
	#define UNDERGLOW_LED_ON 1
	#if defined(PCA10056_MAPPING)
		#define ULED_CLK        13 		// is on P0.13
		#define ULED_SIN        14 		// is on P0.14  
		#define ULED_LATCH      15 		// is on P0.15 
		#define ULED_BLANK      16 		// is on P0.16

		#define ULED_ROW1       29 		//is on P0.29
		#define ULED_ROW2       26 		//is on P0.26
		#define ULED_ROW3       44 		//is on P1.12
		#define ULED_ROW4       30 		//is on P0.30
		#define ULED_ROW5       31 		//is on P0.31 
	#else 
		#define ULED_CLK        25      // D25 is P0.13
		#define ULED_SIN        26      // D26 is P0.14  
		#define ULED_LATCH      24      // D24 is on P0.15 
		#define ULED_BLANK      8       // D8 is on P0.16

		#define ULED_ROW1       20      // D20 is A6 on P0.29
		#define ULED_ROW2       9       // D9 on P0.26
		#define ULED_ROW3       45      // D45 on P1.12
		#define ULED_ROW4       16      // D16 is P0.30 (A2)
		#define ULED_ROW5       21      // D21 is P0.31 (A7, ARef)
	#endif 

	//Speaker Pins
	#define AUDIO_ON 1
	#if defined(PCA10056_MAPPING)
		#define SPEAKER_A       2 		//is P0.02 
		#define SPEAKER_B       3 		//is P0.03 
	#else 
		#define SPEAKER_A       18      // D18 is P0.02 (A4)
		#define SPEAKER_B       19      // D19 is P0.03 (A5)
	#endif 

	//Rotary Encoder Pins
	#if defined(PCA10056_MAPPING)
		#define ROTARY_A        5 		// P0.05
		#define ROTARY_B        6 		// P0.06
	#else 
		#define ROTARY_A        15      // D15 is P0.05 (A1)
		#define ROTARY_B        11      // D11 is P0.06
	#endif 

	//I2C Bus Pins
	#if defined(PCA10056_MAPPING)
		#define SCL_PIN         11 		//is P0.11
		#define SDA_PIN         12 		//is P0.12
	#else 
		#define SCL_PIN         23      // D23 is P0.11 (SCL)
		#define SDA_PIN         22      // D22 is P0.12 (SDA)
	#endif 

	//#define BACKLIGHT_PWM_ON 0
	#if defined(PCA10056_MAPPING)
		#define WS2812B_LED_PIN 4 				//is P0.04
		#define WS2812B_LED_LOAD_SWITCH_PIN 10 	//is P0.10 (NFC2) //enable load switch to turn neopixels on 
	#else 
		#define WS2812B_LED_PIN 14 				//D14 is P0.04 (A0)
		#define WS2812B_LED_LOAD_SWITCH_PIN 2 	//D2  is P0.10 (NFC2) //enable load switch to turn neopixels on 
	#endif 

	#define WS2812B_LED_LOAD_SWITCH		  	//define this if a hardware load switch is attached to ws2812b for lower power draw
	#define WS2812B_LED_COUNT 12
	#define WS2812B_LED_ON 1 

#else 													//for LOST60 V1.0 or other

	#define DEVICE_NAME_R                         	"LOST60 V1 RIGHT"                          	/**< Name of device. Will be included in the advertising data. */
	#define DEVICE_NAME_L                        	"LOST60 V1 LEFT"                          	/**< Name of device. Will be included in the advertising data. */
	#define DEVICE_NAME_M                         	"LOST60 V1"                          		/**< Name of device. Will be included in the advertising data. */
	#define DEVICE_MODEL                        	"LOST60 V1"                          		/**< Name of device. Will be included in the advertising data. */
	#define MANUFACTURER_NAME                   	"Lizard Power Systems"                      /**< Manufacturer. Will be passed to Device Information Service. */

	//HARDWARE DEFINITION
	// key matrix size 
	#define MATRIX_ROWS 5
	#define MATRIX_COLS 14

	//pin definitions for rows and cols
	#if defined(PCA10056_MAPPING)
		#define MATRIX_ROW_PINS {24, 21, 27, 28, 20}
		#define MATRIX_COL_PINS {37, 38, 39, 40, 41, 22, 46, 45, 42, 47, 33, 36, 35, 34}
	#else 
		#define MATRIX_ROW_PINS {1, 32, 10, 17, 28}
		#define MATRIX_COL_PINS {37, 38, 39, 5, 13, 30, 43, 42, 4, 3, 34, 36, 35, 7}
	#endif 

	/*
	// HARDWARE DEFINITION
	// KEY MATRIX COLS AND ROWS FLIPPED
	// key matrix size
	#define MATRIX_ROWS 14//4
	#define MATRIX_COLS 5//6
	#define MATRIX_ROW_PINS {37, 38, 39, 5, 13, 30, 43, 42, 4, 3, 34, 36, 35, 7} //{ D4, C6, D7, E6 }
	#define MATRIX_COL_PINS {1, 32, 10, 17, 28}//{ F4, F5, F6, F7, B1, B3 }
	*/

	/* READ_ON_ROWS or READ_ON_COLS */
	#define READ_DIRECTION READ_ON_ROWS

	/* COL2ROW or ROW2COL */
	#define DIODE_DIRECTION COL2ROW //LOST60 V1.0 (no shift registers)

	//led pin definition
	//#if defined(PCA10056_MAPPING)
	//	#define MYLED           7 // is on P0.07
	//#else 
	//	#define MYLED           6       //D6 is on P0.07
	//#endif 

	//#define VBATPIN A4 //D18 is A4 on P0.02 where voltage divider is connected

	//for switch underlighting leds
	#define UNDERGLOW_LED_ON 1
	#if defined(PCA10056_MAPPING)
		#define ULED_CLK    17		// is on P0.17
		#define ULED_SIN    14 		// is on P0.14 
		#define ULED_LATCH  15 		// is on P0.15 
		#define ULED_BLANK  16 		// is on P0.16

		#define ULED_ROW1   29 		// is on P0.29
		#define ULED_ROW2   26 		// is on P0.26
		#define ULED_ROW3   44 		// is on P1.12
		#define ULED_ROW4   23 		// is on P0.23
		#define ULED_ROW5   25 		// is on P0.25
	#else 
		#define ULED_CLK    29 		// D29 is on P0.17
		#define ULED_SIN    26 		// D26 is on P0.14 
		#define ULED_LATCH  24 		// D24 is on P0.15 
		#define ULED_BLANK  8  		// D8 is on P0.16

		#define ULED_ROW1   20 		// D20 is A6 on P0.29
		#define ULED_ROW2   9  		// D9 on P0.26
		#define ULED_ROW3   45 		// D45 on P1.12
		#define ULED_ROW4   31 		// D31 is on P0.23
		#define ULED_ROW5   0  		// D0 is on P0.25
	#endif 


	//#define BACKLIGHT_PWM_ON 0
	#if defined(PCA10056_MAPPING)
		#define WS2812B_LED_PIN 			4 	// is P0.04 
		#define WS2812B_LED_LOAD_SWITCH_PIN 30 	// is P0.30 //enable load switch to turn neopixels on //D16 is A2 on P0.30
	#else 
		#define WS2812B_LED_PIN 			14 	// D14 is P0.04 
		#define WS2812B_LED_LOAD_SWITCH_PIN 16 	// D16 is P0.30 (A2) //enable load switch to turn neopixels on //D16 is A2 on P0.30
	#endif 

	#define WS2812B_LED_LOAD_SWITCH		  //define this if a hardware load switch is attached to ws2812b for lower power draw
	#define WS2812B_LED_COUNT 12 
	#define WS2812B_LED_ON 1 

#endif 

#define KEYBOARD_SIDE MASTER
// CHANGE THIS FOR THE KEYBOARD TO MATCH WHAT IS BEING FLASHED. OPTIONS: LEFT  RIGHT  MASTER

#define UNUSED_PINS {}

//lost60 pin mapping macro - used for more easily setting up QMK style layers in keymap.cpp
#define KEYMAP( \
	 K00,   K01,   K02,   K03,  K04,   K05,   K06,   K07,  K08,   K09,   K010,   K011,	K012,	K013,   \
	 K10,   K11,   K12,   K13,  K14,   K15,   K16,   K17,  K18,   K19,   K110,   K111,	K112,	K113,  	\
	 K20,   K21,   K22,   K23,  K24,   K25,   K26,   K27,  K28,   K29,   K210,   K211,	K212,	K213,  	\
	 K30,   K31,   K32,   K33,  K34,   K35,   K36,   K37,  K38,   K39,   K310,   K311,	K312,	K313,	\
	 K40,   K41,   K42,   K43,  K44,   K45,   K46,   K47,  K48,   K49,   K410,   K411,	K412,	K413	\
) { \
	{ K00,   K01,   K02,   K03, K04,   K05,   K06,   K07,  K08,   K09,   K010,   K011,	K012,	K013,  }, \
	{ K10,   K11,   K12,   K13, K14,   K15,   K16,   K17,  K18,   K19,   K110,   K111,	K112,	K113,  }, \
	{ K20,   K21,   K22,   K23, K24,   K25,   K26,   K27,  K28,   K29,   K210,   K211,	K212,	K213,  }, \
	{ K30,   K31,   K32,   K33, K34,   K35,   K36,   K37,  K38,   K39,   K310,   K311,	K312,	K313,  },  \
	{ K30,   K31,   K32,   K33, K34,   K35,   K36,   K37,  K38,   K39,   K310,   K311,	K412,	K413  } \
}

#endif /* KEYBOARD_CONFIG_H */