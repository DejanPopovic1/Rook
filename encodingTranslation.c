#include "GlobalDeclarations.h"
#include "state.h"
#include "encodingTranslation.h"
#include <assert.h>
#include <stdlib.h>
#include "bitUtilities.h"

int whatIsPiece(T_boardState b, int i){
    int result = empty;
    int resultCount = 0;
    if(isBitSet(b.wPawn, i)){
        result = whitePawn;
        resultCount++;
    }
    if(isBitSet(b.wBishop, i)){
        result = whiteBishop;
        resultCount++;
    }
    if(isBitSet(b.wKnight, i)){
        result = whiteKnight;
        resultCount++;
    }
    if(isBitSet(b.wRook, i)){
        result = whiteRook;
        resultCount++;
    }
    if(isBitSet(b.wQueen, i)){
        result = whiteQueen;
        resultCount++;
    }
    if(isBitSet(b.wKing, i)){
        result = whiteKing;
        resultCount++;
    }
    if(isBitSet(b.bPawn, i)){
        result = blackPawn;
        resultCount++;
    }
    if(isBitSet(b.bBishop, i)){
        result = blackBishop;
        resultCount++;
    }
    if(isBitSet(b.bKnight, i)){
        result = blackKnight;
        resultCount++;
    }
    if(isBitSet(b.bRook, i)){
        result = blackRook;
        resultCount++;
    }
    if(isBitSet(b.bQueen, i)){
        result = blackQueen;
        resultCount++;
    }
    if(isBitSet(b.bKing, i)){
        result = blackKing;
        resultCount++;
    }
    assert(resultCount < 2);
    return result;
}

T_chessboard *toIntArray(T_boardState b){
    T_chessboard *result = malloc(sizeof(T_chessboard));
    for(int i = 0; i < BITBOARD_SIZE; i++){
        int piece = whatIsPiece(b, i);
        (*result)[i/FILE_SIZE][i % RANK_SIZE] = piece;
    }
    return result;
}
