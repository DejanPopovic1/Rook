#include "gameState.hpp"
#include "ToAlgNotation.hpp"
#include "output.hpp"
#include "moveGeneration.hpp"
#include <iostream>
#include "keyUtilities.hpp"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::pair;

GameState::GameState(){

}

T_boardState GameState::getState(){
    return (this->c);
}
//Dont pass in board state, rather create it in this constructor
GameState::GameState(T_boardState boardState, bool pA){
    this->randomKey = createRandomKey();
    this->movesWithoutTakeOrPawnMove = 0;
    this->ply = 0;
    this->playingAs = pA;
    this->c = boardState;
    this->ss = initialiseStates();
    uint64_t initialKey = generateKey(&this->c);
    this->previousStates.push_back(initialKey);
    this->previousStatesCount.insert(pair<uint64_t, int>(initialKey, 1));
    genSuccStates(this->ss, &(this->c));
    genListOfValidMoves();
}

//Rope out the for loop and determine if its valid input in a seperate function
void GameState::changeState(string usrInput){
    T_boardState cpy;
    for(int i = 0; i < this->ss->fi; i++){
        //cout << (int)this->movesWithoutTakeOrPawnMove << endl;
        if(validMoves[i] == usrInput){
            cpy = this->c;
            if(!isPawnMoveOrCapture(&cpy, &this->ss->bs[i])){
                this->movesWithoutTakeOrPawnMove++;
            }
            this->ply++;
            this->c = this->ss->bs[i];
            (this->c.whosTurn)++;
            this->ss = initialiseStates();
            genSuccStates(this->ss, &(this->c));
            this->validMoves.clear();
            genListOfValidMoves();
            gameMoves.push_back(usrInput);
            uint64_t key = incrementKey(this->previousStates.back(), &cpy, &this->c, this->randomKey);
            this->previousStates.push_back(key);
            if(this->previousStatesCount.count(key)){
                previousStatesCount[key] += 1;
            }
            else{
                this->previousStatesCount.insert(pair<uint64_t, int>(key, 1));
            }
            if(isCheckMate()){
                this->c.whosTurn ? gameMoves.push_back("1 - 0") : gameMoves.push_back("0 - 1");
            }
            else if(isStaleMate() || isThreeFoldRepetition() || isFiftyMoveRule()){
                gameMoves.push_back("1/2 - 1/2");
            }
            return;
        }
    }
    cout << "Invalid move\n";
    return ;
}

bool GameState::isFiftyMoveRule(){
    if(this->movesWithoutTakeOrPawnMove == 5){
        return true;
    }
    return false;
}

bool GameState::isThreeFoldRepetition(){
    for (auto it = this->previousStatesCount.begin(); it != this->previousStatesCount.end(); ++it)
        if (it->second == 3){
            return true;
        }
    return false;
}

bool GameState::isCheckMate(){
    return isStateInCheck() && !isValidMoves();
}

bool GameState::isStaleMate(){
    return !isStateInCheck() && !isValidMoves();
}

//Rename
bool GameState::isStateInCheck(){
    return isInCheck(&this->c);
}

bool GameState::isValidMoves(){
    return this->ss->fi;
}

//gameMoves must be in .PGN notation. i.e. 1. a4 d6 2. a5 d5 3. ...
void GameState::printGameState(){
    printState(this->c, this->playingAs, this->gameMoves, this->ply, this->previousStates);
    printValidMoves();
}

void GameState::printSuccStates(){
    printStates(this->ss, this->playingAs);
}

//implement isPawn function
bool GameState::isPawnMoveOrCapture(T_boardState *c, T_boardState *ss){
    char from, to, piece, capturedPiece;
    bool isPieceCaptured;
    whereFromTo(c, ss, &from, &to, &piece, &isPieceCaptured, &capturedPiece);
    cout << (int)piece << endl << endl;
    if(piece == whitePawn || piece == blackPawn || isPieceCaptured){
       return true;
    }
    return false;
}

void GameState::printValidMoves(){
    cout << "Valid moves: ";
    for(int i = 0; i < validMoves.size(); i++){
        cout << validMoves[i] << " ";
    }
    cout << endl << endl;
}

//add a return of void
void GameState::genListOfValidMoves(){
    string s;
    for(int i = 0; i < this->ss->fi; i++){
        s = toAlgebraicNotation(&(this->c), &(this->ss->bs[i]));
        this->validMoves.push_back(s);
    }

//    for(int i = 0; i < this->validMoves.size(); i++){
//        cout << validMoves[i] << endl;
//    }
}
