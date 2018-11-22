#include "KeyState.h"
#include <array>
#include <utility>

#ifndef KEY_H
#define KEY_H

using ActArray = std::array<std::array<uint8_t, 5>, 2>;
using DurArray = std::array<std::array<uint16_t, 5>, 2>;

class Key {
    public:
        void press(unsigned long currentMillis);
        void clear(unsigned long currentMillis);

        void addActivation(const uint8_t layer, const uint8_t method, const uint16_t activation);

        uint16_t getActivation(uint8_t layer) const; 
        uint8_t getDuration(uint8_t layer, uint8_t method) const;
        std::pair<uint16_t, uint8_t> getPair(uint8_t layer) const;

        Key(uint16_t activation);

    private:
        KeyState state;

        ActArray activations;
        DurArray durations;
};

#endif /* KEY_H */
