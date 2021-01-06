#include "GlobalDeclarations.h"
#include <stdbool.h>
#include <stdio.h>

void TESTdoesDepartureGoToArrival(){
    T_chessboard c;
    initialiseRandomTest1(c);
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
