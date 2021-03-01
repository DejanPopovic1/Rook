#ifndef GLOBALDECLARATIONS_H
#define GLOBALDECLARATIONS_H

#include <stdbool.h>
#include "GlobalDeclarations.h"

#define RANK_SIZE 8
#define FILE_SIZE 8
#define MAX_USER_INPUT 10
#define MAX_SUCCESSOR_STATES 100 //Setting this to 100 results in runtime error and I DONT KNOW WHY
#define MAX_INPUT_STATES 100
#define PLAYING_AS_INPUT 10
#define MAX_POSITIONS 10
#define MAIN_SELECTION 100

enum PlayingAs{asWhite, asBlack};

enum Turn{whiteTurn, blackTurn};

enum Pieces{empty, whitePawn, whiteBishop, whiteKnight, whiteRook, whiteQueen, whiteKing,
            blackPawn, blackBishop, blackKnight, blackRook, blackQueen, blackKing
            };

typedef int T_chessboard[RANK_SIZE][FILE_SIZE];

struct States{
    T_chessboard states[MAX_SUCCESSOR_STATES];
    int freeIndex;
};

typedef struct States T_states;

struct Position{
    int r;
    int f;
};

typedef struct Position T_position;

typedef struct Positions T_positions;

struct Positions{
    T_position positions[MAX_POSITIONS];
    int freeIndex;
};

typedef struct Moves T_moves;

//struct Moves{
//    char *moves[MAX_SUCCESSOR_STATES];
//    int freeIndex;
//};

bool isNeighbouringPawnDoubleMoved(const int, const int);
bool isPawn(int p);
bool isBishop(int p);
bool isKnight(int p);
bool isRook(int p);
bool isQueen(int p);
bool isKing(int p);
int whosTurn(const int halfPly);
int alternatePlayer(const int playingAs);
bool isSamePosition(const T_position a, const T_position b);
bool isSameRank(T_position a, T_position b);
bool isSameFile(T_position a, T_position b);
T_position* createPosition(const int, const int);

#endif // GLOBALDECLARATIONS_H
