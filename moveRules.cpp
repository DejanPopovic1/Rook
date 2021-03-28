#include "moveRules.hpp"
#include "state.hpp"
#include "bitUtilities.hpp"
#include "output.hpp"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

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

void printMoveRuleValues(){
    T_bitboard **rays = createRays();
    T_bitboard **jumps = createJumps();
    T_bitboard **steps = createSteps();
    FILE *fp;
    fp = fopen("movementRules.txt", "w");
    char str[1000];

    fputs("{\n", fp);
    for(int i = 0; i < 8; i++){
        fputs("\t{", fp);
        for(int j = 0; j < 64; j++){
            sprintf(str, "%u", rays[i][j]);
            fputs(str, fp);
            if(j != 63){
                fputs(", ", fp);
            }
        }
        if(i != 7){
            fputs("},\n", fp);
        }
        else if(i == 7){
            fputs("}\n", fp);
        }
    }
    fputs("};\n\n", fp);

    fputs("{\n", fp);
    for(int i = 0; i < 8; i++){
        fputs("\t{", fp);
        for(int j = 0; j < 64; j++){
            sprintf(str, "%u", jumps[i][j]);
            fputs(str, fp);
            if(j != 63){
                fputs(", ", fp);
            }
        }
        if(i != 7){
            fputs("},\n", fp);
        }
        else if(i == 7){
            fputs("}\n", fp);
        }
    }
    fputs("};\n\n", fp);

    fputs("{\n", fp);
    for(int i = 0; i < 8; i++){
        fputs("\t{", fp);
        for(int j = 0; j < 64; j++){
            sprintf(str, "%u", steps[i][j]);
            fputs(str, fp);
            if(j != 63){
                fputs(", ", fp);
            }
        }
        if(i != 7){
            fputs("},\n", fp);
        }
        else if(i == 7){
            fputs("}\n\n", fp);
        }
    }
    fputs("};\n\n", fp);

    fclose(fp);
}

/*
{
	{16843008, 33686016, 67372032, 134744064, 269488128, 538976256, 1077952512, 2155905024, 16842752, 33685504, 67371008, 134742016, 269484032, 538968064, 1077936128, 2155872256, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{134480384, 268960768, 537921536, 1075843072, 2151686144, 8404992, 32768, 0, 67239936, 134479872, 268959744, 537919488, 1075838976, 2151677952, 8388608, 0, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{254, 252, 248, 240, 224, 192, 128, 0, 65024, 64512, 63488, 61440, 57344, 49152, 32768, 0, 16646144, 16515072, 16252928, 15728640, 14680064, 12582912, 8388608, 0, 4261412864, 4227858432, 4160749568, 4026531840, 3758096384, 3221225472, 2147483648, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 8, 16, 32, 64, 128, 0, 516, 1032, 2064, 4128, 8256, 16512, 32768, 0, 132104, 264208, 528416, 1056832, 2113664, 4227072, 8388608, 0, 33818640, 67637280, 135274560, 270549120, 541097984, 1082130432, 2147483648, 0, 67637280, 135274560, 270549120, 541097984, 1082130432, 2147483648, 0, 0, 135274560, 270549120, 541097984, 1082130432, 2147483648, 0, 0, 0, 270549120, 541097984, 1082130432, 2147483648, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 64, 128, 257, 514, 1028, 2056, 4112, 8224, 16448, 32896, 65793, 131586, 263172, 526344, 1052688, 2105376, 4210752, 8421504, 16843009, 33686018, 67372036, 134744072, 269488144, 538976288, 1077952576, 2155905152, 16843009, 33686018, 67372036, 134744072, 269488144, 538976288, 1077952576, 2155905152, 16843009, 33686018, 67372036, 134744072, 269488144, 538976288, 1077952576, 2155905152, 16843009, 33686018, 67372036, 134744072, 269488144, 538976288, 1077952576, 2155905152},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 64, 0, 256, 513, 1026, 2052, 4104, 8208, 16416, 0, 65536, 131328, 262657, 525314, 1050628, 2101256, 4202512, 0, 16777216, 33619968, 67240192, 134480385, 268960770, 537921540, 1075843080, 0, 0, 16777216, 33619968, 67240192, 134480385, 268960770, 537921540, 0, 0, 0, 16777216, 33619968, 67240192, 134480385, 268960770, 0, 0, 0, 0, 16777216, 33619968, 67240192, 134480385},
	{0, 1, 3, 7, 15, 31, 63, 127, 0, 256, 768, 1792, 3840, 7936, 16128, 32512, 0, 65536, 196608, 458752, 983040, 2031616, 4128768, 8323072, 0, 16777216, 50331648, 117440512, 251658240, 520093696, 1056964608, 2130706432, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 256, 66048, 16909312, 33818624, 67637248, 135274496, 270548992, 0, 65536, 16908288, 33816576, 67633152, 135266304, 270532608, 541065216, 0, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

{
	{131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 0, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1024, 2048, 4096, 8192, 16384, 32768, 0, 0, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 0, 0, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 4, 8, 16, 32, 64, 128, 0, 0, 1024, 2048, 4096, 8192, 16384, 32768, 0, 0, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 0, 0, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 8, 16, 32, 64, 128, 0, 512, 1024, 2048, 4096, 8192, 16384, 32768, 0, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 0, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 64, 0, 256, 512, 1024, 2048, 4096, 8192, 16384, 0, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 0, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 0, 0, 256, 512, 1024, 2048, 4096, 8192, 0, 0, 65536, 131072, 262144, 524288, 1048576, 2097152, 0, 0, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 256, 512, 1024, 2048, 4096, 8192, 0, 0, 65536, 131072, 262144, 524288, 1048576, 2097152, 0, 0, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 0, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

{
	{256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{512, 1024, 2048, 4096, 8192, 16384, 32768, 0, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 0, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{2, 4, 8, 16, 32, 64, 128, 0, 512, 1024, 2048, 4096, 8192, 16384, 32768, 0, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 0, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 8, 16, 32, 64, 128, 0, 512, 1024, 2048, 4096, 8192, 16384, 32768, 0, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 0, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 64, 0, 256, 512, 1024, 2048, 4096, 8192, 16384, 0, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 0, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 2, 4, 8, 16, 32, 64, 0, 256, 512, 1024, 2048, 4096, 8192, 16384, 0, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 0, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 256, 512, 1024, 2048, 4096, 8192, 16384, 0, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 0, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

};
*/
