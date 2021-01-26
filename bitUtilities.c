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
    T_bitboard b;
    clearBits(&b);
    setBit(&n, 48);
    setBit(&n, 49);
    setBit(&n, 50);
    setBit(&n, 51);
    setBit(&n, 52);
    setBit(&n, 53);
    setBit(&n, 54);
    setBit(&n, 55);
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

