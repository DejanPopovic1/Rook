#include "StateChanger.hpp"
#include "ToAlgNotation.hpp"
#include "output.h"

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

T_boardState StateChanger:: getState(){
    return this->c;
}

StateChanger::StateChanger(T_boardState boardState){
    this->c = boardState;
    genSuccStates(&(this->ss), &(this->c));
    //printState(ss.bs[1]);
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
        string s = toAlgebraicNotation(&(this->c), &(this->ss.bs[i]));
        this->validMoves.push_back(s);
    }
}
