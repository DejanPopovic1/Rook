#include "keyUtilities.hpp"
#include "moveGeneration.hpp"
#include "toAlgNotation.hpp"
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

//Doesnt take into accout en passant and castling rights - to be added in backlog
uint64_t generateKey(T_boardState *b){
    uint64_t result = 0;
    T_boardState cpy = *b;
    T_bitboard pc;
    key *rk = createRandomKey();
    int j;
    for(int i = 1; i < 13; i++){
        while(pc = getPieceFromPieces(pieceBitboard(&cpy, i))){
            j = __builtin_ctzll(pc);
            result ^= (*rk)[i][j];
        }
    }
    if(b->whosTurn){
        result ^= rand();
    }
    return result;
}

//If this is either castling or promotion, instead of incrementally adjusting, regenerate the key. So in that instance, call the generateKey function
uint64_t incrementKey(uint64_t key, T_boardState *b, T_boardState *ss){
    char *from, *to, *piece, *capturedPiece;
    bool *isPieceCaptured;
    whereFromTo(b, ss, from, to, piece, isPieceCaptured, capturedPiece);


    return key;
}
