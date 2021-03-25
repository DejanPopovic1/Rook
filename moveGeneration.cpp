#include "moveGeneration.hpp"
#include "state.hpp"
#include "bitUtilities.hpp"
#include "moveRules.hpp"
#include "output.hpp"

#include <stdio.h>
#include <assert.h>
#include <iostream>

//Use MovePiece function to simplify statements
//see if more state functions can come in here so they may be inlined

//Alot of the functions here should be defined in state.cpp so move them there

//Use the fact that this returns zero in the function that calls it
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
void promote(T_Node *node, T_boardState *b, int n, int piece){
    T_boardState cpy = *b;
    T_bitboard *sm = pieceBitboard(&cpy, piece);
    b->whosTurn ? setBit(sm, n - 8) : setBit(sm, n + 8);
    b->whosTurn ? clearBit(&(cpy.bPawn), n) : clearBit(&(cpy.wPawn), n);

    addStateNode(node, &cpy);
}

void takePromote(T_Node *node, T_boardState *b, int n, int piece){
    T_boardState cpy = *b;
    T_bitboard *sm = pieceBitboard(&cpy, piece);
    setBit(sm, n);
    b->whosTurn ? clearBit(&(cpy.bPawn), n) : clearBit(&(cpy.wPawn), n);

    addStateNode(node, &cpy);
}

//factor out specific moves once all moveGenerations complete
//Use generateSlideMoves() to codify these moves
//Use *cpy instead of cpy
void genWPawnSuccStates(T_Node *node, T_boardState *b, int n, T_bitboard **rays, int DUMMY){
    //MOVE UP
    if(isUpEmpty(b, n) && !isSecondLastRank(n)){
        T_boardState cpy = *b;
        move(&cpy, n + 8, n, whitePawn);
        addStateNode(node, &cpy);
    }
    //MOVE UP UP
    if(isUpEmpty(b, n) && isUpUpEmpty(b, n) && !isSecondLastRank(n) && isSecondRank(n)){
        T_boardState cpy = *b;
        move(&cpy, n + 16, n, whitePawn);

        addStateNode(node, &cpy);

        //setCharBit(&((dst->bs[dst->fi - 1]).wEnPassants), 7 - (n % 8));

        setCharBit(&node->scc[node->fp - 1]->b.wEnPassants, 7 - (n % 8));

    }
    //CAPTURE LEFT
    if(isPosBlack(b, n + 7) && (n % 8)){
        T_boardState cpy = *b;
        moveAndAttack(&cpy, n + 7, n, whitePawn);
        if(isRankSeven(n)){
            takePromote(node, &cpy, n + 7, whiteBishop);
            takePromote(node, &cpy, n + 7, whiteKnight);
            takePromote(node, &cpy, n + 7, whiteRook);
            takePromote(node, &cpy, n + 7, whiteQueen);
        }
        else{

            addStateNode(node, &cpy);

        }
    }
    //CAPTURE RIGHT
    if(isPosBlack(b, n + 9) && ((n + 1) % 8)){
        T_boardState cpy = *b;
        moveAndAttack(&cpy, n + 9, n, whitePawn);
        if(isRankSeven(n)){
            takePromote(node, &cpy, n + 9, whiteBishop);
            takePromote(node, &cpy, n + 9, whiteKnight);
            takePromote(node, &cpy, n + 9, whiteRook);
            takePromote(node, &cpy, n + 9, whiteQueen);
        }
        else{

            addStateNode(node, &cpy);

        }
    }
    //EN PASSANT LEFT
    char frFile = whatFile(n);
    if((frFile % 8) && isCharBitSet(b->bEnPassants, 7 - (frFile - 1)) && isRankFive(n)){
        T_boardState cpy = *b;
        clearBit(&((&cpy)->bPawn), n - 1);
        move(&cpy, n + 7, n, whitePawn);
        addStateNode(node, &cpy);
    }
    //EN PASSANT RIGHT
    if(((frFile + 1) % 8) && isCharBitSet(b->bEnPassants, 7 - (frFile + 1)) && isRankFive(n)){
        T_boardState cpy = *b;
        clearBit(&((&cpy)->bPawn), n + 1);
        move(&cpy, n + 9, n, whitePawn);
        addStateNode(node, &cpy);
    }
    //PROMOTIONS
    if(isRankSeven(n) && isUpEmpty(b, n)){
        promote(node, b, n, whiteBishop);
        promote(node, b, n, whiteKnight);
        promote(node, b, n, whiteRook);
        promote(node, b, n, whiteQueen);
    }
}

void genBPawnSuccStates(T_Node *node, T_boardState *b, int n, T_bitboard **rays, int DUMMY){
    //MOVE DOWN
    if(isDownEmpty(b, n) && !isSecondRank(n)){
        T_boardState cpy = *b;
        move(&cpy, n - 8, n, blackPawn);

        addStateNode(node, &cpy);
    }
    //MOVE DOWN DOWN
    if(isDownEmpty(b, n) && isDownDownEmpty(b, n) && !isSecondRank(n) && isSecondLastRank(n)){
        T_boardState cpy = *b;
        move(&cpy, n - 16, n, blackPawn);

        addStateNode(node, &cpy);
        //setCharBit(&((dst->bs[dst->fi - 1]).bEnPassants), 7 - (n % 8));
        setCharBit(&node->scc[node->fp - 1]->b.bEnPassants, 7 - (n % 8));
    }
    //CAPTURE RIGHT
    if(isPosWhite(b, n - 7) && ((n + 1) % 8)){
        T_boardState cpy = *b;
        moveAndAttack(&cpy, n - 7, n, blackPawn);
        if(isRankTwo(n)){
            takePromote(node, &cpy, n - 7, blackBishop);
            takePromote(node, &cpy, n - 7, blackKnight);
            takePromote(node, &cpy, n - 7, blackRook);
            takePromote(node, &cpy, n - 7, blackQueen);
        }
        else{

            addStateNode(node, &cpy);
        }
    }
    //CAPTURE LEFT
    if(isPosWhite(b, n - 9) && (n % 8)){
        T_boardState cpy = *b;
        moveAndAttack(&cpy, n - 9, n, blackPawn);
        if(isRankTwo(n)){
            takePromote(node, &cpy, n - 9, blackBishop);
            takePromote(node, &cpy, n - 9, blackKnight);
            takePromote(node, &cpy, n - 9, blackRook);
            takePromote(node, &cpy, n - 9, blackQueen);
        }
        else{

            addStateNode(node, &cpy);
        }
    }
    //EN PASSANT RIGHT
    char frFile = whatFile(n);
    if(((frFile + 1) % 8) && isCharBitSet(b->wEnPassants, 7 - (frFile + 1)) && isRankFour(n)){
        T_boardState cpy = *b;
        clearBit(&(cpy.wPawn), n + 1);
        move(&cpy, n - 7, n, blackPawn);

        addStateNode(node, &cpy);
    }
    //EN PASSANT LEFT
    if((frFile % 8) && isCharBitSet(b->wEnPassants, 7 - (frFile - 1)) && isRankFour(n)){
        T_boardState cpy = *b;
        clearBit(&(cpy.wPawn), n - 1);
        move(&cpy, n - 9, n, blackPawn);

        addStateNode(node, &cpy);
    }
    //PROMOTIONS
    if(isRankTwo(n) && isDownEmpty(b, n)){
        promote(node, b, n, blackBishop);
        promote(node, b, n, blackKnight);
        promote(node, b, n, blackRook);
        promote(node, b, n, blackQueen);
    }
}

//Copy and paste these for other pieces
void genMoves(T_Node *node, T_boardState *b, int n, T_bitboard *validMoves, int piece, int direction){
    int validMove = (isNortherlyOrEast(direction) ? __builtin_ctzll(*validMoves) : BITBOARD_INDEX_SIZE - __builtin_clzll(*validMoves));
    T_boardState cpy = *b;
    move(&cpy, validMove, n, piece);

    addStateNode(node, &cpy);
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
void genDirStates(T_Node *node, T_boardState *b, int n, T_bitboard **rays, int direction, int piece){
    T_bitboard mb = moveBoardDir(b, n, direction, rays);
    if(!mb){
        return;
    }
    while(__builtin_popcountll(mb) > 1){
        genMoves(node, b, n, &mb, piece, direction);
    }
    int lastPos = BITBOARD_INDEX_SIZE - __builtin_clzll(mb);
    if(isPosSameSide(b, lastPos)){
        return;
    }
    else if(isPosEmpty(b, lastPos)){
        T_boardState cpy = *b;
        move(&cpy, lastPos, n, piece);

        addStateNode(node, &cpy);
    }
    else{
        T_boardState cpy = *b;
        moveAndAttack(&cpy, lastPos, n, piece);

        addStateNode(node, &cpy);
    }
}

void genRaySuccStates(T_Node *node, T_boardState *b, int n, T_bitboard **rays, int piece){
    //int numOfBeforeStates = dst->fi;
    int numOfBeforeStatesN = node->fp;
    switch(piece){
        case whiteBishop:
            genDirStates(node, b, n, rays, northEast, whiteBishop);
            genDirStates(node, b, n, rays, southEast, whiteBishop);
            genDirStates(node, b, n, rays, southWest, whiteBishop);
            genDirStates(node, b, n, rays, northWest, whiteBishop);
            break;
        case whiteRook:
            genDirStates(node, b, n, rays, north, whiteRook);
            genDirStates(node, b, n, rays, east, whiteRook);
            genDirStates(node, b, n, rays, south, whiteRook);
            genDirStates(node, b, n, rays, west, whiteRook);
            break;
        case whiteQueen:
            genDirStates(node, b, n, rays, north, whiteQueen);
            genDirStates(node, b, n, rays, northEast, whiteQueen);
            genDirStates(node, b, n, rays, east, whiteQueen);
            genDirStates(node, b, n, rays, southEast, whiteQueen);
            genDirStates(node, b, n, rays, south, whiteQueen);
            genDirStates(node, b, n, rays, southWest, whiteQueen);
            genDirStates(node, b, n, rays, west, whiteQueen);
            genDirStates(node, b, n, rays, northWest, whiteQueen);
            break;
        case blackBishop:
            genDirStates(node, b, n, rays, northEast, blackBishop);
            genDirStates(node, b, n, rays, southEast, blackBishop);
            genDirStates(node, b, n, rays, southWest, blackBishop);
            genDirStates(node, b, n, rays, northWest, blackBishop);
            break;
        case blackRook:
            genDirStates(node, b, n, rays, north, blackRook);
            genDirStates(node, b, n, rays, east, blackRook);
            genDirStates(node, b, n, rays, south, blackRook);
            genDirStates(node, b, n, rays, west, blackRook);
            break;
        case blackQueen:
            genDirStates(node, b, n, rays, north, blackQueen);
            genDirStates(node, b, n, rays, northEast, blackQueen);
            genDirStates(node, b, n, rays, east, blackQueen);
            genDirStates(node, b, n, rays, southEast, blackQueen);
            genDirStates(node, b, n, rays, south, blackQueen);
            genDirStates(node, b, n, rays, southWest, blackQueen);
            genDirStates(node, b, n, rays, west, blackQueen);
            genDirStates(node, b, n, rays, northWest, blackQueen);
            break;
    }
    //int numOfAfterStates = dst->fi;
    int numOfAfterStatesN = node->fp;
//    if(piece == whiteRook && n == 0){
//        for(int i = numOfBeforeStates; i < numOfAfterStates; i++){
//            dst->bs[i].castlesLRWhite = 0;
//        }
//    }
//    else if(piece == whiteRook && n == 7){
//        for(int i = numOfBeforeStates; i < numOfAfterStates; i++){
//            dst->bs[i].castlesRRWhite = 0;
//        }
//    }
//    else if(piece == blackRook && n == 56){
//        for(int i = numOfBeforeStates; i < numOfAfterStates; i++){
//            dst->bs[i].castlesLRBlack = 0;
//        }
//    }
//    else if(piece == blackRook && n == 63){
//        for(int i = numOfBeforeStates; i < numOfAfterStates; i++){
//            dst->bs[i].castlesRRBlack = 0;
//        }
//    }


    if(piece == whiteRook && n == 0){
        for(int i = numOfBeforeStatesN; i < numOfAfterStatesN; i++){
            node->scc[i]->b.castlesLRWhite = 0;
        }
    }
    else if(piece == whiteRook && n == 7){
        for(int i = numOfBeforeStatesN; i < numOfAfterStatesN; i++){
            node->scc[i]->b.castlesRRWhite = 0;
        }
    }
    else if(piece == blackRook && n == 56){
        for(int i = numOfBeforeStatesN; i < numOfAfterStatesN; i++){
            node->scc[i]->b.castlesLRBlack = 0;
        }
    }
    else if(piece == blackRook && n == 63){
        for(int i = numOfBeforeStatesN; i < numOfAfterStatesN; i++){
            node->scc[i]->b.castlesRRBlack = 0;
        }
    }








}

//Rename this to genPseudoValidStates
bool genSuccStates(T_Node *node, T_boardState *b){
        T_bitboard **rays = createRays();
        T_bitboard **jumps = createJumps();
        T_bitboard **steps = createSteps();
        if(!b->whosTurn){
            genPiecesSuccStates(node, b, rays, whitePawn);
            genPiecesSuccStates(node, b, rays, whiteBishop);
            genPiecesSuccStates(node, b, jumps, whiteKnight);
            genPiecesSuccStates(node, b, rays, whiteRook);
            genPiecesSuccStates(node, b, rays, whiteQueen);
            genPiecesSuccStates(node, b, steps, whiteKing);
        }
        else{
            genPiecesSuccStates(node, b, rays, blackPawn);
            genPiecesSuccStates(node, b, rays, blackBishop);
            genPiecesSuccStates(node, b, jumps, blackKnight);
            genPiecesSuccStates(node, b, rays, blackRook);
            genPiecesSuccStates(node, b, rays, blackQueen);
            genPiecesSuccStates(node, b, steps, blackKing);
        }
        freeRays(rays);
        freeJumps(jumps);
        freeSteps(steps);
        bool player = b->whosTurn;
        if(isKingsExist(node, !player)){
            return false;//Current opposite player is in check
        }
        return true;//Current opposite player is not in check
}

//THIS FUNCTION MUST BE CALLED AS OTHER PLAYER - RATHER BUILD THIS FACT INTO THIS FUNCTION
//Take away whosKing parameter. This may be deduced from n->b->whosTurn++
//This function checks if the whosKing player has a king in any of the successor states. It has nothing to do with n itself but rather its successor states!
bool isKingsExist(T_Node *n, bool whosKing){
    for(int i = 0; i < n->fp; i++){
        if(!isKingExist(n->scc[i], whosKing)){
            return false;
        }
    }
    return true;
}

bool isKingExist(T_Node *n, bool whosKing){
    if(whosKing){
        if(n->b.bKing){
            return true;
        }
    }
    else{
        if(n->b.wKing){
            return true;
        }
    }
    return false;
}





//Refactor out the castling into a seperate function
//Use get piece from pieces
void genPiecesSuccStates(T_Node *node, T_boardState *b, T_bitboard **moveRules, int piece){
    T_bitboard allPieces = *(pieceBitboard(b, piece));
    while(allPieces){
        (*genPieceSuccStates(piece))(node, b, __builtin_ctzll(allPieces), moveRules, piece);
        clearBit(&allPieces, __builtin_ctzll(allPieces));
    }
}

void generateCastlingState(T_Node *node, T_boardState *b, T_bitboard castlePass){
    T_boardState cpy = *b;
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

    addStateNode(node, &cpy);
}

//Use bitboard bit manipulation to speed this up
//Pass in rays for efficiency
//castlePass and turn mechanics are awkward - refactor
//There are three serial "while" loops. When breaking out of one, find a way to break out of all
//Please refactor this dogshow
void generateCastlingStates(T_Node *node, T_boardState *b, T_bitboard **moveRules, int piece, T_bitboard castlePass){
    T_boardState tmp = *b;
    //T_bitboard **rays = createRays();
    T_bitboard **rays = moveRules;
    if(b->whosTurn && (castlePass == BLACK_KINGSIDE_PASS || castlePass == BLACK_QUEENSIDE_PASS)){
        bool cnd1 = !(all(b) & castlePass);
        bool cnd2 = true;
        //
        bool cnd3 = true;
        if(castlePass == BLACK_KINGSIDE_PASS && (BLACK_KINGSIDE_ATTACKING & (b->wPawn | b->wKing) || BLACK_KINGSIDE_ATTACKING_K & b->wKnight)){
            cnd3 = false;
        }
        else if(castlePass == BLACK_QUEENSIDE_PASS && (BLACK_QUEENSIDE_ATTACKING & (b->wPawn | b->wKing) || BLACK_QUEENSIDE_ATTACKING_K & b->wKnight)){
            cnd3 = false;
        }
        //
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
            }
        }
        while(tmp.wRook){
            if(__builtin_popcountll(tmp.wRook)){
                k = __builtin_ctzll(getPieceFromPieces(&(tmp.wRook)));
            }
            else{
                break;
            }
            if(rays[north][k] & castlePass && !(rays[north][k] & a)
               ){
                cnd2 = false;
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
            }
        }
        bool cnd4;
        if(castlePass == BLACK_KINGSIDE_PASS){
            cnd4 = b->castlesKBlack && b->castlesRRBlack;
        }
        else if(castlePass == BLACK_QUEENSIDE_PASS){
            cnd4 = b->castlesKBlack && b->castlesLRBlack;
        }
        if(cnd1 && cnd2 && cnd3 && cnd4){
            generateCastlingState(node, b, castlePass);
        }
    }
    else if(!b->whosTurn && (castlePass == WHITE_KINGSIDE_PASS || castlePass == WHITE_QUEENSIDE_PASS)){
        bool cnd1 = !(all(b) & castlePass);
        bool cnd2 = true;
        //
        bool cnd3 = true;
        if(castlePass == WHITE_KINGSIDE_PASS && (WHITE_KINGSIDE_ATTACKING & (b->bPawn | b->bKing) || WHITE_KINGSIDE_ATTACKING_K & b->bKnight)){
            cnd3 = false;
        }
        else if(castlePass == WHITE_QUEENSIDE_PASS && (WHITE_QUEENSIDE_ATTACKING & (b->bPawn | b->bKing) || WHITE_QUEENSIDE_ATTACKING_K & b->bKnight)){
            cnd3 = false;
        }
        //
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
            }
        }
        while(tmp.bQueen){
            if(__builtin_popcountll(tmp.bQueen)){
               l = __builtin_ctzll(getPieceFromPieces(&(tmp.bQueen)));
            }
            else{
                break;
            }
            if(rays[southEast][l] & castlePass && !(rays[southEast][l] & a) ||
               rays[southWest][l] & castlePass && !(rays[southWest][l] & a) ||
               rays[south][l] & castlePass && !(rays[south][l] & a)
               ){
               cnd2 = false;
            }
        }
        bool cnd4;
        if(castlePass == WHITE_KINGSIDE_PASS){
            cnd4 = b->castlesKWhite && b->castlesRRWhite;
        }
        else if(castlePass == WHITE_QUEENSIDE_PASS){
            cnd4 = b->castlesKWhite && b->castlesLRWhite;
        }
        if(cnd1 && cnd2 && cnd3 && cnd4){
            generateCastlingState(node, b, castlePass);
        }
    }
}

//Remove mentions of white and black generations of castling at the bottom of this functionS
void genJumpOrStepSuccStates(T_Node *node, T_boardState *b, int n, T_bitboard **moveRules, int piece){
    //int numOfBeforeStates = dst->fi;
    int numOfBeforeStatesN = node->fp;
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
        addStateNode(node, &cpy);
    }
    //int numOfAfterStates = dst->fi;
    int numOfAfterStatesN = node->fp;

    if(piece == whiteKing && n == 4){
        for(int i = numOfBeforeStatesN; i < numOfAfterStatesN; i++){
            //dst->bs[i].castlesKWhite = 0;
            node->scc[i]->b.castlesKWhite = 0;
        }
    }
    else if(piece == blackKing && n == 60){
        for(int i = numOfBeforeStatesN; i < numOfAfterStatesN; i++){
            //dst->bs[i].castlesKBlack = 0;
            node->scc[i]->b.castlesKBlack = 0;
        }
    }
    if(piece == whiteKing || piece == blackKing){
        generateCastlingStates(node, b, moveRules, piece, BLACK_KINGSIDE_PASS);
        generateCastlingStates(node, b, moveRules, piece, BLACK_QUEENSIDE_PASS);
        generateCastlingStates(node, b, moveRules, piece, WHITE_KINGSIDE_PASS);
        generateCastlingStates(node, b, moveRules, piece, WHITE_QUEENSIDE_PASS);
    }
}

//Look at potentially removing this. It would have worked if the moveGenerators took the same info
//wPawnGenerate doesnt take the last argument piece so this needs to be corrected
void (*genPieceSuccStates(int piece))(T_Node *node, T_boardState *b, int n, T_bitboard **rays, int piece){
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

//bool isKingsExist(T_boardStates *bss, bool whosKing){
//    for(int i; i < bss->fi; i++){
//        if(!isKingExist(&bss->bs[i], whosKing)){
//            return false;
//        }
//    }
//    return true;
//}

//bool isKingExist(T_boardState *b, bool whosKing){
//    if(whosKing){
//        if(b->bKing){
//            return true;
//        }
//    }
//    else{
//        if(b->wKing){
//            return true;
//        }
//    }
//    return false;
//}

//!!!!!!!!!!!!!!!
//CHANGE BSS TO NODE!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!
//bool isInCheck(T_boardState *b){
//    bool result;
//    bool whosTurn = b->whosTurn;
//    b->whosTurn++;
//    b->evaluateCheck = 1;
//    T_boardStates *bss = initialiseStates();
//    T_Node node;
//    genSuccStates(&node, bss, b);
//    if(!isKingsExist(bss, whosTurn)){
//        b->whosTurn++;
//        b->evaluateCheck = 0;
//        return true;
//    }
//    b->whosTurn++;
//    b->evaluateCheck = 0;
//    return false;
//}
