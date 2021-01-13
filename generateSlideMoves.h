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
//int castNE(int index);
//int castE(int index);
//int castSE(int index);
//int castS(int index);
//int castSW(int index);
//int castW(int index);
//int castNW(int index);
T_bitboard* makeRays(int(*direction)(),int index);
T_bitboard* makeRaysNE(int index);
