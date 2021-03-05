
#ifndef TOALGNOTATION_HPP
#define TOALGNOTATION_HPP

#include <string>
#include <vector>

#define ASCII_CHARACTER_OFFSET 97
#define ASCII_NUMBER_OFFSET 49

//We need to investigate why this works. It should work without extern because the .c file repeates the step after this with extern
#include "state.hpp"

//Namespaces included in headers is bad practice. Is there therefore any way to include them wihtout resorting to excessive use of std::?

void printVector(std::vector<char> v);
T_bitboard *pieceBitboard(T_boardState *b, char piece);
char piece(T_boardState *c, char pos);
bool isSamePosition(const char a, const char b);
bool isSameRank(char a, char b);
bool isSameFile(char a, char b);
bool arePiecesInSameRank(std::vector<char> ps, char p);
bool arePiecesInSameFile(std::vector<char> ps, char p);
T_bitboard whereAreOtherSamePieces(T_bitboard b, char pos);
std::string formatFileDisplay(char f);
std::string formatRankDisplay(char r);
std::string toFileRank(std::vector<char> departures, char departure);
std::string toFileRankPawn(std::vector<char> departures, char departure, bool isCaptured);
bool doesStateChangeDepartFromPos(T_boardState *f, T_boardState *t, char pos);
bool doesDepartureGoToArrival(T_boardState *b, char d, char a);
T_bitboard trimOtherSamePieces(T_boardState *s, T_bitboard ps, char arrival);
std::vector<char> posOfPieces(T_bitboard input);
std::string disambiguate(T_boardState *c, char from, char to, bool isCaptured);
std::string specifier(char piece);
void whereFromTo(T_boardState *c, T_boardState *ss, char *from, char *to, char *piece, bool *isPieceCaptured, bool *isEnPassantCapture);
std::string take(bool isTake);
std::string toSpecifier(char to);
std::string toAlgebraicNotation(T_boardState *c, T_boardState *ss);
extern "C" const char* toAlgebraicNotation_C_WRAPPER(T_boardState *c, T_boardState *ss);

#endif // TOALGNOTATION_HPP

