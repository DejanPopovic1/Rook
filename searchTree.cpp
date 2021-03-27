#include "searchTree.hpp"
#include "moveGeneration.hpp"
#include "testInitialisations.hpp"
#include "output.hpp"
#include "heuristics.hpp"

#include <iostream>

using namespace std;

//Rename this to freeTreeNodeChildren
void freeTreeNode(T_Node *node){
    for(int i = 0; i < node->fp; i++){
        free(node->scc[i]);
    }
}

bool isStateInCheck(T_boardState b){
    T_Node *n = createNode();
    b.whosTurn++;
    genSuccStates(n, &b);
    b.whosTurn++;
    return !isKingsExist(n, b.whosTurn);
}

bool isAllSuccStatesInCheck(T_boardState *input){
    T_Node *preCheck = createNode();
    genSuccStates(preCheck, input);
    for(int i = 0; i < preCheck->fp; i++){
        preCheck->scc[i]->b.whosTurn++;
        if(!isStateInCheck(preCheck->scc[i]->b)){
            return false;
        }
    }
    return true;
}

//Optimisation hack: Have two generateLinkedList functions - one for white and one for black. These then recursively call one another. More efficient because:
//1) No need to conduct if statements below
//2) No need to copy across player turn as a struct member when creating a new node in the tree
//3) KEEP original function and allow swapping between the two :-)
//4) You CAN free the whole tree when its the human players turn so dont worry about freeing this in the fucntion. Do later and see how much faster

//This function is agnostic to what colour AI is assigned to. It will be assigned to the coloour whos turn it currently is
//This function returns the same input if there are no valid moves to make - It doesnt care if this is due to stalemate or checkmate. Thats up to other code
T_boardState computerMove(T_boardState *input){
    if(isAllSuccStatesInCheck(input)){
        exit(-1);
        cout << endl << "!!!CHECK/STALEMATE!!!" << endl << endl;
        return *input;
    }
    int index;
    T_Node *head = createNodeParent(input);
    input->whosTurn ? index = min(&head, DEPTH_LIMIT_LEVEL) : index = max(&head, DEPTH_LIMIT_LEVEL);
    genSuccStates(head, input);
    T_boardState result = head->scc[index]->b;
    free(head);
    cout << "RESULT OF AI" << endl;
    printState(result);
    return result;
}

int max(T_Node **n, int level){
    if(!level){
        freeTreeNode(*n);
        return evaluateBoard(&(*n)->b);
    }
    genSuccStates(*n, &(*n)->b);
    int maxEval = -1000000;
    int maybeNewMaxEval;
    int maxEvalIndex;
    for(int i = 0; i < (*n)->fp; i++){
        maybeNewMaxEval = min(&(*n)->scc[i], level - 1);
        if(maybeNewMaxEval > maxEval){
            maxEval = maybeNewMaxEval;
            maxEvalIndex = i;
        }
    }
    freeTreeNode(*n);
    if(level == DEPTH_LIMIT_LEVEL){
        return maxEvalIndex;
    }
    else{
        return maxEval;
    }
}

int min(T_Node **n, int level){
    if(!level){
        freeTreeNode(*n);
        return evaluateBoard(&(*n)->b);
    }
    genSuccStates(*n, &(*n)->b);
    int minEval = 1000000;
    int maybeNewMinEval;
    int minEvalIndex;
    for(int i = 0; i < (*n)->fp; i++){
        maybeNewMinEval = max(&(*n)->scc[i], level - 1);
        if(maybeNewMinEval < minEval){
            minEval = maybeNewMinEval;
            minEvalIndex = i;
        }
    }
    freeTreeNode(*n);
    if(level == DEPTH_LIMIT_LEVEL){
        return minEvalIndex;
    }
    else{
        return minEval;
    }
}

T_Node* createNodeParent(T_boardState *input){
    T_Node *result = createNode();
    result->b = (*input);
    return result;
}

T_Node* createNode(){
    T_Node *result = (T_Node*)malloc(sizeof(T_Node));
    result->fp = 0;
    return result;
}

void addStateNode(T_Node *dstNode, T_boardState *src){
    src->whosTurn ? src->bEnPassants = 0 : src->wEnPassants = 0;
    src->whosTurn++;
    dstNode->scc[dstNode->fp] = createNode();
    dstNode->scc[dstNode->fp]->b = *src;
    (dstNode->fp)++;
}
