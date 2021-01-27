#include "bitUtilities.h"
#include <limits.h>

T_bitboard bitScanForward(T_bitboard b) {
    __asm__(
        "bsf %rcx,%rax\n"
        "leave\n"
        "ret\n"
    );
}

T_bitboard bitScanReverse(T_bitboard b) {
    __asm__(
        "bsr %rcx,%rax\n"
        "leave\n"
        "ret\n"
    );
}

T_bitboard numOfSetBits(T_bitboard b) {
    __asm__(
        "popcnt %rcx,%rax\n"
        "leave\n"
        "ret\n"
    );
}

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

bool isBitInSecondLastColumn(T_bitboard number){

    return true;
}

void setBit(T_bitboard *number, int n){
    *number ^= (-1ULL ^ *number) & (1ULL << n);
    return;
}

unsigned char setCharBits(unsigned char c){
    return c = UCHAR_MAX;
}

void clearBits(T_bitboard *number){
    *number = 0;
}

void clearCharBits(unsigned char *c){
    *c = 0;
}

bool isBitSet(T_bitboard number, int n){
    if ((number >> n) & 1ULL){
        return true;
    }
    return false;
}

