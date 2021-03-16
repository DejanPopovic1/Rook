#include "heuristics.hpp"
#include "state.hpp"

int evaluateWhiteMaterial(T_boardState *c){
    return PAWN_VALUE*(__builtin_popcountll(c->wPawn)) + BISHOP_VALUE*(__builtin_popcountll(c->wBishop)) +
           KNIGHT_VALUE*(__builtin_popcountll(c->wKnight)) + ROOK_VALUE*(__builtin_popcountll(c->wRook)) +
           QUEEN_VALUE*(__builtin_popcountll(c->wQueen)) + KING_VALUE*(__builtin_popcountll(c->wKing));
}

int evaluateBlackMaterial(T_boardState *c){
    return PAWN_VALUE*(__builtin_popcountll(c->bPawn)) + BISHOP_VALUE*(__builtin_popcountll(c->bBishop)) +
           KNIGHT_VALUE*(__builtin_popcountll(c->bKnight)) + ROOK_VALUE*(__builtin_popcountll(c->bRook)) +
           QUEEN_VALUE*(__builtin_popcountll(c->bQueen)) + KING_VALUE*(__builtin_popcountll(c->bKing));
}

int boardEvaluation(T_boardState *c){
    return evaluateWhiteMaterial(c) - evaluateBlackMaterial(c);
}
