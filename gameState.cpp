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
//Add a class destructor that free's the randomKey malloc
GameState::GameState(bool pA){
    this->randomKey = createRandomKey();
    this->movesWithoutTakeOrPawnMove = 0;
    this->ply = 0;
    this->playingAs = pA;
    this->c = initialiseBoardState();
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
    T_Node *n = createNode();

    genSuccStates(n, s);
    T_Node *v = genValidFromPseudoValidStates(n);
    //return v->scc[i]->b;
    T_boardState result = n->scc[i]->b;
    freeTreeNode(n);
    free(n);
    return result;
}

void GameState::updateMovesWithoutTakeOrPawnMove(T_boardState *c, T_boardState *s){
    //T_Node *n = createNode();
    //genSuccStates(n, c);
    ////isPawnMoveOrCapture(s, &stateAtMoveIndex(s, moveIndex(usrInput)))
    if(!isPawnMoveOrCapture(c, s)){
        s->noCapturesOrPawnMoves++;
    }
    else{
        s->noCapturesOrPawnMoves = 0;
    }
    //free(n);
}

//A map corresponding to moves and states should be made in change State
bool GameState::changeState(string usrInput){
    //genListOfValidMoves();
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
    else if(isStaleMate() || isFiveFoldRepetition() || isSeventyFiveMoveRule()){
        gameMoves.push_back("1/2 - 1/2");
    }
    this->c = successorState;
    this->validMoves = genListOfValidMoves(this->c);
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
    return false;
    //return isStateInCheck() && !isValidMoves();
}

bool GameState::isStaleMate(){
    return false;
    //return !isStateInCheck() && !isValidMoves();
}

//Rename
bool GameState::isStateInCheck2(){
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
    printState(this->c, this->playingAs, this->gameMoves, this->ply, this->previousStates, this->validMoves);
}

void GameState::printSuccStates(){
    //printStates(this->ss, this->playingAs);
}

string GameState::engineMove(){

    //T_boardStates *bss = initialiseStates();
//    //this->c.evaluateCheck = 0;//This is a bad design pattern. The flag was already set to zero. Creating a new state
    T_boardState cm = computerMove(&this->c);

    //genSuccStates(&node, &this->c);
//    //this->validMoves.clear();
//    //this->ss = initialiseStates();
//    //genSuccStates(this->ss, &(this->c));
//    //genListOfValidMoves();
//
////    cout << "===Start Debug===" << endl;
////    printStates(bss, 0);
////
////
////    cout << "===End Debug===" << endl;
    //int randomMoveIndex = rand() % bss->fi;
    //T_boardState ss = bss->bs[randomMoveIndex];
    return toAlgebraicNotation(&this->c, &cm);
}

//As per comment above, this needs refactoring to first determine if input is correct
//Refactor move cycle into white and then black move and in the main loop to check for is check or is stalemate
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
//        cout << "STATE AFTER HUMAN MOVE:" << endl;
//                printState(this->c);
        //printGameState();
        cout << "COMPUTER MOVE:" << endl;
//        printState(computerMove(&this->c));
//        cout << engineMove();
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


//vector<string> genListOfValidSuccStates(T_boardState *input){
//    T_Node *head = createNode();
//    head->b = *input;
//    int bestEval;
//    int indexMaxMin;
//    bestEval = generateTreeNodeMinMax(&head, 0, &indexMaxMin);
//    //cout << endl << bestEval << endl;
//    //cout << endl << indexMaxMin << endl;
//    T_Node *head2 = createNode();
//    genSuccStates(head2, input);
//    T_boardState result = head2->scc[indexMaxMin]->b;
//    return result;
//}

bool GameState::isStateInCheck(T_boardState *b){
    T_Node *n = createNode();
    genSuccStates(n, b);
    bool result = !isKingsExist(n, !b->whosTurn);
    free(n);
    return result;
}

T_Node *GameState::genValidFromPseudoValidStates(T_Node *n){
    T_Node *result = createNode();
    for(int i = 0; i < n->fp; i++){
        if(!isStateInCheck(&n->scc[i]->b)){
            T_boardState cpy = n->scc[i]->b;
            //printState(cpy);
            addStateNode(result, &cpy);
        }
    }
    return result;
}

T_Node *GameState::genValidStatesFromState(T_boardState *input){
    T_Node *n = createNode();
    genSuccStates(n, input);

    T_Node *result = genValidFromPseudoValidStates(n);

    //free(input);

    return result;
    //!!!Free the calling function!!!
}

//Change name to listOfValidNotations
//Calling this as AI wont produce a check state in genSuccStates. But, as a human player it will, and thus we need an additional check
vector<string> GameState::genListOfValidMoves(T_boardState input){

    vector<string> result;
    //this->validMoves.clear();
    //T_Node *n = createNode();

    string s;
    T_Node *vs = genValidStatesFromState(&input);


    //genSuccStates(n, &(input));
    //T_Node *v = genValidFromPseudoValidStates(n);
    for(int i = 0; i < vs->fp; i++){
        s = toAlgebraicNotation(&(input), &vs->scc[i]->b);
        result.push_back(s);
    }
    freeTreeNode(vs);
    free(vs);
    return result;
    //!!!FREE V!!!
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
