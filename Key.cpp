#include </home/julian/Arduino/sketch_jan18a/Key.h> 
#include <array>
#include <utility>
#include <cstdint>

Key::Key() {    
    pressed = false;
    pressedTime = 400;
    previousMillis = 0;
    specialKey = SpecialKey::NO;
}

void Key::setSpecial(const SpecialKey& special) {
    specialKey = special;
}

void Key::setFirstLayer(int layer[][6]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 6; ++j) {
            firstLayer[i][j] = layer[i][j];
        }
    }
}
void Key::setShiftLayer(int layer[][6]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 6; ++j) {
            shiftLayer[i][j] = layer[i][j];
        }
    }
}

void Key::setCurrentLayer(int (&layer)[4][6]) {
    currentLayer = &layer;
}

void Key::startCurrentLayer() {
    currentLayer = &firstLayer;
    aCurrentLayer = &firstBLELayer;
}

char Key::update(const int& currentState, unsigned long millis, const int& row, const int& col) {
    unsigned long currentMillis = millis;

    //if currently being pressed and delta t is larger than the amount of time that the key shouldn't be pressed for
    if (currentState == 0 && (currentMillis - previousMillis) >= pressedTime) {
        previousMillis = currentMillis;
        pressedTime = 300;

        if (specialKey != SpecialKey::NO) {
            switch(specialKey) {
                case SpecialKey::SHIFT: setCurrentLayer(shiftLayer);
                case SpecialKey::WIN: winPressed = true;
                case SpecialKey::CONTROL: controlPressed = true;
            }
        }
        
        if (*(currentLayer)[row][col] != 0) {
            return static_cast<char>((*currentLayer)[row][col]);
        }
        else {
            return ' ';
        }
    }

    else if (currentState == 1) {
        pressedTime = 50;

        if (specialKey != SpecialKey::NO) {
        switch(specialKey) {
            case SpecialKey::SHIFT: setCurrentLayer(firstLayer);
            case SpecialKey::WIN: winPressed = false;
            case SpecialKey::CONTROL: controlPressed = false;
            }
        }
          
       return ' ';
    }  
    else 
        return ' ';
}

std::pair<uint8_t, std::array<uint8_t, 6>> Key::aUpdate(const int& currentState, unsigned long millis, const int& row, const int& col) {
    unsigned long currentMillis = millis;
    uint8_t modifier = 0;
    std::array<uint8_t, 6> keycodes {0, 0, 0, 0, 0, 0};

    //if currently being pressed and delta t is larger than the amount of time that the key shouldn't be pressed for
    if (currentState == 0 && (currentMillis - previousMillis) >= pressedTime) {
        previousMillis = currentMillis;
        pressedTime = 200;

        //if the key that called the function is a special key and if the current layer is the first one
        if (specialKey != SpecialKey::NO && aCurrentLayer == &firstBLELayer) {
            switch(specialKey) {
                case SpecialKey::SHIFT: shiftPressed = true; break;
                case SpecialKey::WIN: winPressed = true; break;
                case SpecialKey::CONTROL: controlPressed = true; break; 
                case SpecialKey::ALT: altPressed = true; break;
            }
        }
        else if (specialKey == SpecialKey::DOWN) {
            setCurrentLayer(downLayer);
        }
        else if (specialKey == SpecialKey::UP) {
            if (currentLayer == &upLayer) {
                setCurrentLayer(firstLayer);
            }
            else {
                setCurrentLayer(upLayer);
            }
        }
        else if ((*aCurrentLayer)[row][col] != 0) {
            keycodes[0] = (*aCurrentLayer)[row][col];
        }
    }

    else if (currentState == 1) {
        pressedTime = 0;

        if (specialKey != SpecialKey::NO) {
        switch(specialKey) {
            case SpecialKey::SHIFT: shiftPressed = false; break;
            case SpecialKey::WIN: winPressed = false; break;
            case SpecialKey::CONTROL: controlPressed = false; break;
            case SpecialKey::ALT: altPressed = false; break;
            //case SpecialKey::DOWN: setCurrentLayer(firstLayer);
            }
        }
    }  
    
    modifier = 0;

    //specifying returned modifier keys
    if (shiftPressed) {
        modifier += 2;
    }
    if (winPressed) {
        //keycodes[5] = 0xE3;
        modifier += 8;
    }
    if (controlPressed) {
        //keycodes[4] = 0xE1;
        modifier += 16;
    }
    if (altPressed) {
        //keycodes[3] = 0xE2;
        modifier += 4;
    } 

    return std::make_pair(modifier, keycodes);
}

bool Key::shiftPressed = false;
bool Key::winPressed = false;
bool Key::controlPressed = false;
bool Key::altPressed = false;

int Key::firstLayer[4][6] = {
    {116, 114, 101, 119, 113, 27}, 
    {103, 102, 100, 115, 97, 9}, 
    {98, 118, 99, 120, 122, 0},
    {8, 363, 0, 0, 0, 0}
};

int Key::shiftLayer[4][6] = {
    {84, 82, 69, 87, 81, 126},
    {71, 70, 68, 83, 65, 9},
    {66, 86, 67, 88, 90, 0},
    {0, 0, 0, 0, 0, 0}
};

int Key::upLayer[4][6] = {
    {94, 37, 35, 36, 64, 33},
    {54, 53, 52, 51, 50, 49},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
};

int Key::downLayer[4][6] = {
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
};

uint8_t Key::firstBLELayer[4][6] = {
    {23, 21, 8, 26, 20, 41},
    {10, 9, 7, 22, 4, 43},
    {5, 25, 6, 27, 28, 225},
    {42, 0, 0, 0, 0, 0}
};

int (*Key::currentLayer)[4][6];
uint8_t (*Key::aCurrentLayer)[4][6];
