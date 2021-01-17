#include "state.h"
#include <stdbool.h>

T_bitboard bitScanForward(T_bitboard b);
T_bitboard bitScanReverse(T_bitboard b);
void setBit(T_bitboard *number, int n);
void clearBits(T_bitboard *number);
bool isBitSet(T_bitboard number, int n);
