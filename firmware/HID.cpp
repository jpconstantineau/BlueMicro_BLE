/*
Copyright 2020-2021 <Pierre Constantineau>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include "HID.h"

uint16_t hid_GetMediaUsageCode(uint16_t keycode) {
  uint16_t usagecode = 0;

  switch (keycode) {
  case KC_SYSTEM_POWER:
    usagecode = HID_USAGE_CONSUMER_POWER;
    break;
  case KC_SYSTEM_RESET:
    usagecode = HID_USAGE_CONSUMER_RESET;
    break;
  case KC_SYSTEM_SLEEP:
    usagecode = HID_USAGE_CONSUMER_SLEEP;
    break;
  case KC_DISPLAY_BRIGHTI:
    usagecode = HID_USAGE_CONSUMER_BRIGHTNESS_INCREMENT;
    break;
  case KC_DISPLAY_BRIGHTD:
    usagecode = HID_USAGE_CONSUMER_BRIGHTNESS_DECREMENT;
    break;
  case KC_RADIO_CONTROL:
    usagecode = HID_USAGE_CONSUMER_WIRELESS_RADIO_CONTROLS;
    break;
  case KC_RADIO_BUTTONS:
    usagecode = HID_USAGE_CONSUMER_WIRELESS_RADIO_BUTTONS;
    break;
  case KC_RADIO_LED:
    usagecode = HID_USAGE_CONSUMER_WIRELESS_RADIO_LED;
    break;
  case KC_RADIO_SWITCH:
    usagecode = HID_USAGE_CONSUMER_WIRELESS_RADIO_SLIDER_SWITCH;
    break;
  case KC_MEDIA_PLAY_PAUSE:
    usagecode = HID_USAGE_CONSUMER_PLAY_PAUSE;
    break;
  case KC_MEDIA_NEXT_TRACK:
    usagecode = HID_USAGE_CONSUMER_SCAN_NEXT;
    break;
  case KC_MEDIA_PREV_TRACK:
    usagecode = HID_USAGE_CONSUMER_SCAN_PREVIOUS;
    break;
  case KC_MEDIA_STOP:
    usagecode = HID_USAGE_CONSUMER_STOP;
    break;
  case KC_AUDIO_VOL:
    usagecode = HID_USAGE_CONSUMER_VOLUME;
    break;
  case KC_AUDIO_MUTE:
    usagecode = HID_USAGE_CONSUMER_MUTE;
    break;
  case KC_AUDIO_BASS:
    usagecode = HID_USAGE_CONSUMER_BASS;
    break;
  case KC_AUDIO_TREBLE:
    usagecode = HID_USAGE_CONSUMER_TREBLE;
    break;
  case KC_AUDIO_BASS_BOOST:
    usagecode = HID_USAGE_CONSUMER_BASS_BOOST;
    break;
  case KC_AUDIO_VOL_UP:
    usagecode = HID_USAGE_CONSUMER_VOLUME_INCREMENT;
    break;
  case KC_AUDIO_VOL_DOWN:
    usagecode = HID_USAGE_CONSUMER_VOLUME_DECREMENT;
    break;
  case KC_AUDIO_BASS_UP:
    usagecode = HID_USAGE_CONSUMER_BASS_INCREMENT;
    break;
  case KC_AUDIO_BASS_DOWN:
    usagecode = HID_USAGE_CONSUMER_BASS_DECREMENT;
    break;
  case KC_AUDIO_TREBLE_UP:
    usagecode = HID_USAGE_CONSUMER_TREBLE_INCREMENT;
    break;
  case KC_AUDIO_TREBLE_DOWN:
    usagecode = HID_USAGE_CONSUMER_TREBLE_DECREMENT;
    break;
  case KC_MSEL:
    usagecode = HID_USAGE_CONSUMER_AL_CONSUMER_CONTROL_CONFIGURATION;
    break;
  case KC_WWW:
    usagecode = HID_USAGE_CONSUMER_AL_EMAIL_READER;
    break;
  case KC_CALCULATOR:
    usagecode = HID_USAGE_CONSUMER_AL_CALCULATOR;
    break;
  case KC_MYCM:
    usagecode = HID_USAGE_CONSUMER_AL_LOCAL_BROWSER;
    break;

  case KC_WWW_SEARCH:
    usagecode = HID_USAGE_CONSUMER_AC_SEARCH;
    break;
  case KC_WWW_HOME:
    usagecode = HID_USAGE_CONSUMER_AC_HOME;
    break;
  case KC_WWW_BACK:
    usagecode = HID_USAGE_CONSUMER_AC_BACK;
    break;
  case KC_WWW_FORWARD:
    usagecode = HID_USAGE_CONSUMER_AC_FORWARD;
    break;
  case KC_WWW_STOP:
    usagecode = HID_USAGE_CONSUMER_AC_STOP;
    break;
  case KC_WWW_REFRESH:
    usagecode = HID_USAGE_CONSUMER_AC_REFRESH;
    break;
  case KC_WWW_FAVORITES:
    usagecode = HID_USAGE_CONSUMER_AC_BOOKMARKS;
    break;
  case KC_AC_PAN:
    usagecode = HID_USAGE_CONSUMER_AC_PAN;
    break;
  }
  return usagecode;
}