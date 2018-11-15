#define DOUBLETAP_TIME_LIMIT 700
#define TIME_TILL_HOLD 600
#define MT_TAP_DURATION 80

#ifndef KEY_STATE
#define KEY_STATE
class KeyState 
{
    public:
        KeyState();

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
        State state;
        unsigned long lastChanged;
};

#endif
