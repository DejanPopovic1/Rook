#include "GlobalDeclarations.h"
#include "state.h"
#include "encodingTranslation.h"
#include <assert.h>

int whatIsPiece(T_boardState b, int i){
    int result = 1;
    if(isBitSet(b.wPawn, i)){
        return whitePawn;
    }
    if(isBitSet(b.wBishop, i)){
        return whiteBishop;
    }
    if(isBitSet(b.wKnight, i)){
        return whiteKnight;
    }
    if(isBitSet(b.wRook, i)){
        return whiteRook;
    }
    if(isBitSet(b.wQueen, i)){
        return whiteQueen;
    }
    if(isBitSet(b.wKing, i)){
        return whiteKing;
    }
    if(isBitSet(b.bPawn, i)){
        return blackPawn;
    }
    if(isBitSet(b.bBishop, i)){
        return blackBishop;
    }
    if(isBitSet(b.bKnight, i)){
        return blackKnight;
    }
    if(isBitSet(b.bRook, i)){
        return blackRook;
    }
    if(isBitSet(b.bQueen, i)){
        return blackQueen;
    }
    if(isBitSet(b.bKing, i)){
        return blackKing;
    }
    assert (false);
}

T_chessboard **toIntArray(T_boardState b){
    T_chessboard result;
    for(int i = 0; i < BITBOARD_SIZE; i++){
        int piece = whatIsPiece(b, i);
        result[i/FILE_SIZE][i % RANK_SIZE] = piece;
    }
    return result;
}
