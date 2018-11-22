#include "Key.h"

//should be called with the keycode of the default layer
Key::Key(uint16_t activation) 
{
    activations[0][0] = activation; 

    //TODO: add duration
}

//should be called with 
void Key::addActivation(const uint8_t layer, const uint8_t method, const uint16_t activation) 
{
    activations[layer][method] = activation;
    state.addMethod(method);

    //TODO: add duration
}

void Key::press(const unsigned long currentMillis) 
{
    state.press(currentMillis);
}

void Key::clear(const unsigned long currentMillis) 
{
    state.clear(currentMillis);
}

uint16_t Key::getActivation(uint8_t layer) const 
{
    switch(state.getState()) 
    {
        case KeyState::State::PRESSED:
            return activations[layer][0];
            break;
        case KeyState::State::MT_TAPPED:
            return activations[layer][1];
            break;
        case KeyState::State::MT_HELD:
            return activations[layer][2];
            break;
        case KeyState::State::DT_TAPPED:
            return activations[layer][3];
            break;
        case KeyState::State::DT_DOUBLETAPPED:
            return activations[layer][4];
            break;
        default:
            return 0;
    }
}

uint8_t Key::getDuration(uint8_t layer, uint8_t method) const 
{
    return durations[layer][method];
}

std::pair<uint16_t, uint8_t> Key::getPair(uint8_t layer) const
{
    uint8_t method;

    switch(state.getState()) 
    {
        case KeyState::State::PRESSED:
            method = 0;
            break;
        case KeyState::State::MT_TAPPED:
            method = 1;
            break;
        case KeyState::State::MT_HELD:
            method = 2;
            break;
        case KeyState::State::DT_TAPPED:
            method = 3;
            break;
        case KeyState::State::DT_DOUBLETAPPED:
            method = 4;
            break;
        default:
            return std::make_pair(0, 0);
    }

    return std::make_pair(activations[layer][method], durations[layer][method]);
}

