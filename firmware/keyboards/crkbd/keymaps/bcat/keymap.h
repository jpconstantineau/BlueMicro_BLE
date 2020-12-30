#ifndef KEYMAP_H
#define KEYMAP_H

#include <array>
#include <cstdint>

#include "Key.h"
#include "keyboard_config.h"

extern std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix;

void setupKeymap();

#define USER_LAYER_FUNCTION 0
void process_user_layers(std::uint16_t layermask);

#endif  // KEYMAP_H
