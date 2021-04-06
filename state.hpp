#ifndef STATE_H
#define STATE_H

#define MAX_PREV_STATES 10000 //If you apply a 50-move limit, the longest possible chess game is 5898.5 moves long.
#define MAX_SUCC_STATES 200 //Its theoretically possible to go higher, but then we're wasting memory allocation
#define BITBOARD_SIZE 64
#define BITBOARD_INDEX_SIZE BITBOARD_SIZE - 1
#define NUM_PIECE_TYPES 12

#include <stdint.h>
#include <stdbool.h>

struct BoardState;
struct BoardStates;

typedef uint64_t T_bitboard;
typedef struct BoardState T_boardState;
typedef struct BoardStates T_boardStates;

enum Turn{whiteTurn, blackTurn};

enum Pieces{empty, whitePawn, whiteBishop, whiteKnight, whiteRook, whiteQueen, whiteKing,
            blackPawn, blackBishop, blackKnight, blackRook, blackQueen, blackKing
            };

//When copyong states, you can use = for now but moving forward you will have to define this due to the pointer PrevStates
//Use enums to define the bitfield turns white and black
//whosTurn is redundant if there is ply but it saves calculations and recalculations
//Can ply not be stripped out of this - when state depth is built we dont need to know ply
//Lets check how stockfish represents state
//Save wAll bAll and all within the state. This saves recalculating it in future
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
    unsigned char castlesLRWhite : 1;//First bit set if L castle moved. Second R castle moved. Third King moved
    unsigned char castlesRRWhite : 1;//First bit set if L castle moved. Second R castle moved. Third King moved
    unsigned char castlesKWhite : 1;//First bit set if L castle moved. Second R castle moved. Third King moved
    unsigned char castlesLRBlack : 1;//First bit set if L castle moved. Second R castle moved. Third King moved
    unsigned char castlesRRBlack : 1;//First bit set if L castle moved. Second R castle moved. Third King moved
    unsigned char castlesKBlack : 1;//First bit set if L castle moved. Second R castle moved. Third King moved
    unsigned char whosTurn : 1; //0 Indicates white and 1 indicates black move
    unsigned char evaluateCheck : 1;
    unsigned char noCapturesOrPawnMoves;
};

struct BoardStates{
    struct BoardState bs[MAX_SUCC_STATES];
    int fi;
};

struct PrevStates{
    struct BoardState bs[MAX_PREV_STATES];
    int fp;
};

bool isInCheck(T_boardState b);
bool isStatesEqual(T_boardState a, T_boardState b);
T_bitboard *pieceBitboard(T_boardState *b, char piece);
bool isPawn(int p);
T_bitboard wAll(const T_boardState *b);
T_bitboard bAll(const T_boardState *b);
T_bitboard all(const T_boardState *b);
T_bitboard sameAll(const T_boardState *b);
T_bitboard oppositeAll(T_boardState *b);
bool isRankFive(char n);
bool isRankFour(char n);
bool isRankSeven(char n);
bool isRankTwo(char n);
char whatRank(char n);
char whatFile(char n);
bool isPosEmpty(const T_boardState *b, int n);
int length(T_boardStates *bss);
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
void initialiseWEnPassants(unsigned char *c);
void initialiseBEnPassants(unsigned char *c);
void initialiseCastlesTurnCheck(T_boardState *b);
void initialiseNoCapturesOrPawnMoves(unsigned char *c);
void initialisePreviousStates(struct PrevStates **ps);

#endif // STATE_H
