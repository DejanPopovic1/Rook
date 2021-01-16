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
    T_boardState result;
    initialiseWPawns(&(result.wPawn));
    initialiseWBishops(&(result.wBishop));
    initialiseWKnights(&(result.wKnight));
    initialiseWRooks(&(result.wRook));
    initialiseWQueen(&(result.wQueen));
    initialiseWKing(&(result.wKing));
    initialiseBPawns(&(result.bPawn));
    initialiseBBishops(&(result.bBishop));
    initialiseBKnights(&(result.bKnight));
    initialiseBRooks(&(result.bRook));
    initialiseBQueen(&(result.bQueen));
    initialiseBKing(&(result.bKing));
    return result;
}

void initialiseWPawns(T_bitboard *result){
    clearBits(*result);
    for(int i = 8; i <= 15; i++){
        setBit(*result, i);
    }
}
void initialiseWBishops(T_bitboard *result){
    clearBits(*result);
    setBit(*result, 2);
    setBit(*result, 5);
}

void initialiseWKnights(T_bitboard *result){
    clearBits(*result);
    setBit(*result, 1);
    setBit(*result, 6);
}

T_boardState initialiseWRooks(T_bitboard *result){
    clearBits(*result);
    setBit(*result, 0);
    setBit(*result, 7);
}

T_boardState initialiseWQueen(T_bitboard *result){
    clearBits(*result);
    setBit(*result, 3);
}

T_boardState initialiseWKing(T_bitboard *result){
    clearBits(*result);
    setBit(*result, 4);
}

void initialiseBPawns(T_bitboard *result){
    clearBits(*result);
    for(int i = 48; i <= 55; i++){
        setBit(*result, i);
    }
}
void initialiseBBishops(T_bitboard *result){
    clearBits(*result);
    setBit(*result, 58);
    setBit(*result, 61);
}

void initialiseBKnights(T_bitboard *result){
    clearBits(*result);
    setBit(*result, 57);
    setBit(*result, 62);
}

T_boardState initialiseBRooks(T_bitboard *result){
    clearBits(*result);
    setBit(*result, 56);
    setBit(*result, 63);
}

T_boardState initialiseBQueen(T_bitboard *result){
    clearBits(*result);
    setBit(*result, 59);
}

T_boardState initialiseBKing(T_bitboard *result){
    clearBits(*result);
    setBit(*result, 60);
}
