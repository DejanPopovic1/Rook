#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "state.hpp"

#define PAWN_VALUE 1
#define BISHOP_VALUE 3
#define KNIGHT_VALUE 3
#define ROOK_VALUE 5
#define QUEEN_VALUE 9
#define KING_VALUE 200

int evaluateWhiteMaterial(T_boardState *c);
int evaluateBlackMaterial(T_boardState *c);
int boardEvaluationPieces(T_boardState *c);

#endif // HEURISTICS_H
