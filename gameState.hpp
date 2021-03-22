#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "state.hpp"
#include "keyUtilities.hpp"
#include "searchTree.hpp"

#include <stdint.h>
#include <string>
#include <vector>
#include <map>

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
    GameState(bool pA);
    bool changeState(std::string usrInput);
    T_boardState getState();
    void printGameState();
    void printSuccStates();
    bool isFiftyMoveRule();
    bool isThreeFoldRepetition();
    bool isCheckMate();
    bool isStaleMate();
    void moveCycle();
    std::string engineMove();
private:
    int moveIndex(std::string s);
    bool isValidMove(std::string s);
    key *randomKey;
    bool isPawnMoveOrCapture(T_boardState *frm, T_boardState *to);
    void printValidMoves();
    bool isValidMoves();
    bool isStateInCheck();
    void genListOfValidMoves();
    int turnTimeLeft;
    std::vector<std::string> validMoves;
    std::vector<std::string> gameMoves;
    std::vector<uint64_t> previousStates;
    std::map<uint64_t, int> previousStatesCount;
    T_boardState c;
    //T_boardStates *ss;
    bool playingAs;
    unsigned short int ply;
    char movesWithoutTakeOrPawnMove;
};

#endif //GAME_STATE_H
