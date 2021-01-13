#include "generateSlideMoves.h"
#include "state.h"
#include <stdint.h>
#include <stdbool.h>

bool castN(int *index){
    *index += 8;
    if(*index > 63){
        return false;
    }
    return true;
}

bool castNE(int *index){
    *index += 9;
    if(*index > 63 || !((*index) % 8)){
        return false;
    }
    return true;
}

bool castE(int *index){
    *index += 9;
    if(*index > 63 || !((*index) % 8)){
        return false;
    }
    return true;
}

bool castSE(int *index){
    *index += 9;
    if(*index > 63 || !((*index) % 8)){
        return false;
    }
    return true;
}

bool castS(int *index){
    *index += 9;
    if(*index > 63 || !((*index) % 8)){
        return false;
    }
    return true;
}

bool castSW(int *index){
    *index += 9;
    if(*index > 63 || !((*index) % 8)){
        return false;
    }
    return true;
}

bool castW(int *index){
    *index += 9;
    if(*index > 63 || !((*index) % 8)){
        return false;
    }
    return true;
}

bool castNW(int *index){
    *index += 9;
    if(*index > 63 || !((*index) % 8)){
        return false;
    }
    return true;
}

//int castNE(int index){
//    index += 9;
//    return index;
//}
//
//int castE(int index){
//    index += 1;
//    return index;
//}
//
//int castSE(int index){
//    index -= 7;
//    return index;
//}
//
//int castS(int index){
//    index -= 8;
//    return index;
//}
//
//int castSW(int index){
//    index -= 9;
//    return index;
//}
//
//int castW(int index){
//    index -= 1;
//    return index;
//}
//
//int castNW(int index){
//    index += 7;
//    return index;
//}

T_bitboard* makeRays(int(*castDir)(),int index){
    T_bitboard *result = malloc(sizeof(T_bitboard));
    *result = 0;
    while((*castDir)(&index)){
        setBit(result, index);
    }
//    for(int i = (*castDir)(&index); i < BITBOARD_SIZE; i = (*castDir)(&i)){
//        if(i > 63){
//            break;
//        }
//        setBit(result, i);
//    }
    printTBitboard(*result);
    printf("\n");
    return result;
}

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
