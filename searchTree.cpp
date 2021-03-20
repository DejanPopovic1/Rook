#include "searchTree.hpp"
#include "moveGeneration.hpp"
#include "testInitialisations.hpp"
#include "output.hpp"

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
void genSuccStatesSTUB(T_Node *node){
    node->scc[0] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[1] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[2] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[3] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[4] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[5] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[6] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[7] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[8] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[9] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[10] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[11] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[12] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[13] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[14] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[15] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[16] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[17] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[18] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[19] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[20] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[21] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[22] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[23] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[24] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[25] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[26] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[27] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[28] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[29] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[30] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[31] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[32] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[33] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[34] = (T_Node*)malloc(sizeof(T_Node));
//    node->scc[35] = (T_Node*)malloc(sizeof(T_Node));
    node->scc[30] = NULL;
    node->scc[0]->b = initialiseBoardState();
    node->scc[1]->b = CMinitialiseBoardState();
    node->scc[2]->b = SMinitialiseBoardState();
    node->scc[3]->b = initialiseBoardState();
    node->scc[4]->b = PPinitialiseBoardState();
    node->scc[5]->b = initialiseBoardState();
    node->scc[6]->b = CMinitialiseBoardState();
    node->scc[7]->b = SMinitialiseBoardState();
    node->scc[8]->b = initialiseBoardState();
    node->scc[9]->b = PPinitialiseBoardState();
    node->scc[10]->b = initialiseBoardState();
    node->scc[11]->b = CMinitialiseBoardState();
    node->scc[12]->b = SMinitialiseBoardState();
    node->scc[13]->b = initialiseBoardState();
    node->scc[14]->b = PPinitialiseBoardState();
    node->scc[15]->b = initialiseBoardState();
    node->scc[16]->b = CMinitialiseBoardState();
    node->scc[17]->b = SMinitialiseBoardState();
    node->scc[18]->b = initialiseBoardState();
    node->scc[19]->b = PPinitialiseBoardState();
    node->scc[20]->b = initialiseBoardState();
    node->scc[21]->b = CMinitialiseBoardState();
    node->scc[22]->b = SMinitialiseBoardState();
    node->scc[23]->b = initialiseBoardState();
    node->scc[24]->b = PPinitialiseBoardState();
    node->scc[25]->b = initialiseBoardState();
    node->scc[26]->b = CMinitialiseBoardState();
    node->scc[27]->b = SMinitialiseBoardState();
    node->scc[28]->b = initialiseBoardState();
    node->scc[29]->b = PPinitialiseBoardState();
//    node->scc[30]->b = initialiseBoardState();
//    node->scc[31]->b = CMinitialiseBoardState();
//    node->scc[32]->b = SMinitialiseBoardState();
//    node->scc[33]->b = initialiseBoardState();
//    node->scc[34]->b = PPinitialiseBoardState();
//    node->scc[35]->b = initialiseBoardState();
}

//Optimisation hack: Have two generateLinkedList functions - one for white and one for black. These then recursively call one another. More efficient because:
//1) No need to conduct if statements below
//2) No need to copy across player turn as a struct member when creating a new node in the tree
//3) KEEP original function and allow swapping between the two :-)
//4) You CAN free the whole tree when its the human players turn so dont worry about freeing this in the fucntion. Do later and see how much faster

int evaluateSTUB(T_Node **iterator){
    return 5;
}

int generateTreeNode(T_Node **iterator, int level){
    if(level == DEPTH_LIMIT_LEVEL){
        //cout << "Leaf evaluated" << endl;
        return evaluateSTUB(iterator);//Heuristically evaluate the state and return this evaluated value. For now, let it evaluate to
    }
    level++;
    genSuccStatesSTUB(*iterator);
    if((*iterator)->b.whosTurn){
        //cout << "black turn" << endl;
        int min = 1000;
        int e;
        //cout << "This should print 1" << endl;
        //cout << newNode->scc[0]<< endl;
        for(int i = 0; (*iterator)->scc[i] != NULL; i++){
            //cout << "Test black" << endl;
            e = generateTreeNode(&(*iterator)->scc[i], level);
            if(e < min){
                min = e;
            }
        }
        return min;
    }
    else{
        //cout << "white turn" << endl;
        int max = -1000;
        int e;
        //cout << "This should print 2" << endl;
//                cout << newNode->scc[0]<< endl;
        for(int i = 0; (*iterator)->scc[i] != NULL; i++){
            //cout << "Test white" << endl;
            e = generateTreeNode(&(*iterator)->scc[i], level);
            if(e > max){
                max = e;
            }
        }
        return max;
    }
}



        //Contain the following statement in a for loop. Iterate UNTIL a NULL pointer is reached
    //generateLinkedList(iterator, level); //Iterate through all the pointers. The function returns an int value so you must add in if statement to say if white then if result of function is greater than current max, then set new current max
        //End for
        //Return min/max














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
