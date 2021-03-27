#include "output.hpp"
#include "toAlgNotation.hpp"
#include "state.hpp"
#include "bitUtilities.hpp"
#include "gameState.hpp"

#include <assert.h>
#include <stdint.h>
#include <wchar.h>
#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <iostream>

using namespace std;

void multiPlayerPrompt(){
    cout << " -> ";
    return;
}

//Add in an assertion that the player in move cannot also hold a check on opponent

//Rather use pointer to boardState
int whatIsPiece(T_boardState b, int i){
    int result = empty;
    int resultCount = 0;
    if(isBitSet(b.wPawn, i)){
        result = whitePawn;
        resultCount++;
    }
    if(isBitSet(b.wBishop, i)){
        result = whiteBishop;
        resultCount++;
    }
    if(isBitSet(b.wKnight, i)){
        result = whiteKnight;
        resultCount++;
    }
    if(isBitSet(b.wRook, i)){
        result = whiteRook;
        resultCount++;
    }
    if(isBitSet(b.wQueen, i)){
        result = whiteQueen;
        resultCount++;
    }
    if(isBitSet(b.wKing, i)){
        result = whiteKing;
        resultCount++;
    }
    if(isBitSet(b.bPawn, i)){
        result = blackPawn;
        resultCount++;
    }
    if(isBitSet(b.bBishop, i)){
        result = blackBishop;
        resultCount++;
    }
    if(isBitSet(b.bKnight, i)){
        result = blackKnight;
        resultCount++;
    }
    if(isBitSet(b.bRook, i)){
        result = blackRook;
        resultCount++;
    }
    if(isBitSet(b.bQueen, i)){
        result = blackQueen;
        resultCount++;
    }
    if(isBitSet(b.bKing, i)){
        result = blackKing;
        resultCount++;
    }
    if(resultCount >= 2){
        cout << endl << i << endl;
        assert(false);
    }
    return result;
}

T_chessboard *toIntArray(T_boardState b){
    T_chessboard *result = (T_chessboard *)malloc(sizeof(T_chessboard));
    for(int i = 0; i < BITBOARD_SIZE; i++){
        int piece = whatIsPiece(b, i);
        (*result)[i/FILE_SIZE][i % RANK_SIZE] = piece;
    }
    return result;
}

void printTBitboardNumbersBin(T_bitboard **b){
    for(int i = 0; i < 64; i++){
        printTBitboardNumber(*(b[i]));
        cout << endl;
    }
}

//To-do: Omit leading zero in printing castling state
void printState(T_boardState b, int playerColour, vector<string> gameMoves, unsigned short int ply, vector<uint64_t> previousStates, vector<string> vm){
    T_chessboard *c = toIntArray(b);
    printBoard(playerColour, *c);
    free(c);
    cout << "Ply: " << ply << endl;
    (!b.whosTurn) ? cout << "White Turn" << endl : cout << "Black Turn" << endl;
    cout << "State of white en Passants: ";
    printBits(sizeof(b.wEnPassants), &(b.wEnPassants));
    cout << "State of white castling: " << (int)b.castlesLRWhite << (int)b.castlesKWhite << (int)b.castlesRRWhite << endl;
    cout << "State of black en Passants: ";
    printBits(sizeof(b.bEnPassants), &(b.bEnPassants));
    cout << "State of black castling: " << (int)b.castlesLRBlack << (int)b.castlesKBlack << (int)b.castlesRRBlack << endl;
    cout << "No captures or pawn moves: "<< (int)b.noCapturesOrPawnMoves << endl;
    cout << "Hash table of previous chess states:" << endl;
    for(unsigned int i = 0; i < previousStates.size(); i++){
        cout << "- " << hex << previousStates[i] << endl << dec ;
    }
    printf("Game moves: ");
    for(unsigned int i = 0; i < gameMoves.size(); i++){
        cout << gameMoves[i] << " ";
    }
    cout << endl;
    cout << "Valid moves: ";
    for(unsigned int i = 0; i < vm.size(); i++){
        cout << vm[i] << " ";
    }
    cout << endl << endl;
}

void printStates(T_boardStates *b, int playerColour){
    vector<string> v;
    vector<uint64_t> p;
    for(int i = 0; i < length(b); i++){
        printState((b->bs)[i], playerColour, v, 0, p);
    }
}

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    for (int i = size-1; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

void printTBitboardNumbersDec(T_bitboard **b){
    for(int i = 0; i < 64; i++){
        printf("%llu\n", *(b[i]));
    }
    printf("\n\n\n");
    return;
}

void printTBitboardNumber(T_bitboard b){
    T_bitboard bit;
    for(int i = 63; i >= 0; i--){
        bit = (b >> i) & 1UL;
        printf("%llu", bit);
    }
    printf("\n");
}

void printTBitboard(T_bitboard b){
    T_bitboard bit;
    int index;
    for(int i = RANK_SIZE - 1; i >= 0; i--){
        for(int j = 0; j <= FILE_SIZE - 1; j++){
            index = (i * FILE_SIZE) + j;
            bit = (b >> index) & 1U;
            printf("%llu ", bit);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void landingMessage(){
    cout << "Rook Chess Engine (Open source version)" << endl;
    cout << "2021-03-28\nAuthor - Dejan Popovic" << endl;
    cout << "For help on commands, type \"help\"" << endl;
    cout << "This open source version of Rook excludes:" << endl;
    cout << "*) Alpha Beta pruning" << endl;
    cout << "*) Opening moves" << endl;
    cout << "*) Advanced board evaluation heuristics" << endl;
    cout << "*) Pruning heuristics" << endl;
    cout << "*) Transposition tables" << endl;
    cout << "*) Magic bitboards" << endl;
    cout << "For detailed documentation and code base, please visit github.com/users/DeanPopovic/RookEngine" << endl << endl;
}

void printBoard(int playingAs, T_chessboard chessboard){
    playingAs == asWhite ? printBoardPlayingAsWhite(chessboard) : printBoardPlayingAsBlack(chessboard);
    return;
}

void printMove(char* c){
    printf("%s", c);
    return;
}

bool isWhiteTile(int rank, int file){
    bool isEvenTile = ((rank + file) % 2 == 0);
    return (isEvenTile ? false : true);
}

void printBoardPlayingAsBlack(T_chessboard chessboard){
    HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD n;
    int rankIndex = 1;
    const char* fileIndex = "   h g f e d c b a";
    printf("\n%s\n", fileIndex);
    WriteConsoleW(cons, L"  \u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557",
                  wcslen(L"\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659"), &n, NULL );
    printf("\n");
    for(int i = 0; i < RANK_SIZE; i++){
        printf(" %d", rankIndex);
        WriteConsoleW(cons, L"\u2551", wcslen(L"\u2659"), &n, NULL );
        for(int j = FILE_SIZE - 1; j >= 0; j--){
            printGlyph(chessboard[i][j], isWhiteTile(i, j));
        }
        WriteConsoleW(cons, L"\u2551", wcslen(L"\u2659"), &n, NULL );
        printf("%d\n", rankIndex);
        rankIndex++;
    }
    WriteConsoleW(cons, L"  \u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D",
                  wcslen(L"\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659"), &n, NULL );
    printf("\n%s\n", fileIndex);
}

void printBoardPlayingAsWhite(T_chessboard chessboard){
    HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD n;
    int rankIndex = 8;
    const char* fileIndex = "   a b c d e f g h";
    printf("\n%s\n", fileIndex);
    WriteConsoleW(cons, L"  \u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557",
                  wcslen(L"\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659"), &n, NULL );
    printf("\n");
    for(int i = RANK_SIZE - 1; i >= 0; i--){
        printf(" %d", rankIndex);
        WriteConsoleW(cons, L"\u2551", wcslen(L"\u2659"), &n, NULL );
        for(int j = 0; j < FILE_SIZE; j++){
            printGlyph(chessboard[i][j], isWhiteTile(i, j));
        }
        WriteConsoleW(cons, L"\u2551", wcslen(L"\u2659"), &n, NULL );
        printf("%d\n", rankIndex);
        rankIndex--;
    }
    WriteConsoleW(cons, L"  \u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D",
                  wcslen(L"\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659\u2659"), &n, NULL );
    printf("\n%s\n", fileIndex);
}

void setColourForBlack(bool isWhiteTile){
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    isWhiteTile ? SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_BLUE):
    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
    return;
}

void setColourForWhite(bool isWhiteTile){
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    isWhiteTile ? SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_BLUE):
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE);
    return;
}

void printGlyph(int piece, bool isWhiteTile){
    HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD n;
    switch(piece){
        case empty:
            setColourForBlack(isWhiteTile);
            WriteConsoleW(cons, L" ", wcslen(L"  "), &n, NULL );
            break;
        case whitePawn:
            setColourForWhite(isWhiteTile);
            WriteConsoleW(cons, L"\u265F", wcslen(L"\u2659"), &n, NULL );
            break;
        case whiteBishop:
            setColourForWhite(isWhiteTile);
            WriteConsoleW(cons, L"\u265D", wcslen(L"\u2659"), &n, NULL );
            break;
        case whiteKnight:
            setColourForWhite(isWhiteTile);
            WriteConsoleW(cons, L"\u265E", wcslen(L"\u2659"), &n, NULL );
            break;
        case whiteRook:
            setColourForWhite(isWhiteTile);
            WriteConsoleW(cons, L"\u265C", wcslen(L"\u2659"), &n, NULL );
            break;
        case whiteQueen:
            setColourForWhite(isWhiteTile);
            WriteConsoleW(cons, L"\u265B", wcslen(L"\u2659"), &n, NULL );
            break;
        case whiteKing:
            setColourForWhite(isWhiteTile);
            WriteConsoleW(cons, L"\u265A", wcslen(L"\u2659"), &n, NULL );
            break;
        case blackPawn:
            setColourForBlack(isWhiteTile);
            WriteConsoleW(cons, L"\u265F", wcslen(L"\u2659"), &n, NULL );
            break;
        case blackBishop:
            setColourForBlack(isWhiteTile);
            WriteConsoleW(cons, L"\u265D", wcslen(L"\u2659"), &n, NULL );
            break;
        case blackKnight:
            setColourForBlack(isWhiteTile);
            WriteConsoleW(cons, L"\u265E", wcslen(L"\u2659"), &n, NULL );
            break;
        case blackRook:
            setColourForBlack(isWhiteTile);
            WriteConsoleW(cons, L"\u265C", wcslen(L"\u2659"), &n, NULL );
            break;
        case blackQueen:
            setColourForBlack(isWhiteTile);
            WriteConsoleW(cons, L"\u265B", wcslen(L"\u2659"), &n, NULL );
            break;
        case blackKing:
            setColourForBlack(isWhiteTile);
            WriteConsoleW(cons, L"\u265A", wcslen(L"\u2659"), &n, NULL );
            break;
        default:
            fprintf(stderr, "%s%d", "Error: Chessboard position has a value out of range. A corresponding glyph does not exist and cannot be printed. Value of chessboard piece is: ", piece);
            exit(-1);
            break;
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    return;
}

void displayHelp(){
    printf("For detailed documentation and code base, please visit https://github.com/DejanPopovic1/Rook\n\n");
    printf("help\t\t-\tDisplay all Rook commands\n");
    printf("sp\t\t-\tBegins a single player game whereby the user plays against the Rook AI engine. Argument 'w' sets player as white. Argument 'b' sets player as black.\n");
    printf("mp\t\t-\tBegins a multiplayer game whereby the user plays against another user/themselves. Argument 'w' faces white side down. Argument 'b' faces black side down. \n");
    printf("version\t\t-\tDisplay Rook version\n");
    printf("exit\t\t-\tExit Rook\n");
    printf("\n");
    return;
}

void displayVersion(){
    cout << "Version: 1.1\nDate of version update: 2021/03/28" << endl;
    return;
}

void invalidAlert(){
    cout << "Invalid command - see help for valid commands" << endl;
    return;
}

void mainPrompt(){
    cout << "Rook>";
    return;
}

void printInvalidArgumentAlert(){
    cout << "Invalid multi_player argument. See \"help\" for more details" << endl;
}
