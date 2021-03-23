#include "gameState.hpp"
#include "ToAlgNotation.hpp"
#include "output.hpp"
#include "moveGeneration.hpp"
#include "keyUtilities.hpp"
#include "searchTree.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::pair;
using std::find;
using std::iterator;

GameState::GameState(){

}

T_boardState GameState::getState(){
    return (this->c);
}
//Dont pass in board state, rather create it in this constructor
GameState::GameState(bool pA){
    this->randomKey = createRandomKey();
    this->movesWithoutTakeOrPawnMove = 0;
    this->ply = 0;
    this->playingAs = pA;
    this->c = initialiseBoardState();
    uint64_t initialKey = generateKey(&this->c);
    this->previousStates.push_back(initialKey);
    this->previousStatesCount.insert(pair<uint64_t, int>(initialKey, 1));
    genListOfValidMoves();
}

bool GameState::isValidMove(string s){
    if(find(this->validMoves.begin(), this->validMoves.end(), s) != this->validMoves.end()){
        return true;
    }
    return false;
}

int GameState::moveIndex(string s){
    vector<string>::iterator it = find(this->validMoves.begin(), this->validMoves.end(), s);
    return std::distance(this->validMoves.begin(), it);
}

T_boardState stateAtMoveIndex(T_boardState *s, int i){
    T_Node *n = createNode();
    genSuccStates(n, s);
    return n->scc[i]->b;
}

void GameState::updateMovesWithoutTakeOrPawnMove(T_boardState *c, T_boardState *s){
    T_Node *n = createNode();
    genSuccStates(n, c);
    //isPawnMoveOrCapture(s, &stateAtMoveIndex(s, moveIndex(usrInput)))
    if(!isPawnMoveOrCapture(c, s)){
        s->noCapturesOrPawnMoves++;
    }
    else{
        s->noCapturesOrPawnMoves = 0;
    }
}

bool GameState::changeState(string usrInput){
    if(!isValidMove(usrInput)){
       cout << "Invalid move\n" << endl;
       return false;
    }
    T_boardState successorState = stateAtMoveIndex(&this->c, moveIndex(usrInput));
    updateMovesWithoutTakeOrPawnMove(&this->c, &successorState);
    this->ply++;
    this->gameMoves.push_back(usrInput);
    uint64_t key = incrementKey(this->previousStates.back(), &this->c, &successorState, this->randomKey);
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
    else if(isStaleMate() || isThreeFoldRepetition() || isSeventyFiveMoveRule()){
        gameMoves.push_back("1/2 - 1/2");
    }
    this->c = successorState;
    return true;
}

bool GameState::isSeventyFiveMoveRule(){
    if(this->movesWithoutTakeOrPawnMove == 150){
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
    return false;
    //return isStateInCheck() && !isValidMoves();
}

bool GameState::isStaleMate(){
    return false;
    //return !isStateInCheck() && !isValidMoves();
}

//Rename
bool GameState::isStateInCheck(){
    return false;
    //return isInCheck(&this->c);
}

bool GameState::isValidMoves(){
    return true;
    //return this->ss->fi;
}

//gameMoves must be in .PGN notation. i.e. 1. a4 d6 2. a5 d5 3. ...
//printValidmoves should be part of printState
void GameState::printGameState(){
    printState(this->c, this->playingAs, this->gameMoves, this->ply, this->previousStates);
    printValidMoves();
}

void GameState::printSuccStates(){
    //printStates(this->ss, this->playingAs);
}

string GameState::engineMove(){
    T_Node node;
    T_boardStates *bss = initialiseStates();
    //this->c.evaluateCheck = 0;//This is a bad design pattern. The flag was already set to zero. Creating a new state
    genSuccStates(&node, &this->c);
    //this->validMoves.clear();
    //this->ss = initialiseStates();
    //genSuccStates(this->ss, &(this->c));
    //genListOfValidMoves();

//    cout << "===Start Debug===" << endl;
//    printStates(bss, 0);
//
//
//    cout << "===End Debug===" << endl;
    int randomMoveIndex = rand() % bss->fi;
    T_boardState ss = bss->bs[randomMoveIndex];
    return toAlgebraicNotation(&this->c, &ss);
}

//As per comment above, this needs refactoring to first determine if input is correct
void GameState::moveCycle(){
    string usrInput;
    if(this->playingAs){
        printGameState();
        changeState(engineMove());
        printGameState();
        do{
            multiPlayerPrompt();
            std::cin >> usrInput;
        }while(!changeState(usrInput));
    }
    else{
        printGameState();
        do{
            multiPlayerPrompt();
            std::cin >> usrInput;
        }while(!changeState(usrInput));
        printGameState();
        changeState(engineMove());
    }


//        printGameState();
//        do{
//            multiPlayerPrompt();
//            std::cin >> usrInput;
//        }while(!changeState(usrInput));


//        printGameState();
//        changeState(engineMove());

}

//implement isPawn function
bool GameState::isPawnMoveOrCapture(T_boardState *c, T_boardState *ss){
    char from, to, piece, capturedPiece;
    bool isPieceCaptured;
    whereFromTo(c, ss, &from, &to, &piece, &isPieceCaptured, &capturedPiece);
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
    this->validMoves.clear();
    T_Node *n = createNode();
    string s;
    genSuccStates(n, &(this->c));
    for(int i = 0; i < n->fp; i++){
        s = toAlgebraicNotation(&(this->c), &n->scc[i]->b);
        this->validMoves.push_back(s);
    }
    //printValidMoves();
}


//    T_Node node;xxxxxxxxxxxxxx
//    T_boardState cpy;xxxxxxxxx
//    for(int i = 0; i < this->ss->fi; i++){xxxxxxxxxxx
//        //cout << (int)this->movesWithoutTakeOrPawnMove << endl;////////////
//        if(validMoves[i] == usrInput){xxxxxxxxxxxxxxxxx
//            cpy = this->c;xxxxxxxxxxx
//            if(!isPawnMoveOrCapture(&cpy, &this->ss->bs[i])){////////
//                this->movesWithoutTakeOrPawnMove++;/////////////
//            }//////////////
//            else{////////////
//                this->movesWithoutTakeOrPawnMove = 0;///////////
//            }//////////////////
//            this->ply++;///////////////////////////////////
//            this->c = this->ss->bs[i];xxxxxxxxxxx
//            (this->c.whosTurn)++;xxxxxxxxxxxxxxxxxxxxxxxxxxx
//            this->ss = initialiseStates();xxxxxxxxx
//            genSuccStates(&node, &(this->c));xxxxxxxxxxxxxxxxx
//            this->validMoves.clear();xxxxxxxxxxxxxxxxxxxx
//            genListOfValidMoves();////////////////
//            gameMoves.push_back(usrInput);//////////////////////
//            uint64_t key = incrementKey(this->previousStates.back(), &cpy, &this->c, this->randomKey);////////////////
//            this->previousStates.push_back(key);//////////////
//            if(this->previousStatesCount.count(key)){////////////
//                previousStatesCount[key] += 1;///////////
//            }//////////////
//            else{///////////////////////
//                this->previousStatesCount.insert(pair<uint64_t, int>(key, 1));//////////////
//            }////////////////////
//            if(isCheckMate()){//////////////
//                this->c.whosTurn ? gameMoves.push_back("1 - 0") : gameMoves.push_back("0 - 1");//////////////
//            }//////////////
//            else if(isStaleMate() || isThreeFoldRepetition() || isFiftyMoveRule()){//////////////
//                gameMoves.push_back("1/2 - 1/2");//////////////
//            }//////////////
//            return true;xxxxxxxxx
//        }xxxxxxxxxxxx
//    }xxxxxxxxxxxxx
