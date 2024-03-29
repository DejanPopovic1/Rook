#ifndef TEST_INITIALISATIONS_H
#define TEST_INITIALISATIONS_H

#include "state.hpp"

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

T_boardState PPinitialiseBoardState();
void PPinitialiseWPawns(T_bitboard *result);
void PPinitialiseWBishops(T_bitboard *result);
void PPinitialiseWKnights(T_bitboard *result);
void PPinitialiseWRooks(T_bitboard *result);
void PPinitialiseWQueen(T_bitboard *result);
void PPinitialiseWKing(T_bitboard *result);
void PPinitialiseBPawns(T_bitboard *result);
void PPinitialiseBBishops(T_bitboard *result);
void PPinitialiseBKnights(T_bitboard *result);
void PPinitialiseBRooks(T_bitboard *result);
void PPinitialiseBQueen(T_bitboard *result);
void PPinitialiseBKing(T_bitboard *result);
void PPinitialiseWEnPassants(unsigned char *c);
void PPinitialiseBEnPassants(unsigned char *c);
void PPinitialiseCastlesTurnCheck(T_boardState *b);
void PPinitialiseNoCapturesOrPawnMoves(unsigned char *c);

T_boardState ICinitialiseBoardState();
void ICinitialiseWPawns(T_bitboard *result);
void ICinitialiseWBishops(T_bitboard *result);
void ICinitialiseWKnights(T_bitboard *result);
void ICinitialiseWRooks(T_bitboard *result);
void ICinitialiseWQueen(T_bitboard *result);
void ICinitialiseWKing(T_bitboard *result);
void ICinitialiseBPawns(T_bitboard *result);
void ICinitialiseBBishops(T_bitboard *result);
void ICinitialiseBKnights(T_bitboard *result);
void ICinitialiseBRooks(T_bitboard *result);
void ICinitialiseBQueen(T_bitboard *result);
void ICinitialiseBKing(T_bitboard *result);
void ICinitialiseWEnPassants(unsigned char *c);
void ICinitialiseBEnPassants(unsigned char *c);
void ICinitialiseCastlesTurnCheck(T_boardState *b);
void ICinitialiseNoCapturesOrPawnMoves(unsigned char *c);

T_boardState LKinitialiseBoardState();
void LKinitialiseWPawns(T_bitboard *result);
void LKinitialiseWBishops(T_bitboard *result);
void LKinitialiseWKnights(T_bitboard *result);
void LKinitialiseWRooks(T_bitboard *result);
void LKinitialiseWQueen(T_bitboard *result);
void LKinitialiseWKing(T_bitboard *result);
void LKinitialiseBPawns(T_bitboard *result);
void LKinitialiseBBishops(T_bitboard *result);
void LKinitialiseBKnights(T_bitboard *result);
void LKinitialiseBRooks(T_bitboard *result);
void LKinitialiseBQueen(T_bitboard *result);
void LKinitialiseBKing(T_bitboard *result);
void LKinitialiseWEnPassants(unsigned char *c);
void LKinitialiseBEnPassants(unsigned char *c);
void LKinitialiseCastlesTurnCheck(T_boardState *b);
void LKinitialiseNoCapturesOrPawnMoves(unsigned char *c);

T_boardState MMinitialiseBoardState();
void MMinitialiseWPawns(T_bitboard *result);
void MMinitialiseWBishops(T_bitboard *result);
void MMinitialiseWKnights(T_bitboard *result);
void MMinitialiseWRooks(T_bitboard *result);
void MMinitialiseWQueen(T_bitboard *result);
void MMinitialiseWKing(T_bitboard *result);
void MMinitialiseBPawns(T_bitboard *result);
void MMinitialiseBBishops(T_bitboard *result);
void MMinitialiseBKnights(T_bitboard *result);
void MMinitialiseBRooks(T_bitboard *result);
void MMinitialiseBQueen(T_bitboard *result);
void MMinitialiseBKing(T_bitboard *result);
void MMinitialiseWEnPassants(unsigned char *c);
void MMinitialiseBEnPassants(unsigned char *c);
void MMinitialiseCastlesTurnCheck(T_boardState *b);
void MMinitialiseNoCapturesOrPawnMoves(unsigned char *c);


#endif // TEST_INITIALISATIONS_H
