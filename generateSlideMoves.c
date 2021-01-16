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

T_bitboard castRay(int(*castDir)(),int index){
    //T_bitboard *result = malloc(sizeof(T_bitboard));
    //*result = 0;
    T_bitboard result = 0;
    while((*castDir)(&index)){
        result = setBit(result, index);
    }
    return result;
}


T_bitboard *castRays(bool (*castDir)(int*)){
    T_bitboard result [BITBOARD_SIZE];
    //T_bitboard **result = malloc(BITBOARD_SIZE * sizeof(T_bitboard*));
    for(int i = 0; i < BITBOARD_SIZE; i++){
        result[i] = castRay(castDir, i);
    }
    return result;
}

void createAndPrintRays(){
    T_bitboard *nR = castRays(&castN);
    T_bitboard *neR = castRays(&castNE);
    T_bitboard *eR = castRays(&castE);
    T_bitboard *seR = castRays(&castSE);
    T_bitboard *sR = castRays(&castS);
    T_bitboard *swR = castRays(&castSW);
    T_bitboard *wR = castRays(&castW);
    T_bitboard *nwR = castRays(&castNW);
    printTBitboardNumbersDec(nR);
    printTBitboardNumbersDec(neR);
    printTBitboardNumbersDec(eR);
    printTBitboardNumbersDec(seR);
    printTBitboardNumbersDec(sR);
    printTBitboardNumbersDec(swR);
    printTBitboardNumbersDec(wR);
    printTBitboardNumbersDec(nwR);
}
