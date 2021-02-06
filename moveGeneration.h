#ifndef MOVEGENERATION_H
#define MOVEGENERATION_H

#include <stdbool.h>
#include "state.h"

enum Directions{north, northEast, east, southEast, south, southWest, west, northWest};

void setBit(T_bitboard *number, int n);
void clearBit(T_bitboard *number, int n);
T_bitboard checkBit(T_bitboard number, int n);
bool isWhitePiece(int pieceValue);
bool isBlackPiece(int pieceValue);
bool isPosSameSide(T_boardState *b, int n);
bool isPosWhite(T_boardState *b, int n);
bool isPosBlack(T_boardState *b, int n);
bool isSecondLastRank(int n);
bool isNortherlyOrEast(int direction);
bool isUpEmpty(const T_boardState *b, int n);
bool isUpUpEmpty(const T_boardState *b, int n);
void clearOppPosition(T_boardState *b, char pos);
T_bitboard *stateMember(T_boardState *b, int piece);
void moveAndAttack(T_boardState *b, char dst, char src, char piece);
void move(T_boardState *b, char dst, char src, char piece);
void genWPawnSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays);
void genMoves(T_boardStates *dst, const T_boardState *b, int n, T_bitboard *validMoves, int piece, int direction);
T_bitboard moveBoardDir(const T_boardState *b, int n, int direction, const T_bitboard **rays);
void genDirStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays, int direction, int piece);
void genRaySuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays, int piece);
void genWBishopSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays);
void genWRookSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays);
void genWQueenSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays);
void genSuccStates(T_boardStates *dst, const T_boardState *b);
void genPiecesSuccStates(T_boardStates *dst, const T_boardState *b, const T_bitboard **moveRules, int piece);
void genJumpOrStepSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **moveRules, int piece);
void genBPawnSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays);
void genBBishopSuccStates(T_boardState c, T_boardStates *ss);
void genBKnightSuccStates(T_boardState c, T_boardStates *ss);
void genBRookSuccStates(T_boardState c, T_boardStates *ss);
void genBQueenSuccStates(T_boardState c, T_boardStates *ss);
void genBKingSuccStates(T_boardState c, T_boardStates *ss);
void (*genPieceSuccStates(int piece))(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays, int piece);

#endif // MOVEGENERATION_H