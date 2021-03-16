#ifndef HEURISTICS_H
#define HEURISTICS_H

#define PAWN_VALUE 1
#define BISHOP_VALUE 3
#define KNIGHT_VALUE 3
#define ROOK_VALUE 5
#define QUEEN_VALUE 9
#define KING_VALUE 200

int evaluateWhite(T_boardState *c);
int evaluateBlack(T_boardState *c);
int boardEvaluation(T_boardState *c);

#endif // HEURISTICS_H
