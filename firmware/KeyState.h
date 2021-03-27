/*
Copyright 2018-2021 <Pierre Constantineau, Julian Komaromy>

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
#include "advanced_keycodes.h"
#include "hid_keycodes.h"
#ifndef KEY_STATE
#define KEY_STATE

#include "firmware_config.h"
#include "keyboard_config.h"

#ifndef DOUBLETAP_TIME_LIMIT
#define DOUBLETAP_TIME_LIMIT 200
#endif
#ifndef TIME_TILL_HOLD
#define TIME_TILL_HOLD 200
#endif
#ifndef TIME_TILL_RELEASE
#define TIME_TILL_RELEASE 20 // was 80
#endif

enum class Method {
  PRESS = 0,
  MT_TAP = 1,
  MT_HOLD = 2,
  DT_TAP = 3,
  DT_DOUBLETAP = 4,
  NONE = 5,
};

class KeyState {
public:
  KeyState();

  void press(unsigned long currentMillis);
  void clear(unsigned long currentMillis);

  void addMethod(Method method);

  enum class State {
    RELEASED, // simply released
    PRESSED,  // a simple press

    MT_TAPPED, // a released press
    MT_HELD,   // a constant press

    DT_TAPPED,      // if a tap can't be doubled anymore
    DT_DOUBLETAPPED // two presses with a release/tap in between
  };

  State getState() const;

private:
  bool canDoubletap;
  bool checkModTap, checkDoubleTap;

  // std::array<5, bool> checkMethods;

  State state;
  unsigned long lastChanged;
};

#endif
