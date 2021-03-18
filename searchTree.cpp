#include "searchTree.hpp"
#include "moveGeneration.hpp"

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


T_Node *createNode(T_boardState *s){
    T_Node sn;
    sn.b = *s;
    return &sn;
}

void expandNode(T_boardState *s){


}

T_Node *generateSearchTree(T_boardState *s){
    T_Node *result;
//    genSuccStatesSTUB(s, );
    return result;
}

T_Node* initialiseSearchTree(T_boardState *rootState){
    T_Node rootNode;
    rootNode.b = *rootState;
    for(int i = 0; i < MAX_SUCC_STATES; i++){
        rootNode.scc[i] = NULL;
    }
    return &rootNode;
}
