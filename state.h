#ifndef STATE_H
#define STATE_H

#define MAX_PREV_STATES 8849
//Find a theoretical maximum of the following value:
#define MAX_SUCC_STATES 100
#define BITBOARD_SIZE 64

#include <stdint.h>
#include <stdbool.h>

typedef uint64_t T_bitboard;

typedef struct BoardState T_boardState;

typedef struct BoardStates T_boardStates;

struct PrevStates;

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
    unsigned char wEnPassants;
    unsigned char bEnPassants;
    unsigned char castlesWhite : 3;//First bit set if L castle moved. Second R castle moved. Third King moved
    unsigned char castlesBlack : 3;//First bit set if L castle moved. Second R castle moved. Third King moved
    unsigned char noCapturesOrPawnMoves;
    struct PrevStates *ps;
    unsigned int ply;
};

struct BoardStates{
    struct BoardState bs[MAX_SUCC_STATES];
    int fi;
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

void printStates(T_boardStates *b);
int whosTurnNEW(const int ply);
bool isRankFive(char n);
bool isRankFour(char n);
bool isRankSeven(char n);
char whatRank(char n);
char whatFile(char n);
bool isPosWhite(T_boardState *b, int n);
bool isPosBlack(T_boardState *b, int n);
bool isPosInSecondLastColumn(int n);
void addState(T_boardStates *dst, const T_boardState *src);
int length(T_boardStates *bss);
bool isPosEmpty(const T_boardState *b, int n);
T_boardState initialiseBoardState();
void initialiseWPawns(T_bitboard *result);
void initialiseWBishops(T_bitboard *result);
void initialiseWKnights(T_bitboard *result);
void initialiseWRooks(T_bitboard *result);
void initialiseWQueen(T_bitboard *result);
void initialiseWKing(T_bitboard *result);
void initialiseBPawns(T_bitboard *result);
void initialiseBBishops(T_bitboard *result);
void initialiseBKnights(T_bitboard *result);
void initialiseBRooks(T_bitboard *result);
void initialiseBQueen(T_bitboard *result);
void initialiseBKing(T_bitboard *result);
void initialiseWEnPassants(char *c);
void initialiseBEnPassants(char *c);
void initialiseCastles(T_boardState *b);
void initialiseNoCapturesOrPawnMoves(char *c);
void initialisePreviousStates(struct PrevStates **ps);
void initialisePly(int *i);

#endif // STATE_H
