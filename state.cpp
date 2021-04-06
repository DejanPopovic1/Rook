#include "state.hpp"
#include "bitUtilities.hpp"
#include "moveGeneration.hpp"

#include <assert.h>

T_bitboard *pieceBitboard(T_boardState *b, char piece){
    switch(piece){
    case whitePawn:
        return &b->wPawn;
        break;
    case whiteBishop:
        return &b->wBishop;
        break;
    case whiteKnight:
        return &b->wKnight;
        break;
    case whiteRook:
        return &b->wRook;
        break;
    case whiteQueen:
        return &b->wQueen;
        break;
    case whiteKing:
        return &b->wKing;
        break;
    case blackPawn:
        return &b->bPawn;
        break;
    case blackBishop:
        return &b->bBishop;
        break;
    case blackKnight:
        return &b->bKnight;
        break;
    case blackRook:
        return &b->bRook;
        break;
    case blackQueen:
        return &b->bQueen;
        break;
    case blackKing:
        return &b->bKing;
        break;
    default:
        assert(false);
    }
}



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

bool isStatesEqual(T_boardState a, T_boardState b){
    return
        a.wPawn == b.wPawn &&
        a.bPawn == b.bPawn &&
        a.wBishop == b.wBishop &&
        a.bBishop == b.bBishop &&
        a.wKnight == b.wKnight &&
        a.bKnight == b.bKnight &&
        a.wRook == b.wRook &&
        a.bRook == b.bRook &&
        a.wQueen == b.wQueen &&
        a.bQueen == b.bQueen &&
        a.wKing == b.wKing &&
        a.bKing == b.bKing &&
        a.wEnPassants == b.wEnPassants &&
        a.bEnPassants == b.bEnPassants &&
        a.castlesLRWhite == b.castlesLRWhite &&
        a.castlesRRWhite == b.castlesRRWhite &&
        a.castlesKWhite == b.castlesKWhite &&
        a.castlesLRBlack == b.castlesLRBlack &&
        a.castlesRRBlack == b.castlesRRBlack &&
        a.castlesKBlack == b.castlesKBlack &&
        a.whosTurn == b.whosTurn &&
        a.evaluateCheck == b.evaluateCheck &&
        a.noCapturesOrPawnMoves == b.noCapturesOrPawnMoves;
}

bool isInCheck(T_boardState b){
    T_Node *n = createNode();
    b.whosTurn++;
    genSuccStates(n, &b);
    b.whosTurn++;
    return !isKingsExist(n, b.whosTurn);
}

bool isPawn(int p){
    return (p == whitePawn || p == blackPawn) ? true : false;
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
    initialiseCastlesTurnCheck(&result);
    initialiseNoCapturesOrPawnMoves(&(result.noCapturesOrPawnMoves));
//    initialisePreviousStates(&(result.ps));
//    initialisePly(&(result.ply));
    return result;
}

void initialiseWPawns(T_bitboard *result){
    clearBits(result);
    setBit(result, 8);
    setBit(result, 9);
    setBit(result, 10);
    setBit(result, 11);
    setBit(result, 12);
    setBit(result, 13);
    setBit(result, 14);
    setBit(result, 15);
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
    //setBit(result, 18);
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
    setBit(result, 48);
    setBit(result, 49);
    setBit(result, 50);
    setBit(result, 51);
    setBit(result, 52);
    setBit(result, 53);
    setBit(result, 54);
    setBit(result, 55);
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
    //setBit(result, 21);
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

void initialiseBEnPassants(unsigned char *c){
    clearCharBits(c);
}

void initialiseCastlesTurnCheck(T_boardState *b){
    b->castlesLRWhite = 1;
    b->castlesRRWhite = 1;
    b->castlesKWhite = 1;
    b->castlesLRBlack = 1;
    b->castlesRRBlack = 1;
    b->castlesKBlack = 1;
    b->whosTurn = 0;
    b->evaluateCheck = 0;
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
