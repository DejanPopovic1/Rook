#include "state.h"
#include <stdbool.h>

enum Directions{north, northEast, east, southEast, south, southWest, west, northWest};

void genSuccStates(T_boardStates *dst, const T_boardState *b);
void (*returnGenerator(int piece))(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays);
void genWPawnsSuccStates(T_boardStates *dst, const T_boardState *b, const T_bitboard **rays);
void genPiecesSuccStates(T_boardStates *dst, const T_boardState *b, const T_bitboard **rays, int piece);
bool isUpEmpty(const T_boardState *b, int n);
bool isUpUpEmpty(const T_boardState *b, int n);
void genWPawnSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays);
void genWBishopSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays);
void genWKnightSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays);
void genWRookSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays);
void genWQueenSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays);
void genWKingSuccStates(T_boardState c, T_boardStates *ss);
void genBPawnSuccStates(T_boardState c, T_boardStates *ss);
void genBBishopSuccStates(T_boardState c, T_boardStates *ss);
void genBKnightSuccStates(T_boardState c, T_boardStates *ss);
void genBRookSuccStates(T_boardState c, T_boardStates *ss);
void genBQueenSuccStates(T_boardState c, T_boardStates *ss);
void genBKingSuccStates(T_boardState c, T_boardStates *ss);
