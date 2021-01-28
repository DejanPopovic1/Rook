#include "state.h"
#include "moveGenerator.h"
#include "bitUtilities.h"

void genWPawnsSuccStates(T_boardStates *dst, const T_boardState *b){
    T_bitboard i = b->wPawn;
    int n;
    int maxIt = numOfSetBits(i);
    for(int j = 0; j < maxIt; j++){
        n = bitScanForward(i);
        genWPawnSuccStates(dst, b, n);
        clearBit(&i, n);
        //printf("%d ", n);
    }
}

bool isUpEmpty(const T_boardState *b, int n){
    if(isPosEmpty(b, n + 8)){
        return true;
    }
    return false;
}

bool isUpUpEmpty(const T_boardState *b, int n){
    if(isPosEmpty(b, n + 8) && isPosEmpty(b, n + 16)){
        return true;
    }
    return false;
}

//factor out specific moves once all moveGenerations complete
void genWPawnSuccStates(T_boardStates *dst, const T_boardState *b, int n){
    //MOVE UP
    if(isUpEmpty(b, n) && !isPosInSecondLastColumn(n)){
        T_boardState cpy = *b;
        setBit(&(cpy.wPawn), n + 8);
        clearBit(&(cpy.wPawn), n);
        addState(dst, &cpy);
    }
//    //MOVE UP UP
    if(isUpEmpty(b, n) && !isPosInSecondLastColumn(n)){
        T_boardState cpy = *b;
        setBit(&(cpy.wPawn), n + 16);
        clearBit(&(cpy.wPawn), n);
        setBit(&(cpy.wEnPassants), n - 8);
        addState(dst, &cpy);
    }
//    //CAPTURE LEFT
    if(isPosBlack(b, n + 7) && (n % 8) /*opponent bit*/){
        T_boardState cpy = *b;
        removeOpponent(&cpy, n + 7);
        setBit(&(cpy.wPawn), n + 7);
        clearBit(&(cpy.wPawn), n);
        addState(dst, &cpy);
    }
    //CAPTURE RIGHT
    if(isPosBlack(b, n + 9) && ((n + 1) % 8)){
        T_boardState cpy = *b;
        removeOpponent(&cpy, n + 9);
        setBit(&(cpy.wPawn), n + 9);
        clearBit(&(cpy.wPawn), n);
        addState(dst, &cpy);
    }
    //EN PASSANT LEFT
    char frFile = whatFile(n);
    if((frFile % 8) && isCharBitSet(b->bEnPassants, frFile - 1) && isRankFive(n)){
        T_boardState cpy = *b;
        clearBit(b->bPawn, n - 1);
        setBit(b->wPawn, n + 7);
        clearBit(b->wPawn, n);
        addState(dst, &cpy);
    }
    //EN PASSANT RIGHT
    if(((frFile + 1) % 8) && isCharBitSet(b->bEnPassants, frFile + 1) && isRankFive(n)){
        T_boardState cpy = *b;
        clearBit(b->bPawn, n + 1);
        setBit(b->wPawn, n + 9);
        clearBit(b->wPawn, n);
        addState(dst, &cpy);
    }
    //PROMOTIONS
        //BISHOP
    if(isRankSeven(n) && isUpEmpty(b, n)){
        T_boardState cpy = *b;
        setBit(b->wBishop, n + 8);
        clearBit(b->wPawn, n);
        addState(dst, &cpy);
    }
        //KNIGHT
    if(isRankSeven(n) && isUpEmpty(b, n)){
        T_boardState cpy = *b;
        setBit(b->wKnight, n + 8);
        clearBit(b->wPawn, n);
        addState(dst, &cpy);
    }
        //ROOK
    if(isRankSeven(n) && isUpEmpty(b, n)){
        T_boardState cpy = *b;
        setBit(b->wRook, n + 8);
        clearBit(b->wPawn, n);
        addState(dst, &cpy);
    }
        //QUEEN
    if(isRankSeven(n) && isUpEmpty(b, n)){
        T_boardState cpy = *b;
        setBit(b->wQueen, n + 8);
        clearBit(b->wPawn, n);
        addState(dst, &cpy);
    }
}

void genWBishopSuccStates(T_boardState c, T_boardStates *ss){
    //Generate Pawn Moves
}

void genWKnightSuccStates(T_boardState c, T_boardStates *ss){
    //Generate Pawn Moves
}

void genWRookSuccStates(T_boardState c, T_boardStates *ss){

}

void genWQueenSuccStates(T_boardState c, T_boardStates *ss){

}

void genWKingSuccStates(T_boardState c, T_boardStates *ss){

}

void genBPawnSuccStates(T_boardState c, T_boardStates *ss){


}

void genBBishopSuccStates(T_boardState c, T_boardStates *ss){

}

void genBKnightSuccStates(T_boardState c, T_boardStates *ss){

}

void genBRookSuccStates(T_boardState c, T_boardStates *ss){

}

void genBQueenSuccStates(T_boardState c, T_boardStates *ss){

}

void genBKingSuccStates(T_boardState c, T_boardStates *ss){


}
