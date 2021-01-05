#ifndef GLOBALDECLARATIONS_H
#define GLOBALDECLARATIONS_H

#define RANK_SIZE 8
#define FILE_SIZE 8
#define MAX_USER_INPUT 10
#define MAX_SUCCESSOR_STATES 100
#define MAX_INPUT_STATES 100
#define PLAYING_AS_INPUT 10
#define MAX_POSITIONS 10

enum PlayingAs{asWhite, asBlack};

enum Turn{white, black};

enum Pieces{empty, whitePawn, whiteBishop, whiteKnight, whiteRook, whiteQueen, whiteKing,
            blackPawn, blackBishop, blackKnight, blackRook, blackQueen, blackKing,
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
    int freeIndex2;
};

//char** listOfMoves(){


//}

#endif // GLOBALDECLARATIONS_H
