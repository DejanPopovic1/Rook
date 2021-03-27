#include "moveRules.hpp"
#include "state.hpp"
#include "bitUtilities.hpp"
#include "output.hpp"

#include <stdbool.h>
#include <stdlib.h>

//Remove returning bools from the jump casts
bool cast1(int *index){
    *index += 17;
    if(*index > 63 || !(*index % 8)){
        return false;
    }
    return true;
}

bool cast2(int *index){
    *index += 10;
    if(*index > 63 || !((*index) % 8) || !((*index - 1) % 8)){
        return false;
    }
    return true;
}

bool cast3(int *index){
    *index -= 6;
    if(*index < 0 || !((*index) % 8) || !((*index - 1) % 8)){
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
    if(*index < 0 || !((*index + 1) % 8) || !((*index + 2) % 8)){
        return false;
    }
    return true;
}

bool cast7(int *index){
    *index += 6;
    if(*index > 63 || !((*index + 1) % 8) || !((*index + 2) % 8)){
        return false;
    }
    return true;
}

bool cast8(int *index){
    *index += 15;
    if(*index > 63 || !((*index + 1) % 8)){
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

T_bitboard castStep(bool(*castDir)(int*), int index){
    T_bitboard result = 0;
    if((*castDir)(&index)){
        setBit(&result, index);
    }
    return result;
}

//CHANGE ARGUMENT TO bool (*castDir)(int*)
T_bitboard castRay(bool(*castDir)(int*), int index){
    T_bitboard result = 0;
    while((*castDir)(&index)){
        setBit(&result, index);
    }
    return result;
}

T_bitboard castJump(bool(*castDir)(int*), int index){
    T_bitboard result = 0;
    if((*castDir)(&index)){
        setBit(&result, index);
    }
    return result;
}

T_bitboard *castSteps(bool (*castDir)(int*)){
    T_bitboard *result = (T_bitboard *)malloc(BITBOARD_SIZE * sizeof(T_bitboard));
    for(int i = 0; i < BITBOARD_SIZE; i++){
        result[i] = castStep(castDir, i);
    }
    return result;
}

T_bitboard *castRays(bool (*castDir)(int*)){
    T_bitboard *result = (T_bitboard *)malloc(BITBOARD_SIZE * sizeof(T_bitboard));
    for(int i = 0; i < BITBOARD_SIZE; i++){
        result[i] = castRay(castDir, i);
    }
    return result;
}

T_bitboard *castJumps(bool (*castDir)(int*)){
    T_bitboard *result = (T_bitboard *)malloc(BITBOARD_SIZE * sizeof(T_bitboard));
    for(int i = 0; i < BITBOARD_SIZE; i++){
        result[i] = castJump(castDir, i);
    }
    return result;
}

//Enumerate directions 0 - 7
T_bitboard** createRays(){
    T_bitboard **rays = (T_bitboard **)malloc(8 * sizeof(T_bitboard*));
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

T_bitboard** createSteps(){
    T_bitboard **steps = (T_bitboard **)malloc(8 * sizeof(T_bitboard*));
    steps[0] = castSteps(&castN);
    steps[1] = castSteps(&castNE);
    steps[2] = castSteps(&castE);
    steps[3] = castSteps(&castSE);
    steps[4] = castSteps(&castS);
    steps[5] = castSteps(&castSW);
    steps[6] = castSteps(&castW);
    steps[7] = castSteps(&castNW);
    return steps;
}

//Enumerate directions 0 - 7
T_bitboard **createJumps(){
    T_bitboard **jumps = (T_bitboard **)malloc(8 * sizeof(T_bitboard*));
    jumps[0] = castJumps(&cast1);
    jumps[1] = castJumps(&cast2);
    jumps[2] = castJumps(&cast3);
    jumps[3] = castJumps(&cast4);
    jumps[4] = castJumps(&cast5);
    jumps[5] = castJumps(&cast6);
    jumps[6] = castJumps(&cast7);
    jumps[7] = castJumps(&cast8);
    return jumps;
}

void freeRays(T_bitboard **rays){
    free(rays[0]);
    free(rays[1]);
    free(rays[2]);
    free(rays[3]);
    free(rays[4]);
    free(rays[5]);
    free(rays[6]);
    free(rays[7]);
    free(rays);
}

void freeSteps(T_bitboard **steps){
    free(steps[0]);
    free(steps[1]);
    free(steps[2]);
    free(steps[3]);
    free(steps[4]);
    free(steps[5]);
    free(steps[6]);
    free(steps[7]);
    free(steps);
}

void freeJumps(T_bitboard **jumps){
    free(jumps[0]);
    free(jumps[1]);
    free(jumps[2]);
    free(jumps[3]);
    free(jumps[4]);
    free(jumps[5]);
    free(jumps[6]);
    free(jumps[7]);
    free(jumps);
}

//Use this in moveGeneration
T_bitboard **createWPawnAttacks(){
    T_bitboard **pAttacks = (T_bitboard **)malloc(2 * sizeof(T_bitboard*));
    pAttacks[0] = castSteps(&castNE);
    pAttacks[1] = castSteps(&castNW);
    return pAttacks;
}

T_bitboard **createBPawnAttacks(){
    T_bitboard **pAttacks = (T_bitboard **)malloc(2 * sizeof(T_bitboard*));
    pAttacks[0] = castSteps(&castSE);
    pAttacks[1] = castSteps(&castSW);
    return pAttacks;
}
