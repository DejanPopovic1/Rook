#ifndef TOALGEBRAICNOTATION_H
#define TOALGEBRAICNOTATION_H

#include "GlobalDeclarations.h"

#define MAX_DISAMBIGUATOR_STRING 3
#define ASCII_CHARACTER_OFFSET 97
#define ASCII_NUMBER_OFFSET 49
#define MOVE_INPUT 100
#define FILE_STRING 2
#define RANK_STRING 2

void (*mvmntRulePtr)(T_chessboard currentState, T_position, T_states *consolidatedStates);

void (*returnMvmntRule(T_chessboard c, T_position p))(T_chessboard, T_position, T_states *);
bool arePiecesInSameRank(T_positions *ps, T_position p);
bool arePiecesInSameFile(T_positions *ps, T_position p);
char* formatFileDisplay(int f);
char* formatRankDisplay(int r);
char* toFileRank(T_positions *departures, T_position departure);
T_position whereArrival(T_chessboard c, T_chessboard ss);
bool doesDepartureGoToArrival(T_chessboard c, T_position d, T_position a);
T_positions* trimOtherSamePieces(T_chessboard c, T_positions *ps, T_position arrival);
char* disambiguator(T_chessboard c, T_position departure, T_position arrival, bool);
T_positions* whereAreOtherSamePieces(T_chessboard c, T_position p);
char* toAlgebraicNotation(T_chessboard c, T_chessboard ss);

#endif // TOALGEBRAICNOTATION_H
