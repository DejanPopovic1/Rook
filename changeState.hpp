#ifndef CHANGE_STATE_H
#define CHANGE_STATE_H

#include "state.h"
#include <string>
#include <vector>

class StateChanger{
public:
    StateChanger();
    StateChanger(T_boardState boardState);
    void changeInputState(std::string usrInput);
    std::vector<std::string> printValidMoves();
private:
    genListOfValidMoves();
    std::vector<std::string> validMoves;
    T_boardState c;
    T_boardStates ss;
};

#endif //CHANGE_STATE_H
