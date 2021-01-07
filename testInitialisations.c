#include "GlobalDeclarations.h"

//Add in tests for en passants
void initialiseWPawnTestBoard(int chessboard [RANK_SIZE][FILE_SIZE]) {
    clearBoard(chessboard);
    chessboard[1][1] = whitePawn;
    chessboard[1][2] = whitePawn;
    chessboard[1][3] = whitePawn;
    chessboard[1][4] = whitePawn;
    chessboard[1][5] = whitePawn;
    chessboard[2][2] = whiteRook;
    chessboard[3][3] = whiteRook;
    chessboard[2][4] = blackPawn;
    chessboard[3][5] = blackPawn;
    chessboard[6][1] = whitePawn;
    return;
}

void initialiseWBishopTestBoard(int chessboard [RANK_SIZE][FILE_SIZE]) {
    clearBoard(chessboard);
    chessboard[3][3] = whiteBishop;
    chessboard[1][1] = whitePawn;
    chessboard[5][5] = whitePawn;
    chessboard[5][1] = whitePawn;
    chessboard[1][5] = whitePawn;
    chessboard[4][3] = whiteBishop;
    chessboard[2][1] = blackPawn;
    chessboard[6][5] = blackPawn;
    chessboard[6][1] = blackPawn;
    chessboard[2][5] = blackPawn;
    chessboard[3][5] = whiteBishop;
    return;
}

void initialiseWKnightTestBoard(int chessboard [RANK_SIZE][FILE_SIZE]) {
    clearBoard(chessboard);
    chessboard[3][3] = whiteKnight;
    chessboard[1][1] = whitePawn;
    chessboard[5][5] = whitePawn;
    chessboard[5][1] = whitePawn;
    chessboard[1][5] = whitePawn;
    chessboard[4][3] = whiteKnight;
    chessboard[2][1] = blackPawn;
    chessboard[6][5] = blackPawn;
    chessboard[6][1] = blackPawn;
    chessboard[2][5] = blackPawn;
    chessboard[3][5] = whiteKnight;
    chessboard[6][6] = whiteKnight;
    chessboard[1][1] = whiteKnight;
    return;
}

void initialiseWRookTestBoard(int chessboard [RANK_SIZE][FILE_SIZE]) {
    clearBoard(chessboard);
    chessboard[3][3] = whiteRook;
    chessboard[3][5] = whitePawn;
    chessboard[3][1] = whitePawn;
    chessboard[5][3] = whitePawn;
    chessboard[1][3] = whitePawn;
    chessboard[4][4] = whiteRook;
    chessboard[4][6] = blackPawn;
    chessboard[4][2] = blackPawn;
    chessboard[6][4] = blackPawn;
    chessboard[2][4] = blackPawn;
    chessboard[6][6] = whiteRook;
    chessboard[1][1] = whiteRook;
    return;
}

void initialiseWQueenTestBoard(int chessboard [RANK_SIZE][FILE_SIZE]) {
    clearBoard(chessboard);
    chessboard[3][3] = whiteQueen;
    chessboard[3][5] = whitePawn;
    chessboard[3][1] = whitePawn;
    chessboard[5][3] = whitePawn;
    chessboard[1][3] = whitePawn;
    chessboard[4][4] = whiteQueen;
    chessboard[4][6] = blackPawn;
    chessboard[4][2] = blackPawn;
    chessboard[6][4] = blackPawn;
    chessboard[2][4] = blackPawn;
    chessboard[6][6] = whiteQueen;
    chessboard[1][1] = whiteQueen;
    chessboard[6][6] = whiteQueen;
    return;
}

void initialiseWKingTestBoard(int chessboard [RANK_SIZE][FILE_SIZE]) {
    clearBoard(chessboard);
    chessboard[3][3] = whiteKing;
    chessboard[3][4] = whitePawn;
    chessboard[3][2] = whitePawn;
    chessboard[4][3] = whitePawn;
    chessboard[2][3] = whitePawn;
    chessboard[5][5] = whiteKing;
    chessboard[4][5] = blackPawn;
    chessboard[6][5] = blackPawn;
    chessboard[5][4] = blackPawn;
    chessboard[5][6] = blackPawn;
    chessboard[0][0] = whiteKing;
    chessboard[7][7] = whiteKing;
    chessboard[6][1] = whiteKing;
    return;
}
//===============================================================

void initialiseBPawnTestBoard(int chessboard [RANK_SIZE][FILE_SIZE]) {
    clearBoard(chessboard);
    chessboard[1][1] = blackPawn;
    chessboard[1][2] = blackPawn;
    chessboard[1][3] = blackPawn;
    chessboard[1][4] = blackPawn;
    chessboard[1][5] = blackPawn;
    chessboard[2][2] = blackRook;
    chessboard[3][3] = blackRook;
    chessboard[2][4] = whitePawn;
    chessboard[3][5] = whitePawn;
    chessboard[6][1] = blackPawn;
    chessboard[6][2] = blackPawn;
    chessboard[6][3] = blackPawn;
    chessboard[6][4] = blackPawn;
    chessboard[5][2] = whitePawn;
    chessboard[4][3] = whitePawn;
    return;
}

void initialiseBBishopTestBoard(int chessboard [RANK_SIZE][FILE_SIZE]) {
    clearBoard(chessboard);
    chessboard[3][3] = blackBishop;
    chessboard[1][1] = blackPawn;
    chessboard[5][5] = blackPawn;
    chessboard[5][1] = blackPawn;
    chessboard[1][5] = blackPawn;
    chessboard[4][3] = blackBishop;
    chessboard[2][1] = whitePawn;//
    chessboard[6][5] = whitePawn;//
    chessboard[6][1] = whitePawn;//
    chessboard[2][5] = whitePawn;//
    chessboard[3][5] = blackBishop;
    return;
}

void initialiseBKnightTestBoard(int chessboard [RANK_SIZE][FILE_SIZE]) {
    clearBoard(chessboard);
    chessboard[3][3] = blackKnight;
    chessboard[1][1] = blackPawn;
    chessboard[5][5] = blackPawn;
    chessboard[5][1] = blackPawn;
    chessboard[1][5] = blackPawn;
    chessboard[4][3] = blackKnight;
    chessboard[2][1] = whitePawn;//
    chessboard[6][5] = whitePawn;//
    chessboard[6][1] = whitePawn;//
    chessboard[2][5] = whitePawn;//
    chessboard[3][5] = blackKnight;
    chessboard[6][6] = blackKnight;
    chessboard[1][1] = blackKnight;
    return;
}

void initialiseBRookTestBoard(int chessboard [RANK_SIZE][FILE_SIZE]) {
    clearBoard(chessboard);
    chessboard[3][3] = blackRook;
    chessboard[3][5] = blackPawn;
    chessboard[3][1] = blackPawn;
    chessboard[5][3] = blackPawn;
    chessboard[1][3] = blackPawn;
    chessboard[4][4] = blackRook;
    chessboard[4][6] = whitePawn;//
    chessboard[4][2] = whitePawn;//
    chessboard[6][4] = whitePawn;//
    chessboard[2][4] = whitePawn;//
    chessboard[6][6] = blackRook;
    chessboard[1][1] = blackRook;
    return;
}

void initialiseBQueenTestBoard(int chessboard [RANK_SIZE][FILE_SIZE]) {
    clearBoard(chessboard);
    chessboard[3][3] = blackQueen;
    chessboard[3][5] = blackPawn;
    chessboard[3][1] = blackPawn;
    chessboard[5][3] = blackPawn;
    chessboard[1][3] = blackPawn;
    chessboard[4][4] = blackQueen;
    chessboard[4][6] = whitePawn;//
    chessboard[4][2] = whitePawn;//
    chessboard[6][4] = whitePawn;//
    chessboard[2][4] = whitePawn;//
    chessboard[6][6] = blackQueen;
    chessboard[1][1] = blackQueen;
    chessboard[6][6] = blackQueen;
    return;
}

void initialiseBKingTestBoard(int chessboard [RANK_SIZE][FILE_SIZE]) {
    clearBoard(chessboard);
    chessboard[3][3] = blackKing;
    chessboard[3][4] = blackPawn;
    chessboard[3][2] = blackPawn;
    chessboard[4][3] = blackPawn;
    chessboard[2][3] = blackPawn;
    chessboard[5][5] = blackKing;
    chessboard[4][5] = whitePawn;//
    chessboard[6][5] = whitePawn;//
    chessboard[5][4] = whitePawn;//
    chessboard[5][6] = whitePawn;//
    chessboard[0][0] = blackKing;
    chessboard[7][7] = blackKing;
    chessboard[6][1] = blackKing;
    return;
}


//===============================================================

void initialiseRandomTest1(int chessboard [RANK_SIZE][FILE_SIZE]) {
    clearBoard(chessboard);
    chessboard[1][1] = whiteKnight;
    chessboard[2][3] = whitePawn;
    chessboard[5][5] = whitePawn;
    chessboard[5][1] = whiteBishop;
    chessboard[1][5] = whiteKnight;
    chessboard[4][3] = whiteKnight;
    chessboard[2][1] = blackBishop;
    chessboard[6][5] = blackPawn;
    chessboard[6][1] = blackPawn;
    chessboard[2][5] = blackPawn;
    chessboard[3][5] = whiteKnight;
    chessboard[6][6] = whiteKnight;
    chessboard[1][1] = whiteKnight;
    chessboard[0][6] = whiteKnight;
    chessboard[4][6] = whiteKnight;
    chessboard[5][3] = whiteBishop;
    chessboard[1][0] = blackPawn;
    return;
}

void initialiseDisambiguator(int chessboard [RANK_SIZE][FILE_SIZE]) {
    clearBoard(chessboard);
    chessboard[3][3] = whiteKnight;
    chessboard[5][7] = whiteKnight;
    return;
}

void clearBoard(int chessboard[RANK_SIZE][FILE_SIZE]){
    for(int i = 0; i < RANK_SIZE; i++){
        for(int j = 0; j < FILE_SIZE; j++){
            chessboard[i][j] = empty;
        }
    }
}
