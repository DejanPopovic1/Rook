#include "toAlgebraicNotation.h"
#include "GlobalDeclarations.h"
#include "applicableActions.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int (*returnMvmntRule(T_chessboard c, T_position p))(T_chessboard, T_position, T_states *){
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
            return &generateBlackRookSuccessorStates;
        case blackQueen:
            return &generateBlackQueenSuccessorStates;
        case blackKing:
            return &generateBlackKingSuccessorStates;
        default:
            assert(false);
    }
}

bool arePiecesInSameRank(T_positions *ps, T_position p){
    for(int i = 0; i < ps->freeIndex; i++){
//        if(isSamePosition(ps->positions[i], p)){
//            continue;
//        }
        if(isSameRank(ps->positions[i], p)){
            return true;
        }
    }
    return false;
}

bool arePiecesInSameFile(T_positions *ps, T_position p){
    for(int i = 0; i < ps->freeIndex; i++){
//        if(isSamePosition(ps->positions[i], p)){
//            continue;
//        }
        if(isSameFile(ps->positions[i], p)){
            return true;
        }
    }
    return false;
}

char* formatFileDisplay(int f){
    char *result = malloc(FILE_STRING * sizeof(char));
    assert(f >= 0 && f < 8);
    result[0] = f + ASCII_CHARACTER_OFFSET;
    result[1] = '\0';
    return result;
}

char* formatRankDisplay(int r){
    char *result = malloc(FILE_STRING * sizeof(char));
    assert(r >= 0 && r < 8);
    result[0] = r + ASCII_NUMBER_OFFSET;
    result[1] = '\0';
    return result;
}

char* toFileRank(T_positions *departures, T_position departure){
    char *result = malloc(MAX_DISAMBIGUATOR_STRING * sizeof(char));
    if(departures->freeIndex == 0){
            return "";
    }
    else if(arePiecesInSameFile(departures, departure) && arePiecesInSameRank(departures, departure)){
        strcpy(result, formatFileDisplay(departure.f));
        strcat(result, formatFileDisplay(departure.r));
    }
    else if(!arePiecesInSameFile(departures, departure)){
        strcpy(result, formatFileDisplay(departure.f));
    }
    else if(arePiecesInSameFile(departures, departure)){
        strcpy(result, formatRankDisplay(departure.r));
    }
    else{
        assert(false);
    }
    return result;
}

char* toFileRankPawn(T_positions *departures, T_position departure, bool isCaptured){
    char *result = malloc(MAX_DISAMBIGUATOR_STRING * sizeof(char));
    if(isCaptured){
        strcpy(result, formatFileDisplay(departure.f));
    }
    else if(!isCaptured){
        strcpy(result, "");
    }
    else{
        assert(false);
    }
    return result;
}

//Need to account for en passant castling and promotion
T_position whereArrival(T_chessboard c, T_chessboard ss){
    bool breakOut = false;
    T_position arrival;
    for(int i = 0; i < RANK_SIZE && breakOut == false; i++){
        for(int j = 0; j < FILE_SIZE && breakOut == false; j++){
            if(c[i][j] != ss[i][j] && ss[i][j] != empty){
                arrival.r = i;
                arrival.f = j;
                breakOut = true;
            }
        }
    }
    return arrival;
}

bool doesDepartureGoToArrival(T_chessboard c, T_position d, T_position a){
    T_states *s = malloc(sizeof(T_states));
//    T_position *p = createPosition(2, 3);
    mvmntRulePtr = returnMvmntRule(c, d);
    (*mvmntRulePtr)(c, d, s);
    for(int i = 0; i < s->freeIndex; i++){
        if(isSamePosition(whereArrival(c, s->states[i]), a)){
            return true;
        }
    }
    return false;
}

T_positions* trimOtherSamePieces(T_chessboard c, T_positions *ps, T_position arrival){
    T_positions *result = malloc(sizeof(T_positions));
    result->freeIndex = 0;
    for(int i = 0; i < ps->freeIndex; i++){
        if(doesDepartureGoToArrival(c, ps->positions[i], arrival)){
            result->positions[result->freeIndex] = ps->positions[i];
            result->freeIndex++;
//            printf("Matched Position: ");
//            printPosition(result->positions[i]);
//            printf("\n");
        }
    }
    return result;
}

char* disambiguator(T_chessboard c, T_position departure, T_position arrival, bool isCaptured){
    T_positions *ps = whereAreOtherSamePieces(c, departure);
    T_positions *rps;
    rps = trimOtherSamePieces(c, ps, arrival);
    free(ps);
    if(!isPawn(c[departure.r][departure.f])){
        return toFileRank(rps, departure);
    }
    else if(isPawn(c[departure.r][departure.f])){
        return toFileRankPawn(rps, departure, isCaptured);
    }
}

T_positions* whereAreOtherSamePieces(T_chessboard c, T_position p){
    T_positions *result = malloc(sizeof(T_positions));
    result->freeIndex = 0;
    int pieceType = c[p.r][p.f];
    for(int i = 0; i < RANK_SIZE; i++){
        for(int j = 0; j < FILE_SIZE; j++){
            if(i == p.r && j == p.f){
                continue;
            }
            if(pieceType == c[i][j]){
                T_position *pos = createPosition(i, j);
                result->positions[result->freeIndex] = *pos;
                (result->freeIndex)++;
                free(pos);
            }
        }
    }
    return result;
}

//THESE CURRENTLY DONT FACTOR INTO ACCOUNT EN PASSANTS AND CASTLING and promotion and CHECK/CHECKMATE and having more than 3 pieces of non-pawn
//Refactor so that parts 1, 2 and 3 each return individual strings
//Use the position creation functions over here!
char* toAlgebraicNotation(T_chessboard c, T_chessboard ss){
    char* result = malloc(MOVE_INPUT * sizeof(char));
    strcpy(result, "");
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
    breakOut = false;
    //Determine arrival location and whether piece is captured
    for(int i = 0; i < RANK_SIZE && breakOut == false; i++){
        for(int j = 0; j < FILE_SIZE && breakOut == false; j++){
            if((c[i][j] != ss[i][j]) && (ss[i][j] != empty)){
                arrival.r = i;
                arrival.f = j;
                breakOut = true;
                if(c[i][j] != empty){
                    isPieceCaptured = true;
                }
            }
        }
    }
    //strcpy(result, "|");
    int movedPiece = c[departure.r][departure.f];
    //Part 1: Piece to be moved
    switch(movedPiece){
        case whitePawn:
        case blackPawn:
            ;//strcpy(result, "");
            break;
        case whiteBishop:
        case blackBishop:
            strcat(result, "B");
            break;
        case whiteKnight:
        case blackKnight:
            strcat(result, "N");
            break;
        case whiteRook:
        case blackRook:
            strcat(result, "R");
            break;
        case whiteQueen:
        case blackQueen:
            strcat(result, "Q");
            break;
        case whiteKing:
        case blackKing:
            strcat(result, "K");
            break;
    }
    //strcat(result, "-");
    strcat(result, disambiguator(c, departure, arrival, isPieceCaptured));
    //Part 3: Take?
    //strcat(result, "-");
    if(isPieceCaptured){
        strcat(result, "x");
    }
    //Part 4: Arrival
    //strcat(result, "-");
    char *ff = formatFileDisplay(arrival.f);
    char *fr = formatRankDisplay(arrival.r);
    strcat(result, ff);
    strcat(result, fr);
    //Part 5: Check(mate)?
    //strcat(result, "-");
    //strcat(result, "|");
    //printf("%s\n", result);
    return result;
}
