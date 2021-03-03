#ifndef CHANGE_STATE_H
#define CHANGE_STATE_H

#include "state.hpp"
#include <string>
#include <vector>

enum PlayingAs{asWhite, asBlack};
//What state does state changer keep that stat doesnt? There are three
//1. Playing As
//2. Ply number
//3. List of valid moves
//4. Time left in current move (if there is a time limit imposed)

class StateChanger{
public:
    StateChanger();
    StateChanger(T_boardState boardState, bool pA);
    void changeState(std::string usrInput);
    void printValidMoves();
    T_boardState getState();
    void printGameState();
private:
    int turnTimeLeft;
    void genListOfValidMoves();
    std::vector<std::string> validMoves;
    T_boardState c;
    T_boardStates *ss;
    bool playingAs;
    short int ply;
};

#endif //CHANGE_STATE_H
