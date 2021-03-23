#include "searchTree.hpp"
#include "moveGeneration.hpp"
#include "testInitialisations.hpp"
#include "output.hpp"
#include "heuristics.hpp"

#include <iostream>

using namespace std;

//struct node{
//    int info;
//    node *link;
//};
//
//void printList(node *n){
//    if(n == NULL){
//        return;
//    }
//    while(n->link != NULL){
//        cout << n->info << endl;
//        n = n->link;
//    }
//    cout << n->info << endl;
//}
//
//void newNode(node** tail){
//    node *newNode = (node*)malloc(sizeof(node));
//    newNode->info = 3;
//    (*tail)->link = newNode;
//    newNode->link = NULL;
//    (*tail) = newNode;
//}

//Arbitrarily populate 5 Successor states

void freeTreeNode(T_Node *node){
    for(int i = 0; i < node->fp; i++){
        free(node->scc[i]);
    }
}

void genSuccStatesSTUB(T_Node *node, T_boardState *b){
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
    addStateNode(node, b);
//    addStateNode(node, b);
//    addStateNode(node, b);
//    addStateNode(node, b);
//    addStateNode(node, b);
//    addStateNode(node, b);
//    addStateNode(node, b);
//    addStateNode(node, b);
//    addStateNode(node, b);
//    addStateNode(node, b);
//    addStateNode(node, b);
//    addStateNode(node, b);
//    addStateNode(node, b);
//    addStateNode(node, b);
//    addStateNode(node, b);
//    addStateNode(node, b);

//    node->scc[0] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[1] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[2] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[3] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[4] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[5] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[6] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[7] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[8] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[9] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[10] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[11] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[12] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[13] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[14] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[15] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[16] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[17] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[18] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[19] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[20] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[21] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[22] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[23] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[24] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[25] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[26] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[27] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[28] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[29] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[30] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[31] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[32] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[33] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[34] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[35] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[0]->b = initialiseBoardState();
//    node->scc[1]->b = CMinitialiseBoardState();
//    node->scc[2]->b = SMinitialiseBoardState();
//    node->scc[3]->b = initialiseBoardState();
//    node->scc[4]->b = PPinitialiseBoardState();
//    node->scc[5]->b = initialiseBoardState();
//    node->scc[6]->b = CMinitialiseBoardState();
//    node->scc[7]->b = SMinitialiseBoardState();
//    node->scc[8]->b = initialiseBoardState();
//    node->scc[9]->b = PPinitialiseBoardState();
//    node->scc[10]->b = initialiseBoardState();
//    node->scc[11]->b = CMinitialiseBoardState();
//    node->scc[12]->b = SMinitialiseBoardState();
//    node->scc[13]->b = initialiseBoardState();
//    node->scc[14]->b = PPinitialiseBoardState();
//    node->scc[15]->b = initialiseBoardState();
//    node->scc[16]->b = CMinitialiseBoardState();
//    node->scc[17]->b = SMinitialiseBoardState();
//    node->scc[18]->b = initialiseBoardState();
//    node->scc[19]->b = PPinitialiseBoardState();
//    node->scc[20]->b = initialiseBoardState();
//    node->scc[21]->b = CMinitialiseBoardState();
//    node->scc[22]->b = SMinitialiseBoardState();
//    node->scc[23]->b = initialiseBoardState();
//    node->scc[24]->b = PPinitialiseBoardState();
//    node->scc[25]->b = initialiseBoardState();
//    node->scc[26]->b = CMinitialiseBoardState();
//    node->scc[27]->b = SMinitialiseBoardState();
//    node->scc[28]->b = initialiseBoardState();
//    node->scc[29]->b = PPinitialiseBoardState();
//    node->scc[30]->b = initialiseBoardState();
//    node->scc[31]->b = CMinitialiseBoardState();
//    node->scc[32]->b = SMinitialiseBoardState();
//    node->scc[33]->b = initialiseBoardState();
//    node->scc[34]->b = PPinitialiseBoardState();
//    node->scc[35]->b = initialiseBoardState();
//    node->fp = 36;
}

//Optimisation hack: Have two generateLinkedList functions - one for white and one for black. These then recursively call one another. More efficient because:
//1) No need to conduct if statements below
//2) No need to copy across player turn as a struct member when creating a new node in the tree
//3) KEEP original function and allow swapping between the two :-)
//4) You CAN free the whole tree when its the human players turn so dont worry about freeing this in the fucntion. Do later and see how much faster

//This function is agnostic to what colour AI is assigned to. It will be assigned to the coloour whos turn it currently is
T_boardState computerMove(T_boardState *input){
    T_Node *head = createNode();
    head->b = *input;
    int bestEval;
    int indexMaxMin;
    bestEval = generateTreeNodeMinMax(&head, 0, &indexMaxMin);
    cout << endl << bestEval << endl;
    cout << endl << indexMaxMin << endl;
    T_Node *head2 = createNode();
    genSuccStates(head2, input);
    T_boardState result = head2->scc[indexMaxMin]->b;
    return result;
}

//If depth limit is reached for one node, then exit for loop for all nodes in that loop - you can do this by testing a return code
//Rather countdown to zero instead of specifying to start at zero
//return NUMBER of moves - this is needed for mobility heuristics
int generateTreeNodeMinMax(T_Node **iterator, int level, int *indexMaxMin){
    if(level == DEPTH_LIMIT_LEVEL){
        return evaluateBoard(&(*iterator)->b);
    }
    bool isOppPlayerInCheck = genSuccStates(*iterator, &(*iterator)->b);
    //Opposite player is in check, which means opposite player made a move that put them in check (illegal)
    //Thus, no further nodes may be generated
    //Since its illegal, its the same as losing the king, something to be avoided based on its value
    level++;
    if((*iterator)->b.whosTurn){
        if(isOppPlayerInCheck){//Condition: Black turn, White in check
            return -1000;//This line is executed as black and returns to white code
        }
        int min = 1000;
        int maybeNewMin;
        for(int i = 0; i < (*iterator)->fp; i++){
            maybeNewMin = generateTreeNodeMinMax(&(*iterator)->scc[i], level, indexMaxMin);
            if(maybeNewMin == 1000){//Condition: Black has just generated a tree node where it is in check
                continue;
            }
            if(maybeNewMin < min){
                min = maybeNewMin;
                if(level == 1){
                    *indexMaxMin = i;
                }
            }
        }
        freeTreeNode(*iterator);
        return min;
    }
    else{
        if(isOppPlayerInCheck){//Condition: White turn, Black in check
            return 1000;//This line is executed as white and returns to black code
        }
        int max = -1000;
        int maybeNewMax;
        for(int i = 0; i < (*iterator)->fp; i++){
            maybeNewMax = generateTreeNodeMinMax(&(*iterator)->scc[i], level, indexMaxMin);
            if(maybeNewMax == -1000){//Condition: White has just generated a tree node where it is in check
                continue;
            }
            if(maybeNewMax > max){
                max = maybeNewMax;
                if(level == 1){
                    *indexMaxMin = i;
                }
            }
        }
        freeTreeNode(*iterator);
        return max;
    }
}
        //Contain the following statement in a for loop. Iterate UNTIL a NULL pointer is reached
    //generateLinkedList(iterator, level); //Iterate through all the pointers. The function returns an int value so you must add in if statement to say if white then if result of function is greater than current max, then set new current max
        //End for
        //Return min/max

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

//void addStateNodeOLDVERSION(T_Node *dstNode, T_boardState *src){
//    if(src->evaluateCheck){
//        src->whosTurn ? src->bEnPassants = 0 : src->wEnPassants = 0;
//        dstNode->scc[dstNode->fp] = (T_Node*)malloc(sizeof(T_Node));
//        dstNode->scc[dstNode->fp]->b = *src;
//        dstNode->fp++;
//    }
//    else {
//        T_boardState cpy = *src;//A copy was already passed in. Do we need a copy of a copy? I think yes, because it is going down into the *next* level
//        //if(!isInCheck(&cpy)){
//        if(true){
//            src->whosTurn ? src->bEnPassants = 0 : src->wEnPassants = 0;
//            dstNode->scc[dstNode->fp] = (T_Node*)malloc(sizeof(T_Node));
//            dstNode->scc[dstNode->fp]->b = *src;
//            dstNode->fp++;
//        }
//    }
//}

//int min(T_Node *n){
//    int min = 1000;
//    for(int i = 0; n->scc[i] != NULL; i++){
//        if(n->scc[i].b < min){
//            min = n->scc[i].b;
//        }
//    }
//    return min;
//}
//
//int max(T_Node *n){
//    int max = -1000;
//    for(int i = 0; n->scc[i] != NULL; i++){
//        if(n->scc[i].b < max){
//            max = n->scc[i].b;
//        }
//    }
//    return min;
//}


//T_Node *createNode(T_boardState *s){
//    T_Node sn;
//    sn.b = *s;
//    return &sn;
//}
//
//void expandNode(T_boardState *s){
//
//
//}
//
//T_Node *generateSearchTree(T_boardState *s){
//    T_Node *result;
////    genSuccStatesSTUB(s, );
//    return result;
//}
//
//T_Node* initialiseSearchTree(T_boardState *rootState){
//    T_Node rootNode;
//    rootNode.b = *rootState;
//    for(int i = 0; i < MAX_SUCC_STATES; i++){
//        rootNode.scc[i] = NULL;
//    }
//    return &rootNode;
//}
