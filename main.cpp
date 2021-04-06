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
#include <algorithm>

#define INPUT_LIMIT 100

using namespace std;

void multiPlayerSession(string playerColourInput){
    if(playerColourInput != "w" && playerColourInput != "b"){
        printInvalidArgumentAlert();
        return;
    }
    int playerColour;
    if(playerColourInput == "w"){
        playerColour = asWhite;
    }
    else if(playerColourInput == "b"){
        playerColour = asBlack;
    }
    GameState sc(initialiseBoardState(), playerColour);
    string usrInput;
    T_boardState s;
    vector<string> l;
    sc.printGameState();
    while(!sc.isCheckMate() && !sc.isStaleMate() && !sc.isFiveFoldRepetition() && !sc.isSeventyFiveMoveRule()){
        s = sc.getState();
        l = sc.genListOfValidNotations(s);
        multiPlayerPrompt();
        cin >> usrInput;
        while(!(find(l.begin(), l.end(), usrInput) != l.end())){
            multiPlayerPrompt();
            cin >> usrInput;
        }
        sc.changeState(usrInput);
        sc.printGameState();
    }
    cin.get();
    return;
}

void singlePlayerSession(string playerColourInput){
    if(playerColourInput != "w" && playerColourInput != "b"){
        printInvalidArgumentAlert();
        return;
    }
    int playerColour;
    if(playerColourInput == "w"){
        playerColour = asWhite;
    }
    else if(playerColourInput == "b"){
        playerColour = asBlack;
    }
    GameState sc(LKinitialiseBoardState(), playerColour);
    string usrInput;
    T_boardState s;
    vector<string> l;
    sc.printGameState();
    while(true){
        if(sc.isCheckMate() || sc.isStaleMate() || sc.isFiveFoldRepetition() || sc.isSeventyFiveMoveRule()){
            break;
        }
        s = sc.getState();
        l = sc.genListOfValidNotations(s);
        multiPlayerPrompt();
        cin >> usrInput;
        while(!(find(l.begin(), l.end(), usrInput) != l.end())){
            multiPlayerPrompt();
            cin >> usrInput;
        }
        sc.changeState(usrInput);
        sc.printGameState();
        if(sc.isCheckMate() || sc.isStaleMate() || sc.isFiveFoldRepetition() || sc.isSeventyFiveMoveRule()){
            break;
        }
        sc.changeState(sc.engineMove(sc.getState()));
        sc.printGameState();
    }
    cin.get();
    return;
}

void test(){
    //printMoveRuleValues();
}

int main(){
    //test();
    string selection1 = "mp";
    string selection2 = "sp";
    string selection3 = "exit";
    string selection4 = "help";
    string selection5 = "version";
    string mainInputString;
    string commandString;
    string argument1String;
    char mainInput[INPUT_LIMIT];
    char command[INPUT_LIMIT];
    char argument1[INPUT_LIMIT];
    landingMessage();
    while(true){
        mainPrompt();
        fgets(mainInput, INPUT_LIMIT, stdin);
        mainInput[strlen(mainInput) - 1] = '\0';
        sscanf(mainInput, "%s %s", command, argument1);
        argument1String = argument1;
        commandString = command;
        if(!strcmp(mainInput, "\0")){
            ;
        }
        else if(commandString == selection1){
            multiPlayerSession(argument1String);
        }
        else if(commandString == selection2){
            singlePlayerSession(argument1String);
        }
        else if(!strcmp(mainInput, selection3.c_str())){
            break;
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
