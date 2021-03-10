#include "state.hpp"
//#include "output.h"
#include "bitUtilities.hpp"
#include "assert.h"

//bAll and wAll might need to be done immediately after a state generatioin and saved as a state
T_bitboard wAll(const T_boardState *b){
    T_bitboard o = b->wPawn | b->wBishop | b->wKnight | b->wRook | b->wQueen | b->wKing;
    return o;
}

T_bitboard bAll(const T_boardState *b){
    T_bitboard o = b->bPawn | b->bBishop | b->bKnight | b->bRook | b->bQueen | b->bKing;
    return o;
}

T_bitboard all(const T_boardState *b){
    T_bitboard o =  b->wPawn | b->wBishop | b->wKnight | b->wRook | b->wQueen | b->wKing | b->bPawn | b->bBishop | b->bKnight | b->bRook | b->bQueen | b->bKing;
    return o;
}

T_bitboard sameAll(const T_boardState *b){
    if(!b->whosTurn){
        return wAll(b);
    }
    else{
        return bAll(b);
    }
}

T_bitboard oppositeAll(T_boardState *b){
    if(!b->whosTurn){
        return bAll(b);
    }
    else{
        return wAll(b);
    }
}

//void removeOpponent(T_boardState *b, int pos){
//    if(whosTurnNEW(b->ply) == whiteTurn){
//        clearBit(&(b->bPawn), pos);
//        clearBit(&(b->bBishop), pos);
//        clearBit(&(b->bKnight), pos);
//        clearBit(&(b->bRook), pos);
//        clearBit(&(b->bQueen), pos);
//        clearBit(&(b->bKing), pos);
//    }
//    if(whosTurnNEW(b->ply) == blackTurn){
//        clearBit(&(b->wPawn), pos);
//        clearBit(&(b->wBishop), pos);
//        clearBit(&(b->wKnight), pos);
//        clearBit(&(b->wRook), pos);
//        clearBit(&(b->wQueen), pos);
//        clearBit(&(b->wKing), pos);
//    }
//}


//
//void printStatesAndValidMoves(T_boardState *c, T_boardStates *b){
//    for(int i = 0; i < length(b); i++){
//        printStateAndValidMoves(*c, (b->bs)[i]);
//    }
//}

//void printValidMoves(T_boardState *c, T_boardStates *ss){
//    char **list = malloc(MAX_SUCCESSOR_STATES * sizeof(char*));
//    T_chessboard *ssArr, *cArr = toIntArray(*c);
//    for(int i = 0; i < length(ss); i++){
//        ssArr = toIntArray(ss->bs[i]);
//        list[i] = toAlgebraicNotation(cArr, ssArr);
//    }
//    //printf("%s", list[0]);
//    return list;
//}

bool isPawn(int p){
    return (p == whitePawn || p == blackPawn) ? true : false;
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

bool isRankTwo(char n){
    if(n <= 15 && n >= 8){
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

bool isPosEmpty(const T_boardState *b, int n){
    T_bitboard o = b->wPawn | b->wBishop | b->wKnight | b->wRook | b->wQueen | b->wKing |
                    b->bPawn | b->bBishop | b->bKnight | b->bRook | b->bQueen | b->bKing;
    if(!isBitSet(o, n)){
       return true;
    }
    return false;
}

void addState(T_boardStates *dst, T_boardState *src){
    src->whosTurn ? src->bEnPassants = 0 : src->wEnPassants = 0;
    (dst->bs)[dst->fi] = *src;
    (dst->fi)++;
}

T_boardStates *initialiseStates(){
    T_boardStates *bss = (T_boardStates *)malloc(sizeof(T_boardStates));
    bss->fi = 0;
    return bss;
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
    initialiseNoCapturesOrPawnMoves(&(result.noCapturesOrPawnMoves));
    initialisePreviousStates(&(result.ps));
//    initialisePly(&(result.ply));
    return result;
}

void initialiseWPawns(T_bitboard *result){
    clearBits(result);
//    setBit(result, 8);
//    setBit(result, 9);
//    setBit(result, 10);
//    setBit(result, 11);
//    setBit(result, 12);
//    setBit(result, 13);
//    setBit(result, 14);
//    setBit(result, 15);
//    //setBit(result, 50);
}
void initialiseWBishops(T_bitboard *result){
    clearBits(result);
    //setBit(result, 2);
    //setBit(result, 5);
}

void initialiseWKnights(T_bitboard *result){
    clearBits(result);
    //setBit(result, 1);
    //setBit(result, 6);
}

void initialiseWRooks(T_bitboard *result){
    clearBits(result);
    setBit(result, 0);
    setBit(result, 7);
}

void initialiseWQueen(T_bitboard *result){
    clearBits(result);
    //setBit(result, 3);
}

void initialiseWKing(T_bitboard *result){
    clearBits(result);
    setBit(result, 4);
}

void initialiseBPawns(T_bitboard *result){
    clearBits(result);
    setBit(result, 48);
    setBit(result, 49);
    setBit(result, 50);
    setBit(result, 51);
    setBit(result, 52);
    setBit(result, 53);
    setBit(result, 54);
    setBit(result, 55);
    //setBit(result, 13);
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
    //setBit(result, 34);
    setBit(result, 37);
}

void initialiseBKing(T_bitboard *result){
    clearBits(result);
    setBit(result, 60);
}

void initialiseWEnPassants(unsigned char *c){
    clearCharBits(c);
}

void initialiseBEnPassants(unsigned char *c){
    clearCharBits(c);
}

void initialiseCastlesAndTurn(T_boardState *b){
    b->castlesLRWhite = 1;
    b->castlesRRWhite = 1;
    b->castlesKWhite = 1;
    b->castlesLRBlack = 1;
    b->castlesRRBlack = 1;
    b->castlesKBlack = 1;
    b->whosTurn = 0;
}

void initialiseNoCapturesOrPawnMoves(unsigned char *c){
    *c = 0;
}

//Need to add in this functionality later
void initialisePreviousStates(struct PrevStates **ps){
    *ps = (struct PrevStates *)malloc(MAX_PREV_STATES * sizeof(struct PrevStates));
    (*ps)->fp = 0;
    return;
}

//void initialisePly(unsigned short *i){
//    *i = 1;
//}
