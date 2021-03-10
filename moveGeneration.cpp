#include <assert.h>
#include "moveGeneration.hpp"
#include "state.hpp"
//#include "GlobalDeclarations.h"
#include "bitUtilities.hpp"
#include "moveRules.hpp"
#include <stdio.h>
#include "output.hpp"

//Use MovePiece function to simplify statements
//see if more state functions can come in here so they may be inlined

T_bitboard getPieceFromPieces(T_bitboard *pcs){
    if(!__builtin_popcountll(*pcs)){
        return 0;
    }
    T_bitboard result = 0;
    char i = __builtin_ctzll(*pcs);
    clearBit(pcs, i);
    setBit(&result, i);
    return result;
}

//for efficiency, enumerate empty as 6. White 0 - 5 and black 7 - 12. Then just test <6
bool isWhitePiece(int pieceValue){
    if(pieceValue > 0 && pieceValue < 7){
        return true;
    }
    return false;
}

//for efficiency, enumerate empty as 6. White 0 - 5 and black 7 - 12. Then just test >6
bool isBlackPiece(int pieceValue){
    if(pieceValue > 6 && pieceValue < 13){
        return true;
    }
    return false;
}

bool isPosSameSide(T_boardState *b, int n){
    if(!b->whosTurn){
        T_bitboard o = b->wPawn | b->wBishop | b->wKnight | b->wRook | b->wQueen | b->wKing;
        if(isBitSet(o, n)){
            return true;
        }
        return false;
    }
    else{
        T_bitboard o = b->bPawn | b->bBishop | b->bKnight | b->bRook | b->bQueen | b->bKing;
        if(isBitSet(o, n)){
            return true;
        }
        return false;
    }
}

bool isPosWhite(T_boardState *b, int n){
    T_bitboard o = b->wPawn | b->wBishop | b->wKnight | b->wRook | b->wQueen | b->wKing;
    if(isBitSet(o, n)){
        return true;
    }
    return false;
}

bool isPosBlack(T_boardState *b, int n){
    T_bitboard o = b->bPawn | b->bBishop | b->bKnight | b->bRook | b->bQueen | b->bKing;
    if(isBitSet(o, n)){
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

bool isUpEmpty(T_boardState *b, int n){
    if(isPosEmpty(b, n + 8)){
        return true;
    }
    return false;
}

bool isUpUpEmpty(T_boardState *b, int n){
    if(isPosEmpty(b, n + 8) && isPosEmpty(b, n + 16)){
        return true;
    }
    return false;
}

bool isDownEmpty(T_boardState *b, int n){
    if(isPosEmpty(b, n - 8)){
        return true;
    }
    return false;
}

bool isDownDownEmpty(T_boardState *b, int n){
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

T_bitboard *pieceBitboard(T_boardState *b, int piece){
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
    T_bitboard *sm = (*pieceBitboard)(b, piece);
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
    T_bitboard *sm = (*pieceBitboard)(b, piece);
    clearBit(sm, src);
    setBit(sm, dst);
}

//Refactor this to be more inline with takePromote which will allow the use of a single promote function
void promote(T_boardStates *dst, T_boardState *b, int n, int piece){
    T_boardState cpy = *b;
    T_bitboard *sm = pieceBitboard(&cpy, piece);
    b->whosTurn ? setBit(sm, n - 8) : setBit(sm, n + 8);
    b->whosTurn ? clearBit(&(cpy.bPawn), n) : clearBit(&(cpy.wPawn), n);
    addState(dst, &cpy);
}

void takePromote(T_boardStates *dst, T_boardState *b, int n, int piece){
    T_boardState cpy = *b;
    T_bitboard *sm = pieceBitboard(&cpy, piece);
    setBit(sm, n);
    b->whosTurn ? clearBit(&(cpy.bPawn), n) : clearBit(&(cpy.wPawn), n);
    addState(dst, &cpy);
}

//factor out specific moves once all moveGenerations complete
//Use generateSlideMoves() to codify these moves
//Use *cpy instead of cpy
void genWPawnSuccStates(T_boardStates *dst, T_boardState *b, int n, T_bitboard **rays, int DUMMY){
    //MOVE UP
    if(isUpEmpty(b, n) && !isSecondLastRank(n)){
        T_boardState cpy = *b;
        move(&cpy, n + 8, n, whitePawn);
        addState(dst, &cpy);
    }
    //MOVE UP UP
    if(isUpEmpty(b, n) && isUpUpEmpty(b, n) && !isSecondLastRank(n) && isSecondRank(n)){
        T_boardState cpy = *b;
        move(&cpy, n + 16, n, whitePawn);
        addState(dst, &cpy);
        setCharBit(&((dst->bs[dst->fi - 1]).wEnPassants), 7 - (n % 8));
    }
    //CAPTURE LEFT
    if(isPosBlack(b, n + 7) && (n % 8)){
        T_boardState cpy = *b;
        moveAndAttack(&cpy, n + 7, n, whitePawn);
        if(isRankSeven(n)){
            takePromote(dst, &cpy, n + 7, whiteBishop);
            takePromote(dst, &cpy, n + 7, whiteKnight);
            takePromote(dst, &cpy, n + 7, whiteRook);
            takePromote(dst, &cpy, n + 7, whiteQueen);
        }
        else{
            addState(dst, &cpy);
        }
    }
    //CAPTURE RIGHT
    if(isPosBlack(b, n + 9) && ((n + 1) % 8)){
        T_boardState cpy = *b;
        moveAndAttack(&cpy, n + 9, n, whitePawn);
        if(isRankSeven(n)){
            takePromote(dst, &cpy, n + 9, whiteBishop);
            takePromote(dst, &cpy, n + 9, whiteKnight);
            takePromote(dst, &cpy, n + 9, whiteRook);
            takePromote(dst, &cpy, n + 9, whiteQueen);
        }
        else{
            addState(dst, &cpy);
        }
    }
    //EN PASSANT LEFT
    char frFile = whatFile(n);
    if((frFile % 8) && isCharBitSet(b->bEnPassants, 7 - (frFile - 1)) && isRankFive(n)){
        T_boardState cpy = *b;
        clearBit(&((&cpy)->bPawn), n - 1);
        move(&cpy, n + 7, n, whitePawn);
        addState(dst, &cpy);
    }
    //EN PASSANT RIGHT
    if(((frFile + 1) % 8) && isCharBitSet(b->bEnPassants, 7 - (frFile + 1)) && isRankFive(n)){
        T_boardState cpy = *b;
        clearBit(&((&cpy)->bPawn), n + 1);
        move(&cpy, n + 9, n, whitePawn);
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

void genBPawnSuccStates(T_boardStates *dst, T_boardState *b, int n, T_bitboard **rays, int DUMMY){
    //MOVE DOWN
    if(isDownEmpty(b, n) && !isSecondRank(n)){
        T_boardState cpy = *b;
        move(&cpy, n - 8, n, blackPawn);
        addState(dst, &cpy);
    }
    //MOVE DOWN DOWN
    if(isDownEmpty(b, n) && isDownDownEmpty(b, n) && !isSecondRank(n) && isSecondLastRank(n)){
        T_boardState cpy = *b;
        move(&cpy, n - 16, n, blackPawn);
        //setCharBit(&(cpy.bEnPassants), 7 - (n % 8));
        addState(dst, &cpy);
        setCharBit(&((dst->bs[dst->fi - 1]).bEnPassants), 7 - (n % 8));
    }
    //CAPTURE RIGHT
    if(isPosWhite(b, n - 7) && ((n + 1) % 8)){
        T_boardState cpy = *b;
        moveAndAttack(&cpy, n - 7, n, blackPawn);
        if(isRankTwo(n)){
            takePromote(dst, &cpy, n - 7, blackBishop);
            takePromote(dst, &cpy, n - 7, blackKnight);
            takePromote(dst, &cpy, n - 7, blackRook);
            takePromote(dst, &cpy, n - 7, blackQueen);
        }
        else{
            addState(dst, &cpy);
        }
    }
    //CAPTURE LEFT
    if(isPosWhite(b, n - 9) && (n % 8)){
        T_boardState cpy = *b;
        moveAndAttack(&cpy, n - 9, n, blackPawn);
        if(isRankTwo(n)){
            takePromote(dst, &cpy, n - 9, blackBishop);
            takePromote(dst, &cpy, n - 9, blackKnight);
            takePromote(dst, &cpy, n - 9, blackRook);
            takePromote(dst, &cpy, n - 9, blackQueen);
        }
        else{
            addState(dst, &cpy);
        }
    }
    //EN PASSANT RIGHT
    char frFile = whatFile(n);
    if(((frFile + 1) % 8) && isCharBitSet(b->wEnPassants, 7 - (frFile + 1)) && isRankFour(n)){
        T_boardState cpy = *b;
        clearBit(&(cpy.wPawn), n + 1);
        move(&cpy, n - 7, n, blackPawn);
        addState(dst, &cpy);
    }
    //EN PASSANT LEFT
    if((frFile % 8) && isCharBitSet(b->wEnPassants, 7 - (frFile - 1)) && isRankFour(n)){
        T_boardState cpy = *b;
        clearBit(&(cpy.wPawn), n - 1);
        move(&cpy, n - 9, n, blackPawn);
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
void genMoves(T_boardStates *dst, T_boardState *b, int n, T_bitboard *validMoves, int piece, int direction){
    int validMove = (isNortherlyOrEast(direction) ? __builtin_ctzll(*validMoves) : BITBOARD_INDEX_SIZE - __builtin_clzll(*validMoves));
    T_boardState cpy = *b;
    move(&cpy, validMove, n, piece);
//    if(piece == whiteRook){
//        cpy.castlesWhite
//    }
    addState(dst, &cpy);
    clearBit(validMoves, validMove);
}

//The result of this is passed to genDirStates and it includes the ray up to and including the end of board/same piece/opponent piece
T_bitboard moveBoardDir(T_boardState *b, int n, int direction, T_bitboard **rays){
    T_bitboard ray = rays[direction][n];
    T_bitboard occupancyBoard = bAll(b) | wAll(b);
    T_bitboard intersect = ray & occupancyBoard;
    int firstBlocker = (isNortherlyOrEast(direction) ? __builtin_ctzll(intersect) : BITBOARD_INDEX_SIZE - __builtin_clzll(intersect));
    T_bitboard intersectRay = (!intersect) ? 0 : rays[direction][firstBlocker];
    return (ray ^ intersectRay);
}

//Refactor out quiete vs attacking moves
//This function wont work for black unless you have a function called OPPOSING_COLOUR instead of isPosBlack. Or, pass function pointer. Better yet, use info in state.
void genDirStates(T_boardStates *dst, T_boardState *b, int n, T_bitboard **rays, int direction, int piece){
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

void genRaySuccStates(T_boardStates *dst, T_boardState *b, int n, T_bitboard **rays, int piece){
    int numOfBeforeStates = dst->fi;
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
        case blackBishop:
            genDirStates(dst, b, n, rays, northEast, blackBishop);
            genDirStates(dst, b, n, rays, southEast, blackBishop);
            genDirStates(dst, b, n, rays, southWest, blackBishop);
            genDirStates(dst, b, n, rays, northWest, blackBishop);
            break;
        case blackRook:
            genDirStates(dst, b, n, rays, north, blackRook);
            genDirStates(dst, b, n, rays, east, blackRook);
            genDirStates(dst, b, n, rays, south, blackRook);
            genDirStates(dst, b, n, rays, west, blackRook);
            break;
        case blackQueen:
            genDirStates(dst, b, n, rays, north, blackQueen);
            genDirStates(dst, b, n, rays, northEast, blackQueen);
            genDirStates(dst, b, n, rays, east, blackQueen);
            genDirStates(dst, b, n, rays, southEast, blackQueen);
            genDirStates(dst, b, n, rays, south, blackQueen);
            genDirStates(dst, b, n, rays, southWest, blackQueen);
            genDirStates(dst, b, n, rays, west, blackQueen);
            genDirStates(dst, b, n, rays, northWest, blackQueen);
            break;
    }
    int numOfAfterStates = dst->fi;
    if(piece == whiteRook && n == 0){
        for(int i = numOfBeforeStates; i < numOfAfterStates; i++){
            dst->bs[i].castlesLRWhite = 0;
        }
    }
    else if(piece == whiteRook && n == 7){
        for(int i = numOfBeforeStates; i < numOfAfterStates; i++){
            dst->bs[i].castlesRRWhite = 0;
        }
    }
    else if(piece == blackRook && n == 56){
        for(int i = numOfBeforeStates; i < numOfAfterStates; i++){
            dst->bs[i].castlesLRBlack = 0;
        }
    }
    else if(piece == blackRook && n == 63){
        for(int i = numOfBeforeStates; i < numOfAfterStates; i++){
            dst->bs[i].castlesRRBlack = 0;
        }
    }
}

void genSuccStates(T_boardStates *dst, T_boardState *b){
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
            genPiecesSuccStates(dst, b, rays, blackBishop);
            genPiecesSuccStates(dst, b, jumps, blackKnight);
            genPiecesSuccStates(dst, b, rays, blackRook);
            genPiecesSuccStates(dst, b, rays, blackQueen);
            genPiecesSuccStates(dst, b, steps, blackKing);
        }
}

//Refactor out the castling into a seperate function
void genPiecesSuccStates(T_boardStates *dst, T_boardState *b, T_bitboard **moveRules, int piece){
    T_bitboard allPieces = *(pieceBitboard(b, piece));
    while(allPieces){
        (*genPieceSuccStates(piece))(dst, b, __builtin_ctzll(allPieces), moveRules, piece);
        clearBit(&allPieces, __builtin_ctzll(allPieces));
    }
}

//Just check rays for now but add in pawns/kings/knights thereafter
bool isPosAttacked(T_boardState *b, T_bitboard castlePass){
    //Generate SW, S, SE rays from all bishops, rooks and queens - all bitboards anded

    return false;
}

void generateCastlingState(T_boardStates *dst, T_boardState *b, T_bitboard castlePass){
    T_boardState cpy = *b;
    std::vector<std::string> gameMoves;
    //printState(*b, 0, gameMoves);
    switch(castlePass){
        case BLACK_KINGSIDE_PASS:
            clearBit(&cpy.bRook, 63);
            clearBit(&cpy.bKing, 60);
            setBit(&cpy.bRook, 61);
            setBit(&cpy.bKing, 62);
            break;
        case BLACK_QUEENSIDE_PASS:
            clearBit(&cpy.bRook, 56);
            clearBit(&cpy.bKing, 60);
            setBit(&cpy.bRook, 59);
            setBit(&cpy.bKing, 58);
            break;
        case WHITE_KINGSIDE_PASS:
            clearBit(&cpy.wRook, 7);
            clearBit(&cpy.wKing, 4);
            setBit(&cpy.wRook, 5);
            setBit(&cpy.wKing, 6);
            break;
        case WHITE_QUEENSIDE_PASS:
            clearBit(&cpy.wRook, 0);
            clearBit(&cpy.wKing, 4);
            setBit(&cpy.wRook, 3);
            setBit(&cpy.wKing, 2);
            break;
        default:
            assert(false);
    }
    addState(dst, &cpy);
}

//Use bitboard bit manipulation to speed this up
//Pass in rays for efficiency
//castlePass and turn mechanics are awkward - refactor
void generateCastlingStates(T_boardStates *dst, T_boardState *b, T_bitboard **moveRules, int piece, T_bitboard castlePass){
    T_boardState tmp = *b;
    T_bitboard **rays = createRays();
    if(b->whosTurn && (castlePass == BLACK_KINGSIDE_PASS || castlePass == BLACK_QUEENSIDE_PASS)){
        bool cnd1 = !(all(b) & castlePass);
        bool cnd2 = true;
        int j, k, l;
        T_bitboard a = all(b);
        while(tmp.wBishop){
            if(__builtin_popcountll(tmp.wBishop)){
                j = __builtin_ctzll(getPieceFromPieces(&(tmp.wBishop)));
            }
            else{
                break;
            }
            if(rays[northEast][j] & castlePass && !(rays[northEast][j] & a) ||
               rays[northWest][j] & castlePass && !(rays[northWest][j] & a)
               ){
                cnd2 = false;
                break;
            }
        }
        while(tmp.wRook){
            if(__builtin_popcountll(tmp.wRook)){
                k = __builtin_ctzll(getPieceFromPieces(&(tmp.wRook)));
            }
            else{
                break;
            }
            if(rays[north][k] & castlePass && !(rays[north][k] & a)){
                cnd2 = false;
                break;
            }
        }
        while(tmp.wQueen){
            if(__builtin_popcountll(tmp.wQueen)){
               l = __builtin_ctzll(getPieceFromPieces(&(tmp.wQueen)));
            }
            else{
                break;
            }
            if(rays[northEast][l] & castlePass && !(rays[northEast][l] & a) ||
               rays[northWest][l] & castlePass && !(rays[northWest][l] & a) ||
               rays[north][l] & castlePass && !(rays[north][l] & a)
               ){
                cnd2 = false;
                break;
            }
        }
        if(cnd1 && cnd2){
            generateCastlingState(dst, &tmp, castlePass);
        }
    }
    else if(!b->whosTurn && (castlePass == WHITE_KINGSIDE_PASS || castlePass == WHITE_QUEENSIDE_PASS)){
        bool cnd1 = !(all(b) & castlePass);
        bool cnd2 = true;
        int j, k, l;
        T_bitboard a = all(b);
        while(tmp.bBishop){
            if(__builtin_popcountll(tmp.bBishop)){
                j = __builtin_ctzll(getPieceFromPieces(&(tmp.bBishop)));
            }
            else{
                break;
            }
            if(rays[southEast][j] & castlePass && !(rays[southEast][j] & a) ||
               rays[southWest][j] & castlePass && !(rays[southWest][j] & a)
               ){
                cnd2 = false;
                //break;
            }
        }
        while(tmp.bRook){
            if(__builtin_popcountll(tmp.bRook)){
                k = __builtin_ctzll(getPieceFromPieces(&(tmp.bRook)));
            }
            else{
                break;
            }
            if(rays[south][k] & castlePass && !(rays[south][k] & a)
               ){
                cnd2 = false;
                //break;
            }
        }
        while(tmp.bQueen){
            if(__builtin_popcountll(tmp.bQueen)){
               l = __builtin_ctzll(getPieceFromPieces(&(tmp.bQueen)));
            }
            else{
                break;
            }
            T_bitboard test = 57548;
            printTBitboard(test);
//            printTBitboard(getPieceFromPieces(&test));
//            printTBitboard(getPieceFromPieces(&test));
//            printTBitboard(getPieceFromPieces(&test));
//            printTBitboard(getPieceFromPieces(&test));
//            printTBitboard(getPieceFromPieces(&test));
//            printTBitboard(getPieceFromPieces(&test));
//            printTBitboard(getPieceFromPieces(&test));
//            printTBitboard(getPieceFromPieces(&test));

            //l = __builtin_ctzll(getPieceFromPieces(&test));
            //printTBitboard(a);
            //printf("%d\n\n", l);
            //printTBitboard(castlePass);
            //printTBitboard(rays[southEast][l]);
            if(rays[southEast][l] & castlePass && !(rays[southEast][l] & a) ||
               rays[southWest][l] & castlePass && !(rays[southWest][l] & a) ||
               rays[south][l] & castlePass && !(rays[south][l] & a)
               ){
               cnd2 = false;
                //break;
            }
        }
        //printf("%d %d\n\n", cnd1, cnd2);
        if(cnd1 && cnd2){
            generateCastlingState(dst, b, castlePass);
        }
    }
}

//Remove mentions of white and black generations of castling at the bottom of this functionS
void genJumpOrStepSuccStates(T_boardStates *dst, T_boardState *b, int n, T_bitboard **moveRules, int piece){
    int numOfBeforeStates = dst->fi;
    T_boardState cpy = *b;
    int j;
    T_bitboard test;
    for(int i = 0; i < 8; i++){
        j = __builtin_ctzll(moveRules[i][n]);
        if(!j){
            continue;
        }
        test = 0;
        setBit(&test, j);
        if(test & sameAll(b)){
            continue;
        }
        T_boardState cpy = *b;
        moveAndAttack(&cpy, j, n, piece);
        addState(dst, &cpy);
    }
    int numOfAfterStates = dst->fi;
    if(piece == whiteKing && n == 4){
        for(int i = numOfBeforeStates; i < numOfAfterStates; i++){
            dst->bs[i].castlesKWhite = 0;
        }
    }
    else if(piece == blackKing && n == 60){
        for(int i = numOfBeforeStates; i < numOfAfterStates; i++){
            dst->bs[i].castlesKBlack = 0;
        }
    }
    if(piece == whiteKing || piece == blackKing){
        generateCastlingStates(dst, b, moveRules, piece, BLACK_KINGSIDE_PASS);
        generateCastlingStates(dst, b, moveRules, piece, BLACK_QUEENSIDE_PASS);
        generateCastlingStates(dst, b, moveRules, piece, WHITE_KINGSIDE_PASS);
        generateCastlingStates(dst, b, moveRules, piece, WHITE_QUEENSIDE_PASS);
    }
}

//Look at potentially removing this. It would have worked if the moveGenerators took the same info
//wPawnGenerate doesnt take the last argument piece so this needs to be corrected
void (*genPieceSuccStates(int piece))(T_boardStates *dst, T_boardState *b, int n, T_bitboard **rays, int piece){
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
        case blackBishop:
            return &genRaySuccStates;
        case blackKnight:
            return &genJumpOrStepSuccStates;
        case blackRook:
            return &genRaySuccStates;
        case blackQueen:
            return &genRaySuccStates;
        case blackKing:
            return &genJumpOrStepSuccStates;
        default:
            assert(false);
    }
}
