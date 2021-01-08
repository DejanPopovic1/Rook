#ifndef APPLICABLEACTIONS_H
#define APPLICABLEACTIONS_H

#include "GlobalDeclarations.h"

//void copyState(int successorStates [RANK_SIZE][FILE_SIZE][MAX_SUCCESSOR_STATES], int chessBoard[RANK_SIZE][FILE_SIZE], int numOfStates);

bool isWhitePiece(int pieceValue);
bool isBlackPiece(int pieceValue);

bool isWhite(T_chessboard chessboard, int rank, int file);

bool isBlack(T_chessboard chessboard, int rank, int file);

//Change this to pass the copied state
void copyState(T_chessboard *destination, T_chessboard source);

bool isPiece(T_chessboard chessboard, int rank, int file, int piece);

int whatPiece(T_chessboard c, T_position p);

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
