#ifndef OUTPUT_H
#define OUTPUT_H

#include "state.h"
#include "GlobalDeclarations.h"
#include <wchar.h>
#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>

void printTBitboardNumbersBin(T_bitboard **b);
void printTBitboardNumbersDec(T_bitboard **b);
void printPlayerTurn(int halfPly);
void printMove(char* c);
void printMoves(T_moves *a);
void landingMessage();
void printPosition(T_position);
void printPositions(T_positions);
void printBoard(int, T_chessboard);
void printBoardsAndAlgNot(T_chessboard, int, T_states*);
void printBoards(int, T_states*);
bool isWhiteTile(int, int);
void printBoardPlayingAsBlack(T_chessboard);
void printBoardPlayingAsWhite(T_chessboard);
void setColourForBlack(bool);
void setColourForWhite(bool);
void printGlyph(int, bool);
void displayHelp();

#endif // OUTPUT_H
