#include "state.hpp"
#include "moveGeneration.hpp"
#include "output.hpp"
#include "stateChanger.hpp"
#include <iostream>

#include "bitUtilities.hpp"

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
    T_boardStates *bss = initialiseStates();
    T_boardState c;
    while(true){
        sc.printGameState();
        std::cout << std::endl;
        //sc.printSuccStates();
        //printState(sc.getState(), playerColour);
        sc.printValidMoves();
        multiPlayerPrompt();
        std::cin >> usrInput;
        sc.changeState(usrInput);
        std::cin.get();
     }
     return;
}

void test(){
    //std::cin.get();
    T_bitboard test1 = 0;
    setBit(&test1, 58);
    setBit(&test1, 59);
    std::cout << test1 << std::endl;
    T_bitboard test2 = 0;
    setBit(&test2, 2);
    setBit(&test2, 3);
    std::cout << test2 << std::endl;

       printTBitboard(BLACK_KINGSIDE_PASS);
   printTBitboard(BLACK_QUEENSIDE_PASS);
   printTBitboard(WHITE_KINGSIDE_PASS);
   printTBitboard(WHITE_QUEENSIDE_PASS);
//    T_bitboard test1 = 0;
//    setBit(&test1, 51);
//    setBit(&test1, 52);
//    setBit(&test1, 44);
//    setBit(&test1, 45);
//    setBit(&test1, 46);
//    setBit(&test1, 47);
//    setBit(&test1, 55);
//    T_bitboard test2 = 0;
//    setBit(&test2, 48);
//    setBit(&test2, 49);
//    setBit(&test2, 41);
//    setBit(&test2, 42);
//    setBit(&test2, 43);
//    setBit(&test2, 44);
//    setBit(&test2, 52);
//    setBit(&test2, 53);
//    T_bitboard test3 = 0;
//    setBit(&test3, 11);
//    setBit(&test3, 12);
//    setBit(&test3, 20);
//    setBit(&test3, 21);
//    setBit(&test3, 22);
//    setBit(&test3, 23);
//    setBit(&test3, 15);
//    T_bitboard test4 = 0;
//    setBit(&test4, 8);
//    setBit(&test4, 9);
//    setBit(&test4, 17);
//    setBit(&test4, 18);
//    setBit(&test4, 19);
//    setBit(&test4, 20);
//    setBit(&test4, 12);
//    setBit(&test4, 13);
//
//    std::cout << test1 << std::endl;
//        std::cout << test2 << std::endl;
//            std::cout << test3 << std::endl;
//                std::cout << test4 << std::endl;
//   printTBitboard(BLACK_KINGSIDE_ATTACKING);
//   printTBitboard(BLACK_QUEENSIDE_ATTACKING);
//   printTBitboard(WHITE_KINGSIDE_ATTACKING);
//   printTBitboard(WHITE_QUEENSIDE_ATTACKING);
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
