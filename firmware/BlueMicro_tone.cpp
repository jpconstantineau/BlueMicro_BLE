/*
Copyright 2018-2021 <Pierre Constantineau>

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
#include "BlueMicro_tone.h"


BlueMicro_tone::BlueMicro_tone(PersistentState* cfg, DynamicState* stat) // Constructor
{ 
    config=cfg;
    status=stat;
    _pin = 0;  /// default is 0 - this ensures that a pin is set before playing anything.
}

void BlueMicro_tone::setSpeakerPin(uint8_t pin)
{
    _pin = pin;
}


void BlueMicro_tone::playTone(toneList_t toneToPlay)
{
  toneQueue.push(toneToPlay);
}


void BlueMicro_tone::playToneNow(unsigned int frequency, unsigned long duration)
{
    if (_pin)
    {
  #ifdef SPEAKER_EN_PIN
    digitalWrite(SPEAKER_EN_PIN, HIGH);
    delay(50);
  #endif

  tone(_pin, frequency, duration);
  delay(duration);

  #ifdef SPEAKER_EN_PIN
    digitalWrite(SPEAKER_EN_PIN, LOW);
  #endif
  }
}

void BlueMicro_tone::playAllQueuedTonesNow()
{
  while (!toneQueue.empty())
  {
    NRF_WDT->RR[0] = WDT_RR_RR_Reload;    // pet watchdog
    processTones();
  }
}

void BlueMicro_tone::clearAllQueuedTones()
{
  while (!toneQueue.empty()) toneQueue.pop();
}


void BlueMicro_tone::processTones()
{
  if (!toneQueue.empty())
  {
    if (millis() - toneDelay < 750) return;

    toneList_t toneToPlay = toneQueue.front();
    toneQueue.pop();
    if (_pin)
    {
    #ifdef SPEAKER_EN_PIN
      digitalWrite(_pin, HIGH);
      delay(50);
    #endif

    switch (toneToPlay)
    {
      case TONE_STARTUP:
        tone(_pin, NOTE_E4, 50);
        delay(65);
        tone(_pin, NOTE_A4, 50);
        delay(65);
        tone(_pin, NOTE_E5, 50);
        delay(65);
      break;

      case TONE_BLE_PROFILE:
        for (uint8_t clicks = 0; clicks < (config->BLEProfile + 1); clicks++)
        {
          tone(_pin, TONE_A320_CLICK, 15);
          delay(250);
        }
      break;

      case TONE_BLE_CONNECT:
        tone(_pin, NOTE_B5, 100);
        delay(100);
        tone(_pin, NOTE_E6, 350);
        delay(350);
      break;

      case TONE_BLE_DISCONNECT:
        tone(_pin, NOTE_E6, 100);
        delay(100);
        tone(_pin, NOTE_B5, 350);
        delay(350);
      break;

      case TONE_SLEEP:
        tone(_pin, NOTE_E5, 50);
        delay(65);
        tone(_pin, NOTE_A4, 50);
        delay(65);
        tone(_pin, NOTE_E4, 50);
        delay(65);
      break;
    }

    #ifdef SPEAKER_EN_PIN
      digitalWrite(SPEAKER_EN_PIN, LOW);
    #endif
    }
    toneDelay = millis();
  }
}

std::queue<toneList_t> BlueMicro_tone::toneQueue;
uint32_t BlueMicro_tone::toneDelay = 0;
PersistentState*  BlueMicro_tone::config = NULL;
DynamicState*  BlueMicro_tone::status  = NULL;
namespace std
{
  void __throw_bad_alloc() { while(true); }
}