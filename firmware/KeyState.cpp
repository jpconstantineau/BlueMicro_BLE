#include "KeyState.h"

KeyState::KeyState() {
    state = State::RELEASED;
    lastChanged = 0;
    canDoubletap = false;
}

KeyState::KeyState(uint32_t keycode) 
{
    state = State::RELEASED;
    lastChanged = 0;
    canDoubletap = false;

    auto modifier = keycode & 0x00FF0000;

    /*checkMethods = {true, false, false, false, false};
    if (modifier == MD_MT_TAP) {
        checkMethods[1] = true;
    }
    if (modifier == MD_MT_HOLD) {
        checkMethods[2] = true;
    }
    if (modifier == MD_DT_TAP) {
        checkMethods[3] = true;
    }
    if (modifier == MD_DT_DOUBLETAP) {
        checkMethods[4] = true;
    }*/

    if (modifier == MD_MT_TAP || modifier == MD_MT_HOLD) {
        checkMT = true;
    }
    else {
        checkMT = false;
    }
    if (modifier == MD_DT_TAP || modifier == MD_DT_DOUBLETAP) {
        checkDT = true;
    }
    else {
        checkDT = false;
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
    //else if ((state == State::RELEASED || state == State::MT_TAPPED) && canDoubletap) 
    else if (state == State::RELEASED || state == State::MT_TAPPED)
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
    //else if (state != State::PRESSED && state != State::MT_HELD) 
    /*{
        state = State::PRESSED;
        lastChanged = currentMillis;
        canDoubletap = true;
    }*/
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


