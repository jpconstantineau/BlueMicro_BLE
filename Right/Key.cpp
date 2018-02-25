#include </home/julian/Arduino/sketch_feb20a/Key.h> 
#include <array>
#include <utility>
#include <cstdint>

Key::Key() {    
    pressed = false;
    pressedTime = 560;
    previousMillis = 0;
    specialKey = SpecialKey::NO;
}

void Key::setSpecial(const SpecialKey& special) {
    specialKey = special;
}

void Key::setCurrentLayer(uint8_t (&layer)[4][6]) {
    aCurrentLayer = &layer;
}

void Key::startCurrentLayer() {
    aCurrentLayer = &firstBLELayer;
}

std::array<uint8_t, 2> Key::aUpdate(const int& currentState, unsigned long currentMillis, const int& row, const int& col) {

    currentReport = {0, 0};
    
    //if currently being pressed and delta t is larger than the amount of time that the key shouldn't be pressed for
    if (currentState == 0 && (currentMillis - previousMillis) >= pressedTime) {
        previousMillis = currentMillis;
        if (!pressed) {
            pressedTime = 560;
            pressed = true;
        }
        else {
            pressedTime = 40;
        }

        //if the key that called the function is a special key and if the current layer is the first one
        if (specialKey != SpecialKey::NO) {
            switch(specialKey) {
                case SpecialKey::SHIFT: shiftPressed = true; break;
                case SpecialKey::WIN: winPressed = true; break;
                case SpecialKey::CONTROL: controlPressed = true; break; 
                case SpecialKey::ALT: altPressed = true; break;
                case SpecialKey::UP: aCurrentLayer = &upBLELayer; upPressed = true; break;
            }
        }

        else if ((*aCurrentLayer)[row][col] != 0) {
            currentReport[1] = (*aCurrentLayer)[row][col];
        }
    }

    else if (currentState == 1) {
        pressedTime = 16;
        pressed = false;

        if (specialKey != SpecialKey::NO) {
        switch(specialKey) {
            case SpecialKey::SHIFT: shiftPressed = false; break;
            case SpecialKey::WIN: winPressed = false; break;
            case SpecialKey::CONTROL: controlPressed = false; break;
            case SpecialKey::ALT: altPressed = false; break; 
            }
        }

        if (specialKey == SpecialKey::UP && aCurrentLayer == &upBLELayer) {
            aCurrentLayer = &firstBLELayer;
            upPressed = false;
        }
    }  
    
    //specifying returned modifier keys
    if (shiftPressed) {
        currentReport[0] += 2;
    }
    if (winPressed) {
        //keycodes[5] = 0xE3;
        currentReport[0] += 8;
    }
    if (controlPressed) {
        //keycodes[4] = 0xE1;
        currentReport[0] += 16;
    }
    if (altPressed) {
        //keycodes[3] = 0xE2;
        currentReport[0] += 4;
    } 

    return currentReport;
}

bool Key::shiftPressed = false;
bool Key::winPressed = false;
bool Key::controlPressed = false;
bool Key::altPressed = false;
bool Key::downPressed = false;
bool Key::upPressed = false;

std::array<uint8_t, 2> Key::currentReport = {0, 0};

uint8_t Key::downBLELayer[4][6] = {
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 49, 48, 47},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
};

uint8_t Key::upBLELayer[4][6] = {
    {46, 45, 39, 38, 37, 36},
    {46, 45, 39, 38, 37, 36},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
};

uint8_t Key::firstBLELayer[4][6] = {
    {42, 19, 18, 12, 24, 28},
    {52, 51, 15, 14, 13, 11},
    {0, 56, 55, 54, 16, 17},
    {0, 0, 0, 0, 44, 40}
};

int (*Key::currentLayer)[4][6];
uint8_t (*Key::aCurrentLayer)[4][6];
