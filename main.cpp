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
    GameState sc(LKinitialiseBoardState(), playerColour);
    string usrInput;
    while(true){
        sc.printGameState();
        do{
            multiPlayerPrompt();
            std::cin >> usrInput;
        }while(!sc.changeState(usrInput));
    }
    return;
}

void singlePlayerSession(char *playerColourInput){
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
    GameState sc(LKinitialiseBoardState(), playerColour);
    string usrInput;
    while(true){
        sc.printGameState();
        do{
            multiPlayerPrompt();
            std::cin >> usrInput;
        }while(!sc.changeState(usrInput));
    }
    return;
}

int main(){
    string selection1 = "mp";
    string selection2 = "sp";
    string selection3 = "exit";
    string selection4 = "help";
    string selection5 = "version";
    string mainInputString;
    string commandString;
    string argument1String;
    char mainInput[100];
    char command[100];
    char argument1[100];
    landingMessage();
    while(true){
        mainPrompt();
        fgets(mainInput, 100, stdin);
        mainInput[strlen(mainInput) - 1] = '\0';
        sscanf(mainInput, "%s %s", command, argument1);
        argument1String = argument1;
        commandString = command;
        if(!strcmp(mainInput, "\0")){
            ;
        }
        else if(commandString == selection1){
            multiPlayerSession(argument1);
        }
        else if(commandString == selection2){
            singlePlayerSession(argument1);
        }
        else if(!strcmp(mainInput, selection3.c_str())){
            exit(0);
        }
        else if(!strcmp(mainInput, selection4.c_str())){
            displayHelp();
        }
        else if(!strcmp(mainInput, selection5.c_str())){
                displayVersion();
        }
        else{
            invalidAlert();
        }
    }
    return 0;
}
