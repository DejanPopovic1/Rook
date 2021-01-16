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

T_bitboard setBit(T_bitboard number, int n){
    T_bitboard result;
    result ^= (-1ULL ^ number) & (1ULL << n);
    return result;
}

T_bitboard clearBits(T_bitboard number){
    T_bitboard result;
    result = 0;
    return result;
}
