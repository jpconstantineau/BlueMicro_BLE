class Key {
    public:

        enum class SpecialKey {NO, SHIFT, WIN, CONTROL};

        Key();
        
        void setSpecial(const SpecialKey& special);

        static void setFirstLayer(int layer[][6]);
        static void setShiftLayer(int layer[][6]);
    
        static void setCurrentLayer(int layer[][6]);

        static void startCurrentLayer();

        static int firstLayer[4][6];
        static int shiftLayer[4][6];

        char update(const int& currentState, unsigned long millis, const int& row, const int& col);

        static bool shiftPressed;
        static bool winPressed;
        static bool controlPressed;

        static int currentLayer[4][6];

    private:
        unsigned long pressedTime;
        unsigned long previousMillis;
    
        bool pressed;

        SpecialKey specialKey;

};
