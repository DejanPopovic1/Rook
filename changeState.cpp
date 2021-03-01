#include "changeState.hpp"
#include "ToAlgNotation.hpp"
#include "moveGeneration.h"
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;

ChangeState::ChangeState(){

}

ChangeState::ChangeState(T_boardState boardState){
    this->c = boardState;
}



T_boardState ChangeState::changeInputState(T_boardStates *bss, string usrInput){

}


vector<string> ChangeState::printValidMoves(){
    for(int i = 0; i < validMoves.size(); i++){
        cout << validMoves[i] << endl;
    }
}

//T_boardStates ChangeState::genSuccStates(){
//    genSuccStates();
//
//}




ChangeState::genListOfValidMoves(T_boardStates *bss){
    for(int i = 0; i < bss->fi; i++){
        validMoves[i] = toAlgebraicNotation(&(this->c), &(bss->bs[i]));
    }
}
