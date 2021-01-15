#include "state.h"
#include "generateSlideMoves.h"
#include "output.h"
#include "GlobalDeclarations.h"
#include "bitUtilities.h"

int whosTurnNEW(const int ply){
    if((ply % 2) == 1){
        return whiteTurn;
    }
    return blackTurn;
}

T_boardState initialiseBoardState(){
    T_boardState i;
//    s.wPawn =
    return i;
}

T_boardState initialiseWPawns(T_bitboard i){
    clearBits(i);
//    setBit()
}

T_boardState initialiseBPawns(){

}

T_boardState initialiseWBishops(){

}

T_boardState initialiseBBishops(){

}
