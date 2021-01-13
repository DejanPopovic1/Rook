#include "GlobalDeclarations.h"
#include <stdbool.h>
#include <stdio.h>
#include "state.h"
#include "generateSlideMoves.h"

void TESTprintBitboard(){
    T_bitboard a = 5;
    printTBitboard(a);
    return;
}

void TESTmakeRaysNE(){
    T_bitboard *a1_ne = makeRays(&castNE, 0);
    T_bitboard *b1_ne = makeRays(&castNE, 1);
    T_bitboard *c1_ne = makeRays(&castNE, 2);
    T_bitboard *d1_ne = makeRays(&castNE, 3);
    T_bitboard *e1_ne = makeRays(&castNE, 4);
    T_bitboard *f1_ne = makeRays(&castNE, 5);
    T_bitboard *g1_ne = makeRays(&castNE, 6);
    T_bitboard *h1_ne = makeRays(&castNE, 7);
    T_bitboard *a2_ne = makeRays(&castNE, 8);
    T_bitboard *b2_ne = makeRays(&castNE, 9);
    T_bitboard *c2_ne = makeRays(&castNE, 10);
    T_bitboard *d2_ne = makeRays(&castNE, 11);
    T_bitboard *e2_ne = makeRays(&castNE, 12);
    T_bitboard *f2_ne = makeRays(&castNE, 13);
    T_bitboard *g2_ne = makeRays(&castNE, 14);
    T_bitboard *h2_ne = makeRays(&castNE, 15);



    T_bitboard *d4_ne = makeRays(&castNE, 29);
    T_bitboard *d4_e = makeRays(&castE, 29);
    T_bitboard *d4_se = makeRays(&castSE, 29);
//    T_bitboard *a1_ne = makeRaysNE(0);
//    T_bitboard *b1_ne = makeRaysNE(1);
//    T_bitboard *c1_ne = makeRaysNE(2);
//    T_bitboard *d1_ne = makeRaysNE(3);
//    T_bitboard *e1_ne = makeRaysNE(4);
//    T_bitboard *f1_ne = makeRaysNE(5);
//    T_bitboard *g1_ne = makeRaysNE(6);
//    T_bitboard *h1_ne = makeRaysNE(7);
//    T_bitboard *a2_ne = makeRaysNE(8);
//    T_bitboard *b2_ne = makeRaysNE(9);
//    T_bitboard *c2_ne = makeRaysNE(10);
//    T_bitboard *d2_ne = makeRaysNE(11);
//    T_bitboard *e2_ne = makeRaysNE(12);
//    T_bitboard *f2_ne = makeRaysNE(13);
//    T_bitboard *g2_ne = makeRaysNE(14);
//    T_bitboard *h2_ne = makeRaysNE(15);
//    T_bitboard *a3_ne = makeRaysNE(16);
//    T_bitboard *b3_ne = makeRaysNE(17);
//    T_bitboard *c3_ne = makeRaysNE(18);
//    T_bitboard *d3_ne = makeRaysNE(19);
//    T_bitboard *e3_ne = makeRaysNE(20);
//    T_bitboard *f3_ne = makeRaysNE(21);
//    T_bitboard *g3_ne = makeRaysNE(22);
//    T_bitboard *h3_ne = makeRaysNE(23);
//    T_bitboard *a4_ne = makeRaysNE(24);
//    T_bitboard *b4_ne = makeRaysNE(25);
//    T_bitboard *c4_ne = makeRaysNE(26);
//    T_bitboard *d4_ne = makeRaysNE(27);
//    T_bitboard *e4_ne = makeRaysNE(28);
//    T_bitboard *f4_ne = makeRaysNE(29);
//    T_bitboard *g4_ne = makeRaysNE(30);
//    T_bitboard *h4_ne = makeRaysNE(31);
//    T_bitboard *a5_ne = makeRaysNE(32);
//    T_bitboard *b5_ne = makeRaysNE(33);
//    T_bitboard *c5_ne = makeRaysNE(34);
//    T_bitboard *d5_ne = makeRaysNE(35);
//    T_bitboard *e5_ne = makeRaysNE(36);
//    T_bitboard *f5_ne = makeRaysNE(37);
//    T_bitboard *g5_ne = makeRaysNE(38);
//    T_bitboard *h5_ne = makeRaysNE(39);
//    T_bitboard *a6_ne = makeRaysNE(40);
//    T_bitboard *b6_ne = makeRaysNE(41);
//    T_bitboard *c6_ne = makeRaysNE(42);
//    T_bitboard *d6_ne = makeRaysNE(43);
//    T_bitboard *e6_ne = makeRaysNE(44);
//    T_bitboard *f6_ne = makeRaysNE(45);
//    T_bitboard *g6_ne = makeRaysNE(46);
//    T_bitboard *h6_ne = makeRaysNE(47);
//    T_bitboard *a7_ne = makeRaysNE(48);
//    T_bitboard *b7_ne = makeRaysNE(49);
//    T_bitboard *c7_ne = makeRaysNE(50);
//    T_bitboard *d7_ne = makeRaysNE(51);
//    T_bitboard *e7_ne = makeRaysNE(52);
//    T_bitboard *f7_ne = makeRaysNE(53);
//    T_bitboard *g7_ne = makeRaysNE(54);
//    T_bitboard *h7_ne = makeRaysNE(55);
//    T_bitboard *a8_ne = makeRaysNE(56);
//    T_bitboard *b8_ne = makeRaysNE(57);
//    T_bitboard *c8_ne = makeRaysNE(58);
//    T_bitboard *d8_ne = makeRaysNE(59);
//    T_bitboard *e8_ne = makeRaysNE(60);
//    T_bitboard *f8_ne = makeRaysNE(61);
//    T_bitboard *g8_ne = makeRaysNE(62);
//    T_bitboard *h8_ne = makeRaysNE(63);
}

void TESTprintBitboardNumber(){
    T_bitboard a = 5;
    printTBitboardNumber(a);
    return;
}

void TESTformatFileDisplay(){
    printf("%c\n", formatFileDisplay(0));
    return;
}

void TESTcopyState(){
    T_chessboard *des = initialiseBoard1();
    T_chessboard *src = initialiseBoard2();
    printBoard(asWhite, *des);
    printBoard(asWhite, *src);
    copyState(des, *src);
    printBoard(asWhite, *des);
    return;
}

void TESTdoesDepartureGoToArrival(){
    T_chessboard c;
    initialiseRandomTest1(c);
    printBoard(whiteTurn, c);
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
    initialiseDisambiguator(c);
    printBoard(whiteTurn, c);
    T_position d;
    T_position a1;
    T_position a2;
    d.r = 3;
    d.f = 3;
    a1.r = 4;
    a1.f = 5;
    //a2.r = 4;
    //a2.f = 7;
    printf("Test 1: %s\n", disambiguate(c, d, a1));
    //printf("Test 2: %s\n", disambiguator(c, d, a2));
}
