

#include <Arduino.h>
#include <bluefruit.h>
BLEDis bledis;
BLEHidAdafruit blehid;
int pinlist1 [2] ={ 42, 36};
uint8_t pins[]    = { 29, 2, 28, 3, 10, 9, 24, 13};
#ifndef PIN_BUZZER
#define PIN_BUZZER    45 //1.13
#endif


// A few music note frequencies as defined in this tone example:
//   https://www.arduino.cc/en/Tutorial/toneMelody
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988

// Define note durations.  You only need to adjust the whole note
// time and other notes will be subdivided from it directly.
#define WHOLE         2200       // Length of time in milliseconds of a whole note (i.e. a full bar).
#define HALF          WHOLE/2
#define QUARTER       HALF/2
#define EIGHTH        QUARTER/2
#define EIGHTH_TRIPLE QUARTER/3
#define SIXTEENTH     EIGHTH/2

// Play a note of the specified frequency and for the specified duration.
// Hold is an optional bool that specifies if this note should be held a
// little longer, i.e. for eigth notes that are tied together.
// While waiting for a note to play the waitBreath delay function is used
// so breath detection and pixel animation continues to run.  No tones
// will play if the slide switch is in the -/off position or all the
// candles have been blown out.
void playNote(int frequency, int duration, bool hold=false, bool measure=true) {
  (void) measure;

  if (hold) {
    // For a note that's held play it a little longer than the specified duration
    // so it blends into the next tone (but there's still a small delay to 
    // hear the next note).
    tone(PIN_BUZZER, frequency, duration + duration/32);
  }
  else {
    // For a note that isn't held just play it for the specified duration.
    tone(PIN_BUZZER, frequency, duration);
  }

  delay(duration + duration/16);
}

// Song to play when the candles are blown out.
void celebrateSong() {
  // Play a little charge melody, from:
  //  https://en.wikipedia.org/wiki/Charge_(fanfare)
  // Note the explicit boolean parameters in particular the measure=false
  // at the end.  This means the notes will play without any breath measurement
  // logic.  Without this false value playNote will try to keep waiting for candles
  // to blow out during the celebration song!
  playNote(NOTE_G4, EIGHTH_TRIPLE, true, false);
  playNote(NOTE_C5, EIGHTH_TRIPLE, true, false);
  playNote(NOTE_E5, EIGHTH_TRIPLE, false, false);
  playNote(NOTE_G5, EIGHTH, true, false);
  playNote(NOTE_E5, SIXTEENTH, false);
  playNote(NOTE_G5, HALF, false);
}

void setup() {


// this is the code needed to change the default voltage from the on chip voltage regulator.
// see https://infocenter.nordicsemi.com/pdf/nRF52840_PS_v1.0.pdf page 45

    if (NRF_UICR->REGOUT0 != UICR_REGOUT0_VOUT_3V3) {
    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
    NRF_UICR->REGOUT0 = UICR_REGOUT0_VOUT_3V3;

    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
        delay(500);
        NVIC_SystemReset();
    }

// this code is needed to switch the nfc pins to standard GPIOs.
    if ((NRF_UICR->NFCPINS & UICR_NFCPINS_PROTECT_Msk) == (UICR_NFCPINS_PROTECT_NFC << UICR_NFCPINS_PROTECT_Pos)){
        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy);
        NRF_UICR->NFCPINS &= ~UICR_NFCPINS_PROTECT_Msk;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy);
        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy);
        Serial.println("Done");
        delay(500);
        NVIC_SystemReset();
      }
  
  // Initialize serial output and Circuit Playground library.
  Serial.begin(115200);

  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);


 Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("BlueHand");
  bledis.setManufacturer("jpconstantineau.com");
  bledis.setModel("BlueHand Tester");
  bledis.begin();
  blehid.begin();
  startAdv();
  for (int i = 0; i< 2; i++ )
  {
    pinMode(pinlist1[i], OUTPUT);
  }

  // set up pin as input
  for (uint8_t i=0; i<8; i++)
  {
    pinMode(pins[i], INPUT_PULLUP);
  }

  
  celebrateSong();
}

void flashpin(int pinno)
{
  digitalWrite(pinno, LOW); delay(100); digitalWrite(pinno, HIGH);  delay(100);digitalWrite(pinno, LOW); 
  }
  
void startAdv(void)
{  
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  // Include BLE HID service
  Bluefruit.Advertising.addService(blehid);

  // There is enough room for the dev name in the advertising packet
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds

  
}

void loop() {
  static int i = 0;
  flashpin(pinlist1[i]);
  i++;
  if (i ==2){i=0;}    

    if ( 0 == digitalRead(pins[0]) )
    {
       playNote(NOTE_A4, SIXTEENTH, false);
    }
    if ( 0 == digitalRead(pins[1]) )
    {
       playNote(NOTE_B4, SIXTEENTH, false);
    }

    if ( 0 == digitalRead(pins[2]) )
    {
       playNote(NOTE_C5, SIXTEENTH, false);
    }
    if ( 0 == digitalRead(pins[3]) )
    {
       playNote(NOTE_D5, SIXTEENTH, false);
    }
    if ( 0 == digitalRead(pins[4]) )
    {
       playNote(NOTE_E5, SIXTEENTH, false);
    }
    if ( 0 == digitalRead(pins[5]) )
    {
       playNote(NOTE_F5, SIXTEENTH, false);
    }

    if ( 0 == digitalRead(pins[6]) )
    {
       playNote(NOTE_G5, SIXTEENTH, false);
    }
    if ( 0 == digitalRead(pins[7]) )
    {
       playNote(NOTE_A5, SIXTEENTH, false);
    }
  
}

void rtos_idle_callback(void)
{
  // Don't call any other FreeRTOS blocking API()
  // Perform background task(s) here
}
