#include "generateSlideMoves.h"
#include "state.h"
#include <stdint.h>

T_bitboard* makeRaysNE(int index){
    T_bitboard *result = malloc(sizeof(T_bitboard));
    *result = 0;
    for(int i = index + 9; i < BITBOARD_SIZE; i += 9){
        if(!(i % 8)){
            break;
        }
        setBit(result, i);
    }
    printTBitboard(*result);
    printf("\n");
    return result;
}

void setBit(T_bitboard *number, int n){
    *number ^= (-1ULL ^ *number) & (1ULL << n);
    return;
}
