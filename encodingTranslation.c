#include "GlobalDeclarations.h"
#include "state.h"
#include "encodingTranslation.h"

int piece = whatIsPiece(T_boardState b, i){

}

T_chessboard **toIntArray(T_boardState b){
    T_chessboard result;
    for(int i = 0; i < BITBOARD_SIZE; i++){
        int piece = whatIsPiece(b, i);
        result[i/FILE_SIZE][i % RANK_SIZE] = piece;
    }
    return result;
}
