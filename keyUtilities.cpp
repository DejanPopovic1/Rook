#include "keyUtilities.hpp"
#include "moveGeneration.hpp"
#include "output.hpp"
#include "state.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

uint64_t rand64(){
    return rand() ^ ((uint64_t)rand() << 15) ^ ((uint64_t)rand() << 30) ^ ((uint64_t)rand() << 45) ^ ((uint64_t)rand() << 60);
}

key *createRandomKey(){
    key *result = (key *)malloc(sizeof(key));
    for(int i = 0; i < PIECE; i++){
        for(int j = 0; j < POSITIONS; j++){
            (*result)[i][j] = rand64();
        }
    }
    return result;
}

uint64_t generateKey(T_boardState *b, uint64_t constantRandomNumber){
    uint64_t result = 0;
    T_boardState cpy = *b;
    T_bitboard pc;
    key *rk = createRandomKey();
    int j;
    for(int i = 1; i < 13; i++){
        while(pc = getPieceFromPieces(pieceBitboard(&cpy, i))){
            j = __builtin_ctzll(pc);

            //printTBitboard(pc);
            //printf("%d\n", j);
        }
    }
    return result;
}
