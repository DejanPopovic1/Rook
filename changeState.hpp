#ifndef CHANGE_STATE_H
#define CHANGE_STATE_H

#include "state.h"
#include <string>
#include <vector>

class StateChanger{
public:
    StateChanger();
    StateChanger(T_boardState boardState);

    T_boardState changeInputState(T_boardStates *bss, std::string usrInput);
    std::vector<std::string> printValidMoves();
private:
    genListOfValidMoves(T_boardStates *bss);
    std::vector<std::string> validMoves;
    T_boardState c;
    T_boardStates *bss;
};

#endif //CHANGE_STATE_H
