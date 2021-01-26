#include "state.h"
#include <stdbool.h>

T_bitboard numOfSetBits(T_bitboard b);
bool isBitInSecondLastColumn(T_bitboard number);
T_bitboard bitScanForward(T_bitboard b);
T_bitboard bitScanReverse(T_bitboard b);
void setBit(T_bitboard *number, int n);
void clearBits(T_bitboard *number);
bool isBitSet(T_bitboard number, int n);
unsigned char setCharBits(unsigned char c);
void clearCharBits(unsigned char *c);
