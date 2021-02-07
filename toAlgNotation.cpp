

#include <string>
#include <stdbool.h>
#include <assert.h>

#include "GlobalDeclarations.h"
#include "state.h"
#include "bitUtilities.h"

using std::string;

T_bitboard stateMemberCpy(T_boardState *b, char piece){
    switch(piece){
    case whitePawn:
        return b->wPawn;
        break;
    case whiteBishop:
        return b->wBishop;
        break;
    case whiteKnight:
        return b->wKnight;
        break;
    case whiteRook:
        return b->wRook;
        break;
    case whiteQueen:
        return b->wQueen;
        break;
    case whiteKing:
        return b->wKing;
        break;
    case blackPawn:
        return b->bPawn;
        break;
    case blackBishop:
        return b->bBishop;
        break;
    case blackKnight:
        return b->bKnight;
        break;
    case blackRook:
        return b->bRook;
        break;
    case blackQueen:
        return b->bQueen;
        break;
    case blackKing:
        return b->bKing;
        break;
    default:
        assert(false);
    }
}

string disambiguate(T_boardState *c, char from, char to, bool isPieceCaptured){
    string result;




    return result;
}

string specifier(char piece){
    string result;
    switch(piece){
        case whitePawn:
        case blackPawn:
            ;
            break;
        case whiteBishop:
        case blackBishop:
            result += "B";
            break;
        case whiteKnight:
        case blackKnight:
            result += "K";
            break;
        case whiteRook:
        case blackRook:
            result += "R";
            break;
        case whiteQueen:
        case blackQueen:
            result += "Q";
            break;
        case whiteKing:
        case blackKing:
            result += "K";
            break;
    }
    return result;
}

//Doesnt take into account en Passants
//simplify so that stateMember doesnt return pointer but rather a copy of the board
//Use C++ pass by reference
void whereFromTo(T_boardState *c, T_boardState *ss, char *from, char *to, char *piece, bool *isPieceCaptured){
    *isPieceCaptured = false;
    bool cond1, cond2;
    T_bitboard cB, ssB;
    for(char i = 1; i < 13; i++){
        cB = stateMemberCpy(c, i);
        ssB = stateMemberCpy(ss, i);
        if(cB != ssB && (__builtin_popcountll(cB) == __builtin_popcountll(ssB))){
            *piece = i;
            T_bitboard fromTo = cB ^ ssB;
            *from = __builtin_ctzll(cB & fromTo);
            *to = __builtin_ctzll(ssB & fromTo);
        }
        else if(cB != ssB && (__builtin_popcountll(cB) != __builtin_popcountll(ssB))){
            *isPieceCaptured = true;
        }
    }
}

string toAlgebraicNotation(T_boardState *c, T_boardState *ss){
    string result;
    char piece, from, to;
    bool isPieceCaptured;
    whereFromTo(c, ss, &from, &to, &piece, &isPieceCaptured);
    string part1 = specifier(piece);
    string part2 = disambiguate(c, from, to, isPieceCaptured);
    string part3;
    string part4;
//    char *part1 = specifier(piece);
//    char *part2 = disambiguate(c, from, to, isPieceCaptured);
//    char *part3 = take(isPieceCaptured);
//    char *part4 = toSpecifier(to);
//    strcpy(result, "");
//    strcat(result, part1);
//    strcat(result, part2);
//    strcat(result, part3);
//    strcat(result, part4);
//    free(part1);
//    //free(part2);
//    free(part3);
//    free(part4);
    return result;
}
