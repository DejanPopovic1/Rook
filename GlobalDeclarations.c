#include "GlobalDeclarations.h"
#include <stdbool.h>

bool isNeighbouringPawnDoubleMoved(int rank, int file){
    return false;
}

int playerTurn(int halfPly){
    if(halfPly % 2 == 1){
        return white;
    }
    return black;
}

int alternatePlayer(int playingAs){
    if(playingAs == white){
        return black;
    }
    return white;
}
