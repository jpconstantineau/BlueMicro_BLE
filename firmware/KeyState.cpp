/*
Copyright 2018 <Pierre Constantineau, Julian Komaromy>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include "KeyState.h"

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


