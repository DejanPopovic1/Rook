#include "state.h"
#define BITBOARD_SIZE 64

int castN(int index);
//int castNE(int index);
//int castE(int index);
//int castSE(int index);
//int castS(int index);
//int castSW(int index);
//int castW(int index);
//int castNW(int index);
T_bitboard* makeRays(int(*direction)(),int index);
T_bitboard* makeRaysNE(int index);
