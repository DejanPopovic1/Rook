#include "GlobalDeclarations.h"

#define MAX_DISAMBIGUATOR_STRING 2

void (*movementPtr)(T_chessboard currentState, T_position, T_states *consolidatedStates);

T_positions* whereAreSamePieces(T_chessboard, int);
T_positions* whichSamePiecesMoveToArrival(T_chessboard, T_positions *, T_position);
