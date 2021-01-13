#ifndef STATE_H
#define STATE_H

#define MAX_PREV_STATES 10000

#include <stdint.h>

typedef uint64_t T_bitboard;

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

struct GameState{
    struct BoardState bs;
    struct PrevStates ps;
};

struct PrevStates{
    struct BoardState bs[MAX_PREV_STATES];
    int fp;
};

#endif // STATE_H
