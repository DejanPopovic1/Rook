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
    node->fp = 0;
}

void freeTreeNodeOptimised(T_Node *node){
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
        cout << endl << "!!!CHECK/STALEMATE!!!" << endl << endl;
        exit(-1);
        return *input;
    }
    int index;
    T_Node *head = createNodeParent(input);
    cout << "Evaluation of board is: " << evaluateBoard(&head->b) << endl;
    input->whosTurn ? index = min(&head, DEPTH_LIMIT_LEVEL) : index = max(&head, DEPTH_LIMIT_LEVEL);
    free(head);
    //freeTreeNode(head);
    T_Node *head2 = createNodeParent(input);
    genSuccStates(head2, input);
    if(index >= head2->fp){//This code is executed typically when a loss is imminent because the search tree returns a garbage index value due to lack of search tree depth. Instead of crashing the program, a legal index value is selected
        cout << "LARGE INDEX PRESENT!! Index is: " << index << " # of legal positions is: " << head2->fp << endl << endl;
        for(int i = 0; i < head2->fp; i++){
            T_boardState test = head2->scc[i]->b;
            test.whosTurn++;
            if(!isInCheck(test)){
                index = i;
                cout << "Selected index is: " << i << endl;
                break;
            }
        }
    }
    T_boardState result = head2->scc[index]->b;

    //freeTreeNode(head);
    free(head2);
    cout << "RESULT OF AI" << endl;
    cout << "RESULT INDEX " << index << endl;
    printState(result);
    return result;
}

int max(T_Node **n, int level){
    if(!level){
        freeTreeNodeOptimised(*n);
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
    freeTreeNodeOptimised(*n);
    if(level == DEPTH_LIMIT_LEVEL){
        return maxEvalIndex;
    }
    else{
        return maxEval;
    }
}

int min(T_Node **n, int level){
    if(!level){
        freeTreeNodeOptimised(*n);
        return evaluateBoard(&(*n)->b);
    }
    genSuccStates(*n, &(*n)->b);
    int minEval = 1000000;
    int maybeNewMinEval;
    int minEvalIndex;
    for(int i = 0; i < (*n)->fp; i++){
        maybeNewMinEval = max(&(*n)->scc[i], level - 1);
//        if(level == DEPTH_LIMIT_LEVEL){///////////
//            cout << "Index: " << i << " value is: " << maybeNewMinEval << endl;////////////
//            printState((*n)->scc[i]->b);///////////////
//        }////////////////
        if(maybeNewMinEval < minEval){
            minEval = maybeNewMinEval;
            minEvalIndex = i;
        }
    }
    freeTreeNodeOptimised(*n);
    if(level == DEPTH_LIMIT_LEVEL){
//        cout << minEvalIndex << endl;
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
