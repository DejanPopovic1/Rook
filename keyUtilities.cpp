#include "keyUtilities.hpp"
#include <stdint.h>
#include <stdlib.h>

uint64_t rand64(){
    return rand() ^ ((uint64_t)rand() << 15) ^ ((uint64_t)rand() << 30) ^ ((uint64_t)rand() << 45) ^ ((uint64_t)rand() << 60);
}

uint64_t ***createRandomKey(){
    uint64_t ***result = (uint64_t ***)malloc(1 * sizeof(key));
    for(int i = 0; i < MAX_PIECES; i++){
        for(int j = 0; j < MAX_COLOURS; j++){
            for(int k = 0; k < MAX_POSITIONS; k++){
                result[i][j][k] = rand64();
            }
        }
    }
}
