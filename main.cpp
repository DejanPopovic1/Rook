#include "searchTree.hpp"
#include "state.hpp"
#include "moveGeneration.hpp"
#include "output.hpp"
#include "gameState.hpp"
#include "moveRules.hpp"
#include "testInitialisations.hpp"
#include "heuristics.hpp"
#include "bitUtilities.hpp"
#include "keyUtilities.hpp"

#include <iostream>
#include <cstdlib>

#define MAIN_SELECTION 100
#define MOVE_INPUT 100

using namespace std;

//convert idiomatic c into idiomatic c++

void mainPrompt(){
    printf("Rook>");
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
    GameState sc(s, playerColour);
    std::string usrInput;
    T_boardStates *bss = initialiseStates();
    T_boardState c;
    while(!sc.isCheckMate() && !sc.isStaleMate() && !sc.isThreeFoldRepetition() && !sc.isFiftyMoveRule()){
        //sc.printGameState();
        sc.moveCycle();
    }
    sc.printGameState();
    std::cin.get();
    return;
}

void test(){
    T_Node head, h2, h3, h4;
    head.b = initialiseBoardState();
    h2.b = CMinitialiseBoardState();
    h3.b = SMinitialiseBoardState();
    h4.b = PPinitialiseBoardState();
    int level = 0;
    T_Node *headPtr = &head;

    T_Node *test = createNode();
//    printState(head.b);
//    printState(h2.b);
//    printState(h3.b);
//    printState(h4.b);
//    std::cout << evaluateBoard(&head.b) << endl;
//    std::cout << evaluateBoard(&h2.b)<< endl;
//    std::cout << evaluateBoard(&h3.b)<< endl;
//    std::cout << evaluateBoard(&h4.b)<< endl;
    std::cout << generateTreeNode(&headPtr, level) << std::endl;
    getchar();
}

int main(){
    test();
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
        //printf("MAIN LOOP\n\n");
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
