#ifndef KEYUTILITIES_H
#define KEYUTILITIES_H

#define PIECE_TYPES 6
#define PLAYERS 2
#define POSITIONS 64

#include <stdint.h>

typedef uint64_t key[PIECE_TYPES][PLAYERS][POSITIONS];

uint64_t rand64();

uint64_t ***createRandomKey();


#endif // KEYUTILITIES_H
