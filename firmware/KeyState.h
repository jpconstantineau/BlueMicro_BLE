// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include "advanced_keycodes.h"
#include "hid_keycodes.h"
#ifndef KEY_STATE
#define KEY_STATE


#include "keyboard_config.h"
#include "firmware_config.h"




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

class KeyState 
{
    public:
        KeyState();
        
        void press(unsigned long currentMillis);
        void clear(unsigned long currentMillis);

        void addMethod(Method method);

        enum class State
        {
            RELEASED,       // simply released 
            PRESSED,        // a simple press

            MT_TAPPED,      // a released press
            MT_HELD,        // a constant press
            
            DT_TAPPED,      // if a tap can't be doubled anymore
            DT_DOUBLETAPPED // two presses with a release/tap in between
        };

        State getState() const;

    private:
        bool canDoubletap;
        bool checkModTap, checkDoubleTap;

        //std::array<5, bool> checkMethods;

        State state;
        unsigned long lastChanged;
};

#endif
