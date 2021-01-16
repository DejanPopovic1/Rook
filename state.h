#ifndef STATE_H
#define STATE_H

#define MAX_PREV_STATES 8849
#define BITBOARD_SIZE 64

#include <stdint.h>

typedef uint64_t T_bitboard;

typedef struct BoardState T_boardState;

struct BoardState{
    T_bitboard wPawn;
    T_bitboard wBishop;
    T_bitboard wKnight;
    T_bitboard wRook;
    T_bitboard wQueen;
    T_bitboard wKing;
    T_bitboard bPawn;
    T_bitboard bBishop;
    T_bitboard bKnight;
    T_bitboard bRook;
    T_bitboard bQueen;
    T_bitboard bKing;
};

struct PrevStates{
    struct BoardState bs[MAX_PREV_STATES];
    int fp;
};

struct GameState{
    struct BoardState bs;
    struct PrevStates ps;
    char noPawnMovesOrCaptures;
    int ply;
};

int whosTurnNEW(const int ply);
T_boardState initialiseBoardState();
void initialiseWPawns(T_bitboard *result);
void initialiseWBishops(T_bitboard *result);
void initialiseWKnights();
T_boardState initialiseWRooks();
T_boardState initialiseWQueen();
T_boardState initialiseWKing();
void initialiseBPawns(T_bitboard *result);
void initialiseBBishops(T_bitboard *result);
void initialiseBKnights();
T_boardState initialiseBRooks();
T_boardState initialiseBQueen();
T_boardState initialiseBKing();
#endif // STATE_H
