#include "bitUtilities.hpp"
#include <limits.h>
#include "stdio.h"
//#include "moveGeneration.h"

//rather make this a number for efficiency
T_bitboard createSecondLastColumnMask(){
    T_bitboard result;
    clearBits(&result);
    setBit(&result, 48);
    setBit(&result, 49);
    setBit(&result, 50);
    setBit(&result, 51);
    setBit(&result, 52);
    setBit(&result, 53);
    setBit(&result, 54);
    setBit(&result, 55);
    return result;
}

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

#if 0
void toggleBit(T_bitboard *number, int n){
    *number ^= 1UL << n;
}

T_bitboard checkBit(T_bitboard number, int n){
    return (number >> n) & 1ULL;
}
#endif
