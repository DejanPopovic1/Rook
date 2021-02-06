#include <assert.h>
#include "moveGeneration.h"
#include "state.h"
#include "GlobalDeclarations.h"

//Use MovePiece function to simplify statements
//see if more state functions can come in here so they may be inlined

void setBit(T_bitboard *number, int n){
    *number ^= (-1ULL ^ *number) & (1ULL << n);
}

void clearBit(T_bitboard *number, int n){
    *number &= ~(1ULL << n);
}

T_bitboard checkBit(T_bitboard number, int n){
    return (number >> n) & 1ULL;
}

//for efficiency, just test less than 7
bool isWhitePiece(int pieceValue){
    if(pieceValue > 0 && pieceValue < 7){
        return true;
    }
    return false;
}

//for efficiency just test greater than 6
bool isBlackPiece(int pieceValue){
    if(pieceValue > 6 && pieceValue < 13){
        return true;
    }
    return false;
}

bool isPosSameSide(T_boardState *b, int n){
    if(!b->whosTurn){
        T_bitboard or = b->wPawn | b->wBishop | b->wKnight | b->wRook | b->wQueen | b->wKing;
        if(isBitSet(or, n)){
            return true;
        }
        return false;
    }
    else{
        T_bitboard or = b->bPawn | b->bBishop | b->bKnight | b->bRook | b->bQueen | b->bKing;
        if(isBitSet(or, n)){
            return true;
        }
        return false;
    }
}

bool isPosWhite(T_boardState *b, int n){
    T_bitboard or = b->wPawn | b->wBishop | b->wKnight | b->wRook | b->wQueen | b->wKing;
    if(isBitSet(or, n)){
        return true;
    }
    return false;
}

bool isPosBlack(T_boardState *b, int n){
    T_bitboard or = b->bPawn | b->bBishop | b->bKnight | b->bRook | b->bQueen | b->bKing;
    if(isBitSet(or, n)){
        return true;
    }
    return false;
}

//Test only one condition
bool isSecondLastRank(int n){
    if(n <= 55 && n >= 48){
        return true;
    }
    return false;
}

//Test only one condition
bool isSecondRank(int n){
    if(n <= 15 && n >= 8){
        return true;
    }
    return false;
}

//Enumerate the direction
//Do a logical test of less than a certain number to establish truth rather than 4 OR statements. To enable this the enumerations must be designed cleverly
bool isNortherlyOrEast(int direction){
    if(direction == northEast || direction == north || direction == northWest || direction == east){
        return true;
    }
    return false;
}

bool isUpEmpty(const T_boardState *b, int n){
    if(isPosEmpty(b, n + 8)){
        return true;
    }
    return false;
}

bool isUpUpEmpty(const T_boardState *b, int n){
    if(isPosEmpty(b, n + 8) && isPosEmpty(b, n + 16)){
        return true;
    }
    return false;
}

bool isDownEmpty(const T_boardState *b, int n){
    if(isPosEmpty(b, n - 8)){
        return true;
    }
    return false;
}

bool isDownDownEmpty(const T_boardState *b, int n){
    if(isPosEmpty(b, n - 8) && isPosEmpty(b, n - 16)){
        return true;
    }
    return false;
}

//King will never be cleared so can remove it
//Is there benefit to testing whether there was a bit and then clearing it and then avoiding the rest of the clearing of bits?
void clearOppPosition(T_boardState *b, char pos){
    if(!b->whosTurn){
        clearBit(&(b->bPawn), pos);
        clearBit(&(b->bBishop), pos);
        clearBit(&(b->bKnight), pos);
        clearBit(&(b->bRook), pos);
        clearBit(&(b->bQueen), pos);
        clearBit(&(b->bKing), pos);
    }
    else{
        clearBit(&(b->wPawn), pos);
        clearBit(&(b->wBishop), pos);
        clearBit(&(b->wKnight), pos);
        clearBit(&(b->wRook), pos);
        clearBit(&(b->wQueen), pos);
        clearBit(&(b->wKing), pos);
    }
}

T_bitboard *stateMember(T_boardState *b, int piece){
    switch(piece){
    case whitePawn:
        return &(b->wPawn);
        break;
    case whiteBishop:
        return &(b->wBishop);
        break;
    case whiteKnight:
        return &(b->wKnight);
        break;
    case whiteRook:
        return &(b->wRook);
        break;
    case whiteQueen:
        return &(b->wQueen);
        break;
    case whiteKing:
        return &(b->wKing);
        break;
    case blackPawn:
        return &(b->bPawn);
        break;
    case blackBishop:
        return &(b->bBishop);
        break;
    case blackKnight:
        return &(b->bKnight);
        break;
    case blackRook:
        return &(b->bRook);
        break;
    case blackQueen:
        return &(b->bQueen);
        break;
    case blackKing:
        return &(b->bKing);
        break;
    default:
        assert(false);
    }
}

//Piece is a redundant piece of info that is supplied for efficiency purposes
//First make sure destination does not contain same colour before calling this function
//When calling this function, we dont know if the move also constitutes an attack
void moveAndAttack(T_boardState *b, char dst, char src, char piece){
    T_bitboard oppPieces = isWhitePiece(piece) ? bAll(b) : wAll(b);
    T_bitboard *sm = (*stateMember)(b, piece);
    clearBit(sm, src);
    setBit(sm, dst);
    if(checkBit(oppPieces, dst)){
        clearOppPosition(b, dst);
    }
}

//Piece is a redundant piece of info that is supplied for efficiency purposes
//First make sure destination does not contain same colour before calling this function
//When calling this function, we know the move does not constitute an attack
void move(T_boardState *b, char dst, char src, char piece){
    T_bitboard *sm = (*stateMember)(b, piece);
    clearBit(sm, src);
    setBit(sm, dst);
}

void promote(T_boardStates *dst, const T_boardState *b, int n, int piece){
        T_boardState cpy = *b;
        T_bitboard *sm = stateMember(&cpy, piece);
        setBit(sm, n + 8);
        clearBit(sm, n);
        addState(dst, &cpy);
}

//factor out specific moves once all moveGenerations complete
//Use generateSlideMoves() to codify these moves
void genWPawnSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays){
    //MOVE UP
    if(isUpEmpty(b, n) && !isSecondLastRank(n)){
        T_boardState cpy = *b;
        move(&cpy, n + 8, n, whitePawn);
        addState(dst, &cpy);
    }
    //MOVE UP UP
    if(isUpEmpty(b, n) && isUpUpEmpty(b, n) && !isSecondLastRank(n)){
        T_boardState cpy = *b;
        move(&cpy, n + 16, n, whitePawn);
        setBit(&(cpy.wEnPassants), n % 8);
        addState(dst, &cpy);
    }
    //CAPTURE LEFT
    if(isPosBlack(b, n + 7) && (n % 8)){
        T_boardState cpy = *b;
        moveAndAttack(&cpy, n + 7, n, whitePawn);
        addState(dst, &cpy);
    }
    //CAPTURE RIGHT
    if(isPosBlack(b, n + 9) && ((n + 1) % 8)){
        T_boardState cpy = *b;
        moveAndAttack(&cpy, n + 9, n, whitePawn);
        addState(dst, &cpy);
    }
    //EN PASSANT LEFT
    char frFile = whatFile(n);
    if((frFile % 8) && isCharBitSet(b->bEnPassants, frFile - 1) && isRankFive(n)){
        T_boardState cpy = *b;
        clearBit(b->bPawn, n - 1);
        move(b, n + 7, n, whitePawn);
        addState(dst, &cpy);
    }
    //EN PASSANT RIGHT
    if(((frFile + 1) % 8) && isCharBitSet(b->bEnPassants, frFile + 1) && isRankFive(n)){
        T_boardState cpy = *b;
        clearBit(b->bPawn, n + 1);
        move(b, n + 9, n, whitePawn);
        addState(dst, &cpy);
    }
    //PROMOTIONS
    if(isRankSeven(n) && isUpEmpty(b, n)){
        promote(dst, b, n, whiteBishop);
        promote(dst, b, n, whiteKnight);
        promote(dst, b, n, whiteRook);
        promote(dst, b, n, whiteQueen);
    }
}

void genBPawnSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays){
    //MOVE DOWN
    if(isDownEmpty(b, n) && !isSecondRank(n)){
        T_boardState cpy = *b;
        move(&cpy, n - 8, n, blackPawn);
        addState(dst, &cpy);
    }
    //MOVE DOWN DOWN
    if(isDownEmpty(b, n) && isDownDownEmpty(b, n) && !isSecondRank(n)){
        T_boardState cpy = *b;
        move(&cpy, n - 16, n, blackPawn);
        setBit(&(cpy.bEnPassants), n % 8);
        addState(dst, &cpy);
    }
    //CAPTURE RIGHT
    if(isPosWhite(b, n - 7) && ((n + 1) % 8)){
        printf("Test\n");
        T_boardState cpy = *b;
        moveAndAttack(&cpy, n - 7, n, blackPawn);
        addState(dst, &cpy);
    }
    //CAPTURE LEFT
    if(isPosWhite(b, n - 9) && (n % 8)){
        T_boardState cpy = *b;
        moveAndAttack(&cpy, n - 9, n, blackPawn);
        addState(dst, &cpy);
    }
    //EN PASSANT RIGHT
    char frFile = whatFile(n);
    if(((frFile + 1) % 8) && isCharBitSet(b->wEnPassants, frFile + 1) && isRankFour(n)){
        T_boardState cpy = *b;
        clearBit(b->bPawn, n + 1);
        move(b, n - 7, n, blackPawn);
        addState(dst, &cpy);
    }
    //EN PASSANT LEFT
    if((frFile % 8) && isCharBitSet(b->wEnPassants, frFile - 1) && isRankFour(n)){
        T_boardState cpy = *b;
        clearBit(b->bPawn, n - 1);
        move(b, n - 9, n, blackPawn);
        addState(dst, &cpy);
    }
    //PROMOTIONS
    if(isRankTwo(n) && isDownEmpty(b, n)){
        promote(dst, b, n, blackBishop);
        promote(dst, b, n, blackKnight);
        promote(dst, b, n, blackRook);
        promote(dst, b, n, blackQueen);
    }
}

//Copy and paste these for other pieces
void genMoves(T_boardStates *dst, const T_boardState *b, int n, T_bitboard *validMoves, int piece, int direction){
    int validMove = (isNortherlyOrEast(direction) ? __builtin_ctzll(*validMoves) : BITBOARD_INDEX_SIZE - __builtin_clzll(*validMoves));
    T_boardState cpy = *b;
    move(&cpy, validMove, n, piece);
    addState(dst, &cpy);
    clearBit(validMoves, validMove);
}

T_bitboard moveBoardDir(const T_boardState *b, int n, int direction, const T_bitboard **rays){
    T_bitboard ray = rays[direction][n];
    T_bitboard occupancyBoard = bAll(b) | wAll(b);
    T_bitboard intersect = ray & occupancyBoard;
    int firstBlocker = (isNortherlyOrEast(direction) ? __builtin_ctzll(intersect) : BITBOARD_INDEX_SIZE - __builtin_clzll(intersect));
    T_bitboard intersectRay = (!intersect) ? 0 : rays[direction][firstBlocker];
    return (ray ^ intersectRay);
}

//Refactor out quiete vs attacking moves
//This function wont work for black unless you have a function called OPPOSING_COLOUR instead of isPosBlack. Or, pass function pointer. Better yet, use info in state.
void genDirStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays, int direction, int piece){
    T_bitboard mb = moveBoardDir(b, n, direction, rays);
    if(!mb){
        return;
    }
    while(__builtin_popcountll(mb) > 1){
        genMoves(dst, b, n, &mb, piece, direction);
    }
    int lastPos = BITBOARD_INDEX_SIZE - __builtin_clzll(mb);
    if(isPosSameSide(b, lastPos)){
        return;
    }
    else if(isPosEmpty(b, lastPos)){
        T_boardState cpy = *b;
        move(&cpy, lastPos, n, piece);
        addState(dst, &cpy);
    }
    else{
        T_boardState cpy = *b;
        moveAndAttack(&cpy, lastPos, n, piece);
        addState(dst, &cpy);
    }
}

void genRaySuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays, int piece){
    switch(piece){
        case whiteBishop:
            genDirStates(dst, b, n, rays, northEast, whiteBishop);
            genDirStates(dst, b, n, rays, southEast, whiteBishop);
            genDirStates(dst, b, n, rays, southWest, whiteBishop);
            genDirStates(dst, b, n, rays, northWest, whiteBishop);
            break;
        case whiteRook:
            genDirStates(dst, b, n, rays, north, whiteRook);
            genDirStates(dst, b, n, rays, east, whiteRook);
            genDirStates(dst, b, n, rays, south, whiteRook);
            genDirStates(dst, b, n, rays, west, whiteRook);
            break;
        case whiteQueen:
            genDirStates(dst, b, n, rays, north, whiteQueen);
            genDirStates(dst, b, n, rays, northEast, whiteQueen);
            genDirStates(dst, b, n, rays, east, whiteQueen);
            genDirStates(dst, b, n, rays, southEast, whiteQueen);
            genDirStates(dst, b, n, rays, south, whiteQueen);
            genDirStates(dst, b, n, rays, southWest, whiteQueen);
            genDirStates(dst, b, n, rays, west, whiteQueen);
            genDirStates(dst, b, n, rays, northWest, whiteQueen);
            break;
    }
}

void genSuccStates(T_boardStates *dst, const T_boardState *b){
        T_bitboard **rays = createRays();
        T_bitboard **jumps = createJumps();
        T_bitboard **steps = createSteps();
        if(!b->whosTurn){
            genPiecesSuccStates(dst, b, rays, whitePawn);
            genPiecesSuccStates(dst, b, rays, whiteBishop);
            genPiecesSuccStates(dst, b, jumps, whiteKnight);
            genPiecesSuccStates(dst, b, rays, whiteRook);
            genPiecesSuccStates(dst, b, rays, whiteQueen);
            genPiecesSuccStates(dst, b, steps, whiteKing);
        }
        else{
            genPiecesSuccStates(dst, b, rays, blackPawn);
            //genPiecesSuccStates(dst, b, rays, blackBishop);
            //genPiecesSuccStates(dst, b, rays, blackKnight);
            //genPiecesSuccStates(dst, b, rays, blackRook);
            //genPiecesSuccStates(dst, b, rays, blackQueen);
            //genPiecesSuccStates(dst, b, rays, blackKing);
        }
}

void genPiecesSuccStates(T_boardStates *dst, const T_boardState *b, const T_bitboard **moveRules, int piece){
    T_bitboard allPieces = *(stateMember(b, piece));
    while(allPieces){
        (*genPieceSuccStates(piece))(dst, b, __builtin_ctzll(allPieces), moveRules, piece);
        clearBit(&allPieces, __builtin_ctzll(allPieces));
    }
}

void genJumpOrStepSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **moveRules, int piece){
    T_boardState cpy = *b;
    int j;
    T_bitboard test;
    for(int i = 0; i < 8; i++){
        j =  __builtin_ctzll(moveRules[i][n]);
        test = 0;
        setBit(&test, j);
        if(test & wAll(b)){
            continue;
        }
        T_boardState cpy = *b;
        moveAndAttack(&cpy, j, n, piece);
        addState(dst, &cpy);
    }
}

void genBBishopSuccStates(T_boardState c, T_boardStates *ss){

}

void genBKnightSuccStates(T_boardState c, T_boardStates *ss){

}

void genBRookSuccStates(T_boardState c, T_boardStates *ss){

}

void genBQueenSuccStates(T_boardState c, T_boardStates *ss){

}

void genBKingSuccStates(T_boardState c, T_boardStates *ss){


}

void (*genPieceSuccStates(int piece))(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays, int piece){
    switch(piece){
        case whitePawn:
            return &genWPawnSuccStates;
        case whiteBishop:
            return &genRaySuccStates;
        case whiteKnight:
            return &genJumpOrStepSuccStates;
        case whiteRook:
            return &genRaySuccStates;
        case whiteQueen:
            return &genRaySuccStates;
        case whiteKing:
            return &genJumpOrStepSuccStates;
        case blackPawn:
            return &genBPawnSuccStates;
//        case blackBishop:
//            return &genWBishopSuccStates;
//        case blackKnight:
//            return &genWBishopSuccStates;
//        case blackRook:
//            return &genWBishopSuccStates;
//        case blackQueen:
//            return &genWBishopSuccStates;
//        case blackKing:
//            return &genWBishopSuccStates;
        default:
            assert(false);
    }
}