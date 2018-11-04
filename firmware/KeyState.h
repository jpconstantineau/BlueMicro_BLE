#define DOUBLETAP_TIME 500

class KeyState 
{
    public:
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
        State state;
        unsigned long lastChanged;
};

