#ifndef MOVEGENERATION_H
#define MOVEGENERATION_H

#include <stdbool.h>
#include "state.hpp"

enum Directions{north, northEast, east, southEast, south, southWest, west, northWest};

T_bitboard checkBit(T_bitboard number, int n);
bool isWhitePiece(int pieceValue);
bool isBlackPiece(int pieceValue);
bool isPosSameSide(T_boardState *b, int n);
bool isPosWhite(T_boardState *b, int n);
bool isPosBlack(T_boardState *b, int n);
bool isSecondLastRank(int n);
bool isSecondRank(int n);
bool isNortherlyOrEast(int direction);
bool isUpEmpty(T_boardState *b, int n);
bool isUpUpEmpty(T_boardState *b, int n);
bool isDownEmpty(T_boardState *b, int n);
bool isDownDownEmpty(T_boardState *b, int n);
void clearOppPosition(T_boardState *b, char pos);
T_bitboard *pieceBitboard(T_boardState *b, int piece);
void moveAndAttack(T_boardState *b, char dst, char src, char piece);
void move(T_boardState *b, char dst, char src, char piece);
void promote(T_boardStates *dst, T_boardState *b, int n, int piece);
void genWPawnSuccStates(T_boardStates *dst, T_boardState *b, int n, T_bitboard **rays, int DUMMY);
void genBPawnSuccStates(T_boardStates *dst, T_boardState *b, int n, T_bitboard **rays, int DUMMY);
void genMoves(T_boardStates *dst, T_boardState *b, int n, T_bitboard *validMoves, int piece, int direction);
T_bitboard moveBoardDir(T_boardState *b, int n, int direction, T_bitboard **rays);
void genDirStates(T_boardStates *dst, T_boardState *b, int n, T_bitboard **rays, int direction, int piece);
void genRaySuccStates(T_boardStates *dst, T_boardState *b, int n, T_bitboard **rays, int piece);
void genSuccStates(T_boardStates *dst, T_boardState *b);
void genPiecesSuccStates(T_boardStates *dst, T_boardState *b, T_bitboard **moveRules, int piece);
bool isPosAttacked(T_boardState *b, int n);
void generateCastlingStates(T_boardStates *dst, T_boardState *b, int n, T_bitboard **moveRules, int piece);
void genJumpOrStepSuccStates(T_boardStates *dst, T_boardState *b, int n, T_bitboard **moveRules, int piece);
void (*genPieceSuccStates(int piece))(T_boardStates *dst, T_boardState *b, int n, T_bitboard **rays, int piece);

#endif // MOVEGENERATION_H
