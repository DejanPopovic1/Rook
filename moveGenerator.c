#include "state.h"
#include "moveGenerator.h"

void genWPawnsSuccStates(T_boardStates *dst, const T_boardState *b){
    T_bitboard i = b->wPawn;
    int n;
    for(int j = 0; j < numOfSetBits(*b); j++){
        n = bitScanForward(i);
        genWPawnSuccStates(dst, b, n);

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

void genWPawnSuccStates(T_boardStates *dst, const T_boardState *b, int n){
    //MOVE UP ONE
    if(isUpEmpty(b, n) && !isPosInSecondLastColumn(n)){
        setBit(b->wPawn, n + 8);
        clearBit(b->wPawn, n);
    }
    //MOVE UP TWO
    if(isUpEmpty(b, n) && !isPosInSecondLastColumn(n)){
        setBit(b->wPawn, n + 16);
        clearBit(b->wPawn, n);
    }






    //If(isUpEmpty && !isSecondLastRow)
    //src.wPawn = 0;
   // addState(dst, &src);
//    c->wPawn = 0;
    //MOVE UP TWO
    //CAPTURE LEFT
    //CAPTURE RIGHT
    //EN PASSANT LEFT
    //EN PASSANT RIGHT
    //PROMOTIONS
        //BISHOP
        //KNIGHT
        //ROOK
        //QUEEN

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
