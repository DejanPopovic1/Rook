#ifndef CHANGE_STATE_H
#define CHANGE_STATE_H

#include "state.hpp"
#include <string>
#include <vector>

class StateChanger{
public:
    StateChanger();
    StateChanger(T_boardState boardState);
    void changeState(std::string usrInput);
    void printValidMoves();
    T_boardState getState();
private:
    void genListOfValidMoves();
    std::vector<std::string> validMoves;
    T_boardState c;
    T_boardStates *ss;
};

#endif //CHANGE_STATE_H
