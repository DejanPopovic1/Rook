#ifndef KEYUTILITIES_H
#define KEYUTILITIES_H

#include <stdint.h>
#include "state.hpp"

#define PIECE 12
#define POSITIONS 64

typedef uint64_t key[PIECE][POSITIONS];

uint64_t rand64();
key *createRandomKey();
uint64_t generateKey(T_boardState *b);
uint64_t incrementKey(uint64_t k, T_boardState *b, T_boardState *ss, key *randomKey);

#endif // KEYUTILITIES_H
