#include <cstdint>

#ifndef ADVANCED_KEYCODES_H
#define ADVANCED_KEYCODES_H

#define MOD_LCTRL 1
#define MOD_LSHIFT 2
#define MOD_LALT 4
#define MOD_LGUI 8
#define MOD_RCTRL 16
#define MOD_RSHIFT 32
#define MOD_RALT 64
#define MOD_RGUI 128

#define MOD(M, KC) ((uint32_t) KC | (uint32_t) M)

#endif
