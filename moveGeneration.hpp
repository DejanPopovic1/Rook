#ifndef MOVEGENERATION_H
#define MOVEGENERATION_H

#include "state.hpp"
#include "searchTree.hpp"

#include <stdbool.h>

#define WHITE_KINGSIDE_PASS 96
#define WHITE_QUEENSIDE_PASS 12
#define BLACK_KINGSIDE_PASS 6917529027641081856
#define BLACK_QUEENSIDE_PASS 864691128455135232
#define WHITE_KINGSIDE_ATTACKING 61440
#define WHITE_QUEENSIDE_ATTACKING 7680
#define BLACK_KINGSIDE_ATTACKING 67553994410557440
#define BLACK_QUEENSIDE_ATTACKING 8444249301319680
#define WHITE_KINGSIDE_ATTACKING_K 15767552
#define WHITE_QUEENSIDE_ATTACKING_K 1979136
#define BLACK_KINGSIDE_ATTACKING_K 43048079250685952
#define BLACK_QUEENSIDE_ATTACKING_K 14388209161076736

enum Directions{north, northEast, east, southEast, south, southWest, west, northWest};

T_bitboard getPieceFromPieces(T_bitboard *pcs);
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
void moveAndAttack(T_boardState *b, char dst, char src, char piece);
void move(T_boardState *b, char dst, char src, char piece);
void promote(T_Node *node, T_boardState *b, int n, int piece);
void genWPawnSuccStates(T_Node *node, T_boardState *b, int n, int DUMMY);
void genBPawnSuccStates(T_Node *node, T_boardState *b, int n, int DUMMY);
void genMoves(T_Node *node, T_boardState *b, int n, T_bitboard *validMoves, int piece, int direction);
T_bitboard moveBoardDir(T_boardState *b, int n, int direction);
void genDirStates(T_Node *node, T_boardState *b, int n, int direction, int piece);
void genRaySuccStates(T_Node *node, T_boardState *b, int n, int piece);
bool genSuccStates(T_Node *node, T_boardState *b);
void genPiecesSuccStates(T_Node *node, T_boardState *b, int piece);
void generateCastlingState(T_Node *node, T_boardState *b, T_bitboard castlePass);
void generateCastlingStates(T_Node *node, T_boardState *b, int piece, T_bitboard castlePass);
void genJumpOrStepSuccStates(T_Node *node, T_boardState *b, int n, int piece);
void (*genPieceSuccStates(int piece))(T_Node *node, T_boardState *b, int n, int piece);
bool isKingsExist(T_Node *n, bool whosKing);
bool isKingExist(T_Node *n, bool whosKing);

#endif // MOVEGENERATION_H
