#include "GlobalDeclarations.h"
#include <stdbool.h>
#include <stdio.h>
#include "state.h"
#include "moveRules.h"

void TESTprintBitboard(){
    T_bitboard a = 5;
    printTBitboard(a);
    return;
}

void TESTcreateAndPrintRays(){
    createRays();
    return;
}

void TESTprintBitboardNumber(){
    T_bitboard a = 5;
    printTBitboardNumber(a);
    return;
}

//void TESTformatFileDisplay(){
//    printf("%c\n", formatFileDisplay(0));
//    return;
//}

void TESTcopyState(){
    T_chessboard *des = initialiseBoard1();
    T_chessboard *src = initialiseBoard2();
    printBoard(asWhite, *des);
    printBoard(asWhite, *src);
    copyState(des, *src);
    printBoard(asWhite, *des);
    return;
}

//void TESTdoesDepartureGoToArrival(){
//    T_chessboard c;
//    initialiseRandomTest1(c);
//    printBoard(whiteTurn, c);
//    T_position d;
//    T_position a;
//    d.r = 5;
//    d.f = 3;
//    a.r = 4;
//    a.f = 4;
//    bool b = doesDepartureGoToArrival(c, d, a);
//    if(b){
//        printf("True\n");
//    }
//    else if(!b){
//        printf("False\n");
//    }
//    return;
//}

//void TESTdisambiguator(){
//    T_chessboard c;
//    initialiseDisambiguator(c);
//    printBoard(whiteTurn, c);
//    T_position d;
//    T_position a1;
//    T_position a2;
//    d.r = 3;
//    d.f = 3;
//    a1.r = 4;
//    a1.f = 5;
//    //a2.r = 4;
//    //a2.f = 7;
//    printf("Test 1: %s\n", disambiguate(c, d, a1));
//    //printf("Test 2: %s\n", disambiguator(c, d, a2));
//}
