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

int min(T_Node **n, int level);
int max(T_Node **n, int level);
T_Node* createNodeParent(T_boardState *input);
bool isAllSuccStatesInCheck(T_boardState *input);
bool isComputerInCheck(T_boardState b);
T_Node* createNode();
void freeTreeNode(T_Node *node);
void genSuccStatesSTUB(T_Node *newNode);
int generateTreeNodeMinMax(T_Node **iterator, int level, int *indexMaxMin);
void addStateNode(T_Node *dstNode, T_boardState *src);
T_boardState computerMove(T_boardState *input);

#endif // SEARCH_TREE_H
