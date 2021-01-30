#ifndef BITUTILITIES_H
#define BITUTILITIES_H

#include "state.h"
#include <stdbool.h>
#define incl 1

#include "bitUtilities.h"
#include <limits.h>


int32_t asmSimpleTest();
uint64_t asmTest();

T_bitboard bitScanForward(T_bitboard b);
T_bitboard bitScanReverse(T_bitboard b);
T_bitboard numOfSetBits(T_bitboard b);
uint64_t isZFSet();

T_bitboard createSecondLastColumnMask();
void setBit(T_bitboard *number, int n);
void clearBit(T_bitboard *number, int n);
unsigned char setCharBits(unsigned char c);
void clearBits(T_bitboard *number);
void clearCharBits(unsigned char *c);
bool isCharBitSet(char number, int n);
bool isBitSet(T_bitboard number, int n);
void toggleBit(T_bitboard *number, int n);
T_bitboard checkBit(T_bitboard number, int n);

#endif // BITUTILITIES_H
