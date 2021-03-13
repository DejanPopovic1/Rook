#ifndef KEYUTILITIES_H
#define KEYUTILITIES_H

#define MAX_PIECES 32
#define MAX_COLOURS 2
#define MAX_POSITIONS 64

#include <stdint.h>

typedef uint64_t key[MAX_PIECES][MAX_COLOURS][MAX_POSITIONS];

uint64_t rand64();

uint64_t ***createRandomKey();


#endif // KEYUTILITIES_H
