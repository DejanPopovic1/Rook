#include "changeState.hpp"
#include "ToAlgNotation.hpp"
#include "moveGeneration.h"
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;

StateChanger::StateChanger(){

}

StateChanger::StateChanger(T_boardState boardState){
    this->c = boardState;
}



T_boardState StateChanger::changeInputState(T_boardStates *bss, string usrInput){

}


vector<string> StateChanger::printValidMoves(){
    for(int i = 0; i < validMoves.size(); i++){
        cout << validMoves[i] << endl;
    }
}

//T_boardStates ChangeState::genSuccStates(){
//    genSuccStates();
//
//}




StateChanger::genListOfValidMoves(T_boardStates *bss){
    for(int i = 0; i < bss->fi; i++){
        validMoves[i] = toAlgebraicNotation(&(this->c), &(bss->bs[i]));
    }
}
