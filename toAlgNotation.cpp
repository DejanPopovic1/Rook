#include <string>
#include <vector>
#include <stdbool.h>
#include <assert.h>


#include "toAlgNotation.hpp"
#include "GlobalDeclarations.h"
#include "state.h"

extern "C" {
    #include "bitUtilities.h"
}

using std::string;
using std::vector;

//Add consts in this file

//void (*moveGenerator(T_chessboard c, T_position p))(T_chessboard, T_position, T_states *){
//    int movedPiece = whatPiece(c, p);
//    switch(movedPiece){
//        case whitePawn:
//            return &generateWhitePawnSuccessorStates;
//        case whiteBishop:
//            return &generateWhiteBishopSuccessorStates;
//        case whiteKnight:
//            return &generateWhiteKnightSuccessorStates;
//        case whiteRook:
//            return &generateWhiteRookSuccessorStates;
//        case whiteQueen:
//            return &generateWhiteQueenSuccessorStates;
//        case whiteKing:
//            return &generateWhiteKingSuccessorStates;
//        case blackPawn:
//            return &generateBlackPawnSuccessorStates;
//        case blackBishop:
//            return &generateBlackBishopSuccessorStates;
//        case blackKnight:
//            return &generateBlackKnightSuccessorStates;
//        case blackRook:
//            return &generateBlackRookSuccessorStates;
//        case blackQueen:
//            return &generateBlackQueenSuccessorStates;
//        case blackKing:
//            return &generateBlackKingSuccessorStates;
//        default:
//            assert(false);
//    }
//}

T_bitboard *pieceBitboard(T_boardState *b, char piece){
    switch(piece){
    case whitePawn:
        return &b->wPawn;
        break;
    case whiteBishop:
        return &b->wBishop;
        break;
    case whiteKnight:
        return &b->wKnight;
        break;
    case whiteRook:
        return &b->wRook;
        break;
    case whiteQueen:
        return &b->wQueen;
        break;
    case whiteKing:
        return &b->wKing;
        break;
    case blackPawn:
        return &b->bPawn;
        break;
    case blackBishop:
        return &b->bBishop;
        break;
    case blackKnight:
        return &b->bKnight;
        break;
    case blackRook:
        return &b->bRook;
        break;
    case blackQueen:
        return &b->bQueen;
        break;
    case blackKing:
        return &b->bKing;
        break;
    default:
        assert(false);
    }
}

char piece(T_boardState *c, char pos){
    for(char i = 1; i < 13; i++){
        if(isBitSet(*pieceBitboard(c, i), pos)){
            return i;
        }
    }
}

T_bitboard whereAreOtherSamePieces(T_bitboard b, char pos){
    T_bitboard mask;
    setBits(&mask);
    clearBit(&mask, pos);
    return b & mask;
}
//trimOtherSamePieces
//isPawn
//toFileRank
//toFileRankPawn


bool doesDepartureGoToArrival(T_boardState *b, char d, char a){
//    char dps = pieceBitboard(b, d);
//    char aps = pieceBitboard(b, a);

}

T_bitboard trimOtherSamePieces(T_boardState *s, T_bitboard p, char arrival){



}

string disambiguate(T_boardState *c, char from, char to, bool isCaptured){
    string result;
    char p = piece(c, from);
    T_bitboard ps = whereAreOtherSamePieces(*pieceBitboard(c, p), from);



//        T_positions *ps = whereAreOtherSamePieces(c, departure);
//    T_positions *rps;
//    rps = trimOtherSamePieces(c, ps, arrival);
//    free(ps);
//    if(!isPawn(c[departure.r][departure.f])){
//        return toFileRank(rps, departure);
//    }
//    else if(isPawn(c[departure.r][departure.f])){
//        return toFileRankPawn(rps, departure, isCaptured);
//    }







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
        cB = *pieceBitboard(c, i);
        ssB = *pieceBitboard(ss, i);
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