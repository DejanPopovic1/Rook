#include "StateChanger.hpp"
#include "ToAlgNotation.hpp"
#include "output.hpp"
#include "moveGeneration.hpp"
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;

StateChanger::StateChanger(){

}

T_boardState StateChanger::getState(){
    return (this->c);
}
//INCORPORATE FIRST COMMENT AS ITS ABSENCE LEADS TO A BUG
StateChanger::StateChanger(T_boardState boardState){
    this->c = boardState;
    this->ss = initialiseStates();
    genSuccStates(this->ss, &(this->c));
    genListOfValidMoves();
}

void StateChanger::changeState(string usrInput){
    for(int i = 0; i < this->ss->fi; i++){
        if(validMoves[i] == usrInput){
            this->c = this->ss->bs[i];
            return;
        }
    }
    this->c;
    cout << "Invalid move\n";
    return ;
}

void StateChanger::printValidMoves(){
    for(int i = 0; i < validMoves.size(); i++){
        cout << validMoves[i] << endl;
    }
}

StateChanger::genListOfValidMoves(){
    string s;
    for(int i = 0; i < this->ss->fi; i++){
        s = toAlgebraicNotation(&(this->c), &(this->ss->bs[i]));
        this->validMoves.push_back(s);
    }
    for(int i = 0; i < this->validMoves.size(); i++){
        cout << validMoves[i] << endl;
    }
}
