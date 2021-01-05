#include "GlobalDeclarations.h"

void (*movementPtr)(T_chessboard currentState, T_position, T_states *consolidatedStates);

T_positions* whereAreSamePieces(int, T_chessboard);
T_positions* whichSamePiecesMoveToArrival(T_chessboard, T_positions *, T_position);
