#include "advanced_keycodes.h"

#ifndef KEY_STATE
#define KEY_STATE

#define DOUBLETAP_TIME_LIMIT 700
#define TIME_TILL_HOLD 600
#define TIME_TILL_RELEASE 80

class KeyState 
{
    public:
        KeyState();
        KeyState(uint32_t keycode);

        void press(unsigned long currentMillis);
        void clear(unsigned long currentMillis);

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
        bool checkMT, checkDT;
        //std::array<5, bool> checkMethods;

        State state;
        unsigned long lastChanged;
};

#endif
