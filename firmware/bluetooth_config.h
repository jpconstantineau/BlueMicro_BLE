/*
Copyright 2018-2020 <Pierre Constantineau>

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

#ifndef BLUETOOTH_CONFIG_H
#define BLUETOOTH_CONFIG_H


// NEW BLE KEYBOARD LINK BLE SERVICE & CHARACTERISTICS  -- randomly generated UUID. DO NOT CHANGE. 
#define UUID128_SVC_KEYBOARD_LINK             0xf9ed59d396fa4752a7dfb16d7b9e0443           // SERVICE TO BE RUN ON SLAVES. "CLIENT" TO RUN ON MASTER
#define UUID128_CHR_KEYBOARD_LAYERS           0xccccc76aa03d43f993ec2fc6d82a7902           // 1 Byte for Active Layer
#define UUID128_CHR_KEYBOARD_LAYER_REQUEST    0xae31cd09b0734df5b5bd20baaf18239c           // 1 Byte for request from Master to Slaves to change layer 
#define UUID128_CHR_KEYBOARD_BUFFER           0x220f9018372a46da81d3cd196a57d5ab           // 7 Bytes for passing HID MODS and BUFFER from Slave to Master
#define UUID128_COUNT 4


/***************************************************************************/
/*   Maximum current (current peaks) when radio is ON broadcasting         */
/*   Measured on E73 modules without power circuitry                       */
/*   Measured and Powered using a Nordic Power Profiler                    */
/*   over a measurement window of 17.8 seconds                             */
/*                                                                         */
/*   DEVICE_POWER                   nrf52832                nrf52840       */
/*   -40                                                    16.245mA       */
/*   -30                                                    20.23 mA (1)   */
/*   -20                                                    16.63 mA       */
/*   -16                                                    17.35 mA       */
/*   -12                                                    17.93 mA       */
/*    -8                                                    18.87 mA       */
/*    -4                                                    19.03 mA       */
/*     0                                                    19.99 mA       */ 
/*     4                                                    30.52 mA (1)   */    
/*     8                              n/a                   42.64 mA (1)   */
/*                                                                         */
/*   Notes:                                                                */
/*   (1) Measured twice for double-checking...                             */
/*   (2) The table above show max current over a long period and is only   */
/*       representative of peak current needed.  Average current needed    */
/*       is much lower. For example, during another test at a power of 0,  */
/*       average current consumption over a period of 17.8 seconds was     */
/*       975 uA while max current was 20.62 mA, When bluetooth is off,     */
/*       average current consumption is only 152 uA indicating that peak   */
/*       contribution is 43% of the total time                             */
/*       Enabling PWM device increases the baseline                        */
/*       current consumption to 723 uA                                     */
/*   (3) updating the slave_latency to a non-zero value decreased average  */
/*       current consumption by about 300uA                                */
/*       Note that this only applies when connected                        */
/***************************************************************************/

// Set max power. Accepted values are: -40, -30, -20, -16, -12, -8, -4, 0, 4 
#ifndef DEVICE_POWER
  #define DEVICE_POWER                        0                    // Use 0.  This uses less power and allows for a longer battery life. See above...
#endif
#define FILTER_RSSI_BELOW_STRENGTH -90

// These can be modified.  Not sure of what values are allowed.
#define PNP_ID_VENDOR_ID_SOURCE             0x02                                       /**< Vendor ID Source. */
#define PNP_ID_VENDOR_ID                    0x1915                                     /**< Vendor ID. */
#define PNP_ID_PRODUCT_ID                   0xEEEE                                     /**< Product ID. */
#define PNP_ID_PRODUCT_VERSION              0x0001                                     /**< Product Version. */


#endif /* BLUETOOTH_CONFIG_H */
