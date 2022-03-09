// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include "keystate.h"

KeyState::KeyState() {
    state = State::RELEASED;
    lastChanged = 0;
    canDoubletap = false;
    checkDoubleTap = false;
    checkModTap = false;
}

void KeyState::addMethod(Method method)
{
    if (method == Method::MT_TAP || method == Method::MT_HOLD) {
        checkModTap = true;
    }
    else if (method == Method::DT_TAP || method == Method::DT_DOUBLETAP) 
    {
        checkDoubleTap = true;
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
    if (state == State::PRESSED && timeElapsed > TIME_TILL_HOLD && checkModTap) 
    {
        state = State::MT_HELD;
        lastChanged = currentMillis;
    }
    else if ((state == State::RELEASED || state == State::MT_TAPPED))
    {
        if (canDoubletap && checkDoubleTap) 
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
    if (state == State::PRESSED && checkModTap)
    {
        state = State::MT_TAPPED;
        lastChanged = currentMillis;
    }
    else if (timeElapsed > DOUBLETAP_TIME_LIMIT && canDoubletap && checkDoubleTap) 
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


