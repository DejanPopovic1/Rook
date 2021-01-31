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
#include "movementRules.h"
#include "moveGenerator.h"
#include "bitUtilities.h"

void mainPrompt();
void multiPlayerPrompt();
char* mainSelection();
char* moveInput();
void multiPlayerSession(char *playerColourInput);
T_chessboard* initialiseBoard();
T_moves* generateListOfMoves(T_chessboard c, T_states *ss);
bool nextState(T_chessboard **c, char* input, int turn);
T_states *generateSuccessorStates(int playingAs, T_chessboard chessboard);

void mainPrompt(){
    printf("Rook>");
    return;
}

void multiPlayerPrompt(){
    printf(" -> ");
    return;
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
//Need to NOT advance the turn colour when a wrong input is made
void multiPlayerSession(char *playerColourInput){
    if(strcmp(playerColourInput, "w") && strcmp(playerColourInput, "b")){
        printf("Invalid multi_player argument. See \"help\" for more details\n");
        return;
    }
    int playerColour;
    if(!strcmp(playerColourInput, "w")){
        playerColour = asWhite;
    }
    else if(!strcmp(playerColourInput, "b")){
        playerColour = asBlack;
    }
    //printf("%d\n", playerColour);
    int halfPly = 1;
    int colourTurn;
    T_chessboard *c;
    c = initialiseBoard();
    char *multiPlayerInput;

    while(true){
        colourTurn = whosTurn(halfPly);
        printPlayerTurn(halfPly);
        printBoard(asWhite, *c);
        T_states *wS = generateSuccessorStates(asWhite, *c);
        T_states *bS = generateSuccessorStates(asBlack, *c);
        T_moves *mW = generateListOfMoves(c, wS);
        T_moves *mB = generateListOfMoves(c, bS);
        printMoves(mW);
        printMoves(mB);
        //printBoards(playerColour, successorStates);
        multiPlayerPrompt();
        multiPlayerInput = moveInput();
        if(nextState(&c, multiPlayerInput, colourTurn)){
            halfPly++;
        }
    }
    return;
}

//BoardStates must be malloced so that they may be initialised when they are created. Initialisation is not the job of the caller
void testCases(){
    createRays();
    T_boardState c = initialiseBoardState();
    //printTBitboard(c.bBishop);
    T_boardStates *bss = initialiseStates();
    printState(c);
    T_bitboard** bbptr = createRays();
    //genWPawnsSuccStates(bss, &c, bbptr);
    //genPiecesSuccStates(bss, &c, bbptr, whiteBishop);
    genPiecesSuccStates(bss, &c, bbptr, whiteRook);
        //genPiecesSuccStates(bss, &c, bbptr, whiteBishop);
    //printTBitboard(bbptr[7][36]);

    printStates(bss);
    //printTBitboard(c.bKing);
    //printState(c);
    getch();
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

T_moves* generateListOfMoves(T_chessboard c, T_states *ss){
    T_moves *a = malloc(sizeof(T_moves));
    a->freeIndex = 0;
    for(int i = 0; i < ss->freeIndex; i++){
        a->moves[i] = toAlgebraicNotation(c, ss->states[i]);
        (a->freeIndex)++;
    }
    return a;
}

bool nextState(T_chessboard **c, char* input, int turn){
    T_states *successorStates = generateSuccessorStates(turn, **c);
    T_moves *a = generateListOfMoves(**c, successorStates);
    for(int i = 0; i < a->freeIndex; i++){
        if(!strcmp(a->moves[i], input)){
            T_chessboard *result = malloc(sizeof(T_chessboard));
            result = &(successorStates->states[i]);
            free(*c);
            *c = result;
            return true;
        }
    }
    printf("Invalid move\n");
    return false;
}

//T_boardStates generateSuccStates(T_boardState b){
//    T_boardStates result;
//    if(whosTurn(b.ply) == whiteTurn){
//        genWPawnSuccStates(b, &result);
//        genWBishopSuccStates(b, &result);
//        genWKnightSuccStates(b, &result);
//        genWRookSuccStates(b, &result);
//        genWQueenSuccStates(b, &result);
//        genWKingSuccStates(b, &result);
//        return result;
//    }
//    else if(whosTurn(b.ply) == blackTurn){
//        genBPawnSuccStates(b, &result);
//        genBBishopSuccStates(b, &result);
//        genBKnightSuccStates(b, &result);
//        genBRookSuccStates(b, &result);
//        genBQueenSuccStates(b, &result);
//        genBKingSuccStates(b, &result);
//        return result;
//    }
//}


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
