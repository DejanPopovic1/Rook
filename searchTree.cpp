#include "searchTree.hpp"
#include "moveGeneration.hpp"
#include "testInitialisations.hpp"

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
void genSuccStatesSTUB(T_Node **newNode){
    (*newNode)->scc[1] = (T_Node*)malloc(sizeof(T_Node));
    (*newNode)->scc[2] = (T_Node*)malloc(sizeof(T_Node));
    (*newNode)->scc[3] = (T_Node*)malloc(sizeof(T_Node));
    (*newNode)->scc[4] = (T_Node*)malloc(sizeof(T_Node));
    (*newNode)->scc[5] = (T_Node*)malloc(sizeof(T_Node));
    (*newNode)->scc[6] = NULL;
    (*newNode)->scc[1]->b = initialiseBoardState();
    (*newNode)->scc[2]->b = CMinitialiseBoardState();
    (*newNode)->scc[3]->b = SMinitialiseBoardState();
    (*newNode)->scc[4]->b = initialiseBoardState();
    (*newNode)->scc[5]->b = PPinitialiseBoardState();
}

//Optimisation hack: Have two generateLinkedList functions - one for white and one for black. These then recursively call one another. More efficient because:
//1) No need to conduct if statements below
//2) No need to copy across player turn as a struct member when creating a new node in the tree
//3) KEEP original function and allow swapping between the two :-)
//4) You CAN free the whole tree when its the human players turn so dont worry about freeing this in the fucntion. Do later and see how much faster

int evaluateSTUB(T_Node **iterator){
    return 5;
}

int generateLinkedList(T_Node **iterator, int level){
    if(level == DEPTH_LIMIT_LEVEL){
        return evaluateSTUB(iterator);//Heuristically evaluate the state and return this evaluated value. For now, let it evaluate to
    }
    level++;
    T_Node *newNode = (T_Node*)malloc(sizeof(T_Node));
    newNode->b = (*iterator)->b;
    genSuccStatesSTUB(&newNode);

    //newNode->info = 3;//In this step, you would pass execute genSuccStates(newNode); The genSuccStates will populate the array of pointers to point to Nodes with values of each succesor states. These pointed to nodes array's will be left undefined. When there are no more successor states, a NULL value is added in the array
//    **iterator = newNode;
    //newNode->link = NULL;
    (*iterator) = newNode;
        //Contain the following statement in a for loop. Iterate UNTIL a NULL pointer is reached
    //generateLinkedList(iterator, level); //Iterate through all the pointers. The function returns an int value so you must add in if statement to say if white then if result of function is greater than current max, then set new current max
        //End for
        //Return min/max
}














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
