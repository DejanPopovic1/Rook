#ifndef KEYUTILITIES_H
#define KEYUTILITIES_H

#include <stdint.h>
#include "state.hpp"

#define PIECE 12
//#define PLAYERS 2
#define POSITIONS 64

typedef uint64_t key[PIECE][POSITIONS];

uint64_t rand64();
uint64_t ***createRandomKey();
uint64_t generateKey(T_boardState *b, uint64_t constantRandomNumber);

#endif // KEYUTILITIES_H
