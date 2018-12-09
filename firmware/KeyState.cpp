#include "KeyState.h"

KeyState::KeyState() {
    state = State::RELEASED;
    lastChanged = 0;
    canDoubletap = false;
    checkDT = false;
    checkMT = false;
}

void KeyState::addMethod(uint8_t method)
{
    if (method == 1 || method == 2) {
        checkMT = true;
    }
    else if (method == 3 || method == 4) 
    {
        checkDT = true;
    }
}

void KeyState::press(unsigned long currentMillis)
{
    // the time between now and the last change
    unsigned long timeElapsed = currentMillis - lastChanged;

    /*
     * if the state is pressed and a certain amount of time has passed
     * since the state has been changed, the key is held
     * if the previous state isn't pressed, then set it to 
     * pressed now and update the change time
     */
    if (state == State::PRESSED && timeElapsed > TIME_TILL_HOLD && checkMT) 
    {
        state = State::MT_HELD;
        lastChanged = currentMillis;
    }
    else if ((state == State::RELEASED || state == State::MT_TAPPED))
    {
        if (canDoubletap && checkDT) 
        {
            state = State::DT_DOUBLETAPPED;
            canDoubletap = false;
        }
        else 
        {
            state = State::PRESSED;
            canDoubletap = true;
        }
            
        lastChanged = currentMillis;
    }
}

void KeyState::clear(unsigned long currentMillis)
{
    // the time between now and the last change
    unsigned long timeElapsed = currentMillis - lastChanged;

    // if the previous state was pressed, then set the state to 
    // tapped, otherwise set it to released
    if (state == State::PRESSED && checkMT)
    {
        state = State::MT_TAPPED;
        lastChanged = currentMillis;
    }
    else if (timeElapsed > DOUBLETAP_TIME_LIMIT && canDoubletap && checkDT) 
    {
        state = State::DT_TAPPED;
        lastChanged = currentMillis;
        canDoubletap = false;
    }
    else if (state != State::RELEASED && timeElapsed > TIME_TILL_RELEASE)
    {
        state = State::RELEASED;
        lastChanged = currentMillis;
    }
}

KeyState::State KeyState::getState() const
{
    return state;
}


