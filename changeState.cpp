#include "changeState.hpp"
#include "ToAlgNotation.hpp"

extern "C"{
    void genSuccStates(T_boardStates *dst, const T_boardState *b);
}

#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;

StateChanger::StateChanger(){

}

StateChanger::StateChanger(T_boardState boardState){
    this->c = boardState;
    genSuccStates(&(this->ss), &(this->c));
    genListOfValidMoves();
}

void StateChanger::changeInputState(string usrInput){
    for(int i = 0; i < this->ss.fi; i++){
        if(validMoves[i] == usrInput){
            this->c = this->ss.bs[i];
            return;
        }
    }
    this->c;
    cout << "Invalid move\n";
    return ;
}

vector<string> StateChanger::printValidMoves(){
    for(int i = 0; i < validMoves.size(); i++){
        cout << validMoves[i] << endl;
    }
}

StateChanger::genListOfValidMoves(){
    for(int i = 0; i < this->ss.fi; i++){
        this->validMoves[i] = toAlgebraicNotation(&(this->c), &(this->ss.bs[i]));
    }
}
