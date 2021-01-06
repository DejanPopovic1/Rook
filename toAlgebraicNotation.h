#include "GlobalDeclarations.h"

#define MAX_DISAMBIGUATOR_STRING 3

void (*mvmntRulePtr)(T_chessboard currentState, T_position, T_states *consolidatedStates);

T_positions* whereAreOtherSamePieces(T_chessboard, T_position);
T_positions* whatPiecesMoveToArrival(T_chessboard, T_positions *, T_position);
