#ifndef TOALGNOTATION_HPP
#define TOALGNOTATION_HPP
#define ASCII_CHARACTER_OFFSET 97
#define ASCII_NUMBER_OFFSET 49

#include "state.hpp"

#include <string>
#include <vector>

//Namespaces included in headers is bad practice. Is there therefore any way to include them wihtout resorting to excessive use of std::?

void printVector(std::vector<char> v);
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
void whereFromTo(T_boardState *c, T_boardState *ss, char *from, char *to, char *piece, bool *isPieceCaptured, char* capturedPiece);
std::string take(bool isTake);
std::string toSpecifier(char to);
char isPromoted(T_boardState *c, T_boardState *ss, char *promotedFile, bool *isAlsoTake, char* promotedRank, char *from);
bool isKingSideCastle(T_boardState *c, T_boardState *ss);
bool isQueenSideCastle(T_boardState *c, T_boardState *ss);
std::string toAlgebraicNotation(T_boardState *c, T_boardState *ss);

#endif // TOALGNOTATION_HPP

