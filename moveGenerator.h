#include "state.h"
#include <stdbool.h>



void genWPawnsSuccStates(T_boardStates *dst, const T_boardState *b);
bool isUpEmpty(const T_boardState *b, int n);
bool isUpUpEmpty(const T_boardState *b, int n);
void genWPawnSuccStates(T_boardStates *dst, const T_boardState *b, int n);
void genWBishopSuccStates(T_boardStates *dst, const T_boardState *b, int n);
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
