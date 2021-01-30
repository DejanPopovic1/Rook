#include "state.h"
#include "moveGenerator.h"
#include "bitUtilities.h"
#include <assert.h>
#include "GlobalDeclarations.h"

void genWPawnsSuccStates(T_boardStates *dst, const T_boardState *b, const T_bitboard **rays){
    T_bitboard i = b->wPawn;
    int n;
    int maxIt = numOfSetBits(i);
    for(int j = 0; j < maxIt; j++){
        n = bitScanForward(i);
        genWPawnSuccStates(dst, b, n, rays);
        clearBit(&i, n);
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
void genWPawnSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays){
    //MOVE UP
    if(isUpEmpty(b, n) && !isPosInSecondLastColumn(n)){
        T_boardState cpy = *b;
        setBit(&(cpy.wPawn), n + 8);
        clearBit(&(cpy.wPawn), n);
        addState(dst, &cpy);
    }
    //MOVE UP UP
    if(isUpEmpty(b, n) && isUpUpEmpty(b, n) && !isPosInSecondLastColumn(n)){
        T_boardState cpy = *b;
        setBit(&(cpy.wPawn), n + 16);
        clearBit(&(cpy.wPawn), n);
        setBit(&(cpy.wEnPassants), n - 8);
        addState(dst, &cpy);
    }
    //CAPTURE LEFT
    if(isPosBlack(b, n + 7) && (n % 8)){
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

//Copy and paste these for other pieces
void genWBishopSuccState(T_boardStates *dst, const T_boardState *b, int n, T_bitboard *validMoves){
    int validMove = __builtin_ctzll(*validMoves);
    T_boardState cpy = *b;
    setBit(&(cpy.wBishop), validMove);
    clearBit(&(cpy.wBishop), n);
    addState(dst, &cpy);
    clearBit(validMoves, validMove);
}

//set bit and clear bit should be in one function called move() and this should be applied to all moveGenerator functions
//Check the ZF flag to see if there is a bit set in the forward and reverse scans
void genWBishopSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays){
    //UP RIGHT
    T_bitboard ray = rays[northEast][n];
    T_bitboard blocker = bAll(b) | wAll(b);
    T_bitboard intersect = ray & blocker;
    T_bitboard intersectRay;
    int locOfFirstNonZero = __builtin_ctzll(intersect);
    if(!intersect){
        intersectRay = 0;
    }
    else{
        intersectRay = rays[northEast][locOfFirstNonZero];
    }
    T_bitboard validMoves = ray ^ intersectRay;
    //printTBitboard(validMoves);
        //printf("Testing 1: %u\n", numOfSetBits(validMoves));
    //printf("Testing 1: %u\n", __builtin_popcountll(validMoves));
    //printf("%d", __builtin_popcount);
    for(int i = 0; i < (__builtin_popcountll(validMoves) - 1); i++){
        printf("Testing 2\n");
        genWBishopSuccState(dst, b, n, &validMoves);
    }
    //ADD CAPTURE OPTIONS ASWELL OVER HERE
}

void genWBishopsSuccStates(T_boardStates *dst, const T_boardState *b, const T_bitboard **rays){
    T_bitboard i = b->wBishop;
    int n;
    int maxIt = numOfSetBits(i);
    for(int j = 0; j < maxIt; j++){
        n = __builtin_ctzll(i);
        genWBishopSuccStates(dst, b, n, rays);
        clearBit(&i, n);
    }
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
