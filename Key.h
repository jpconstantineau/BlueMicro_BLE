#include <array>
#include <utility>
#include <cstdint>

class Key {
    public:

        enum class SpecialKey {NO, SHIFT, WIN, CONTROL, ALT, UP, DOWN};

        Key();
        
        void setSpecial(const SpecialKey& special);

        static void setFirstLayer(int layer[][6]);
        static void setShiftLayer(int layer[][6]);
    
        static void setCurrentLayer(int (&layer)[4][6]);

        static void startCurrentLayer();

        static int firstLayer[4][6];
        static int shiftLayer[4][6];
        static int upLayer[4][6];
        static int downLayer[4][6];

        static uint8_t firstBLELayer[4][6];

        char update(const int& currentState, unsigned long millis, const int& row, const int& col);

        std::pair<uint8_t, std::array<uint8_t, 6>> aUpdate(const int& currentState, unsigned long millis, const int& row, const int& col);

        static bool shiftPressed;
        static bool winPressed;
        static bool controlPressed;
        static bool altPressed;

        static int (*currentLayer)[4][6];
        static uint8_t (*aCurrentLayer)[4][6];

    private:
        unsigned long pressedTime;
        unsigned long previousMillis;
    
        bool pressed;

        SpecialKey specialKey;

};
