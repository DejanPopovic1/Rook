#include <stdio.h>
#include "chess_pieces.h"
#include "applicableActions.h"
#include "GlobalDeclarations.h"
#include "memoryUtilities.h"
#include <stdbool.h>
#include "output.h"
#include "testInitialisations.h"
#include <assert.h>
#include <string.h>

#define MAIN_SELECTION 100
#define MOVE_INPUT 100
#define MAX_DISAMBIGUATOR 3

char* specifyMove();

//Todo List:
//DONT FORGET TO FREE ALL MALLOCS!
//Try making function pointer to iterating through the board. This will then be shared across all functions that iterate board
//Error handle all malloc allocations by defining your own "wrapper" function

T_states *generateSuccessorStates(int playingAs, T_chessboard chessboard);

T_positions* whereAreSamePieces(int, T_chessboard);
char* moveInput();
//T_chessboard updateCurrentState(T_states *successorStates, char* input);

struct ApplicableActions{
    int chessboard [RANK_SIZE][FILE_SIZE];
    char* algebraicNotation;
};

void mainPrompt(){
    printf("Rook>");
    return;
}

void multiPlayerPrompt(){
    printf(" -> ");
    return;
}

//Change == 0 to !strcmp
int playingAsPrompt(){
    char playingAs[PLAYING_AS_INPUT];
    while(true){
        printf("Rook > Multiplayer Session > Select colour (w for white / b for black): \n");
        scanf("%s", playingAs);
        if(strcmp(playingAs, "w") == 0){
            return asWhite;
        }
        else if(strcmp(playingAs, "b") == 0){
            return asBlack;
        }
        else{
            printf("Invalid colour selection. \n");
        }
    }
}

char* mainSelection(){
    char *mainSelection = malloc(MAIN_SELECTION * sizeof(char));
    fgets(mainSelection, MAIN_SELECTION, stdin);
    mainSelection[strlen(mainSelection) - 1] = '\0';
    return mainSelection;
}

char* moveInput(){
    char *moveInput = malloc(MOVE_INPUT * sizeof(char));
    fgets(moveInput, MOVE_INPUT, stdin);
    moveInput[strlen(moveInput) - 1] = '\0';
    return moveInput;
}

//Minimise MOVE_INPUT to hold as few characters as possible
void multiPlayerSession(char *firstMoveColour){
    int turn;
    int firstMover;
    if(!strcmp(firstMoveColour, "w")){
        turn = white;
        firstMover = white;
    }
    else if(!strcmp(firstMoveColour, "b")){
        turn = black;
        firstMover = black;
    }
    else{
        printf("Invalid multi_player argument. See \"help\" for more details\n");
        return;
    }
    int halfPly = 1;
    T_chessboard currentState;
    initialiseRandomTest1(currentState);
    //initialiseBoard(currentState);
    char *multiPlayerInput;
    printBoard(firstMover, currentState);
    while(true){
        multiPlayerPrompt();
        multiPlayerInput = moveInput();
        //updateCurrentState(currentState, multiPlayerInput, turn);

        T_states *successorStates = generateSuccessorStates(turn, currentState);
        //printBoard(black, successorStates->states[15]);
        printBoards(turn, successorStates);
        //printBoard(white, successorStates->states[0]);

        //currentState = updateCurrentState(currentState, successorStates, multiPlayerInput);

        //printBoard(firstMover, currentState);
        //turn = alternatePlayer(turn);
    }
//    free(multiPlayerInput);
    return;
}

int main() {
    const char* selection1 = "mp";
    const char* selection2 = "sp";
    const char* selection3 = "exit";
    const char* selection4 = "help";
    const char* selection5 = "version";
    char *mainInput;
    char command[100];
    char argument1[100];
    landingMessage();
    while(true){
        mainPrompt();

        mainInput = mainSelection();
        sscanf(mainInput, "%s %s", &command, &argument1);
        if(!strcmp(mainInput, "\0")){
            ;
        }
        else if(!strcmp(command, selection1)){
            multiPlayerSession(argument1);
        }
        else if(!strcmp(mainInput, selection2)){
            printf("Single player selected - under construction\n");
        }
        else if(!strcmp(mainInput, selection3)){
            free(mainInput);
            exit(0);
        }
        else if(!strcmp(mainInput, selection4)){
            displayHelp();
        }
        else if(!strcmp(mainInput, selection5)){
            printf("Version: 1.1\nDate of version update: 2020/12/30\n");
        }
        else{
            printf("Invalid command - see help for valid commands\n");
        }
    }
    return 0;
}

void initialiseBoard(int chessboard [RANK_SIZE][FILE_SIZE]) {
    for(int i = 0; i < FILE_SIZE; i++){
        chessboard[1][i] = whitePawn;
    }
    chessboard[0][0] = whiteRook;
    chessboard[0][1] = whiteKnight;
    chessboard[0][2] = whiteBishop;
    chessboard[0][3] = whiteQueen;
    chessboard[0][4] = whiteKing;
    chessboard[0][5] = whiteBishop;
    chessboard[0][6] = whiteKnight;
    chessboard[0][7] = whiteRook;
    for(int i = 0; i < FILE_SIZE; i++){
        chessboard[6][i] = blackPawn;
    }
    chessboard[7][0] = blackRook;
    chessboard[7][1] = blackKnight;
    chessboard[7][2] = blackBishop;
    chessboard[7][3] = blackQueen;
    chessboard[7][4] = blackKing;
    chessboard[7][5] = blackBishop;
    chessboard[7][6] = blackKnight;
    chessboard[7][7] = blackRook;
    for(int i = 2; i < RANK_SIZE - 2; i++){
        for(int j = 0; j < FILE_SIZE; j++){
            chessboard[i][j] = empty;
        }
    }
    return;
}

char* specifyMove(){
    printf("White Move: ");
    //printf("\n\n");
    char *input = malloc(MAX_USER_INPUT + 1);
    //scanf("%[^\n]%*c", input);
    scanf("%s", input);
    return input;
}

bool isFileDifferent(T_position pos1, T_position pos2){
    if(pos1.f != pos2.f){
        return true;
    }
    return false;
}

bool isRankDifferent(T_position pos1, T_position pos2){
    if(pos1.r != pos2.r){
        return true;
    }
    return false;
}

void (*generator)(T_chessboard currentState, int rank, int file, T_states *consolidatedStates);

//generatorSelector(int ){
//
//
//}

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

char* toFileRank(T_positions p){
    char *result = malloc(2 * sizeof(char))
    //Do stuff with p;
    strcpy(result, "ab")
    return result;
}

char* disambiguator(T_chessboard c, T_position departure, T_position arrival){
    char* result = malloc(MAX_DISAMBIGUATOR * sizeof(char))
    int pieceType = c[departure.r][departure.f];
    T_positions *samePieces = whereAreSamePieces(pieceType, c);
    samePieces = whichSamePiecesMoveToArrival(c, samePieces, arrival);
    result = toFileRank(samePieces);
    return result;
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
    for(int i = 0; i < departures->freeIndex; i++){
        generator = generatorPtr(c, departures->positions[i]);


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

void consumeInput(char** input){

    return;
}

int pieceToBeMoved(char* input, int turn){
    int movedPiece;
    switch(input[0]){
        case 'B':
            turn == white ? (movedPiece = whiteBishop) : (movedPiece = blackBishop);
            break;
        case 'N':
            turn == white ? (movedPiece = whiteKnight) : (movedPiece = blackKnight);
            break;
        case 'R':
            turn == white ? (movedPiece = whiteRook) : (movedPiece = blackRook);
            break;
        case 'Q':
            turn == white ? (movedPiece = whiteQueen) : (movedPiece = blackQueen);
            break;
        case 'K':
            turn == white ? (movedPiece = whiteKing) : (movedPiece = blackKing);
            break;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
            turn == white ? (movedPiece = whitePawn) : (movedPiece = blackPawn);
            break;
    }
    return movedPiece;
}

void toListOfMoves(T_states *consolidatedStates){
    char** a = malloc(MOVE_INPUT * MAX_SUCCESSOR_STATES * sizeof(char));
    for(int i = 0; i < consolidatedStates->freeIndex; i++){
        consolidatedStates[i];
    }
}

void updateCurrentState(T_chessboard currentState, char* input, int turn){
    int p = pieceToBeMoved(input, turn);
    T_position potentialDepartures[MAX_POSITIONS][MAX_POSITIONS];
//    generatePotentialDepartures(p, currentState, potentialDepartures);
    //AT THIS POINT IN TIME, WE HAVE ALL DEPARTURES
    //Now, depending on the value of p, we generatePSuccessorStates for all the positions
    T_states *successorStates = generateSuccessorStates(turn, currentState);
    //possiblePieceStates;
//    convertListOfStatesToListOfInputs();

    //Do a bunch of stuff...

    currentState;
    return;
}

T_states *generateSuccessorStates(int playingAs, T_chessboard chessboard){
    int numOfStates = 0;
    T_chessboard *pawnSuccessorStates, *bishopSuccessorStates, *knightSuccessorStates, *rookSuccessorStates, *queenSuccessorStates, *kingSuccessorStates;
    T_states *consolidatedStates = malloc(sizeof(T_states));
    consolidatedStates->freeIndex = 0;
    T_position p;
    for (int i = 0; i < RANK_SIZE; i++){
        for(int j = 0; j < FILE_SIZE; j++){
            p.r = i;
            p.f = j;
            assert(playingAs == asWhite || playingAs == asBlack);
            if(playingAs == asWhite){
                switch (chessboard[i][j]){
                    case empty:
                        break;
                    case whitePawn:
                        generateWhitePawnSuccessorStates(chessboard, p, consolidatedStates);
                        //printf("White Pawn at %d %d: %d\n", i, j, consolidatedStates->freeIndex);
                        break;
                    case whiteBishop:
                        generateWhiteBishopSuccessorStates(chessboard, p, consolidatedStates);
                        //printf("White Bishop at %d %d: %d\n", i, j, consolidatedStates->freeIndex);
                        break;
                    case whiteKnight:
                        generateWhiteKnightSuccessorStates(chessboard, p, consolidatedStates);
                        //printf("White Knight at %d %d: %d\n", i, j, consolidatedStates->freeIndex);
                        break;
                    case whiteRook:
                        generateWhiteRookSuccessorStates(chessboard, p, consolidatedStates);
                        //printf("White Rook at %d %d: %d\n", i, j, consolidatedStates->freeIndex);
                        break;
                    case whiteQueen:
                        generateWhiteQueenSuccessorStates(chessboard, p, consolidatedStates);
                        //printf("White Queen at %d %d: %d\n", i, j, consolidatedStates->freeIndex);
                        break;
                    case whiteKing:
                        generateWhiteKingSuccessorStates(chessboard, p, consolidatedStates);
                        //printf("White King at %d %d: %d\n", i, j, consolidatedStates->freeIndex);
                        break;
                    default:
                        break;
                }
            }
            else if(playingAs == asBlack){
                switch(chessboard[i][j]){
                    case blackPawn:
                        generateBlackPawnSuccessorStates(chessboard, p, consolidatedStates);
                        //printf("Black Pawn at %d %d: %d\n", i, j, consolidatedStates->freeIndex);
                        break;
                    case blackBishop:
                        generateBlackBishopSuccessorStates(chessboard, p, consolidatedStates);
                        //printf("Black Bishop at %d %d: %d\n", i, j, consolidatedStates->freeIndex);
                        break;
                    case blackKnight:
                        generateBlackKnightSuccessorStates(chessboard, p, consolidatedStates);
                        //printf("Black Knight at %d %d: %d\n", i, j, consolidatedStates->freeIndex);
                        break;
                    case blackRook:
                        generateBlackRookSuccessorStates(chessboard, p, consolidatedStates);
                        //printf("Black Rook at %d %d: %d\n", i, j, consolidatedStates->freeIndex);
                        break;
                    case blackQueen:
                        generateBlackQueenSuccessorStates(chessboard, p, consolidatedStates);
                        //printf("Black Queen at %d %d: %d\n", i, j, consolidatedStates->freeIndex);
                        break;
                    case blackKing:
                        generateBlackKingSuccessorStates(chessboard, p, consolidatedStates);
                        //printf("Black King at %d %d: %d\n", i, j, consolidatedStates->freeIndex);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    //printBoards(playingAs, *consolidatedStates);
    return consolidatedStates;
}

void iterateChessBoard(int chessboard [RANK_SIZE][FILE_SIZE], bool turn){
    printf("%d", chessboard[0][0]);

}

void validBlackMoves(int chessboard [RANK_SIZE][FILE_SIZE]){

}

//void movePiece(int playingAs, int chessboard [RANK_SIZE][FILE_SIZE], char *moveString){
//    generateSuccessorStates(playingAs, chessboard);
//    return;
//}

void generateAllWhite(){

    return;
}
