#include "state.h"

genWPawnSuccStates(T_boardStates *dst, const T_boardState *b){
    T_boardState src;
    //MOVE UP ONE
    //If(isUpEmpty && !isSecondLastRow)





    src.wPawn = 0;
    addState(dst, &src);
//    c->wPawn = 0;
    //MOVE UP TWO
    //CAPTURE LEFT
    //CAPTURE RIGHT
    //EN PASSANT LEFT
    //EN PASSANT RIGHT
    //PROMOTIONS
        //BISHOP
        //KNIGHT
        //ROOK
        //QUEEN

}

genWBishopSuccStates(T_boardState c, T_boardStates *ss){
    //Generate Pawn Moves
}

genWKnightSuccStates(T_boardState c, T_boardStates *ss){
    //Generate Pawn Moves
}

genWRookSuccStates(T_boardState c, T_boardStates *ss){

}

genWQueenSuccStates(T_boardState c, T_boardStates *ss){

}

genWKingSuccStates(T_boardState c, T_boardStates *ss){

}

genBPawnSuccStates(T_boardState c, T_boardStates *ss){


}

genBBishopSuccStates(T_boardState c, T_boardStates *ss){

}

genBKnightSuccStates(T_boardState c, T_boardStates *ss){

}

genBRookSuccStates(T_boardState c, T_boardStates *ss){

}

genBQueenSuccStates(T_boardState c, T_boardStates *ss){

}

genBKingSuccStates(T_boardState c, T_boardStates *ss){


}
