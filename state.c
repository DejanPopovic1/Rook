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

bool isPosWhite(T_boardState *b, int n){
    T_bitboard and = b->wPawn & b->wBishop & b->wKnight & b->wRook & b->wQueen & b->wKing;
    if(isBitSet(and, n)){
        return true;
    }
    return false;
}

bool isPosBlack(T_boardState *b, int n){
    T_bitboard and = b->bPawn & b->bBishop & b->bKnight & b->bRook & b->bQueen & b->bKing;
    if(isBitSet(and, n)){
        return true;
    }
    return false;
}

bool isPosInSecondLastColumn(int n){
    if(n <= 55 && n >= 48){
        return true;
    }
    return false;
}

void addState(T_boardStates *dst, const T_boardState *src){
    dst->bs[dst->fi] = *src;
    (dst->fi)++;
}

bool isPosEmpty(T_boardState *b, int n){
    T_bitboard or = b->wPawn | b->wBishop | b->wKnight | b->wRook | b->wQueen | b->wKing | b->bPawn | b->bBishop | b->bKnight | b->bRook | b->bQueen | b->bKing;
    if(!isBitSet(or, n)){
       return true;
    }
    return false;
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
    initialiseWEnPassants(&(result.wEnPassants));
    initialiseBEnPassants(&(result.bEnPassants));
    initialiseCastles(&result);
    initialiseNoCapturesOrPawnMoves(&(result.noCapturesOrPawnMoves));
    initialisePreviousStates(&(result.ps));
    initialisePly(&(result.ply));
    return result;
}

void initialiseWPawns(T_bitboard *result){
    clearBits(result);
    for(int i = 8; i <= 15; i++){
        setBit(result, i);
    }
}
void initialiseWBishops(T_bitboard *result){
    clearBits(result);
    setBit(result, 2);
    setBit(result, 5);
}

void initialiseWKnights(T_bitboard *result){
    clearBits(result);
    setBit(result, 1);
    setBit(result, 6);
}

void initialiseWRooks(T_bitboard *result){
    clearBits(result);
    setBit(result, 0);
    setBit(result, 7);
}

void initialiseWQueen(T_bitboard *result){
    clearBits(result);
    setBit(result, 3);
}

void initialiseWKing(T_bitboard *result){
    clearBits(result);
    setBit(result, 4);
}

void initialiseBPawns(T_bitboard *result){
    clearBits(result);
    for(int i = 48; i <= 55; i++){
        setBit(result, i);
    }
}
void initialiseBBishops(T_bitboard *result){
    clearBits(result);
    setBit(result, 58);
    setBit(result, 61);
}

void initialiseBKnights(T_bitboard *result){
    clearBits(result);
    setBit(result, 57);
    setBit(result, 62);
}

void initialiseBRooks(T_bitboard *result){
    clearBits(result);
    setBit(result, 56);
    setBit(result, 63);
}

void initialiseBQueen(T_bitboard *result){
    clearBits(result);
    setBit(result, 59);
}

void initialiseBKing(T_bitboard *result){
    clearBits(result);
    setBit(result, 60);
}

void initialiseWEnPassants(char *c){
    clearCharBits(c);
}

void initialiseBEnPassants(char *c){
    clearCharBits(c);
}

void initialiseCastles(T_boardState *b){
    b->castlesBlack = 7;
    b->castlesWhite = 7;
    //setCharBits(b->castlesWhite);
}

void initialiseNoCapturesOrPawnMoves(char *c){
    *c = 0;
}

//Need to add in this functionality later
void initialisePreviousStates(struct PrevStates **ps){
    *ps = malloc(MAX_PREV_STATES * sizeof(struct PrevStates));
    (*ps)->fp = 0;
    return;
}

void initialisePly(int *i){
    *i = 1;
}
