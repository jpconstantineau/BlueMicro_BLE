#include "KeyState.h"

KeyState::KeyState() {
    state = State::RELEASED;
    lastChanged = 0;
    canDoubletap = false;
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
    if (state == State::PRESSED && timeElapsed > TIME_TILL_HOLD) 
    {
        state = State::MT_HELD;
        lastChanged = currentMillis;
    }
    else if ((state == State::RELEASED || state == State::MT_TAPPED) && canDoubletap) {
        state = State::DT_DOUBLETAPPED;
        lastChanged = currentMillis;
        canDoubletap = false;
    }
    else if (state != State::PRESSED) 
    {
        state = State::PRESSED;
        lastChanged = currentMillis;
        canDoubletap = true;
    }
}

void KeyState::clear(unsigned long currentMillis)
{
    // the time between now and the last change
    unsigned long timeElapsed = currentMillis - lastChanged;

    // if the previous state was pressed, then set the state to 
    // tapped, otherwise set it to released
    if (state == State::PRESSED)
    {
        state = State::MT_TAPPED;
        lastChanged = currentMillis;
    }
    else if (timeElapsed > DOUBLETAP_TIME_LIMIT && canDoubletap) {
        state = State::DT_TAPPED;
        lastChanged = currentMillis;
        canDoubletap = false;
    }
    else if (state != State::RELEASED) 
    {
        if (state == State::MT_TAPPED && timeElapsed < MT_TAP_DURATION) 
        {
            //do nothing, wait until tapped state has stayed long enough to be released
        }
        else 
        {
            state = State::RELEASED;
            lastChanged = currentMillis;
        }
    }
}

KeyState::State KeyState::getState() const
{
    return state;
}


