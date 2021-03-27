#include "testInitialisations.hpp"
#include "bitUtilities.hpp"
#include "moveGeneration.hpp"

#include <assert.h>


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
//    CMinitialisePreviousStates(&(result.ps));
    return result;
}

void CMinitialiseWPawns(T_bitboard *result){
    clearBits(result);
    setBit(result, 8);
    setBit(result, 9);
    setBit(result, 10);
    setBit(result, 11);
    setBit(result, 13);
    setBit(result, 14);
    setBit(result, 15);
    setBit(result, 3);
    setBit(result, 5);
}
void CMinitialiseWBishops(T_bitboard *result){
    clearBits(result);
    setBit(result, 2);
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
    setBit(result, 53);
    setBit(result, 54);
    setBit(result, 55);
    setBit(result, 59);
    setBit(result, 61);
}
void CMinitialiseBBishops(T_bitboard *result){
    clearBits(result);
    setBit(result, 58);
}

void CMinitialiseBKnights(T_bitboard *result){
    clearBits(result);
    setBit(result, 57);
    setBit(result, 62);
}

void CMinitialiseBRooks(T_bitboard *result){
    clearBits(result);
    setBit(result, 56);
    setBit(result, 63);
}

void CMinitialiseBQueen(T_bitboard *result){
    clearBits(result);
    setBit(result, 24);
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
//void CMinitialisePreviousStates(struct PrevStates **ps){
//    *ps = (struct PrevStates *)malloc(MAX_PREV_STATES * sizeof(struct PrevStates));
//    (*ps)->fp = 0;
//    return;
//}

T_boardState SMinitialiseBoardState(){
    T_boardState result;
    SMinitialiseWPawns(&(result.wPawn));
    SMinitialiseWBishops(&(result.wBishop));
    SMinitialiseWKnights(&(result.wKnight));
    SMinitialiseWRooks(&(result.wRook));
    SMinitialiseWQueen(&(result.wQueen));
    SMinitialiseWKing(&(result.wKing));
    SMinitialiseBPawns(&(result.bPawn));
    SMinitialiseBBishops(&(result.bBishop));
    SMinitialiseBKnights(&(result.bKnight));
    SMinitialiseBRooks(&(result.bRook));
    SMinitialiseBQueen(&(result.bQueen));
    SMinitialiseBKing(&(result.bKing));
    SMinitialiseWEnPassants(&(result.wEnPassants));
    SMinitialiseBEnPassants(&(result.bEnPassants));
    SMinitialiseCastlesTurnCheck(&result);
    SMinitialiseNoCapturesOrPawnMoves(&(result.noCapturesOrPawnMoves));
//    SMinitialisePreviousStates(&(result.ps));
    return result;
}

void SMinitialiseWPawns(T_bitboard *result){
    clearBits(result);
}
void SMinitialiseWBishops(T_bitboard *result){
    clearBits(result);
}

void SMinitialiseWKnights(T_bitboard *result){
    clearBits(result);
}

void SMinitialiseWRooks(T_bitboard *result){
    clearBits(result);
}

void SMinitialiseWQueen(T_bitboard *result){
    clearBits(result);
}

void SMinitialiseWKing(T_bitboard *result){
    clearBits(result);
    setBit(result, 4);
}

void SMinitialiseBPawns(T_bitboard *result){
    clearBits(result);
}
void SMinitialiseBBishops(T_bitboard *result){
    clearBits(result);
    setBit(result, 58);
}

void SMinitialiseBKnights(T_bitboard *result){
    clearBits(result);
    setBit(result, 57);
    setBit(result, 62);
}

void SMinitialiseBRooks(T_bitboard *result){
    clearBits(result);
    setBit(result, 56);
    setBit(result, 63);
}

void SMinitialiseBQueen(T_bitboard *result){
    clearBits(result);
    setBit(result, 24);
}

void SMinitialiseBKing(T_bitboard *result){
    clearBits(result);
    setBit(result, 60);
}

void SMinitialiseWEnPassants(unsigned char *c){
    clearCharBits(c);
}

void SMinitialiseBEnPassants(unsigned char *c){
    clearCharBits(c);
}

void SMinitialiseCastlesTurnCheck(T_boardState *b){
    b->castlesLRWhite = 1;
    b->castlesRRWhite = 1;
    b->castlesKWhite = 1;
    b->castlesLRBlack = 1;
    b->castlesRRBlack = 1;
    b->castlesKBlack = 1;
    b->whosTurn = 0;
    b->evaluateCheck = 0;
}

void SMinitialiseNoCapturesOrPawnMoves(unsigned char *c){
    *c = 0;
}

//Need to add in this functionality later
//void SMinitialisePreviousStates(struct PrevStates **ps){
//    *ps = (struct PrevStates *)malloc(MAX_PREV_STATES * sizeof(struct PrevStates));
//    (*ps)->fp = 0;
//    return;
//}

T_boardState PPinitialiseBoardState(){
    T_boardState result;
    PPinitialiseWPawns(&(result.wPawn));
    PPinitialiseWBishops(&(result.wBishop));
    PPinitialiseWKnights(&(result.wKnight));
    PPinitialiseWRooks(&(result.wRook));
    PPinitialiseWQueen(&(result.wQueen));
    PPinitialiseWKing(&(result.wKing));
    PPinitialiseBPawns(&(result.bPawn));
    PPinitialiseBBishops(&(result.bBishop));
    PPinitialiseBKnights(&(result.bKnight));
    PPinitialiseBRooks(&(result.bRook));
    PPinitialiseBQueen(&(result.bQueen));
    PPinitialiseBKing(&(result.bKing));
    PPinitialiseWEnPassants(&(result.wEnPassants));
    PPinitialiseBEnPassants(&(result.bEnPassants));
    PPinitialiseCastlesTurnCheck(&result);
    PPinitialiseNoCapturesOrPawnMoves(&(result.noCapturesOrPawnMoves));
//    PPinitialisePreviousStates(&(result.ps));
    return result;
}

void PPinitialiseWPawns(T_bitboard *result){
    clearBits(result);
    setBit(result, 49);
}
void PPinitialiseWBishops(T_bitboard *result){
    clearBits(result);
}

void PPinitialiseWKnights(T_bitboard *result){
    clearBits(result);
}

void PPinitialiseWRooks(T_bitboard *result){
    clearBits(result);
}

void PPinitialiseWQueen(T_bitboard *result){
    clearBits(result);
}

void PPinitialiseWKing(T_bitboard *result){
    clearBits(result);
    setBit(result, 4);
}

void PPinitialiseBPawns(T_bitboard *result){
    clearBits(result);
}
void PPinitialiseBBishops(T_bitboard *result){
    clearBits(result);
    setBit(result, 58);
}

void PPinitialiseBKnights(T_bitboard *result){
    clearBits(result);
    //setBit(result, 57);
    setBit(result, 62);
}

void PPinitialiseBRooks(T_bitboard *result){
    clearBits(result);
    setBit(result, 56);
    setBit(result, 63);
}

void PPinitialiseBQueen(T_bitboard *result){
    clearBits(result);
    setBit(result, 24);
}

void PPinitialiseBKing(T_bitboard *result){
    clearBits(result);
    setBit(result, 60);
}

void PPinitialiseWEnPassants(unsigned char *c){
    clearCharBits(c);
}

void PPinitialiseBEnPassants(unsigned char *c){
    clearCharBits(c);
}

void PPinitialiseCastlesTurnCheck(T_boardState *b){
    b->castlesLRWhite = 1;
    b->castlesRRWhite = 1;
    b->castlesKWhite = 1;
    b->castlesLRBlack = 1;
    b->castlesRRBlack = 1;
    b->castlesKBlack = 1;
    b->whosTurn = 0;
    b->evaluateCheck = 0;
}

void PPinitialiseNoCapturesOrPawnMoves(unsigned char *c){
    *c = 0;
}

//Need to add in this functionality later
//void PPinitialisePreviousStates(struct PrevStates **ps){
//    *ps = (struct PrevStates *)malloc(MAX_PREV_STATES * sizeof(struct PrevStates));
//    (*ps)->fp = 0;
//    return;
//}

T_boardState ICinitialiseBoardState(){
    T_boardState result;
    ICinitialiseWPawns(&(result.wPawn));
    ICinitialiseWBishops(&(result.wBishop));
    ICinitialiseWKnights(&(result.wKnight));
    ICinitialiseWRooks(&(result.wRook));
    ICinitialiseWQueen(&(result.wQueen));
    ICinitialiseWKing(&(result.wKing));
    ICinitialiseBPawns(&(result.bPawn));
    ICinitialiseBBishops(&(result.bBishop));
    ICinitialiseBKnights(&(result.bKnight));
    ICinitialiseBRooks(&(result.bRook));
    ICinitialiseBQueen(&(result.bQueen));
    ICinitialiseBKing(&(result.bKing));
    ICinitialiseWEnPassants(&(result.wEnPassants));
    ICinitialiseBEnPassants(&(result.bEnPassants));
    ICinitialiseCastlesTurnCheck(&result);
    ICinitialiseNoCapturesOrPawnMoves(&(result.noCapturesOrPawnMoves));
//    PPinitialisePreviousStates(&(result.ps));
    return result;
}

void ICinitialiseWPawns(T_bitboard *result){
    clearBits(result);
    setBit(result, 49);
}
void ICinitialiseWBishops(T_bitboard *result){
    clearBits(result);
}

void ICinitialiseWKnights(T_bitboard *result){
    clearBits(result);
}

void ICinitialiseWRooks(T_bitboard *result){
    clearBits(result);
}

void ICinitialiseWQueen(T_bitboard *result){
    clearBits(result);
}

void ICinitialiseWKing(T_bitboard *result){
    clearBits(result);
    setBit(result, 45);
}

void ICinitialiseBPawns(T_bitboard *result){
    clearBits(result);
}
void ICinitialiseBBishops(T_bitboard *result){
    clearBits(result);
    setBit(result, 58);
}

void ICinitialiseBKnights(T_bitboard *result){
    clearBits(result);
    //setBit(result, 57);
    setBit(result, 62);
}

void ICinitialiseBRooks(T_bitboard *result){
    clearBits(result);
    setBit(result, 56);
    setBit(result, 63);
}

void ICinitialiseBQueen(T_bitboard *result){
    clearBits(result);
    setBit(result, 8);
}

void ICinitialiseBKing(T_bitboard *result){
    clearBits(result);
    setBit(result, 60);
}

void ICinitialiseWEnPassants(unsigned char *c){
    clearCharBits(c);
}

void ICinitialiseBEnPassants(unsigned char *c){
    clearCharBits(c);
}

void ICinitialiseCastlesTurnCheck(T_boardState *b){
    b->castlesLRWhite = 1;
    b->castlesRRWhite = 1;
    b->castlesKWhite = 1;
    b->castlesLRBlack = 1;
    b->castlesRRBlack = 1;
    b->castlesKBlack = 1;
    b->whosTurn = 0;
    b->evaluateCheck = 0;
}

void ICinitialiseNoCapturesOrPawnMoves(unsigned char *c){
    *c = 0;
}




T_boardState LKinitialiseBoardState(){
    T_boardState result;
    LKinitialiseWPawns(&(result.wPawn));
    LKinitialiseWBishops(&(result.wBishop));
    LKinitialiseWKnights(&(result.wKnight));
    LKinitialiseWRooks(&(result.wRook));
    LKinitialiseWQueen(&(result.wQueen));
    LKinitialiseWKing(&(result.wKing));
    LKinitialiseBPawns(&(result.bPawn));
    LKinitialiseBBishops(&(result.bBishop));
    LKinitialiseBKnights(&(result.bKnight));
    LKinitialiseBRooks(&(result.bRook));
    LKinitialiseBQueen(&(result.bQueen));
    LKinitialiseBKing(&(result.bKing));
    LKinitialiseWEnPassants(&(result.wEnPassants));
    LKinitialiseBEnPassants(&(result.bEnPassants));
    LKinitialiseCastlesTurnCheck(&result);
    LKinitialiseNoCapturesOrPawnMoves(&(result.noCapturesOrPawnMoves));
//    PPinitialisePreviousStates(&(result.ps));
    return result;
}

void LKinitialiseWPawns(T_bitboard *result){
    clearBits(result);
    setBit(result, 32);
}
void LKinitialiseWBishops(T_bitboard *result){
    clearBits(result);
}

void LKinitialiseWKnights(T_bitboard *result){
    clearBits(result);
}

void LKinitialiseWRooks(T_bitboard *result){
    clearBits(result);
}

void LKinitialiseWQueen(T_bitboard *result){
    clearBits(result);
    setBit(result, 11);
    setBit(result, 13);
    //setBit(result, 1);
}

void LKinitialiseWKing(T_bitboard *result){
    clearBits(result);
    setBit(result, 7);
}

void LKinitialiseBPawns(T_bitboard *result){
    clearBits(result);
}
void LKinitialiseBBishops(T_bitboard *result){
    clearBits(result);
    //setBit(result, 58);
}

void LKinitialiseBKnights(T_bitboard *result){
    clearBits(result);
    //setBit(result, 57);
    //setBit(result, 62);
}

void LKinitialiseBRooks(T_bitboard *result){
    clearBits(result);
    //setBit(result, 56);
    //setBit(result, 63);
}

void LKinitialiseBQueen(T_bitboard *result){
    clearBits(result);
    //setBit(result, 8);
}

void LKinitialiseBKing(T_bitboard *result){
    clearBits(result);
    setBit(result, 60);
}

void LKinitialiseWEnPassants(unsigned char *c){
    clearCharBits(c);
}

void LKinitialiseBEnPassants(unsigned char *c){
    clearCharBits(c);
}

void LKinitialiseCastlesTurnCheck(T_boardState *b){
    b->castlesLRWhite = 1;
    b->castlesRRWhite = 1;
    b->castlesKWhite = 1;
    b->castlesLRBlack = 1;
    b->castlesRRBlack = 1;
    b->castlesKBlack = 1;
    b->whosTurn = 0;
    b->evaluateCheck = 0;
}

void LKinitialiseNoCapturesOrPawnMoves(unsigned char *c){
    *c = 0;
}



