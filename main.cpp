#include "state.hpp"
#include "moveGeneration.hpp"
#include "output.hpp"
#include "stateChanger.hpp"
#include <iostream>

#define MAIN_SELECTION 100
#define MOVE_INPUT 100

//convert idiomatic c into idiomatic c++

void mainPrompt(){
    printf("Rook>");
    return;
}

void multiPlayerPrompt(){
    printf(" -> ");
    return;
}

char* mainSelection(){
    char *mainSelection = (char*)malloc(MAIN_SELECTION * sizeof(char));
    fgets(mainSelection, MAIN_SELECTION, stdin);
    mainSelection[strlen(mainSelection) - 1] = '\0';
    return mainSelection;
}

char* moveInput(){
    char *moveInput = (char*)malloc(MOVE_INPUT * sizeof(char));
    fgets(moveInput, MOVE_INPUT, stdin);
    moveInput[strlen(moveInput) - 1] = '\0';
    return moveInput;
}

//Minimise MOVE_INPUT to hold as few characters as possible
//Need to NOT advance the turn colour when a wrong input is made
//Rename player colour to playingAs
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
    T_boardState s = initialiseBoardState();
    StateChanger sc(s, playerColour);
    std::string usrInput;
    //printState(sc.getState());
    while(true){
        printState(sc.getState());
        sc.printValidMoves();
        multiPlayerPrompt();
        std::cin >> usrInput;
        sc.changeState(usrInput);

        //printState(sc.getState());
       ///////////printState(sc.getState());
        //printState(sc.getState());

        std::cin.get();
     }

    //printStates(bss);



//    int halfPly = 1;
//    int colourTurn;
//    T_chessboard *c;
//    c = initialiseBoard();
//    char *multiPlayerInput;
//
//    while(true){
//        colourTurn = whosTurn(halfPly);
//        printPlayerTurn(halfPly);
//        printBoard(asWhite, *c);
//        T_states *wS = generateSuccessorStates(asWhite, *c);
//        T_states *bS = generateSuccessorStates(asBlack, *c);
//        T_moves *mW = generateListOfMoves(c, wS);
//        T_moves *mB = generateListOfMoves(c, bS);
//        printMoves(mW);
//        printMoves(mB);
//        multiPlayerPrompt();
//        multiPlayerInput = moveInput();
//        if(nextState(&c, multiPlayerInput, colourTurn)){
//            halfPly++;
//        }
//    }
    return;
}


int main(){
//    T_boardState s = initialiseBoardState();
//    T_boardStates *bss = initialiseStates();
//    genSuccStates(bss, &s);
//    printStates(bss);
//    return 0;
//    testCases();
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
