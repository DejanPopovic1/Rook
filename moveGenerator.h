#include "state.h"
#include <stdbool.h>

enum Directions{north, northEast, east, southEast, south, southWest, west, northWest};

void genWPawnsSuccStates(T_boardStates *dst, const T_boardState *b, const T_bitboard **rays);
void genWBishopsSuccStates(T_boardStates *dst, const T_boardState *b, const T_bitboard **rays);
bool isUpEmpty(const T_boardState *b, int n);
bool isUpUpEmpty(const T_boardState *b, int n);
void genWPawnSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays);
void genWBishopSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays);
void genWKnightSuccStates(T_boardState c, T_boardStates *ss);
void genWRookSuccStates(T_boardState c, T_boardStates *ss);
void genWQueenSuccStates(T_boardState c, T_boardStates *ss);
void genWKingSuccStates(T_boardState c, T_boardStates *ss);
void genBPawnSuccStates(T_boardState c, T_boardStates *ss);
void genBBishopSuccStates(T_boardState c, T_boardStates *ss);
void genBKnightSuccStates(T_boardState c, T_boardStates *ss);
void genBRookSuccStates(T_boardState c, T_boardStates *ss);
void genBQueenSuccStates(T_boardState c, T_boardStates *ss);
void genBKingSuccStates(T_boardState c, T_boardStates *ss);
