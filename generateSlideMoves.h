#include "state.h"
#include "stdbool.h"
#define BITBOARD_SIZE 64

bool castN(int *index);
bool castNE(int *index);
bool castE(int *index);
bool castSE(int *index);
bool castS(int *index);
bool castSW(int *index);
bool castW(int *index);
bool castNW(int *index);
T_bitboard* castRays(int(*direction)(),int index);
void setBit(T_bitboard *number, int n);
