#include <cstdint>

#ifndef ADVANCED_KEYCODES_H
#define ADVANCED_KEYCODES_H

#define MOD_LCTRL (1 << 8)
#define MOD_LSHIFT (2 << 8)
#define MOD_LALT (4 << 8)
#define MOD_LGUI (8 << 8)
#define MOD_RCTRL (16 << 8)
#define MOD_RSHIFT (32 << 8)
#define MOD_RALT (64 << 8)
#define MOD_RGUI (128 << 8)

#define MOD(M, KC) ((uint32_t) KC | (uint32_t) M)

#define MD_PRESS 0
#define MD_MT_TAP (1 << 16)
#define MD_MT_HOLD (2 << 16)
#define MD_DT_TAP (4 << 16)
#define MD_DT_DOUBLETAP (8 << 16)

#define MD(M, KC) ((uint32_t) M | (uint32_t) KC)
#endif
