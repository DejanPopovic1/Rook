#include "GlobalDeclarations.h"

#define MAX_DISAMBIGUATOR_STRING 3
#define ASCII_CHARACTER_OFFSET 97

void (*mvmntRulePtr)(T_chessboard currentState, T_position, T_states *consolidatedStates);

T_positions* whereAreOtherSamePieces(T_chessboard, T_position);
T_positions* trimOtherSamePieces(T_chessboard, T_positions *, T_position);
