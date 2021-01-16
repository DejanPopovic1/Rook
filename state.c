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

T_bitboard initialiseBoardState(){
    T_bitboard i;
    clearBits(&i);
//    s.wPawn =
    return i;
}

T_bitboard initialiseWPawns(T_bitboard i){
    clearBits(i);
//    setBit()
}

T_boardState initialiseBPawns(){

}

T_boardState initialiseWBishops(){

}

T_boardState initialiseBBishops(){

}
