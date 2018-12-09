#include <cstdint>

#ifndef ADVANCED_KEYCODES_H
#define ADVANCED_KEYCODES_H

#define MOD(M, KC) ((uint16_t) KC | (uint16_t) M)

#define MOD_LCTRL (1 << 8)
#define MOD_LSHIFT (2 << 8)
#define MOD_LALT (4 << 8)
#define MOD_LGUI (8 << 8)
#define MOD_RCTRL (16 << 8)
#define MOD_RSHIFT (32 << 8)
#define MOD_RALT (64 << 8)
#define MOD_RGUI (128 << 8)

#define TG(KC) ((1 << 16) | KC)

#endif
