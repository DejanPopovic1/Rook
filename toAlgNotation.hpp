#include <string>
#include "state.h"

T_bitboard stateMemberCpy(T_boardState *b, char piece);
void whereFromTo(T_boardState *c, T_boardState *ss, char *from, char *to, char *piece);
char whereTo(T_boardState *c, T_boardState *ss, bool *isPieceCaptured);
string toAlgebraicNotation(T_boardState *c, T_boardState *ss);
