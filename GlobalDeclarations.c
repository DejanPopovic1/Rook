#include "GlobalDeclarations.h"
#include <stdbool.h>
#include <stdlib.h>

bool isNeighbouringPawnDoubleMoved(const int rank, const int file){
    return false;
}

int whosTurn(const int halfPly){
    if(halfPly % 2 == 1){
        return whiteTurn;
    }
    return blackTurn;
}

int alternatePlayer(const int playingAs){
    if(playingAs == whiteTurn){
        return blackTurn;
    }
    return whiteTurn;
}

bool isSamePosition(const T_position a, const T_position b){
    if(a.r == b.r && a.f == b.f){
        return true;
    }
    else
        return false;
}

bool isSameRank(T_position a, T_position b){
    if(a.r == b.r){
        return true;
    }
    return false;
}

bool isSameFile(T_position a, T_position b){
    if(a.f == b.f){
        return true;
    }
    return false;
}

//void assignPosition(T_position *dest, const T_position *src){
//    dest->r = src->r;
//    dest->f = src->f;
//}

T_position* createPosition(const int rank, const int file){
    T_position *result = malloc(sizeof(T_position));
    result->r = rank;
    result->f = file;
    return result;
}
