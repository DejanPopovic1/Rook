#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "state.hpp"
#include <string>
#include <vector>

enum PlayingAs{asWhite, asBlack};
//What state does state changer keep that stat doesnt? There are three
//1. Playing As
//2. Ply number
//3. List of valid moves
//4. List of all game moves
//5. Time left in current move (if there is a time limit imposed)

class GameState{
public:
    GameState();
    GameState(T_boardState boardState, bool pA);
    void changeState(std::string usrInput);
    T_boardState getState();
    void printGameState();
    void printSuccStates();
    bool isCheckMate();
    bool isStaleMate();
private:
    void printValidMoves();
    bool isValidMoves();
    bool isStateInCheck();
    void genListOfValidMoves();
    int turnTimeLeft;
    std::vector<std::string> validMoves;
    std::vector<std::string> gameMoves;
    T_boardState c;
    T_boardStates *ss;
    bool playingAs;
    unsigned short int ply;
};

#endif //GAME_STATE_H