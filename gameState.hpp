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

class GameState{
public:
    GameState(T_boardState bs, bool pA);
    bool changeState(std::string usrInput);
    T_boardState getState();
    void printGameState();
    bool isSeventyFiveMoveRule();
    bool isFiveFoldRepetition();
    bool isCheckMate();
    bool isStaleMate();
    std::string engineMove(T_boardState s);
    std::vector<std::string> genListOfValidNotations(T_boardState input);
    ~GameState();
private:
    T_boardState c;
    key *randomKey;
    std::vector<std::string> validMoves;
    std::vector<std::string> gameMoves;
    std::vector<uint64_t> previousStates;
    std::map<uint64_t, int> previousStatesCount;
    bool playingAs;
    unsigned short int ply;
    char movesWithoutTakeOrPawnMove;
    bool isMatesOrRepetitions();
    void updatePreviousStatesCount(uint64_t key);
    std::vector<T_boardState> genValidStatesFromState(T_boardState *input);
    T_boardState stateAtMoveIndex(T_boardState *s, int i);
    void updateMovesWithoutTakeOrPawnMove(T_boardState *c, T_boardState *s);
    int moveIndex(std::string s);
    bool isValidMove(std::string s);
    bool isPawnMoveOrCapture(T_boardState *frm, T_boardState *to);
    void printValidMoves();
    bool isInCheck(T_boardState b);
};

#endif //GAME_STATE_H
