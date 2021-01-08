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
#include "testCases.h"
#include <stdlib.h>
#include "toAlgebraicNotation.h"

char* specifyMove();

T_states *generateSuccessorStates(int playingAs, T_chessboard chessboard);
T_moves* generateListOfMoves(T_chessboard, T_states *);

T_chessboard* nextState(T_chessboard *, char*, int);
T_chessboard* initialiseBoard();

char* moveInput();

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

int playingAsPrompt(){
    char playingAs[PLAYING_AS_INPUT];
    while(true){
        printf("Rook > Multiplayer Session > Select colour (w for white / b for black): \n");
        scanf("%s", playingAs);
        if(!strcmp(playingAs, "w")){
            return asWhite;
        }
        else if(!strcmp(playingAs, "b")){
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
    T_chessboard *c;
    c = initialiseBoard();
    char *multiPlayerInput;
    while(true){
        //printf("Half Ply: %d\n", halfPly);
        printBoard(firstMover, *c);
        T_states* successorStates = generateSuccessorStates(asWhite, *c);
        printMoves(generateListOfMoves(*c, successorStates));
        multiPlayerPrompt();
        multiPlayerInput = moveInput();
        c = nextState(c, multiPlayerInput, white);
       //printBoardsAndAlgNot(*c, asWhite, successorStates);
        halfPly++;
    }
    return;
}

void testCases(){
    //TESTformatFileDisplay();
    //TESTdisambiguator();
    return;
}

int main() {
    testCases();
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
        sscanf(mainInput, "%s %s", command, argument1);
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

T_chessboard* initialiseBoard(){
    T_chessboard *result = malloc(sizeof(T_chessboard));
    for(int i = 0; i < FILE_SIZE; i++){
        (*result)[1][i] = whitePawn;
    }
    (*result)[0][0] = whiteRook;
    (*result)[0][1] = whiteKnight;
    (*result)[0][2] = whiteBishop;
    (*result)[0][3] = whiteQueen;
    (*result)[0][4] = whiteKing;
    (*result)[0][5] = whiteBishop;
    (*result)[0][6] = whiteKnight;
    (*result)[0][7] = whiteRook;
    for(int i = 0; i < FILE_SIZE; i++){
        (*result)[6][i] = blackPawn;
    }
    (*result)[7][0] = blackRook;
    (*result)[7][1] = blackKnight;
    (*result)[7][2] = blackBishop;
    (*result)[7][3] = blackQueen;
    (*result)[7][4] = blackKing;
    (*result)[7][5] = blackBishop;
    (*result)[7][6] = blackKnight;
    (*result)[7][7] = blackRook;
    for(int i = 2; i < RANK_SIZE - 2; i++){
        for(int j = 0; j < FILE_SIZE; j++){
            (*result)[i][j] = empty;
        }
    }
    return result;
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

T_moves* generateListOfMoves(T_chessboard c, T_states *ss){
    T_moves *a = malloc(sizeof(T_moves));
    a->freeIndex = 0;
    for(int i = 0; i < ss->freeIndex; i++){
        printf("%d ", i);
        //toAlgebraicNotation(c, ss->states[i]);
        //printf("toAlgNotation of %d complete.. ", i);
        a->moves[i] = toAlgebraicNotation(c, ss->states[i]);
        (a->freeIndex)++;
    }
    printf("\n");
    return a;
}

T_chessboard* nextState(T_chessboard *c, char* input, int turn){
    T_chessboard *result = malloc(sizeof(T_chessboard));
    T_states *successorStates = generateSuccessorStates(turn, *c);
    T_moves *a = generateListOfMoves(*c, successorStates);
    for(int i = 0; i < a->freeIndex; i++){
        if(!strcmp(a->moves[i], input)){
            T_chessboard *p = malloc(sizeof(T_chessboard));
            p = &(successorStates->states[i]);
            return p;
        }
    }
    printf("Invalid move\n");
    return c;
}

T_states *generateSuccessorStates(int playingAs, T_chessboard chessboard){
    int numOfStates = 0;
    //T_chessboard *pawnSuccessorStates, *bishopSuccessorStates, *knightSuccessorStates, *rookSuccessorStates, *queenSuccessorStates, *kingSuccessorStates;
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

void generateAllWhite(){

    return;
}
