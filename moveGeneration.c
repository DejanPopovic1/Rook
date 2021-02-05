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

//Test only one condition
bool isSecondLastRank(int n){
    if(n <= 55 && n >= 48){
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
        setBit(&(cpy.wEnPassants), n - 8);
        addState(dst, &cpy);
    }
    //CAPTURE LEFT
    if(isPosBlack(b, n + 7) && (n % 8)){
        T_boardState cpy = *b;
        removeOpponent(&cpy, n + 7);
        setBit(&(cpy.wPawn), n + 7);
        clearBit(&(cpy.wPawn), n);
        addState(dst, &cpy);
    }
    //CAPTURE RIGHT
    if(isPosBlack(b, n + 9) && ((n + 1) % 8)){
        T_boardState cpy = *b;
        removeOpponent(&cpy, n + 9);
        setBit(&(cpy.wPawn), n + 9);
        clearBit(&(cpy.wPawn), n);
        addState(dst, &cpy);
    }
    //EN PASSANT LEFT
    char frFile = whatFile(n);
    if((frFile % 8) && isCharBitSet(b->bEnPassants, frFile - 1) && isRankFive(n)){
        T_boardState cpy = *b;
        clearBit(b->bPawn, n - 1);
        setBit(b->wPawn, n + 7);
        clearBit(b->wPawn, n);
        addState(dst, &cpy);
    }
    //EN PASSANT RIGHT
    if(((frFile + 1) % 8) && isCharBitSet(b->bEnPassants, frFile + 1) && isRankFive(n)){
        T_boardState cpy = *b;
        clearBit(b->bPawn, n + 1);
        setBit(b->wPawn, n + 9);
        clearBit(b->wPawn, n);
        addState(dst, &cpy);
    }
    //PROMOTIONS
        //BISHOP
    if(isRankSeven(n) && isUpEmpty(b, n)){
        T_boardState cpy = *b;
        setBit(b->wBishop, n + 8);
        clearBit(b->wPawn, n);
        addState(dst, &cpy);
    }
        //KNIGHT
    if(isRankSeven(n) && isUpEmpty(b, n)){
        T_boardState cpy = *b;
        setBit(b->wKnight, n + 8);
        clearBit(b->wPawn, n);
        addState(dst, &cpy);
    }
        //ROOK
    if(isRankSeven(n) && isUpEmpty(b, n)){
        T_boardState cpy = *b;
        setBit(b->wRook, n + 8);
        clearBit(b->wPawn, n);
        addState(dst, &cpy);
    }
        //QUEEN
    if(isRankSeven(n) && isUpEmpty(b, n)){
        T_boardState cpy = *b;
        setBit(b->wQueen, n + 8);
        clearBit(b->wPawn, n);
        addState(dst, &cpy);
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
//This function wont work for black unless you have a function called OPPOSING_COLOUR instead of isPosBlack. Or, pass function pointer
void genDirStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays, int direction, int piece){
    T_bitboard mb = moveBoardDir(b, n, direction, rays);
    if(!mb){
        return;
    }
    while(__builtin_popcountll(mb) > 1){
        genMoves(dst, b, n, &mb, piece, direction);
    }
    int lastPos = BITBOARD_INDEX_SIZE - __builtin_clzll(mb);
    if(isPosWhite(b, lastPos)){
        return;
    }
    if(!isPosWhite(b, lastPos)){



        genMoves(dst, b, n, &mb, piece, direction);
        if(isPosBlack(b, lastPos)){
            removeOpponent(&(dst->bs[(dst->fi) - 1]), lastPos);
        }
    }
}

//set bit and clear bit should be in one function called move() and this should be applied to all moveGenerator functions
//Check the ZF flag to see if there is a bit set in the forward and reverse scans
void genWBishopSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays){


    genDirStates(dst, b, n, rays, northEast, whiteBishop);
    genDirStates(dst, b, n, rays, southEast, whiteBishop);
    genDirStates(dst, b, n, rays, southWest, whiteBishop);
    genDirStates(dst, b, n, rays, northWest, whiteBishop);
}

void genWRookSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays){
    genDirStates(dst, b, n, rays, north, whiteRook);
    genDirStates(dst, b, n, rays, east, whiteRook);
    genDirStates(dst, b, n, rays, south, whiteRook);
    genDirStates(dst, b, n, rays, west, whiteRook);
}

void genWQueenSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays){
    genDirStates(dst, b, n, rays, north, whiteQueen);
    genDirStates(dst, b, n, rays, northEast, whiteQueen);
    genDirStates(dst, b, n, rays, east, whiteQueen);
    genDirStates(dst, b, n, rays, southEast, whiteQueen);
    genDirStates(dst, b, n, rays, south, whiteQueen);
    genDirStates(dst, b, n, rays, southWest, whiteQueen);
    genDirStates(dst, b, n, rays, west, whiteQueen);
    genDirStates(dst, b, n, rays, northWest, whiteQueen);
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
            ;
            //genPiecesSuccStates(dst, b, rays, blackPawn);
            //genPiecesSuccStates(dst, b, rays, blackBishop);
            //genPiecesSuccStates(dst, b, rays, blackKnight);
            //genPiecesSuccStates(dst, b, rays, blackRook);
            //genPiecesSuccStates(dst, b, rays, blackQueen);
            //genPiecesSuccStates(dst, b, rays, blackKing);
        }
}

void genPiecesSuccStates(T_boardStates *dst, const T_boardState *b, const T_bitboard **rays, int piece){
    T_bitboard allPieces = *(stateMember(b, piece));
    while(allPieces){
        (*genPieceSuccStates(piece))(dst, b, __builtin_ctzll(allPieces), rays);
        clearBit(&allPieces, __builtin_ctzll(allPieces));
    }
}

void genWKnightSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **jumps){
    T_boardState cpy = *b;
    int j;
    T_bitboard test;
    for(int i = 0; i < 8; i++){
        j =  __builtin_ctzll(jumps[i][n]);
        test = 0;
        setBit(&test, j);
        if(test & wAll(b)){
            continue;
        }
        T_boardState cpy = *b;
        moveAndAttack(&cpy, j, n, whiteKnight);
        addState(dst, &cpy);
    }
}

//This is an almost replica to the function above. Merge into one possibly through using function pointer
//wAll and bAll is calculated numerous times - perhaps it should be stored in state or passed throughout
void genWKingSuccStates(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **steps){
    T_boardState cpy = *b;
    int j;
    T_bitboard test;
    for(int i = 0; i < 8; i++){
        j = __builtin_ctzll(steps[i][n]);
        test = 0;
        setBit(&test, j);
        if(test & wAll(b)){
            continue;
        }
        T_boardState cpy = *b;
        moveAndAttack(&cpy, j, n, whiteKing);
        addState(dst, &cpy);
    }
}

void genBPawnSuccStates(T_boardState c, T_boardStates *ss){


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

void (*genPieceSuccStates(int piece))(T_boardStates *dst, const T_boardState *b, int n, const T_bitboard **rays){
    switch(piece){
        case whitePawn:
            return &genWPawnSuccStates;
        case whiteBishop:
            return &genWBishopSuccStates;
        case whiteKnight:
            return &genWKnightSuccStates;
        case whiteRook:
            return &genWRookSuccStates;
        case whiteQueen:
            return &genWQueenSuccStates;
        case whiteKing:
            return &genWKingSuccStates;
//        case blackPawn:
//            return &genWBishopSuccStates;
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
