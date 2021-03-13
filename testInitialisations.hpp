#ifndef TEST_INITIALISATIONS_H
#define TEST_INITIALISATIONS_H

#include "state.hpp"
//#include "output.h"
#include "bitUtilities.hpp"
#include "assert.h"
#include "moveGeneration.hpp"

T_boardState CMinitialiseBoardState();
void CMinitialiseWPawns(T_bitboard *result);
void CMinitialiseWBishops(T_bitboard *result);
void CMinitialiseWKnights(T_bitboard *result);
void CMinitialiseWRooks(T_bitboard *result);
void CMinitialiseWQueen(T_bitboard *result);
void CMinitialiseWKing(T_bitboard *result);
void CMinitialiseBPawns(T_bitboard *result);
void CMinitialiseBBishops(T_bitboard *result);
void CMinitialiseBKnights(T_bitboard *result);
void CMinitialiseBRooks(T_bitboard *result);
void CMinitialiseBQueen(T_bitboard *result);
void CMinitialiseBKing(T_bitboard *result);
void CMinitialiseWEnPassants(unsigned char *c);
void CMinitialiseBEnPassants(unsigned char *c);
void CMinitialiseCastlesTurnCheck(T_boardState *b);
void CMinitialiseNoCapturesOrPawnMoves(unsigned char *c);
void CMinitialisePreviousStates(struct PrevStates **ps);

T_boardState SMinitialiseBoardState();
void SMinitialiseWPawns(T_bitboard *result);
void SMinitialiseWBishops(T_bitboard *result);
void SMinitialiseWKnights(T_bitboard *result);
void SMinitialiseWRooks(T_bitboard *result);
void SMinitialiseWQueen(T_bitboard *result);
void SMinitialiseWKing(T_bitboard *result);
void SMinitialiseBPawns(T_bitboard *result);
void SMinitialiseBBishops(T_bitboard *result);
void SMinitialiseBKnights(T_bitboard *result);
void SMinitialiseBRooks(T_bitboard *result);
void SMinitialiseBQueen(T_bitboard *result);
void SMinitialiseBKing(T_bitboard *result);
void SMinitialiseWEnPassants(unsigned char *c);
void SMinitialiseBEnPassants(unsigned char *c);
void SMinitialiseCastlesTurnCheck(T_boardState *b);
void SMinitialiseNoCapturesOrPawnMoves(unsigned char *c);
void SMinitialisePreviousStates(struct PrevStates **ps);

#endif // TEST_INITIALISATIONS_H
