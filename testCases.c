#include "GlobalDeclarations.h"
#include <stdbool.h>
#include <stdio.h>

void TESTdoesDepartureGoToArrival(){
    T_chessboard c;
    initialiseRandomTest1(c);
    printBoard(white, c);
    T_position d;
    T_position a;
    d.r = 5;
    d.f = 3;
    a.r = 4;
    a.f = 4;
    bool b = doesDepartureGoToArrival(c, d, a);
    if(b){
        printf("True\n");
    }
    else if(!b){
        printf("False\n");
    }
    return;
}

void TESTdisambiguator(){
    T_chessboard c;
    initialiseRandomTest1(c);
    printBoard(white, c);
    T_position d;
    T_position a1;
    T_position a2;
    d.r = 3;
    d.f = 5;
    a1.r = 2;
    a1.f = 7;
    a2.r = 4;
    a2.f = 7;
    printf("Test 1: %s\n", disambiguator(c, d, a1));
    printf("Test 2: %s\n", disambiguator(c, d, a2));
}
