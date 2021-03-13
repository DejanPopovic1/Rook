#ifndef KEYUTILITIES_H
#define KEYUTILITIES_H

#include <stdint.h>
#include "state.hpp"

#define PIECE_TYPES 6
#define PLAYERS 2
#define POSITIONS 64

typedef uint64_t key[PIECE_TYPES][PLAYERS][POSITIONS];

uint64_t rand64();
uint64_t ***createRandomKey();
uint64_t generateKey(T_boardState *b);

#endif // KEYUTILITIES_H
