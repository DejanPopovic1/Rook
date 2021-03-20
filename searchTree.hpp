#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H

#include "state.hpp"

#define DEPTH_LIMIT_LEVEL 6

typedef struct Node T_Node;

struct Node{
    T_boardState b;
    Node *scc[MAX_SUCC_STATES];
};

void genSuccStatesSTUB(T_Node *newNode);
int evaluateSTUB(T_Node **iterator);
int generateTreeNode(T_Node **iterator, int level);

#endif // SEARCH_TREE_H
