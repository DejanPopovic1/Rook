#include "bitUtilities.h"

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

void setBit(T_bitboard *number, int n){
    *number ^= (-1ULL ^ *number) & (1ULL << n);
    return;
}

void clearBits(T_bitboard *number){
    *number = 0;
    return;
}

bool isBitSet(T_bitboard number){
    if ((number >> n) & 1ULL){
        return true;
    }
    return false;
}

