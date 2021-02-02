#include "state.h"
#include "moveGenerator.h"
#include "bitUtilities.h"
#include <assert.h>
#include "GlobalDeclarations.h"

//Use MovePiece function to simplify statements
//see if more state functions can come in here so they may be inlined
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

bool isNortherlyOrEast(int direction){
    if(direction == northEast || direction == north || direction == northWest || direction == east){
        return true;
    }
    return false;
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
void genIterSuccState(T_boardStates *dst, const T_boardState *b, int n, T_bitboard *validMoves, int piece, int direction){
    int validMove = (isNortherlyOrEast(direction) ? __builtin_ctzll(*validMoves) : BITBOARD_INDEX_SIZE - __builtin_clzll(*validMoves));
    T_boardState cpy = *b;
    setBit(stateMember(&cpy, piece), validMove);
    clearBit(stateMember(&cpy, piece), n);
    addState(dst, &cpy);
    clearBit(validMoves, validMove);
}

T_bitboard genPseudoValidMoves(const T_boardState *b, int n, int direction, const T_bitboard **rays){
    T_bitboard ray = rays[direction][n];
    T_bitboard blocker = bAll(b) | wAll(b);
    T_bitboard intersect = ray & blocker;
    int firstPos;
    firstPos = (isNortherlyOrEast(direction) ? __builtin_ctzll(intersect) : BITBOARD_INDEX_SIZE - __builtin_clzll(intersect));
    T_bitboard intersectRay = (!intersect) ? 0 : rays[direction][firstPos];
    return (ray ^ intersectRay);
}

//Refactor out quiete vs attacking moves
void genDirStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays, int direction, int piece){
    T_bitboard pseudoValidMoves;
    int lastPos;
    pseudoValidMoves = genPseudoValidMoves(b, n, direction, rays);
    int i;
    for(int i = 0; __builtin_popcountll(pseudoValidMoves) > 1; i++){
        genIterSuccState(dst, b, n, &pseudoValidMoves, piece, direction);
    }
    if(!pseudoValidMoves){
        return;
    }
    lastPos = (isNortherlyOrEast(direction) ? __builtin_ctzll(pseudoValidMoves) : BITBOARD_INDEX_SIZE - __builtin_clzll(pseudoValidMoves));
    if(!isPosWhite(b, lastPos)){
        genIterSuccState(dst, b, n, &pseudoValidMoves, piece, direction);
        if(isPosBlack(b, lastPos)){
            removeOpponent(&(dst->bs[(dst->fi) - 1]), lastPos);
        }
    }
}

//set bit and clear bit should be in one function called move() and this should be applied to all moveGenerator functions
//Check the ZF flag to see if there is a bit set in the forward and reverse scans
void genWBishopSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays){
    genDirStates(dst, b, n, rays, northEast, whiteBishop);
    genDirStates(dst, b, n, rays, southEast, whiteBishop);
    genDirStates(dst, b, n, rays, southWest, whiteBishop);
    genDirStates(dst, b, n, rays, northWest, whiteBishop);
}

void genWRookSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays){
    genDirStates(dst, b, n, rays, north, whiteRook);
    genDirStates(dst, b, n, rays, east, whiteRook);
    genDirStates(dst, b, n, rays, south, whiteRook);
    genDirStates(dst, b, n, rays, west, whiteRook);
}

void genWQueenSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays){
    genDirStates(dst, b, n, rays, north, whiteQueen);
    genDirStates(dst, b, n, rays, northEast, whiteQueen);
    genDirStates(dst, b, n, rays, east, whiteQueen);
    genDirStates(dst, b, n, rays, southEast, whiteQueen);
    genDirStates(dst, b, n, rays, south, whiteQueen);
    genDirStates(dst, b, n, rays, southWest, whiteQueen);
    genDirStates(dst, b, n, rays, west, whiteQueen);
    genDirStates(dst, b, n, rays, northWest, whiteQueen);
}

//rather create the **rays here instead of passing it into functions
void genSuccStates(T_boardStates *dst, const T_boardState *b){
        T_bitboard** rays = createRays();
        if(!b->whosTurn){
            genPiecesSuccStates(dst, b, rays, whitePawn);
            genPiecesSuccStates(dst, b, rays, whiteBishop);
            //genPiecesSuccStates(dst, b, rays, whiteKnight);
            genPiecesSuccStates(dst, b, rays, whiteRook);
            genPiecesSuccStates(dst, b, rays, whiteQueen);
            //genPiecesSuccStates(dst, b, rays, whiteKing);
        }
        else{
                ;
            //genPiecesSuccStates(dst, b, rays, blackPawn);
            //genPiecesSuccStates(dst, b, rays, blackBishop);
            //genPiecesSuccStates(dst, b, rays, blackKnight);
            //genPiecesSuccStates(dst, b, rays, blackRook);
            //genPiecesSuccStates(dst, b, rays, blackQueen);
            //genPiecesSuccStates(dst, b, rays, blackKing);
        }
}

void genPiecesSuccStates(T_boardStates *dst, const T_boardState *b, const T_bitboard **rays, int piece){
    T_bitboard i = *(stateMember(b, piece));
    int n;
    int maxIt = __builtin_popcountll(i);
    void (*genPtr)(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays);

        for(int j = 0; j < maxIt; j++){
            n = __builtin_ctzll(i);
            genPtr = returnGenerator(piece);
            (*genPtr)(dst, b, n, rays);
            clearBit(&i, n);
        }
}

void (*returnGenerator(int piece))(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays){
    switch(piece){
        case whitePawn:
            return &genWPawnSuccStates;
        case whiteBishop:
            return &genWBishopSuccStates;
        case whiteKnight:
            return &genWKnightSuccStates;
        case whiteRook:
            return &genWRookSuccStates;
        case whiteQueen:
            return &genWQueenSuccStates;
        case whiteKing:
            return &genWKingSuccStates;
//        case blackPawn:
//            return &genWBishopSuccStates;
//        case blackBishop:
//            return &genWBishopSuccStates;
//        case blackKnight:
//            return &genWBishopSuccStates;
//        case blackRook:
//            return &genWBishopSuccStates;
//        case blackQueen:
//            return &genWBishopSuccStates;
//        case blackKing:
//            return &genWBishopSuccStates;
        default:
            assert(false);
    }
}

void genWKnightSuccStates(T_boardState c, T_boardStates *ss){
    //Generate Pawn Moves
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
