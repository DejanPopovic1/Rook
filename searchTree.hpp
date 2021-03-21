#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H

#include "state.hpp"

#define DEPTH_LIMIT_LEVEL 5

struct Node;

typedef struct Node T_Node;

struct Node{
    T_boardState b;
    Node *scc[MAX_SUCC_STATES];
    int fp;
};

T_Node* createNode();
void freeTreeNode(T_Node *node);
void genSuccStatesSTUB(T_Node *newNode);
int evaluateSTUB(T_Node **iterator);
int generateTreeNode(T_Node **iterator, int level);
void addStateNode(T_Node *dstNode, T_boardState *src);

#endif // SEARCH_TREE_H
