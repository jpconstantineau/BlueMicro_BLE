#include "KeyState.h"

void KeyState::press(unsigned long currentMillis)
{
    // the time between now and the last change
    unsigned long timeElapsed = currentMillis - lastChanged;

    // if the time between now and the last change is larger than
    // the time limit for a double tap, then set the state to pressed
    if (timeElapsed > DOUBLETAP_TIME)
    {
        state = State::PRESSED; 
    }
    else 
    {
        // if the time between now and the last change is smaller than
        // the time limit for a double tap and the current state is either
        // a tap or a release, then set the state to doubletapped
        // otherwise, set the state to held
        if (state == State::RELEASED || state == State::MT_TAPPED)
        {
            state = State::DT_DOUBLETAPPED;
        }
        else 
        {
            state = State::MT_HELD;
        }
    }

    lastChanged = currentMillis;
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
    else 
    {
        if (timeElapsed > DOUBLETAP_TIME && (state == State::MT_TAPPED || state == State::RELEASED))
        {
            state = State::DT_TAPPED;
        }
        else 
        {
            state = State::RELEASED;
        }
    }
}

KeyState::State KeyState::getState() const
{
    return state;
}


