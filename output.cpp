#include "toAlgNotation.hpp"
#include "output.hpp"
#include <wchar.h>
#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>
#include "state.hpp"
#include <stdint.h>
#include "output.hpp"
#include <assert.h>
#include "bitUtilities.hpp"
#include "gameState.hpp"
#include <iostream>

//int whosTurn(const int halfPly){
//    if((halfPly % 2) == 1){
//        return whiteTurn;
//    }
//    return blackTurn;
//}

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
        std::cout << std::endl << i << std::endl;
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
        printf("\n");
    }
}

//To-do: Omit leading zero in printing castling state
void printState(T_boardState b, int playerColour, std::vector<std::string> gameMoves, unsigned short int ply, std::vector<uint64_t> previousStates){
    T_chessboard *c = toIntArray(b);
    printBoard(playerColour, *c);
    printf("Ply: %d\n", ply);
    (!b.whosTurn) ? printf("White Turn\n") : printf("Black Turn\n");
    printf("State of white en Passants: ");
    printBits(sizeof(b.wEnPassants), &(b.wEnPassants));
    printf("State of white castling: "); printf("%d", b.castlesLRWhite); printf("%d", b.castlesKWhite); printf("%d\n", b.castlesRRWhite);
    printf("State of black en Passants: ");
    printBits(sizeof(b.bEnPassants), &(b.bEnPassants));
    printf("State of black castling: "); printf("%d", b.castlesLRBlack); printf("%d", b.castlesKBlack); printf("%d\n", b.castlesRRBlack);
    printf("No captures or pawn moves: %d\n", b.noCapturesOrPawnMoves);
    printf("Hash table of previous chess states:\n");
    for(int i = 0; i < previousStates.size(); i++){
        std::cout << "- " << std::hex << previousStates[i] << std::endl << std::dec ;
    }
    printf("Game moves: ");
    for(int i = 0; i < gameMoves.size(); i++){
        std::cout << gameMoves[i] << " ";
    }
    std::cout << std::endl;
}

void printStates(T_boardStates *b, int playerColour){
    std::vector<std::string> v;
    std::vector<uint64_t> p;
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
        printf("%d", bit);
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
            printf("%d ", bit);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void landingMessage(){
    printf("Rook Chess Engine (Open source version)\n2020-12-30\nAuthor - Dejan Popovic\n\nFor help on commands, type \"help\"\nFor detail about how to use a command, type \"man\" followed by a space and the command name\n");
    printf("This open source version of Rook uses rudimentary chessboard position encoding\n\n");
    printf("For detailed documentation and code base, please visit github.com/users/DeanPopovic/RookEngine\n\n");
}

//void printPlayerTurn(int halfPly){
//    if(whosTurn(halfPly) == whiteTurn){
//        printf("W: ");
//    }
//    else if(whosTurn(halfPly) == blackTurn){
//        printf("B: ");
//    }
//    return;
//}

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
    char* fileIndex = "   h g f e d c b a";
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
    char* fileIndex = "   a b c d e f g h";
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
    printf("For detailed documentation and code base, please visit github.com/users/DeanPopovic/RookEngine\n\n");
    printf("help\t\t\t-\tDisplay all Rook commands\n");
    printf("single_player\t\t-\tBegins a single player game whereby the user plays against the Rook AI engine\n");
    printf("multi_player\t\t-\tBegins a multiplayer game whereby the user plays against another user\n");
    printf("configure Engine\t-\tConfigures various Rook AI engine parameters\n");
    printf("configure Display\t-\tConfigures the output and display parameters\n");
    printf("configure Input/Output\t-\tConfigures the methods in which user input is entered and output displayed\n");
    printf("export\t\t\t-\tExport single or multiplayer game\n");
    printf("gameplay settings\t-\tConfigures various gameplay settings\n");
    printf("version\t\t\t-\tDisplay Rook version\n");
    printf("exit\t\t\t-\tExit Rook\n");
    return;
}
