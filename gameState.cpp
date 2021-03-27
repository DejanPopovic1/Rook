#include "gameState.hpp"
#include "ToAlgNotation.hpp"
#include "output.hpp"
#include "moveGeneration.hpp"
#include "keyUtilities.hpp"
#include "searchTree.hpp"
#include "state.hpp"

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

T_boardState GameState::getState(){
    return this->c;
}

//Add a class destructor that free's the randomKey malloc
GameState::GameState(T_boardState bs, bool pA){
    this->randomKey = createRandomKey();
    this->movesWithoutTakeOrPawnMove = 0;
    this->ply = 0;
    this->playingAs = pA;
    this->c = bs;
    uint64_t initialKey = generateKey(&this->c);
    this->previousStates.push_back(initialKey);
    this->previousStatesCount.insert(pair<uint64_t, int>(initialKey, 1));
    this->validMoves = genListOfValidMoves(this->c);
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

T_boardState GameState::stateAtMoveIndex(T_boardState *s, int i){
    vector<T_boardState> bs = genValidStatesFromState(s);
    return bs[i];
}

void GameState::updateMovesWithoutTakeOrPawnMove(T_boardState *c, T_boardState *s){
    if(!isPawnMoveOrCapture(c, s)){
        s->noCapturesOrPawnMoves++;
    }
    else{
        s->noCapturesOrPawnMoves = 0;
    }
}

//A map corresponding to moves and states should be made in change State
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
    this->c = successorState;
    this->validMoves = genListOfValidMoves(this->c);
    if(isCheckMate()){
        this->c.whosTurn ? gameMoves.push_back("1 - 0") : gameMoves.push_back("0 - 1");
        //exit(-1);
        return false;
    }
    else if(isStaleMate() || isFiveFoldRepetition() || isSeventyFiveMoveRule()){
        gameMoves.push_back("1/2 - 1/2");
        //exit(-2);
        return false;
    }
    return true;
}

bool GameState::isSeventyFiveMoveRule(){
    if(this->movesWithoutTakeOrPawnMove == 150){
        return true;
    }
    return false;
}

bool GameState::isFiveFoldRepetition(){
    for (auto it = this->previousStatesCount.begin(); it != this->previousStatesCount.end(); ++it)
        if (it->second == 5){
            return true;
        }
    return false;
}

bool GameState::isCheckMate(){
    if(this->validMoves.empty() && isInCheck(this->c)){
        return true;
    }
    return false;
}

bool GameState::isStaleMate(){
    if(this->validMoves.empty() && !isInCheck(this->c)){
        return true;
    }
    return false;
}

//gameMoves must be in .PGN notation. i.e. 1. a4 d6 2. a5 d5 3. ...
//printValidmoves should be part of printState
void GameState::printGameState(){
    printState(this->c, this->playingAs, this->gameMoves, this->ply, this->previousStates, this->validMoves);
}


//pass in state rather than using "this->"
//Move this to an interface file within the engine and NOT in this class
string GameState::engineMove(){
    T_boardState cm = computerMove(&this->c);
    if(isStatesEqual(cm, this->c)){
        //exit(-1);
        return "";
    }
    cout << toAlgebraicNotation(&this->c, &cm);
    return toAlgebraicNotation(&this->c, &cm);
}



//As per comment above, this needs refactoring to first determine if input is correct
//Refactor move cycle into white and then black move and in the main loop to check for is check or is stalemate
//Rather split this into two functions. One for white and one for black
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
        //cout << "HUMAN TURN COMPLETE" << endl;
        changeState(engineMove());
    }
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

//Is the player, currently in turn, in check
bool GameState::isInCheck(T_boardState b){
    T_Node *n = createNode();
    b.whosTurn++;
    genSuccStates(n, &b);
    b.whosTurn++;
    return !isKingsExist(n, b.whosTurn);
}

//bool GameState::isStateInCheck(T_boardState *b){
//    T_Node *n = createNode();
//    genSuccStates(n, b);
//    bool result = !isKingsExist(n, !b->whosTurn);
//    //free(n);
//    return result;
//}

vector<T_boardState> GameState::genValidStatesFromState(T_boardState *input){
    vector<T_boardState> result;
    T_Node *n = createNode();
    genSuccStates(n, input);
    for(int i = 0; i < n->fp; i++){
        n->scc[i]->b.whosTurn++;
        if
            //(true){
            (!isInCheck(n->scc[i]->b)){
            n->scc[i]->b.whosTurn++;
            result.push_back(n->scc[i]->b);
        }
    }
    return result;
}

//Change name to listOfValidNotations
//Calling this as AI wont produce a check state in genSuccStates. But, as a human player it will, and thus we need an additional check
vector<string> GameState::genListOfValidMoves(T_boardState input){
    vector<string> result;
    string s;
    vector<T_boardState> vs = genValidStatesFromState(&input);
    if(vs.empty()){
        return result;
    }
    for(int i = 0; i < vs.size(); i++){
        s = toAlgebraicNotation(&(input), &vs[i]);
        result.push_back(s);
    }
    //freeTreeNode(vs);
    //free(vs);
    return result;
    //!!!FREE V!!!
}

GameState::~GameState(){
    free(this->randomKey);
}
