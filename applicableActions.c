#include <stdio.h>
#include <stdbool.h>
#include "applicableActions.h"
#include "GlobalDeclarations.h"
#include "memoryUtilities.h"
#include "output.h"
#include <stdlib.h>
#include <assert.h>

//MOVEMENTS "UP", "DOWN", "LEFT" AND "RIGHT" ARE RELATIVE TO AN APPLICABLE COLOUR

//bool isWhitePiece(int pieceValue){
//    if(pieceValue > 0 && pieceValue < 7){
//        return true;
//    }
//    return false;
//}
//
//bool isBlackPiece(int pieceValue){
//    if(pieceValue > 6 && pieceValue < 13){
//        return true;
//    }
//    return false;
//}

bool isWhite(T_chessboard chessboard, int rank, int file){
    return isWhitePiece(chessboard[rank][file]);
}

bool isBlack(T_chessboard chessboard, int rank, int file){
    return isBlackPiece(chessboard[rank][file]);
}

//Change this to pass the copied state
void copyState(T_chessboard *destination, T_chessboard source){
    for(int i = 0; i < RANK_SIZE; i++){
        for(int j = 0; j < FILE_SIZE; j++){
            (*destination)[i][j] = source[i][j];
        }
    }
}

bool isPiece(T_chessboard chessboard, int rank, int file, int piece){
    return (chessboard[rank][file] == piece);
}

int whatPiece(T_chessboard c, T_position p){
    return c[p.r][p.f];
}

void generateWhitePawnSuccessorStates(T_chessboard currentState, T_position p, T_states *consolidatedStates){
    int rank = p.r;
    int file = p.f;
    if(!isPiece(currentState, rank, file, whitePawn)){
        assert(false);
    }
    //MOVE UP ONE
    if(currentState[rank + 1][file] == empty && rank != 6){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file] = whitePawn;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE UP TWO
    if(rank == 1 && currentState[rank + 1][file] == empty && currentState[rank + 2][file] == empty){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 2][file] = whitePawn;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //CAPTURE LEFT
    if(isBlack(currentState, rank + 1, file - 1) && file > 0){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file - 1] = whitePawn;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //CAPTURE RIGHT
    if(isBlack(currentState, rank + 1, file + 1) && file < FILE_SIZE - 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file + 1] = whitePawn;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //EN PASSANT LEFT
    if(isBlack(currentState, rank, file - 1) && rank == 4 && isNeighbouringPawnDoubleMoved(rank, file - 1)){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file - 1] = whitePawn;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file - 1] = empty;
        consolidatedStates->freeIndex++;
    }
    //EN PASSANT RIGHT
    if(isBlack(currentState, rank, file + 1) && rank == 4 && isNeighbouringPawnDoubleMoved(rank, file + 1)){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file + 1] = whitePawn;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file + 1] = empty;
        consolidatedStates->freeIndex++;
    }
    //PROMOTIONS
    if(rank == 6){
        //BISHOP
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file] = whiteBishop;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
        //KNIGHT
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file] = whiteKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
        //ROOK
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file] = whiteRook;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
        //QUEEN
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file] = whiteQueen;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
}

//FOR THIS AND WHITE PAWN INSERT MACRO CALLED PAWN STARTING RANK
void generateBlackPawnSuccessorStates(T_chessboard currentState, T_position p, T_states *consolidatedStates){
    int rank = p.r;
    int file = p.f;
    if(!isPiece(currentState, rank, file, blackPawn)){
        assert(false);
    }
    //MOVE FORWARD ONE
    if(currentState[rank - 1][file] == empty && rank != 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file] = blackPawn;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE FORWARD TWO
    if(rank == 6 && currentState[rank - 1][file] == empty && currentState[rank - 2][file] == empty){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 2][file] = blackPawn;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //CAPTURE LEFTHAND
    if(isWhite(currentState, rank - 1, file + 1) && file < FILE_SIZE){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file + 1] = blackPawn;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //CAPTURE RIGHTHAND
    if(isWhite(currentState, rank - 1, file - 1) && file > 0){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file - 1] = blackPawn;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //EN PASSANT LEFTHAND
    if(isWhite(currentState, rank, file + 1) && rank == 3 && isNeighbouringPawnDoubleMoved(rank, file + 1)){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file + 1] = blackPawn;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file + 1] = empty;
        consolidatedStates->freeIndex++;
    }
    //EN PASSANT RIGHTHAND
    if(isWhite(currentState, rank, file - 1) && rank == 3 && isNeighbouringPawnDoubleMoved(rank, file - 1)){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file - 1] = blackPawn;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file - 1] = empty;
        consolidatedStates->freeIndex++;
    }
    //PROMOTIONS
    if(rank == 1){
        //BISHOP
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file] = blackBishop;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
        //KNIGHT
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file] = blackKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
        //ROOK
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file] = blackRook;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
        //QUEEN
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file] = blackQueen;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
}

//Change rank and file to position
void generateWhiteBishopSuccessorStates(T_chessboard currentState, T_position p, T_states *consolidatedStates){
    int rank = p.r;
    int file = p.f;
    if(!isPiece(currentState, rank, file, whiteBishop)){
        assert(false);
    }
    T_chessboard i;
    int r, f;
    //MOVE UP-RIGHT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(i, r + 1, f + 1) &&  r < RANK_SIZE - 1 && f < FILE_SIZE - 1){
        bool isAdjacentBlack = isBlack(i, r + 1, f + 1);
        i[r + 1][f + 1] = whiteBishop;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r++;
        f++;
        if(isAdjacentBlack){
            break;
        }
    }
    //MOVE DOWN-RIGHT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(i, r - 1, f + 1) &&  r > 0 && f < FILE_SIZE - 1){
        bool isAdjacentBlack = isBlack(i, r - 1, f + 1);
        i[r - 1][f + 1] = whiteBishop;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r--;
        f++;
        if(isAdjacentBlack){
            break;
        }
    }
    //MOVE DOWN-LEFT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(i, r - 1, f - 1) &&  r > 0 && f > 0){
        bool isAdjacentBlack = isBlack(i, r - 1, f - 1);
        i[r - 1][f - 1] = whiteBishop;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r--;
        f--;
        if(isAdjacentBlack){
            break;
        }
    }
    //MOVE UP-LEFT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(i, r + 1, f - 1) &&  r < RANK_SIZE - 1 && f > 0){
        bool isAdjacentBlack = isBlack(i, r + 1, f - 1);
        i[r + 1][f - 1] = whiteBishop;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r++;
        f--;
        if(isAdjacentBlack){
            break;
        }
    }
}

void generateBlackBishopSuccessorStates(T_chessboard currentState, T_position p, T_states *consolidatedStates){
    int rank = p.r;
    int file = p.f;
    if(!isPiece(currentState, rank, file, blackBishop)){
        assert(false);
    }
    T_chessboard i;
    int r, f;
    //MOVE UP-RIGHT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(i, r + 1, f + 1) &&  r < RANK_SIZE - 1 && f < FILE_SIZE - 1){
        bool isAdjacentWhite = isWhite(i, r + 1, f + 1);
        i[r + 1][f + 1] = blackBishop;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r++;
        f++;
        if(isAdjacentWhite){
            break;
        }
    }
    //MOVE DOWN-RIGHT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(i, r - 1, f + 1) &&  r > 0 && f < FILE_SIZE - 1){
        bool isAdjacentWhite = isWhite(i, r - 1, f + 1);
        i[r - 1][f + 1] = blackBishop;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r--;
        f++;
        if(isAdjacentWhite){
            break;
        }
    }
    //MOVE DOWN-LEFT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(i, r - 1, f - 1) &&  r > 0 && f > 0){
        bool isAdjacentWhite = isWhite(i, r - 1, f - 1);
        i[r - 1][f - 1] = blackBishop;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r--;
        f--;
        if(isAdjacentWhite){
            break;
        }
    }
    //MOVE UP-LEFT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(i, r + 1, f - 1) &&  r < RANK_SIZE - 1 && f > 0){
        bool isAdjacentWhite = isWhite(i, r + 1, f - 1);
        i[r + 1][f - 1] = blackBishop;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r++;
        f--;
        if(isAdjacentWhite){
            break;
        }
    }
}

void generateWhiteKnightSuccessorStates(T_chessboard currentState, T_position p, T_states *consolidatedStates){
    int rank = p.r;
    int file = p.f;
    if(!isPiece(currentState, rank, file, whiteKnight)){
        assert(false);
    }
    //MOVE UP-UP-RIGHT
    if(!isWhite(currentState, rank + 2, file + 1) && rank < RANK_SIZE - 2 && file < FILE_SIZE - 1){
        //printf("Printing Test: \n");
        //printBoard(asWhite, consolidatedStates->states);
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 2][file + 1] = whiteKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE UP-RIGHT-RIGHT
    if(!isWhite(currentState, rank + 1, file + 2) && rank < RANK_SIZE - 1 && file < FILE_SIZE - 2){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file + 2] = whiteKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE DOWN-DOWN-RIGHT
    if(!isWhite(currentState, rank - 2, file + 1) && rank > 1 && file < FILE_SIZE - 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 2][file + 1] = whiteKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE DOWN-RIGHT-RIGHT
    if(!isWhite(currentState, rank - 1, file + 2) && rank > 0 && file < FILE_SIZE - 2){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file + 2] = whiteKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE DOWN-DOWN-LEFT
    if(!isWhite(currentState, rank - 2, file - 1) && rank > 1 && file > 0){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 2][file - 1] = whiteKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE DOWN-LEFT-LEFT
    if(!isWhite(currentState, rank - 1, file - 2) && rank > 0 && file > 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file - 2] = whiteKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE UP-LEFT-LEFT
    if(!isWhite(currentState, rank + 1, file - 2) && rank < RANK_SIZE - 1 && file > 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file - 2] = whiteKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE UP-UP-LEFT
    if(!isWhite(currentState, rank + 2, file - 1) && rank < RANK_SIZE - 2 && file > 0){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 2][file - 1] = whiteKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
}

void generateBlackKnightSuccessorStates(T_chessboard currentState, T_position p, T_states *consolidatedStates){
    int rank = p.r;
    int file = p.f;
    if(!isPiece(currentState, rank, file, blackKnight)){
        assert(false);
    }
    //MOVE UP-UP-RIGHT
    if(!isBlack(currentState, rank + 2, file + 1) && rank < RANK_SIZE - 2 && file < FILE_SIZE - 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 2][file + 1] = blackKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE UP-RIGHT-RIGHT
    if(!isBlack(currentState, rank + 1, file + 2) && rank < RANK_SIZE - 1 && file < FILE_SIZE - 2){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file + 2] = blackKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE DOWN-DOWN-RIGHT
    if(!isBlack(currentState, rank - 2, file + 1) && rank > 1 && file < FILE_SIZE - 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 2][file + 1] = blackKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE DOWN-RIGHT-RIGHT
    if(!isBlack(currentState, rank - 1, file + 2) && rank > 0 && file < FILE_SIZE - 2){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file + 2] = blackKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE DOWN-DOWN-LEFT
    if(!isBlack(currentState, rank - 2, file - 1) && rank > 1 && file > 0){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 2][file - 1] = blackKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE DOWN-LEFT-LEFT
    if(!isBlack(currentState, rank - 1, file - 2) && rank > 0 && file > 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file - 2] = blackKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE UP-LEFT-LEFT
    if(!isBlack(currentState, rank + 1, file - 2) && rank < RANK_SIZE - 1 && file > 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file - 2] = blackKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE UP-UP-LEFT
    if(!isBlack(currentState, rank + 2, file - 1) && rank < RANK_SIZE - 2 && file > 0){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 2][file - 1] = blackKnight;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
}

void generateWhiteRookSuccessorStates(T_chessboard currentState, T_position p, T_states *consolidatedStates){
    int rank = p.r;
    int file = p.f;
    if(!isPiece(currentState, rank, file, whiteRook)){
        assert(false);
    }
    T_chessboard i;
    int r, f;
    //MOVE UP
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(i, r + 1, f) &&  r < RANK_SIZE - 1){
        bool isAdjacentBlack = isBlack(i, r + 1, f);
        i[r + 1][f] = whiteRook;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r++;
        if(isAdjacentBlack){
            break;
        }
    }
    //MOVE RIGHT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(i, r, f + 1) &&  f < FILE_SIZE - 1){
        bool isAdjacentBlack = isBlack(i, r, f + 1);
        i[r][f + 1] = whiteRook;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        f++;
        if(isAdjacentBlack){
            break;
        }
    }
    //MOVE DOWN
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(i, r - 1, f) &&  r > 0){
        bool isAdjacentBlack = isBlack(i, r - 1, f);
        i[r - 1][f] = whiteRook;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r--;
        if(isAdjacentBlack){
            break;
        }
    }
    //MOVE LEFT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(i, r, f - 1) &&  f > 0){
        bool isAdjacentBlack = isBlack(i, r, f - 1);
        i[r][f - 1] = whiteRook;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        f--;
        if(isAdjacentBlack){
            break;
        }
    }
}

void generateBlackRookSuccessorStates(T_chessboard currentState, T_position p, T_states *consolidatedStates){
    int rank = p.r;
    int file = p.f;
    if(!isPiece(currentState, rank, file, blackRook)){
        assert(false);
    }
    T_chessboard i;
    int r, f;
    //MOVE UP
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(i, r + 1, f) &&  r < RANK_SIZE - 1){
        bool isAdjacentWhite = isWhite(i, r + 1, f);
        i[r + 1][f] = blackRook;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r++;
        if(isAdjacentWhite){
            break;
        }
    }
    //MOVE RIGHT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(i, r, f + 1) &&  f < FILE_SIZE - 1){
        bool isAdjacentWhite = isWhite(i, r, f + 1);
        i[r][f + 1] = blackRook;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        f++;
        if(isAdjacentWhite){
            break;
        }
    }
    //MOVE DOWN
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(i, r - 1, f) &&  r > 0){
        bool isAdjacentWhite = isWhite(i, r - 1, f);
        i[r - 1][f] = blackRook;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r--;
        if(isAdjacentWhite){
            break;
        }
    }
    //MOVE LEFT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(i, r, f - 1) &&  f > 0){
        bool isAdjacentWhite = isWhite(i, r, f - 1);
        i[r][f - 1] = blackRook;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        f--;
        if(isAdjacentWhite){
            break;
        }
    }
}

void generateWhiteQueenSuccessorStates(T_chessboard currentState, T_position p, T_states *consolidatedStates){
    int rank = p.r;
    int file = p.f;
    if(!isPiece(currentState, rank, file, whiteQueen)){
        assert(false);
    }
    T_chessboard i;
    int r, f;
    //MOVE UP
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(i, r + 1, f) &&  r < RANK_SIZE - 1){
        bool isAdjacentBlack = isBlack(i, r + 1, f);
        i[r + 1][f] = whiteQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r++;
        if(isAdjacentBlack){
            break;
        }
    }
    //MOVE UP RIGHT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(currentState, r + 1, f + 1) &&  r < RANK_SIZE - 1 && f < FILE_SIZE - 1){
        bool isAdjacentBlack = isBlack(i, r + 1, f + 1);
        i[r + 1][f + 1] = whiteQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r++;
        f++;
        if(isAdjacentBlack){
            break;
        }
    }
    //MOVE RIGHT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(currentState, r, f + 1) &&  f < FILE_SIZE - 1){
        bool isAdjacentBlack = isBlack(i, r, f + 1);
        i[r][f + 1] = whiteQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        f++;
        if(isAdjacentBlack){
            break;
        }
    }
    //MOVE DOWN RIGHT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(currentState, r - 1, f + 1) && r > 0 && f < FILE_SIZE - 1){
        bool isAdjacentBlack = isBlack(i, r - 1, f + 1);
        i[r - 1][f + 1] = whiteQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r--;
        f++;
        if(isAdjacentBlack){
            break;
        }
    }
    //MOVE DOWN
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(currentState, r - 1, f) && r > 0){
        bool isAdjacentBlack = isBlack(i, r - 1, f);
        i[r - 1][f] = whiteQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r--;
        if(isAdjacentBlack){
            break;
        }
    }
    //MOVE DOWN LEFT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(currentState, r - 1, f - 1) && r > 0 && f > 0){
        bool isAdjacentBlack = isBlack(i, r - 1, f - 1);
        i[r - 1][f - 1] = whiteQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r--;
        f--;
        if(isAdjacentBlack){
            break;
        }
    }
    //MOVE LEFT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(currentState, r, f - 1) &&  f > 0){
        bool isAdjacentBlack = isBlack(i, r, f - 1);
        i[r][f - 1] = whiteQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        f--;
        if(isAdjacentBlack){
            break;
        }
    }
    //MOVE UP LEFT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isWhite(currentState, r + 1, f - 1) && r < RANK_SIZE - 1 &&  f > 0){
        bool isAdjacentBlack = isBlack(i, r + 1, f - 1);
        i[r + 1][f - 1] = whiteQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r++;
        f--;
        if(isAdjacentBlack){
            break;
        }
    }
    return;
}

void generateBlackQueenSuccessorStates(T_chessboard currentState, T_position p, T_states *consolidatedStates){
    int rank = p.r;
    int file = p.f;
    if(!isPiece(currentState, rank, file, blackQueen)){
        assert(false);
    }
    T_chessboard i;
    int r, f;
    //MOVE UP
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(i, r + 1, f) &&  r < RANK_SIZE - 1){
        bool isAdjacentWhite = isWhite(i, r + 1, f);
        i[r + 1][f] = blackQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r++;
        if(isAdjacentWhite){
            break;
        }
    }
    //MOVE UP RIGHT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(currentState, r + 1, f + 1) &&  r < RANK_SIZE - 1 && f < FILE_SIZE - 1){
        bool isAdjacentWhite = isWhite(i, r + 1, f + 1);
        i[r + 1][f + 1] = blackQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r++;
        f++;
        if(isAdjacentWhite){
            break;
        }
    }
    //MOVE RIGHT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(currentState, r, f + 1) &&  f < FILE_SIZE - 1){
        bool isAdjacentWhite = isWhite(i, r, f + 1);
        i[r][f + 1] = blackQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        f++;
        if(isAdjacentWhite){
            break;
        }
    }
    //MOVE DOWN RIGHT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(currentState, r - 1, f + 1) && r > 0 && f < FILE_SIZE - 1){
        bool isAdjacentWhite = isWhite(i, r - 1, f + 1);
        i[r - 1][f + 1] = blackQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r--;
        f++;
        if(isAdjacentWhite){
            break;
        }
    }
    //MOVE DOWN
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(currentState, r - 1, f) && r > 0){
        bool isAdjacentWhite = isWhite(i, r - 1, f);
        i[r - 1][f] = blackQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r--;
        if(isAdjacentWhite){
            break;
        }
    }
    //MOVE DOWN LEFT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(currentState, r - 1, f - 1) && r > 0 && f > 0){
        bool isAdjacentWhite = isWhite(i, r - 1, f - 1);
        i[r - 1][f - 1] = blackQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r--;
        f--;
        if(isAdjacentWhite){
            break;
        }
    }
    //MOVE LEFT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(currentState, r, f - 1) &&  f > 0){
        bool isAdjacentWhite = isWhite(i, r, f - 1);
        i[r][f - 1] = blackQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        f--;
        if(isAdjacentWhite){
            break;
        }
    }
    //MOVE UP LEFT
    copyState(&i, currentState);
    r = rank;
    f = file;
    while(!isBlack(currentState, r + 1, f - 1) && r < RANK_SIZE - 1 &&  f > 0){
        bool isAdjacentWhite = isWhite(i, r + 1, f - 1);
        i[r + 1][f - 1] = blackQueen;
        i[r][f] = empty;
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), i);
        consolidatedStates->freeIndex++;
        r++;
        f--;
        if(isAdjacentWhite){
            break;
        }
    }
    return;
}

void generateWhiteKingSuccessorStates(T_chessboard currentState, T_position p, T_states *consolidatedStates){
    int rank = p.r;
    int file = p.f;
    if(!isPiece(currentState, rank, file, whiteKing)){
        assert(false);
    }
    //MOVE UP
    if(!isWhite(currentState, rank + 1, file) && rank < RANK_SIZE - 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file] = whiteKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE UP RIGHT
    if(!isWhite(currentState, rank + 1, file + 1) && rank < RANK_SIZE - 1 && file < FILE_SIZE - 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file + 1] = whiteKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE RIGHT
    if(!isWhite(currentState, rank, file + 1) && file < FILE_SIZE - 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file + 1] = whiteKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE DOWN RIGHT
    if(!isWhite(currentState, rank - 1, file + 1) && rank > 0 && file < FILE_SIZE - 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file + 1] = whiteKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE DOWN
    if(!isWhite(currentState, rank - 1, file) && rank > 0){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file] = whiteKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE DOWN LEFT
    if(!isWhite(currentState, rank - 1, file - 1) && rank > 0 && file > 0){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file - 1] = whiteKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE LEFT
    if(!isWhite(currentState, rank, file - 1) && file > 0){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file - 1] = whiteKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE UP LEFT
    if(!isWhite(currentState, rank + 1, file - 1) && file > 0 && rank < RANK_SIZE - 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file - 1] = whiteKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
}

//ADD CASTLING AS AN OPTION
void generateBlackKingSuccessorStates(T_chessboard currentState, T_position p, T_states *consolidatedStates){
    int rank = p.r;
    int file = p.f;
    if(!isPiece(currentState, rank, file, blackKing)){
        assert(false);
    }
    //MOVE UP
    if(!isBlack(currentState, rank + 1, file) && rank < RANK_SIZE - 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file] = blackKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE UP RIGHT
    if(!isBlack(currentState, rank + 1, file + 1) && rank < RANK_SIZE - 1 && file < FILE_SIZE - 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file + 1] = blackKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE RIGHT
    if(!isBlack(currentState, rank, file + 1) && file < FILE_SIZE - 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file + 1] = blackKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE DOWN RIGHT
    if(!isBlack(currentState, rank - 1, file + 1) && rank > 0 && file < FILE_SIZE - 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file + 1] = blackKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE DOWN
    if(!isBlack(currentState, rank - 1, file) && rank > 0){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file] = blackKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE DOWN LEFT
    if(!isBlack(currentState, rank - 1, file - 1) && rank > 0 && file > 0){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank - 1][file - 1] = blackKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE LEFT
    if(!isBlack(currentState, rank, file - 1) && file > 0){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file - 1] = blackKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
    //MOVE UP LEFT
    if(!isBlack(currentState, rank + 1, file - 1) && file > 0 && rank < RANK_SIZE - 1){
        copyState(&(consolidatedStates->states[consolidatedStates->freeIndex]), currentState);
        consolidatedStates->states[consolidatedStates->freeIndex][rank + 1][file - 1] = blackKing;
        consolidatedStates->states[consolidatedStates->freeIndex][rank][file] = empty;
        consolidatedStates->freeIndex++;
    }
}
