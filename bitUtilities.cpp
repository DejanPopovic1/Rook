#include "bitUtilities.hpp"
#include <limits.h>
#include <stdio.h>

void setBit(T_bitboard *number, int n){
    *number ^= (-1ULL ^ *number) & (1ULL << n);
}

void setCharBit(unsigned char *number, int n){
    *number ^= (-1U ^ *number) & (1U << n);
}

void clearBit(T_bitboard *number, int n){
    *number &= ~(1ULL << n);
}

T_bitboard checkBit(T_bitboard number, int n){
    return (number >> n) & 1ULL;
}

void setBit1(T_bitboard *number, int n){
    *number ^= (-1ULL ^ *number) & (1ULL << n);
}

void clearBit1(T_bitboard *number, int n){
    *number &= ~(1ULL << n);
}

void clearBits(T_bitboard *number){
    *number = 0;
}

void setBits(T_bitboard *number){
    *number = ULONG_LONG_MAX;
}

void clearCharBits(unsigned char *c){
    *c = 0;
}
//Can potentially use isBitSet through implicit type conversion. Try this.
bool isCharBitSet(char number, int n){
    if ((number >> n) & 1){
        return true;
    }
    return false;
}

bool isBitSet(T_bitboard number, int n){
    if ((number >> n) & 1ULL){
        return true;
    }
    return false;
}
