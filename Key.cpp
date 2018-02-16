#include </home/julian/Arduino/sketch_jan18a/Key.h>

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

void Key::setCurrentLayer(int layer[][6]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 6; ++j) {
            currentLayer[i][j] = layer[i][j];
        }
    }
}

void Key::startCurrentLayer() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 6; ++j) {
            currentLayer[i][j] = firstLayer[i][j];
        }
    }
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
          
        return currentLayer[row][col];
    }

    else if (currentState == 1) {
        pressedTime = 50;

        if (specialKey != SpecialKey::NO) {
        switch(specialKey) {
            case SpecialKey::SHIFT: shiftPressed = false;
            case SpecialKey::WIN: winPressed = false;
            case SpecialKey::CONTROL: controlPressed = false;
            }
        }
          
        return ' ';
    }  
    else 
        return ' ';
}

bool Key::shiftPressed = false;
bool Key::winPressed = false;
bool Key::controlPressed = false;

int Key::firstLayer[4][6] = {
    {116, 114, 101, 119, 113, 27}, 
    {103, 102, 100, 115, 97, 9}, 
    {98, 118, 99, 120, 122, 0},
    {0, 0, 0, 0, 0, 0}
    };

int Key::shiftLayer[4][6] = {
    {84, 82, 69, 87, 81, 27},
    {71, 70, 68, 83, 65, 9},
    {66, 86, 67, 88, 90, 0},
    {0, 0, 0, 0, 0, 0}
    };

int Key::currentLayer[4][6];
