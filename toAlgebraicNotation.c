#include "toAlgebraicNotation.h"
#include "GlobalDeclarations.h"
#include "applicableActions.h"
#include <assert.h>
#include <stdbool.h>

int (*generatorPtr(T_chessboard c, T_position p))(T_chessboard, T_position, T_states){
    int movedPiece = whatPiece(c, p);
    switch(movedPiece){
        case whitePawn:
            return &generateWhitePawnSuccessorStates;
        case whiteBishop:
            return &generateWhiteBishopSuccessorStates;
        case whiteKnight:
            return &generateWhiteKnightSuccessorStates;
        case whiteRook:
            return &generateWhiteRookSuccessorStates;
        case whiteQueen:
            return &generateWhiteQueenSuccessorStates;
        case whiteKing:
            return &generateWhiteKingSuccessorStates;
        case blackPawn:
            return &generateBlackPawnSuccessorStates;
        case blackBishop:
            return &generateBlackBishopSuccessorStates;
        case blackKnight:
            return &generateBlackKnightSuccessorStates;
        case blackRook:
            return &generateBlackKnightSuccessorStates;
        case blackQueen:
            return &generateBlackKnightSuccessorStates;
        case blackKing:
            return &generateBlackKnightSuccessorStates;
        default:
            assert(false);
    }
}

bool areSamePiecesInSameRank(T_chessboard c, T_position p){
    int pieceType = c[p.r][p.f];
    for(int i = 0; i < FILE_SIZE; i++){
        if(p.f == i){
            continue;
        }
        if(pieceType == c[p.r][i]){
            return true;
        }
    }
    return false;
}

bool areSamePiecesInSameFile(T_chessboard c, T_position p){
    int pieceType = c[p.r][p.f];
    for(int i = 0; i < RANK_SIZE; i++){
        if(p.r == i){
            continue;
        }
        if(pieceType == c[i][p.f]){
            return true;
        }
    }
    return false;
}

char* toFileRank(T_chessboard c, T_positions *departures, T_position departure, T_position arrival){
    char *result = malloc(MAX_DISAMBIGUATOR_STRING * sizeof(char));
    if(areSamePiecesInSameFile(c, ))){


    }
    else if(areSamePiecesInSameRank()){



    }
    else{
        assert(false);
    }


//    char temp1[1];
//    T_position positions[MAX_POSITIONS];
//    if(true/*numOfSamePiecesGoingToArrival(c, positions, movedPiece, arrival) == 2*/){
//        if(isFileDifferent(positions[0], positions[1])){
//            sprintf(temp1, "%d", departure.f);
//            strcat(result, temp1);
//        }
//        else if(isRankDifferent(positions[0], positions[1])){
//            sprintf(temp1, "%d", departure.r);
//            strcat(result, temp1);
//        }
//        else{
//            assert(false);
//        }
//    }
//    else if(false/*numOfSamePiecesGoingToArrival(positions, movedPiece, arrival) > 2*/){
//        //To be added in
//    }
//    else{
//        assert(false);
//    }


    strcpy(result, "ab");
    return result;
}

char* disambiguator(T_chessboard c, T_position departure, T_position arrival){
    int pieceType = c[departure.r][departure.f];
    T_positions *samePieces = whereAreSamePieces(pieceType, c);
    samePieces = whichSamePiecesMoveToArrival(c, samePieces, arrival);
    return toFileRank(samePieces, departure, arrival);
}

T_positions* whereAreSamePieces(int pieceType, T_chessboard c){
    T_positions *p = malloc(sizeof(T_positions));
    p->freeIndex = 0;
    T_position pos;
    for(int i = 0; i < RANK_SIZE; i++){
        for(int j = 0; i < FILE_SIZE; j++){
            if(pieceType == c[i][j]){
                pos.r = i;
                pos.f = j;
                p->positions[p->freeIndex] = pos;
                p->freeIndex++;
            }
        }
    }
    return p;
}

T_positions* whichSamePiecesMoveToArrival(T_chessboard c, T_positions *departures, T_position arrival){
    int pieceType = c[departures->positions[0].r][departures->positions[0].f];
    T_positions *p = malloc(sizeof(T_positions));
    p->freeIndex = 0;
    T_states *movementStates = malloc(100 * sizeof(T_chessboard));
    for(int i = 0; i < departures->freeIndex; i++){
        movementPtr = generatorPtr(c, departures->positions[i]);
        (*movementPtr)(c, departures->positions[i], movementStates);
    }
}


//THESE CURRENTLY DONT FACTOR INTO ACCOUNT EN PASSANTS AND CASTLING and CHECK/CHECKMATE and having more than 3 pieces of non-pawn
//Refactor so that parts 1, 2 and 3 each return individual strings
char* toAlgebraicNotation(T_chessboard c, T_chessboard ss){
    char* result = malloc(MOVE_INPUT * sizeof(char));
    bool isPieceCaptured = false;
    bool breakOut = false;
    T_position departure;
    T_position arrival;
    //Determine departure location
    for(int i = 0; i < RANK_SIZE && breakOut == false; i++){
        for(int j = 0; j < FILE_SIZE && breakOut == false; j++){
            if(c[i][j] != empty && ss[i][j] == empty){
                departure.r = i;
                departure.f = j;
                breakOut = true;
            }
        }
    }
    //Determine arrival location and whether piece is captured
    for(int i = 0; i < RANK_SIZE && breakOut == false; i++){
        for(int j = 0; j < FILE_SIZE && breakOut == false; j++){
            if(c[i][j] != ss[i][j] && ss[i][j] != empty){
                arrival.r = i;
                arrival.f = j;
                breakOut = true;
                if(c[i][j] != empty){
                    isPieceCaptured = true;
                }
            }
        }
    }
    int movedPiece = c[departure.r][departure.f];
    //Part 1: Piece to be moved
    switch(movedPiece){
        case whitePawn:
        case blackPawn:
            ;//strcpy(result, "");
            break;
        case whiteBishop:
        case blackBishop:
            strcpy(result, "B");
            break;
        case whiteKnight:
        case blackKnight:
            strcpy(result, "N");
            break;
        case whiteRook:
        case blackRook:
            strcpy(result, "R");
            break;
        case whiteQueen:
        case blackQueen:
            strcpy(result, "Q");
            break;
        case whiteKing:
        case blackKing:
            strcpy(result, "K");
            break;
    }
    //Part 2: Disambiguator
        //Determine all like pieces and add them to a list
        //From the list above copy only those ones that end up in the same destination into another list

    strcat(result, disambiguator(c, departure, arrival));

    //Part 3: Take?
    if(isPieceCaptured){
        strcat(result, "x");
    }
    //Part 4: Arrival
        char temp2[1];
        char temp3[1];
        sprintf(temp2, "%d", arrival.f);
        sprintf(temp3, "%d", arrival.r);
        strcat(result, temp2);
        strcat(result, temp3);
    //Part 5: Check(mate)?
    return "c3";
}
