#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H

#include "state.hpp"

struct searchNode{
    T_boardState b;
    searchNode *scc[MAX_SUCC_STATES];
};

#endif // SEARCH_TREE_H
