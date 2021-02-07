#ifndef TOALGNOTATION_HPP
#define TOALGNOTATION_HPP

#include <string>

//We need to investigate why this works. It should work without extern because the .c file repeates the step after this with extern
extern "C"{
    #include "state.h"
}














T_bitboard *pieceBitboard(T_boardState *b, char piece);
char piece(T_boardState *c, char pos);
std::vector<char> whereAreOtherSamePieces(T_boardState c, char pos);
std::string disambiguate(T_boardState *c, char from, char to, bool isCaptured);
std::string specifier(char piece);
void whereFromTo(T_boardState *c, T_boardState *ss, char *from, char *to, char *piece, bool *isPieceCaptured);
std::string toAlgebraicNotation(T_boardState *c, T_boardState *ss);

#endif // TOALGNOTATION_HPP

