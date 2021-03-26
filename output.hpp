#ifndef OUTPUT_H
#define OUTPUT_H

#include "state.hpp"

#include <wchar.h>
#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <vector>
#include <string>

#define RANK_SIZE 8
#define FILE_SIZE 8

typedef int T_chessboard[RANK_SIZE][FILE_SIZE];

void displayVersion();
void multiPlayerPrompt();
int whatIsPiece(T_boardState b, int i);
T_chessboard *toIntArray(T_boardState b);
void printTBitboardNumber(T_bitboard b);
void printTBitboard(T_bitboard b);
void printState(T_boardState b, int playerColour = 0, std::vector<std::string> gameMoves = {""}, unsigned short int ply = 0, std::vector<uint64_t> previousStates = {0}, std::vector<std::string> = {""});
void printStates(T_boardStates *b, int playerColour);
void printBits(size_t const size, void const * const ptr);
void printTBitboardNumbersBin(T_bitboard **b);
void printTBitboardNumbersDec(T_bitboard **b);
void printMove(char* c);
void landingMessage();
void printBoard(int, T_chessboard);
bool isWhiteTile(int, int);
void printBoardPlayingAsBlack(T_chessboard);
void printBoardPlayingAsWhite(T_chessboard);
void setColourForBlack(bool);
void setColourForWhite(bool);
void printGlyph(int, bool);
void displayHelp();
void invalidAlert();
void mainPrompt();

#endif // OUTPUT_H
