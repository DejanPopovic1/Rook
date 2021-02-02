#include "GlobalDeclarations.h"
#include "toAlgebraicNotation.h"
#include "output.h"
#include <wchar.h>
#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>
#include "state.h"
#include <stdint.h>
#include "output.h"
#include <assert.h>

void printTBitboardNumbersBin(T_bitboard **b){
    for(int i = 0; i < 64; i++){
        printTBitboardNumber(*(b[i]));
        printf("\n");
    }
}

//To-do: Omit leading zero in printing castling state
void printState(T_boardState b){
    T_chessboard *c = toIntArray(b);
    printBoard(whosTurn(b.ply), *c);
    printf("Ply: %d\n", b.ply);
    (!b.whosTurn) ? printf("Whites TurnTest\n") : printf("Blacks TurnTest\n");
//    if(whosTurn(b.ply) == whiteTurn){
//        printf("Whites Turn\n");
//    }
//    else if(whosTurn(b.ply) == blackTurn){
//        printf("Blacks Turn\n");
//    }
//    else{
//        assert(false);
//    }
    printf("State of white en Passants: ");
    printBits(sizeof(b.wEnPassants), &(b.wEnPassants));
    printf("State of white castling: ");
    char i = b.castlesWhite;
    printBits(sizeof(i), &i);
    printf("State of black en Passants: ");;
    printBits(sizeof(b.bEnPassants), &(b.bEnPassants));
    printf("State of black castling: ");
    i = b.castlesBlack;
    printBits(sizeof(i), &i);
    printf("No captures or pawn moves: %d\n", b.noCapturesOrPawnMoves);
    printf("Hash table of previous chess states:\n - TO BE COMPLETED\n\n");
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








//=============================

void landingMessage(){
    printf("Rook Chess Engine (Open source version)\n2020-12-30\nAuthor - Dejan Popovic\n\nFor help on commands, type \"help\"\nFor detail about how to use a command, type \"man\" followed by a space and the command name\n");
    printf("This open source version of Rook uses rudimentary chessboard position encoding\n\n");
    printf("For detailed documentation and code base, please visit github.com/users/DeanPopovic/RookEngine\n\n");
}

void printPlayerTurn(int halfPly){
    if(whosTurn(halfPly) == whiteTurn){
        printf("W: ");
    }
    else if(whosTurn(halfPly) == blackTurn){
        printf("B: ");
    }
    return;
}

void printPosition(T_position p){
    printf("(%d, %d)\n", p.r, p.f);
}

void printPositions(T_positions ps){
    for(int i = 0; i < ps.freeIndex; i++){
        printPosition(ps.positions[i]);
    }
}

void printBoard(int playingAs, T_chessboard chessboard){
    playingAs == asWhite ? printBoardPlayingAsWhite(chessboard) : printBoardPlayingAsBlack(chessboard);
    return;
}

void printBoardsAndAlgNot(T_chessboard c, int playingAs, T_states* s){
    for(int i = 0; i < s->freeIndex; i++){
        printBoard(playingAs, s->states[i]);
        printf("\n");
        printf(toAlgebraicNotation(c,s->states[i]));
        printf("\n");
    }
    return;
}

void printBoards(int playingAs, T_states* s){
    for(int i = 0; i < s->freeIndex; i++){
        printBoard(playingAs, s->states[i]);
        printf("\n");
    }
    return;
}

void printMove(char* c){
    printf("%s", c);
    return;
}

void printMoves(T_moves *a){
    printf("Number of valid moves: %d\n", a->freeIndex);
    for(int i = 0; i < a->freeIndex; i++){
        printf("%s ", a->moves[i]);
    }
    printf("\n");
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
