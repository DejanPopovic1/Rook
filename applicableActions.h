#ifndef APPLICABLEACTIONS_H
#define APPLICABLEACTIONS_H

#include "GlobalDeclarations.h"

//void copyState(int successorStates [RANK_SIZE][FILE_SIZE][MAX_SUCCESSOR_STATES], int chessBoard[RANK_SIZE][FILE_SIZE], int numOfStates);

void generateWhitePawnSuccessorStates(T_chessboard, T_position, T_states *);

void generateWhiteBishopSuccessorStates(T_chessboard, T_position, T_states *);

void generateWhiteKnightSuccessorStates(T_chessboard, T_position, T_states *);

void generateWhiteRookSuccessorStates(T_chessboard, T_position, T_states *);

void generateWhiteQueenSuccessorStates(T_chessboard, T_position, T_states *);

void generateWhiteKingSuccessorStates(T_chessboard, T_position, T_states *);

void generateBlackPawnSuccessorStates(T_chessboard, T_position, T_states *);

void generateBlackBishopSuccessorStates(T_chessboard, T_position, T_states *);

void generateBlackKnightSuccessorStates(T_chessboard, T_position, T_states *);

void generateBlackRookSuccessorStates(T_chessboard, T_position, T_states *);

void generateBlackQueenSuccessorStates(T_chessboard, T_position, T_states *);

void generateBlackKingSuccessorStates(T_chessboard, T_position, T_states *);

#endif // APPLICABLEACTIONS_H
