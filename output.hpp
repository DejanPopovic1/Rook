#ifndef OUTPUT_H
#define OUTPUT_H

#include "state.hpp"

#include <wchar.h>
#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>

#define RANK_SIZE 8
#define FILE_SIZE 8

typedef int T_chessboard[RANK_SIZE][FILE_SIZE];

int whosTurn(const int halfPly);

int whatIsPiece(T_boardState b, int i);
T_chessboard *toIntArray(T_boardState b);

void printTBitboardNumber(T_bitboard b);
void printTBitboard(T_bitboard b);
void printState(T_boardState b);
void printStates(T_boardStates *b);
void printStateAndValidMoves(T_boardState c, T_boardState s);
void printBits(size_t const size, void const * const ptr);
void printTBitboardNumbersBin(T_bitboard **b);
void printTBitboardNumbersDec(T_bitboard **b);
void printPlayerTurn(int halfPly);
void printMove(char* c);

void landingMessage();
//void printPosition(T_position);
//void printPositions(T_positions);
void printBoard(int, T_chessboard);
//void printBoardsAndAlgNot(T_chessboard, int, T_states*);
//void printBoards(int, T_states*);
bool isWhiteTile(int, int);
void printBoardPlayingAsBlack(T_chessboard);
void printBoardPlayingAsWhite(T_chessboard);
void setColourForBlack(bool);
void setColourForWhite(bool);
void printGlyph(int, bool);
void displayHelp();

#endif // OUTPUT_H
