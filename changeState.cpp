#include "changeState.hpp"
#include "ToAlgNotation.hpp"

extern "C"{
    #include "moveGeneration.h"
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

T_boardState StateChanger::changeInputState(string usrInput){
    for(int i = 0; i < this->ss.fi; i++){
        if(validMoves[i] == usrInput){
            this->c = this->ss.bs[i];
        }
    }
    return this->c;
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
