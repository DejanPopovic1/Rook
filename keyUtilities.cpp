#include "keyUtilities.hpp"
#include "state.hpp"
#include <stdint.h>
#include <stdlib.h>


uint64_t rand64(){
    return rand() ^ ((uint64_t)rand() << 15) ^ ((uint64_t)rand() << 30) ^ ((uint64_t)rand() << 45) ^ ((uint64_t)rand() << 60);
}

uint64_t ***createRandomKey(){
    uint64_t ***result = (uint64_t ***)malloc(1 * sizeof(key));
    for(int i = 0; i < PIECE_TYPES; i++){
        for(int j = 0; j < PLAYERS; j++){
            for(int k = 0; k < POSITIONS; k++){
                result[i][j][k] = rand64();
            }
        }
    }
}

uint64_t generateKey(T_boardState *b, uint64_t constantRandomNumber){
    uint64_t result = 0;
    for(char i = 0; i < 13; i++){


    }
    return result;
}
