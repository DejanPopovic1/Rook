#include "state.h"
#include "generateSlideMoves.h"
#include "output.h"
#include "GlobalDeclarations.h"
#include "bitUtilities.h"
#include "assert.h"


//bAll and wAll might need to be done immediately after a state generatioin and saved as a state
T_bitboard wAll(const T_boardState *b){
    T_bitboard or = b->wPawn | b->wBishop | b->wKnight | b->wRook | b->wQueen | b->wKing;
    return or;
}

T_bitboard bAll(const T_boardState *b){
    T_bitboard or = b->bPawn | b->bBishop | b->bKnight | b->bRook | b->bQueen | b->bKing;
    //printf("Testing: \n");
    //printTBitboard(or);
    return or;
}

//King will never be cleared so can remove it
void clearPosition(T_boardState *b, char pos){
    clearBit(b->wPawn, pos);
    clearBit(b->wBishop, pos);
    clearBit(b->wKnight, pos);
    clearBit(b->wRook, pos);
    clearBit(b->wQueen, pos);
    clearBit(b->wKing, pos);
    clearBit(b->bPawn, pos);
    clearBit(b->bBishop, pos);
    clearBit(b->bKnight, pos);
    clearBit(b->bRook, pos);
    clearBit(b->bQueen, pos);
    clearBit(b->bKing, pos);
}

void removeOpponent(T_boardState *b, int pos){
    if(whosTurnNEW(b->ply) == whiteTurn){
        clearBit(&(b->bPawn), pos);
        clearBit(&(b->bBishop), pos);
        clearBit(&(b->bKnight), pos);
        clearBit(&(b->bRook), pos);
        clearBit(&(b->bQueen), pos);
        clearBit(&(b->bKing), pos);
    }
    if(whosTurnNEW(b->ply) == blackTurn){
        clearBit(&(b->wPawn), pos);
        clearBit(&(b->wBishop), pos);
        clearBit(&(b->wKnight), pos);
        clearBit(&(b->wRook), pos);
        clearBit(&(b->wQueen), pos);
        clearBit(&(b->wKing), pos);
    }
}

void printStates(T_boardStates *b){
    for(int i = 0; i < length(b); i++){
        printState((b->bs)[i]);
    }
}

int whosTurnNEW(const int ply){
    if((ply % 2) == 1){
        return whiteTurn;
    }
    return blackTurn;
}

bool isRankFive(char n){
    if(n <= 39 && n >= 32){
        return true;
    }
    return false;
}

bool isRankFour(char n){
    if(n <= 31 && n >= 24){
        return true;
    }
    return false;
}

bool isRankSeven(char n){
    if(n <= 55 && n >= 48){
        return true;
    }
    return false;
}

char whatRank(char n){
    return (n / 8);
}

char whatFile(char n){
    return (n % 8);
}

bool isPosWhite(T_boardState *b, int n){
    T_bitboard or = b->wPawn | b->wBishop | b->wKnight | b->wRook | b->wQueen | b->wKing;
    if(isBitSet(or, n)){
        return true;
    }
    return false;
}

bool isPosBlack(T_boardState *b, int n){
    T_bitboard or = b->bPawn | b->bBishop | b->bKnight | b->bRook | b->bQueen | b->bKing;
    if(isBitSet(or, n)){
        return true;
    }
    return false;
}

bool isPosEmpty(const T_boardState *b, int n){
    T_bitboard or = b->wPawn | b->wBishop | b->wKnight | b->wRook | b->wQueen | b->wKing |
                    b->bPawn | b->bBishop | b->bKnight | b->bRook | b->bQueen | b->bKing;
    if(!isBitSet(or, n)){
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
    (dst->bs)[dst->fi] = *src;
    (dst->fi)++;
    //printState(*src);
}

T_boardStates *initialiseStates(){
    T_boardStates *bss = malloc(sizeof(T_boardStates));
    bss->fi = 0;
}

int length(T_boardStates *bss){
    return bss->fi;
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
    initialiseCastlesAndTurn(&result);
    //initialiseWhosTurn(&(result.whosTurn));
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
    setBit(result, 18);
    setBit(result, 21);
    setBit(result, 31);
    setBit(result, 34);
}

void initialiseWKnights(T_bitboard *result){
    clearBits(result);
    setBit(result, 1);
    setBit(result, 6);
        setBit(result, 46);
}

void initialiseWRooks(T_bitboard *result){
    clearBits(result);
    setBit(result, 0);
    setBit(result, 7);
    setBit(result, 41);
}

void initialiseWQueen(T_bitboard *result){
    clearBits(result);
    setBit(result, 3);
    setBit(result, 40);
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

void initialiseWEnPassants(unsigned char *c){
    clearCharBits(c);
}

void initialiseBEnPassants(char *c){
    clearCharBits(c);
}

void initialiseCastlesAndTurn(T_boardState *b){
    b->castlesBlack = 7;
    b->castlesWhite = 7;
    b->whosTurn = 0;
    //setCharBits(b->castlesWhite);
}

void initialiseNoCapturesOrPawnMoves(char *c){
    *c = 0;
}

//void initialiseWhosTurn(&(result.whosTurn)){
//
//
//}

//Need to add in this functionality later
void initialisePreviousStates(struct PrevStates **ps){
    *ps = malloc(MAX_PREV_STATES * sizeof(struct PrevStates));
    (*ps)->fp = 0;
    return;
}

void initialisePly(int *i){
    *i = 1;
}
