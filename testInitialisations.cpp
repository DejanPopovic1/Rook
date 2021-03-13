//#include "state.hpp"
//#include "output.h"
#include "bitUtilities.hpp"
#include "assert.h"
#include "moveGeneration.hpp"
#include "testInitialisations.hpp"

T_boardState CMinitialiseBoardState(){
    T_boardState result;
    CMinitialiseWPawns(&(result.wPawn));
    CMinitialiseWBishops(&(result.wBishop));
    CMinitialiseWKnights(&(result.wKnight));
    CMinitialiseWRooks(&(result.wRook));
    CMinitialiseWQueen(&(result.wQueen));
    CMinitialiseWKing(&(result.wKing));
    CMinitialiseBPawns(&(result.bPawn));
    CMinitialiseBBishops(&(result.bBishop));
    CMinitialiseBKnights(&(result.bKnight));
    CMinitialiseBRooks(&(result.bRook));
    CMinitialiseBQueen(&(result.bQueen));
    CMinitialiseBKing(&(result.bKing));
    CMinitialiseWEnPassants(&(result.wEnPassants));
    CMinitialiseBEnPassants(&(result.bEnPassants));
    CMinitialiseCastlesTurnCheck(&result);
    CMinitialiseNoCapturesOrPawnMoves(&(result.noCapturesOrPawnMoves));
    CMinitialisePreviousStates(&(result.ps));
//    initialisePly(&(result.ply));
    return result;
}

void CMinitialiseWPawns(T_bitboard *result){
    clearBits(result);
    setBit(result, 8);
    setBit(result, 9);
    setBit(result, 10);
    setBit(result, 11);
    //setBit(result, 12);
    setBit(result, 13);
    setBit(result, 14);
    setBit(result, 15);
    setBit(result, 3);
    setBit(result, 5);
    //setBit(result, 50);
}
void CMinitialiseWBishops(T_bitboard *result){
    clearBits(result);
    setBit(result, 2);
    //setBit(result, 5);
}

void CMinitialiseWKnights(T_bitboard *result){
    clearBits(result);
    setBit(result, 1);
    setBit(result, 6);
}

void CMinitialiseWRooks(T_bitboard *result){
    clearBits(result);
    setBit(result, 0);
    setBit(result, 7);
}

void CMinitialiseWQueen(T_bitboard *result){
    clearBits(result);
    setBit(result, 37);
    //setBit(result, 3);
}

void CMinitialiseWKing(T_bitboard *result){
    clearBits(result);
    setBit(result, 4);
}

void CMinitialiseBPawns(T_bitboard *result){
    clearBits(result);
    setBit(result, 48);
    setBit(result, 49);
    setBit(result, 50);
    setBit(result, 51);
    //setBit(result, 52);
    setBit(result, 53);
    setBit(result, 54);
    setBit(result, 55);
    setBit(result, 59);
    setBit(result, 61);
}
void CMinitialiseBBishops(T_bitboard *result){
    clearBits(result);
    setBit(result, 58);
    //setBit(result, 61);
}

void CMinitialiseBKnights(T_bitboard *result){
    clearBits(result);
    setBit(result, 57);
    setBit(result, 62);
    //setBit(result, 45);
    //setBit(result, 43);
    //setBit(result, 11);
    //setBit(result, 13);
}

void CMinitialiseBRooks(T_bitboard *result){
    clearBits(result);
    setBit(result, 56);
    setBit(result, 63);
}

void CMinitialiseBQueen(T_bitboard *result){
    clearBits(result);
    //setBit(result, 59);
    setBit(result, 24);

    //setBit(result, 34);

}

void CMinitialiseBKing(T_bitboard *result){
    clearBits(result);
    setBit(result, 60);
}

void CMinitialiseWEnPassants(unsigned char *c){
    clearCharBits(c);
}

void CMinitialiseBEnPassants(unsigned char *c){
    clearCharBits(c);
}

void CMinitialiseCastlesTurnCheck(T_boardState *b){
    b->castlesLRWhite = 1;
    b->castlesRRWhite = 1;
    b->castlesKWhite = 1;
    b->castlesLRBlack = 1;
    b->castlesRRBlack = 1;
    b->castlesKBlack = 1;
    b->whosTurn = 0;
    b->evaluateCheck = 0;
}

void CMinitialiseNoCapturesOrPawnMoves(unsigned char *c){
    *c = 0;
}

//Need to add in this functionality later
void CMinitialisePreviousStates(struct PrevStates **ps){
    *ps = (struct PrevStates *)malloc(MAX_PREV_STATES * sizeof(struct PrevStates));
    (*ps)->fp = 0;
    return;
}

//void initialisePly(unsigned short *i){
//    *i = 1;
//}
