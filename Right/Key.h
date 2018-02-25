#include <array>
#include <utility>
#include <cstdint>

class Key {
    public:

        enum class SpecialKey {NO, SHIFT, WIN, CONTROL, ALT, UP, DOWN};

        Key();
        
        void setSpecial(const SpecialKey& special);
    
        static void setCurrentLayer(uint8_t (&layer)[4][6]);

        static void startCurrentLayer();

        static uint8_t downBLELayer[4][6];
        static uint8_t upBLELayer[4][6];
        static uint8_t firstBLELayer[4][6]; 

        std::array<uint8_t, 2> aUpdate(const int& currentState, unsigned long millis, const int& row, const int& col);

        static bool shiftPressed;
        static bool winPressed;
        static bool controlPressed;
        static bool altPressed;
        static bool downPressed;
        static bool upPressed;

        static std::array<uint8_t, 2> currentReport;
        static int (*currentLayer)[4][6];
        static uint8_t (*aCurrentLayer)[4][6];

    private:
        unsigned long pressedTime;
        unsigned long previousMillis;
    
        bool pressed;

        SpecialKey specialKey;

};
