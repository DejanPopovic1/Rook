#include "searchTree.hpp"
#include "moveGeneration.hpp"

//void expandNode(T){
//
//
//}




T_searchNode* initialiseSearchTree(T_boardState *rootState){
    T_searchNode rootNode;
    rootNode.b = *rootState;
    for(int i = 0; i < MAX_SUCC_STATES; i++){
        rootNode.scc[i] = NULL;
    }
    return &rootNode;
}
