#include "GlobalDeclarations.h"

#define MAX_DISAMBIGUATOR_STRING 3

void (*movementPtr)(T_chessboard currentState, T_position, T_states *consolidatedStates);

T_positions* whereAreSamePieces(T_chessboard, int);
T_positions* whatPiecesMoveToArrival(T_chessboard, T_positions *, T_position);
