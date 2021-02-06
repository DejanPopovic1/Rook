#ifndef MOVELIST_H
#define MOVELIST_H

#include <vector>
#include <string>
#include "GlobalDeclarations.h"




#include "toAlgebraicNotation.h"
#include "GlobalDeclarations.h"
#include "applicableActions.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>



class moveList
{
public:
    moveList();
    void addItem(T_chessboard c, T_chessboard ss);
    void printList();
    char* toAlgebraicNotation(T_chessboard c, T_chessboard ss);


private:
    std::vector <std::string> validMoves;
    char* toSpecifier(T_position to);
    void (*returnMvmntRule(T_chessboard c, T_position p))(T_chessboard, T_position, T_states *);
    bool arePiecesInSameRank(T_positions *ps, T_position p);
    bool arePiecesInSameFile(T_positions *ps, T_position p);
    char* formatFileDisplay(int f);
    char* formatRankDisplay(int r);
    char* toFileRank(T_positions *departures, T_position departure);
    char* toFileRankPawn(T_positions *departures, T_position departure, bool isCaptured);
    T_position whereArrival(T_chessboard c, T_chessboard ss);
    bool doesDepartureGoToArrival(T_chessboard c, T_position d, T_position a);
    T_positions* trimOtherSamePieces(T_chessboard c, T_positions *ps, T_position arrival);
    char* disambiguate(T_chessboard c, T_position departure, T_position arrival, bool isCaptured);
    T_positions* whereAreOtherSamePieces(T_chessboard c, T_position p);
    T_position whereTo(T_chessboard c, T_chessboard s, bool *isPieceCaptured);
    T_position whereFrom(T_chessboard c, T_chessboard s);
    char* specifier(int piece);
    char* take(bool isTake);
    int whatPiece(T_chessboard c, T_position p);
};

#endif // MOVELIST_H






