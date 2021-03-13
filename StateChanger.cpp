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
StateChanger::StateChanger(T_boardState boardState, bool pA){
    this->playingAs = pA;
    this->c = boardState;
    this->ss = initialiseStates();
    genSuccStates(this->ss, &(this->c));
    genListOfValidMoves();
}

void StateChanger::changeState(string usrInput){
    for(int i = 0; i < this->ss->fi; i++){
        if(validMoves[i] == usrInput){
            this->c = this->ss->bs[i];
            (this->c.whosTurn)++;
            this->ss = initialiseStates();
            genSuccStates(this->ss, &(this->c));
            this->validMoves.clear();
            genListOfValidMoves();
            gameMoves.push_back(usrInput);
            if(isCheckMate()){
                this->c.whosTurn ? gameMoves.push_back("1 - 0") : gameMoves.push_back("0 - 1");
            }
            else if(isStaleMate()){
                gameMoves.push_back("1/2 - 1/2");
            }
            return;
        }
    }
    cout << "Invalid move\n";
    return ;
}

bool StateChanger::isCheckMate(){
    return isStateInCheck() && !isValidMoves();
}

bool StateChanger::isStaleMate(){
    return !isStateInCheck() && !isValidMoves();
}

//Rename
bool StateChanger::isStateInCheck(){
    return isInCheck(&this->c);
}

bool StateChanger::isValidMoves(){
    return this->ss->fi;
}

//gameMoves must be in .PGN notation. i.e. 1. a4 d6 2. a5 d5 3. ...
void StateChanger::printGameState(){
    printState(this->c, this->playingAs, this->gameMoves);
    printValidMoves();
}

void StateChanger::printSuccStates(){
    printStates(this->ss, this->playingAs);
}

void StateChanger::printValidMoves(){
    cout << "Valid moves: ";
    for(int i = 0; i < validMoves.size(); i++){
        cout << validMoves[i] << " ";
    }
    cout << endl << endl;
}

//add a return of void
void StateChanger::genListOfValidMoves(){
    string s;
    for(int i = 0; i < this->ss->fi; i++){
        s = toAlgebraicNotation(&(this->c), &(this->ss->bs[i]));
        this->validMoves.push_back(s);
    }

//    for(int i = 0; i < this->validMoves.size(); i++){
//        cout << validMoves[i] << endl;
//    }
}
