#include "generateSlideMoves.h"
#include "state.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "output.h"

bool cast1(int *index){
    *index += 17;
    if(*index > 63 || !(*index % 8)){
        return false;
    }
    return true;
}

bool cast2(int *index){
    *index += 10;
    if(*index > 63 || !((*index - 1) % 8)){
        return false;
    }
    return true;
}

bool cast3(int *index){
    *index -= 6;
    if(*index < 0 || !((*index - 1) % 8)){
        return false;
    }
    return true;
}

bool cast4(int *index){
    *index -= 15;
    if(*index < 0 || !((*index) % 8)){
        return false;
    }
    return true;
}

bool cast5(int *index){
    *index -= 17;
    if(*index < 0 || !((*index + 1) % 8)){
        return false;
    }
    return true;
}

bool cast6(int *index){
    *index -= 10;
    if(*index < 0 || !((*index + 2) % 8)){
        return false;
    }
    return true;
}

bool cast7(int *index){
    *index += 6;
    if(*index > 63 || !((*index + 2) % 8)){
        return false;
    }
    return true;
}

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
    T_bitboard result = 0;
    while((*castDir)(&index)){
        setBit(&result, index);
    }
    return result;
}

T_bitboard castIntersectionRay(int(*castDir)(), int index){
    T_bitboard result = 0;
    setBit(&result, index);
    while((*castDir)(&index)){
        setBit(&result, index);
    }
    return result;
}

T_bitboard *castRays(bool (*castDir)(int*)){
    T_bitboard *result = malloc(BITBOARD_SIZE * sizeof(T_bitboard));
    for(int i = 0; i < BITBOARD_SIZE; i++){
        result[i] = castRay(castDir, i);
    }
    return result;
}

T_bitboard *castJumps(bool (*castDir)(int*)){
    T_bitboard *result = malloc(BITBOARD_SIZE * sizeof(T_bitboard));
    for(int i = 0; i < BITBOARD_SIZE; i++){
        result[i] = castRay(castDir, i);
    }
    return result;
}

//Enumerate directions 0 - 7
T_bitboard** createRays(){
    T_bitboard **rays = malloc(8 * sizeof(T_bitboard*));
    rays[0] = castRays(&castN);
    rays[1] = castRays(&castNE);
    rays[2] = castRays(&castE);
    rays[3] = castRays(&castSE);
    rays[4] = castRays(&castS);
    rays[5] = castRays(&castSW);
    rays[6] = castRays(&castW);
    rays[7] = castRays(&castNW);
    return rays;
}

//Enumerate directions 0 - 7
T_bitboard** createJumps(){
    T_bitboard **jumps = malloc(8 * sizeof(T_bitboard*));
//    jumps[0] = castJumps(&cast1);
//    jumps[1] = castJumps(&cast2);
//    jumps[2] = castJumps(&cast3);
//    jumps[3] = castJumps(&castS4);
//    jumps[4] = castJumps(&cast5);
//    jumps[5] = castJumps(&cast6);
//    jumps[6] = castJumps(&cast7);
//    jumps[7] = castJumps(&cast8);
}
