#include "generateSlideMoves.h"
#include "state.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "output.h"

bool castN(int *index){
    *index += 8;
    if(*index > 63){
        return false;
    }
    return true;
}

bool castNE(int *index){
    *index += 9;
    if(*index > 63 || !(*index % 8)){
        return false;
    }
    return true;
}

bool castE(int *index){
    *index += 1;
    if(!(*index % 8)){
        return false;
    }
    return true;
}

bool castSE(int *index){
    *index -= 7;
    if(*index < 0 || !(*index % 8)){
        return false;
    }
    return true;
}

bool castS(int *index){
    *index -= 8;
    if(*index < 0){
        return false;
    }
    return true;
}

bool castSW(int *index){
    *index -= 9;
    if(*index < 0 || !((*index + 1) % 8)){
        return false;
    }
    return true;
}

bool castW(int *index){
    *index -= 1;
    if(!((*index + 1) % 8)){
        return false;
    }
    return true;
}

bool castNW(int *index){
    *index += 7;
    if(*index > 63 || !((*index + 1) % 8)){
        return false;
    }
    return true;
}

T_bitboard* castRays(int(*castDir)(),int index){
    T_bitboard *result = malloc(sizeof(T_bitboard));
    *result = 0;
    while((*castDir)(&index)){
        setBit(result, index);
    }
    printTBitboard(*result);
    printf("\n");
    return result;
}

void setBit(T_bitboard *number, int n){
    *number ^= (-1ULL ^ *number) & (1ULL << n);
    return;
}
