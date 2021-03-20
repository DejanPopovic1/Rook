#ifndef BITUTILITIES_H
#define BITUTILITIES_H

#include "state.hpp"

#include <stdbool.h>

#define incl 1

#include "bitUtilities.hpp"
#include <limits.h>


T_bitboard createSecondLastColumnMask();
void setBit(T_bitboard *number, int n);
void setCharBit(unsigned char *number, int n);
void clearBit(T_bitboard *number, int n);
T_bitboard checkBit(T_bitboard number, int n);
void setBit1(T_bitboard *number, int n);
void clearBit1(T_bitboard *number, int n);
void clearBits(T_bitboard *number);
void setBits(T_bitboard *number);
void clearCharBits(unsigned char *c);
bool isCharBitSet(char number, int n);
bool isBitSet(T_bitboard number, int n);

#endif // BITUTILITIES_H
