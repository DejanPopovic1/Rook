#include <string>
#include <vector>
#include <stdbool.h>
#include <assert.h>
#include <iostream>
#include "bitUtilities.hpp"
#include "moveGeneration.hpp"

#include "toAlgNotation.hpp"

//#include "StateChanger.hpp"

using std::string;
using std::vector;
using std::cout;
using std::endl;

//Add consts in this file

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
            //cout << (int) i << endl;
            return i;
        }
    }
}

bool isSamePosition(const char a, const char b){
    if(a == b){
        return true;
    }
    else
        return false;
}

bool isSameRank(char a, char b){
    if(a/8 == b/8){
        return true;
    }
    return false;
}

bool isSameFile(char a, char b){
    if(a%8 == b%8){
        return true;
    }
    return false;
}

bool arePiecesInSameRank(vector<char> ps, char p){
    for(int i = 0; i < ps.size(); i++){
        if(isSamePosition(ps[i], p)){
            continue;
        }
        if(isSameRank(ps[i], p)){
            return true;
        }
    }
    return false;
}

bool arePiecesInSameFile(vector<char> ps, char p){
    for(int i = 0; i < ps.size(); i++){
        if(isSamePosition(ps[i], p)){
            continue;
        }
        if(isSameFile(ps[i], p)){
            return true;
        }
    }
    return false;
}

T_bitboard whereAreOtherSamePieces(T_bitboard b, char pos){
    T_bitboard mask;
    setBits(&mask);
    clearBit(&mask, pos);
    return b & mask;
}

string formatFileDisplay(char f){
    string result;
    assert(f >= 0 && f < 8);
    result.push_back(f + ASCII_CHARACTER_OFFSET);
    return result;
}

string formatRankDisplay(char r){
    string result;
    assert(r >= 0 && r < 8);
    result.push_back(r + ASCII_NUMBER_OFFSET);
    return result;
}

string toFileRank(vector<char> departures, char departure){
    string result;
    //printVector(departures);
    if(!departures.size()){
        ;
    }
    else if(arePiecesInSameFile(departures, departure) && arePiecesInSameRank(departures, departure)){
        result += formatFileDisplay(whatFile(departure));
        result += formatRankDisplay(whatRank(departure));
    }
    else if(!arePiecesInSameFile(departures, departure)){
        result += formatFileDisplay(whatFile(departure));
    }
    else if(arePiecesInSameFile(departures, departure)){
        result += formatRankDisplay(whatRank(departure));
    }
    else{
        assert(false);
    }
    return result;
}

string toFileRankPawn(vector<char> departures, char departure, bool isCaptured){
    string result;
    if(isCaptured){
        result += formatFileDisplay(whatFile(departure));
    }
    else if(!isCaptured){
        ;
    }
    else{
        assert(false);
    }
    return result;
}

bool doesStateChangeDepartFromPos(T_boardState *f, T_boardState *t, char pos){
    if(!isPosEmpty(f, pos) && isPosEmpty(t, pos)){
        return true;
    }
    return false;
}

//The problem is here. In the calling function, the pieces are not trimmed despite its intention. In this specific function "d" is not used enough
bool doesDepartureGoToArrival(T_boardState *b, char d, char a){
    char p = piece(b, d);
    T_boardStates *bss = initialiseStates();
    T_boardState *state;
    T_bitboard stateDepPcs;
    genSuccStates(bss, b);
    for(int i = 0; i < bss->fi; i++){
        state = &((bss->bs)[i]);
        if(!doesStateChangeDepartFromPos(b, state, d)){
            continue;
        }
        stateDepPcs = *pieceBitboard(state, p);
        if(isBitSet(stateDepPcs, a)){
            return true;
        }
    }
    return false;
}

T_bitboard trimOtherSamePieces(T_boardState *s, T_bitboard ps, char arrival){
    T_bitboard result = ps;
    for(int i = 0; i < 64; i++){
        if(isBitSet(ps, i) && !doesDepartureGoToArrival(s, i, arrival)){
            clearBit(&result, i);
        }
    }
    return result;
}

void printVector(vector<char> v){
    for(int i = 0; i < v.size(); i++)
        std::cout << (int)v[i] << " ";
//    for (vector<char>::const_iterator i = v.begin(); i != v.end(); ++i){
//        std::cout << *i << " ";
//    }
    cout << endl;
}

vector<char> posOfPieces(T_bitboard input){
    vector<char> result;
    for(int i = 0; i < 64; i++){
        if(isBitSet(input, i)){
            result.push_back(i);
            //cout << "pushed: " << i << "   " << (int)result.back() << endl;
        }
    }
    //printTBitboardNumber(input);
    //printVector(result);
    return result;
}

string disambiguate(T_boardState *c, char from, char to, bool isCaptured){
    string result;
    char p = piece(c, from);
    T_bitboard ps = whereAreOtherSamePieces(*pieceBitboard(c, p), from);
    //printTBitboardNumber(ps);
    T_bitboard rps = trimOtherSamePieces(c, ps, to);
    //printTBitboardNumber(rps);
    if(!isPawn(p)){
        return toFileRank(posOfPieces(rps), from);
    }
    else if(isPawn(p)){
        return toFileRankPawn(posOfPieces(rps), from, isCaptured);
    }
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
            result += "N";
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
//Use wAll instead of cB and ssB
void whereFromTo(T_boardState *c, T_boardState *ss, char *from, char *to, char *piece, bool *isPieceCaptured){
    //*enPassantPromotedPiece = 0;
    *isPieceCaptured = false;
    T_bitboard cB;
    T_bitboard ssB;
    for(char i = 1; i < 13; i++){
        cB = *pieceBitboard(c, i);
        ssB = *pieceBitboard(ss, i);
////        if(__builtin_popcountll(ssB) > __builtin_popcountll(cB)){
//            *enPassantPromotedPiece = i;
//            T_bitboard fromTo = cB ^ ssB;
//            *enPColumn = __builtin_ctzll(fromTo);
//            *isPieceCaptured = false;
//            return;
//        }
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

string take(bool isTake){
    string result;
    if(isTake){
        result += "x";
    }
    return result;
}

string toSpecifier(char to){
    string result;
    string ff = formatFileDisplay(whatFile(to));
    string fr = formatRankDisplay(whatRank(to));
    result += ff;
    result += fr;
    return result;
}

//Use wAll instead of cB and ssB
char isPromoted(T_boardState *c, T_boardState *ss, char *promotedFile, bool *isAlsoTake, char* promotedRank, char *fromFile){
    T_bitboard cB;
    T_bitboard ssB;
    __builtin_popcountll(oppositeAll(c)) > __builtin_popcountll(oppositeAll(ss)) ? *isAlsoTake = true : *isAlsoTake = false;
    c->whosTurn ? *promotedRank = 0 : *promotedRank = 7;
    for(char i = 1; i < 13; i++){
        cB = *pieceBitboard(c, i);
        ssB = *pieceBitboard(ss, i);
        if(__builtin_popcountll(ssB) > __builtin_popcountll(cB)){
            *promotedFile = __builtin_ctzll(ssB ^ cB) % 8;
            return i;
        }
    }
    return 0;
}

//Refactor to make simpler w.r.t enPassants
string toAlgebraicNotation(T_boardState *c, T_boardState *ss){
    string result;
    char piece, from, to, promotedPiece;
    char promotedFile, promotedRank, fromPromotedFile;
    bool isPieceCaptured;
    bool isPromoCapture;
    whereFromTo(c, ss, &from, &to, &piece, &isPieceCaptured);
    promotedPiece = isPromoted(c, ss, &promotedFile, &isPromoCapture, &promotedRank, &fromPromotedFile);
    if(promotedPiece && !isPromoCapture){
        return (formatFileDisplay(whatFile(promotedFile)) + formatRankDisplay(promotedRank) + "=" + specifier(promotedPiece));
    }
    if(promotedPiece && isPromoCapture){
        return (formatFileDisplay(whatFile(promotedFile)) + formatRankDisplay(promotedRank) + "=" + specifier(promotedPiece)); //JUST PREPEND FROM COLUMN AND X
    }
//    if(enPassantPromotedPiece && !isPieceCaptured){
//        string rank;
//        c->whosTurn ? rank = "1" : rank = "8";
//        return (formatFileDisplay(whatFile(enPColumn)) + rank + "=" + specifier(enPassantPromotedPiece));
//    }
    string part1 = specifier(piece);
    string part2 = disambiguate(c, from, to, isPieceCaptured);
    string part3 = take(isPieceCaptured);
    string part4 = toSpecifier(to);
    result.append(part1);
    result.append(part2);
    result.append(part3);
    result.append(part4);
    return result;
}

const char* toAlgebraicNotation_C_WRAPPER(T_boardState *c, T_boardState *ss){
    return (toAlgebraicNotation(c, ss)).c_str();
    //return "Hello it works";
}
