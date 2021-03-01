#ifndef CHANGE_STATE_H
#define CHANGE_STATE_H

#include "state.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class ChangeState{
public:
    ChangeState();
    ChangeState(T_boardState *c, T_boardStates *bss);
    T_boardState changeInputState(T_boardStates *bss, string usrInput);
    vector<string> listValidMoves(T_boardStates *bss);
private:
    vector<string> validMoves;
};

#endif //CHANGE_STATE_H
