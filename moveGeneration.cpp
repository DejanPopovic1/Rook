#include "moveGeneration.hpp"
#include "state.hpp"
#include "bitUtilities.hpp"
#include "moveRules.hpp"
#include "output.hpp"

#include <stdio.h>
#include <assert.h>
#include <iostream>

//see if more state functions can come in here so they may be inlined
//Alot of state recalculations in functions. Rather calculate them once and store them in state
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
void genWPawnSuccStates(T_Node *node, T_boardState *b, int n, int DUMMY){
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

void genBPawnSuccStates(T_Node *node, T_boardState *b, int n, int DUMMY){
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
T_bitboard moveBoardDir(T_boardState *b, int n, int direction){
    T_bitboard rayMovementRules[8][64] =
    {
        {72340172838076672, 144680345676153344, 289360691352306688, 578721382704613376, 1157442765409226752, 2314885530818453504, 4629771061636907008, 9259542123273814016, 72340172838076416, 144680345676152832, 289360691352305664, 578721382704611328, 1157442765409222656, 2314885530818445312, 4629771061636890624, 9259542123273781248, 72340172838010880, 144680345676021760, 289360691352043520, 578721382704087040, 1157442765408174080, 2314885530816348160, 4629771061632696320, 9259542123265392640, 72340172821233664, 144680345642467328, 289360691284934656, 578721382569869312, 1157442765139738624, 2314885530279477248, 4629771060558954496, 9259542121117908992, 72340168526266368, 144680337052532736, 289360674105065472, 578721348210130944, 1157442696420261888, 2314885392840523776, 4629770785681047552, 9259541571362095104, 72339069014638592, 144678138029277184, 289356276058554368, 578712552117108736, 1157425104234217472, 2314850208468434944, 4629700416936869888, 9259400833873739776, 72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808, 0, 0, 0, 0, 0, 0, 0, 0},
        {9241421688590303744, 36099303471055872, 141012904183808, 550831656960, 2151686144, 8404992, 32768, 0, 4620710844295151616, 9241421688590303232, 36099303471054848, 141012904181760, 550831652864, 2151677952, 8388608, 0, 2310355422147510272, 4620710844295020544, 9241421688590041088, 36099303470530560, 141012903133184, 550829555712, 2147483648, 0, 1155177711056977920, 2310355422113955840, 4620710844227911680, 9241421688455823360, 36099303202095104, 141012366262272, 549755813888, 0, 577588851233521664, 1155177702467043328, 2310355404934086656, 4620710809868173312, 9241421619736346624, 36099165763141632, 140737488355328, 0, 288793326105133056, 577586652210266112, 1155173304420532224, 2310346608841064448, 4620693217682128896, 9241386435364257792, 36028797018963968, 0, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {254, 252, 248, 240, 224, 192, 128, 0, 65024, 64512, 63488, 61440, 57344, 49152, 32768, 0, 16646144, 16515072, 16252928, 15728640, 14680064, 12582912, 8388608, 0, 4261412864, 4227858432, 4160749568, 4026531840, 3758096384, 3221225472, 2147483648, 0, 1090921693184, 1082331758592, 1065151889408, 1030792151040, 962072674304, 824633720832, 549755813888, 0, 279275953455104, 277076930199552, 272678883688448, 263882790666240, 246290604621824, 211106232532992, 140737488355328, 0, 71494644084506624, 70931694131085312, 69805794224242688, 67553994410557440, 63050394783186944, 54043195528445952, 36028797018963968, 0, 18302628885633695744, 18158513697557839872, 17870283321406128128, 17293822569102704640, 16140901064495857664, 13835058055282163712, 9223372036854775808, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 8, 16, 32, 64, 128, 0, 516, 1032, 2064, 4128, 8256, 16512, 32768, 0, 132104, 264208, 528416, 1056832, 2113664, 4227072, 8388608, 0, 33818640, 67637280, 135274560, 270549120, 541097984, 1082130432, 2147483648, 0, 8657571872, 17315143744, 34630287488, 69260574720, 138521083904, 277025390592, 549755813888, 0, 2216338399296, 4432676798592, 8865353596928, 17730707128320, 35461397479424, 70918499991552, 140737488355328, 0, 567382630219904, 1134765260439552, 2269530520813568, 4539061024849920, 9078117754732544, 18155135997837312, 36028797018963968, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 64, 128, 257, 514, 1028, 2056, 4112, 8224, 16448, 32896, 65793, 131586, 263172, 526344, 1052688, 2105376, 4210752, 8421504, 16843009, 33686018, 67372036, 134744072, 269488144, 538976288, 1077952576, 2155905152, 4311810305, 8623620610, 17247241220, 34494482440, 68988964880, 137977929760, 275955859520, 551911719040, 1103823438081, 2207646876162, 4415293752324, 8830587504648, 17661175009296, 35322350018592, 70644700037184, 141289400074368, 282578800148737, 565157600297474, 1130315200594948, 2260630401189896, 4521260802379792, 9042521604759584, 18085043209519168, 36170086419038336},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 64, 0, 256, 513, 1026, 2052, 4104, 8208, 16416, 0, 65536, 131328, 262657, 525314, 1050628, 2101256, 4202512, 0, 16777216, 33619968, 67240192, 134480385, 268960770, 537921540, 1075843080, 0, 4294967296, 8606711808, 17213489152, 34426978560, 68853957121, 137707914242, 275415828484, 0, 1099511627776, 2203318222848, 4406653222912, 8813306511360, 17626613022976, 35253226045953, 70506452091906, 0, 281474976710656, 564049465049088, 1128103225065472, 2256206466908160, 4512412933881856, 9024825867763968, 18049651735527937},
        {0, 1, 3, 7, 15, 31, 63, 127, 0, 256, 768, 1792, 3840, 7936, 16128, 32512, 0, 65536, 196608, 458752, 983040, 2031616, 4128768, 8323072, 0, 16777216, 50331648, 117440512, 251658240, 520093696, 1056964608, 2130706432, 0, 4294967296, 12884901888, 30064771072, 64424509440, 133143986176, 270582939648, 545460846592, 0, 1099511627776, 3298534883328, 7696581394432, 16492674416640, 34084860461056, 69269232549888, 139637976727552, 0, 281474976710656, 844424930131968, 1970324836974592, 4222124650659840, 8725724278030336, 17732923532771328, 35747322042253312, 0, 72057594037927936, 216172782113783808, 504403158265495552, 1080863910568919040, 2233785415175766016, 4539628424389459968, 9151314442816847872},
        {0, 256, 66048, 16909312, 4328785920, 1108169199616, 283691315109888, 72624976668147712, 0, 65536, 16908288, 4328783872, 1108169195520, 283691315101696, 72624976668131328, 145249953336262656, 0, 16777216, 4328521728, 1108168671232, 283691314053120, 72624976666034176, 145249953332068352, 290499906664136704, 0, 4294967296, 1108101562368, 283691179835392, 72624976397598720, 145249952795197440, 290499905590394880, 580999811180789760, 0, 1099511627776, 283673999966208, 72624942037860352, 145249884075720704, 290499768151441408, 580999536302882816, 1161999072605765632, 0, 281474976710656, 72620543991349248, 145241087982698496, 290482175965396992, 580964351930793984, 1161928703861587968, 2323857407723175936, 0, 72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    T_bitboard ray = rayMovementRules[direction][n];
    T_bitboard occupancyBoard = bAll(b) | wAll(b);
    T_bitboard intersect = ray & occupancyBoard;
    int firstBlocker = (isNortherlyOrEast(direction) ? __builtin_ctzll(intersect) : BITBOARD_INDEX_SIZE - __builtin_clzll(intersect));
    T_bitboard intersectRay = (!intersect) ? 0 : rayMovementRules[direction][firstBlocker];
    return (ray ^ intersectRay);
}

//Refactor out quiete vs attacking moves
//This function wont work for black unless you have a function called OPPOSING_COLOUR instead of isPosBlack. Or, pass function pointer. Better yet, use info in state.
void genDirStates(T_Node *node, T_boardState *b, int n, int direction, int piece){
    T_bitboard mb = moveBoardDir(b, n, direction);
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

void genRaySuccStates(T_Node *node, T_boardState *b, int n, int piece){
    int numOfBeforeStatesN = node->fp;
    switch(piece){
        case whiteBishop:
            genDirStates(node, b, n, northEast, whiteBishop);
            genDirStates(node, b, n, southEast, whiteBishop);
            genDirStates(node, b, n, southWest, whiteBishop);
            genDirStates(node, b, n, northWest, whiteBishop);
            break;
        case whiteRook:
            genDirStates(node, b, n, north, whiteRook);
            genDirStates(node, b, n, east, whiteRook);
            genDirStates(node, b, n, south, whiteRook);
            genDirStates(node, b, n, west, whiteRook);
            break;
        case whiteQueen:
            genDirStates(node, b, n, north, whiteQueen);
            genDirStates(node, b, n, northEast, whiteQueen);
            genDirStates(node, b, n, east, whiteQueen);
            genDirStates(node, b, n, southEast, whiteQueen);
            genDirStates(node, b, n, south, whiteQueen);
            genDirStates(node, b, n, southWest, whiteQueen);
            genDirStates(node, b, n, west, whiteQueen);
            genDirStates(node, b, n, northWest, whiteQueen);
            break;
        case blackBishop:
            genDirStates(node, b, n, northEast, blackBishop);
            genDirStates(node, b, n, southEast, blackBishop);
            genDirStates(node, b, n, southWest, blackBishop);
            genDirStates(node, b, n, northWest, blackBishop);
            break;
        case blackRook:
            genDirStates(node, b, n, north, blackRook);
            genDirStates(node, b, n, east, blackRook);
            genDirStates(node, b, n, south, blackRook);
            genDirStates(node, b, n, west, blackRook);
            break;
        case blackQueen:
            genDirStates(node, b, n, north, blackQueen);
            genDirStates(node, b, n, northEast, blackQueen);
            genDirStates(node, b, n, east, blackQueen);
            genDirStates(node, b, n, southEast, blackQueen);
            genDirStates(node, b, n, south, blackQueen);
            genDirStates(node, b, n, southWest, blackQueen);
            genDirStates(node, b, n, west, blackQueen);
            genDirStates(node, b, n, northWest, blackQueen);
            break;
    }
    int numOfAfterStatesN = node->fp;
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
//        T_bitboard **rays = createRays();
//        T_bitboard **jumps = createJumps();
//        T_bitboard **steps = createSteps();
        if(!b->whosTurn){
            genPiecesSuccStates(node, b, whitePawn);
            genPiecesSuccStates(node, b, whiteBishop);
            genPiecesSuccStates(node, b, whiteKnight);
            genPiecesSuccStates(node, b, whiteRook);
            genPiecesSuccStates(node, b, whiteQueen);
            genPiecesSuccStates(node, b, whiteKing);
        }
        else{
            genPiecesSuccStates(node, b, blackPawn);
            genPiecesSuccStates(node, b, blackBishop);
            genPiecesSuccStates(node, b, blackKnight);
            genPiecesSuccStates(node, b, blackRook);
            genPiecesSuccStates(node, b, blackQueen);
            genPiecesSuccStates(node, b, blackKing);
        }
//        freeRays(rays);
//        freeJumps(jumps);
//        freeSteps(steps);
        bool player = b->whosTurn;
        if(isKingsExist(node, !player)){
            return false;//Current opposite player is in check
        }
        return true;//Current opposite player is not in check
}

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
void genPiecesSuccStates(T_Node *node, T_boardState *b, int piece){
    T_bitboard allPieces = *(pieceBitboard(b, piece));
    while(allPieces){
        (*genPieceSuccStates(piece))(node, b, __builtin_ctzll(allPieces), piece);
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
void generateCastlingStates(T_Node *node, T_boardState *b, int piece, T_bitboard castlePass){
    T_boardState tmp = *b;
    T_bitboard rayMovementRules[8][64] =
    {
        {72340172838076672, 144680345676153344, 289360691352306688, 578721382704613376, 1157442765409226752, 2314885530818453504, 4629771061636907008, 9259542123273814016, 72340172838076416, 144680345676152832, 289360691352305664, 578721382704611328, 1157442765409222656, 2314885530818445312, 4629771061636890624, 9259542123273781248, 72340172838010880, 144680345676021760, 289360691352043520, 578721382704087040, 1157442765408174080, 2314885530816348160, 4629771061632696320, 9259542123265392640, 72340172821233664, 144680345642467328, 289360691284934656, 578721382569869312, 1157442765139738624, 2314885530279477248, 4629771060558954496, 9259542121117908992, 72340168526266368, 144680337052532736, 289360674105065472, 578721348210130944, 1157442696420261888, 2314885392840523776, 4629770785681047552, 9259541571362095104, 72339069014638592, 144678138029277184, 289356276058554368, 578712552117108736, 1157425104234217472, 2314850208468434944, 4629700416936869888, 9259400833873739776, 72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808, 0, 0, 0, 0, 0, 0, 0, 0},
        {9241421688590303744, 36099303471055872, 141012904183808, 550831656960, 2151686144, 8404992, 32768, 0, 4620710844295151616, 9241421688590303232, 36099303471054848, 141012904181760, 550831652864, 2151677952, 8388608, 0, 2310355422147510272, 4620710844295020544, 9241421688590041088, 36099303470530560, 141012903133184, 550829555712, 2147483648, 0, 1155177711056977920, 2310355422113955840, 4620710844227911680, 9241421688455823360, 36099303202095104, 141012366262272, 549755813888, 0, 577588851233521664, 1155177702467043328, 2310355404934086656, 4620710809868173312, 9241421619736346624, 36099165763141632, 140737488355328, 0, 288793326105133056, 577586652210266112, 1155173304420532224, 2310346608841064448, 4620693217682128896, 9241386435364257792, 36028797018963968, 0, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {254, 252, 248, 240, 224, 192, 128, 0, 65024, 64512, 63488, 61440, 57344, 49152, 32768, 0, 16646144, 16515072, 16252928, 15728640, 14680064, 12582912, 8388608, 0, 4261412864, 4227858432, 4160749568, 4026531840, 3758096384, 3221225472, 2147483648, 0, 1090921693184, 1082331758592, 1065151889408, 1030792151040, 962072674304, 824633720832, 549755813888, 0, 279275953455104, 277076930199552, 272678883688448, 263882790666240, 246290604621824, 211106232532992, 140737488355328, 0, 71494644084506624, 70931694131085312, 69805794224242688, 67553994410557440, 63050394783186944, 54043195528445952, 36028797018963968, 0, 18302628885633695744, 18158513697557839872, 17870283321406128128, 17293822569102704640, 16140901064495857664, 13835058055282163712, 9223372036854775808, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 8, 16, 32, 64, 128, 0, 516, 1032, 2064, 4128, 8256, 16512, 32768, 0, 132104, 264208, 528416, 1056832, 2113664, 4227072, 8388608, 0, 33818640, 67637280, 135274560, 270549120, 541097984, 1082130432, 2147483648, 0, 8657571872, 17315143744, 34630287488, 69260574720, 138521083904, 277025390592, 549755813888, 0, 2216338399296, 4432676798592, 8865353596928, 17730707128320, 35461397479424, 70918499991552, 140737488355328, 0, 567382630219904, 1134765260439552, 2269530520813568, 4539061024849920, 9078117754732544, 18155135997837312, 36028797018963968, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 64, 128, 257, 514, 1028, 2056, 4112, 8224, 16448, 32896, 65793, 131586, 263172, 526344, 1052688, 2105376, 4210752, 8421504, 16843009, 33686018, 67372036, 134744072, 269488144, 538976288, 1077952576, 2155905152, 4311810305, 8623620610, 17247241220, 34494482440, 68988964880, 137977929760, 275955859520, 551911719040, 1103823438081, 2207646876162, 4415293752324, 8830587504648, 17661175009296, 35322350018592, 70644700037184, 141289400074368, 282578800148737, 565157600297474, 1130315200594948, 2260630401189896, 4521260802379792, 9042521604759584, 18085043209519168, 36170086419038336},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 64, 0, 256, 513, 1026, 2052, 4104, 8208, 16416, 0, 65536, 131328, 262657, 525314, 1050628, 2101256, 4202512, 0, 16777216, 33619968, 67240192, 134480385, 268960770, 537921540, 1075843080, 0, 4294967296, 8606711808, 17213489152, 34426978560, 68853957121, 137707914242, 275415828484, 0, 1099511627776, 2203318222848, 4406653222912, 8813306511360, 17626613022976, 35253226045953, 70506452091906, 0, 281474976710656, 564049465049088, 1128103225065472, 2256206466908160, 4512412933881856, 9024825867763968, 18049651735527937},
        {0, 1, 3, 7, 15, 31, 63, 127, 0, 256, 768, 1792, 3840, 7936, 16128, 32512, 0, 65536, 196608, 458752, 983040, 2031616, 4128768, 8323072, 0, 16777216, 50331648, 117440512, 251658240, 520093696, 1056964608, 2130706432, 0, 4294967296, 12884901888, 30064771072, 64424509440, 133143986176, 270582939648, 545460846592, 0, 1099511627776, 3298534883328, 7696581394432, 16492674416640, 34084860461056, 69269232549888, 139637976727552, 0, 281474976710656, 844424930131968, 1970324836974592, 4222124650659840, 8725724278030336, 17732923532771328, 35747322042253312, 0, 72057594037927936, 216172782113783808, 504403158265495552, 1080863910568919040, 2233785415175766016, 4539628424389459968, 9151314442816847872},
        {0, 256, 66048, 16909312, 4328785920, 1108169199616, 283691315109888, 72624976668147712, 0, 65536, 16908288, 4328783872, 1108169195520, 283691315101696, 72624976668131328, 145249953336262656, 0, 16777216, 4328521728, 1108168671232, 283691314053120, 72624976666034176, 145249953332068352, 290499906664136704, 0, 4294967296, 1108101562368, 283691179835392, 72624976397598720, 145249952795197440, 290499905590394880, 580999811180789760, 0, 1099511627776, 283673999966208, 72624942037860352, 145249884075720704, 290499768151441408, 580999536302882816, 1161999072605765632, 0, 281474976710656, 72620543991349248, 145241087982698496, 290482175965396992, 580964351930793984, 1161928703861587968, 2323857407723175936, 0, 72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    if(b->whosTurn && (castlePass == BLACK_KINGSIDE_PASS || castlePass == BLACK_QUEENSIDE_PASS)){
        bool cnd1 = !(all(b) & castlePass);
        bool cnd2 = true;
        bool cnd3 = true;
        if(castlePass == BLACK_KINGSIDE_PASS && (BLACK_KINGSIDE_ATTACKING & (b->wPawn | b->wKing) || BLACK_KINGSIDE_ATTACKING_K & b->wKnight)){
            cnd3 = false;
        }
        else if(castlePass == BLACK_QUEENSIDE_PASS && (BLACK_QUEENSIDE_ATTACKING & (b->wPawn | b->wKing) || BLACK_QUEENSIDE_ATTACKING_K & b->wKnight)){
            cnd3 = false;
        }
        int j, k, l;
        T_bitboard a = all(b);
        while(tmp.wBishop){
            if(__builtin_popcountll(tmp.wBishop)){
                j = __builtin_ctzll(getPieceFromPieces(&(tmp.wBishop)));
            }
            else{
                break;
            }
            if(rayMovementRules[northEast][j] & castlePass && !(rayMovementRules[northEast][j] & a) ||
               rayMovementRules[northWest][j] & castlePass && !(rayMovementRules[northWest][j] & a)
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
            if(rayMovementRules[north][k] & castlePass && !(rayMovementRules[north][k] & a)
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
            if(rayMovementRules[northEast][l] & castlePass && !(rayMovementRules[northEast][l] & a) ||
               rayMovementRules[northWest][l] & castlePass && !(rayMovementRules[northWest][l] & a) ||
               rayMovementRules[north][l] & castlePass && !(rayMovementRules[north][l] & a)
               ){
               cnd2 = false;
            }
        }
        bool cnd4;
        bool cnd5;
        if(castlePass == BLACK_KINGSIDE_PASS){
            cnd4 = b->castlesKBlack && b->castlesRRBlack;
            cnd5 = isBitSet(b->bKing, 60) && isBitSet(b->bRook, 63);
        }
        else if(castlePass == BLACK_QUEENSIDE_PASS){
            cnd4 = b->castlesKBlack && b->castlesLRBlack;
            cnd5 = isBitSet(b->bKing, 60) && isBitSet(b->bRook, 56);
        }
        if(cnd1 && cnd2 && cnd3 && cnd4 && cnd5){
            generateCastlingState(node, b, castlePass);
        }
    }
    else if(!b->whosTurn && (castlePass == WHITE_KINGSIDE_PASS || castlePass == WHITE_QUEENSIDE_PASS)){
        bool cnd1 = !(all(b) & castlePass);
        bool cnd2 = true;
        bool cnd3 = true;
        if(castlePass == WHITE_KINGSIDE_PASS && (WHITE_KINGSIDE_ATTACKING & (b->bPawn | b->bKing) || WHITE_KINGSIDE_ATTACKING_K & b->bKnight)){
            cnd3 = false;
        }
        else if(castlePass == WHITE_QUEENSIDE_PASS && (WHITE_QUEENSIDE_ATTACKING & (b->bPawn | b->bKing) || WHITE_QUEENSIDE_ATTACKING_K & b->bKnight)){
            cnd3 = false;
        }
        int j, k, l;
        T_bitboard a = all(b);
        while(tmp.bBishop){
            if(__builtin_popcountll(tmp.bBishop)){
                j = __builtin_ctzll(getPieceFromPieces(&(tmp.bBishop)));
            }
            else{
                break;
            }
            if(rayMovementRules[southEast][j] & castlePass && !(rayMovementRules[southEast][j] & a) ||
               rayMovementRules[southWest][j] & castlePass && !(rayMovementRules[southWest][j] & a)
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
            if(rayMovementRules[south][k] & castlePass && !(rayMovementRules[south][k] & a)
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
            if(rayMovementRules[southEast][l] & castlePass && !(rayMovementRules[southEast][l] & a) ||
               rayMovementRules[southWest][l] & castlePass && !(rayMovementRules[southWest][l] & a) ||
               rayMovementRules[south][l] & castlePass && !(rayMovementRules[south][l] & a)
               ){
               cnd2 = false;
            }
        }
        bool cnd4;
        bool cnd5;
        if(castlePass == WHITE_KINGSIDE_PASS){
            cnd4 = b->castlesKWhite && b->castlesRRWhite;
            cnd5 = isBitSet(b->wKing, 4) && isBitSet(b->wRook, 7);
        }
        else if(castlePass == WHITE_QUEENSIDE_PASS){
            cnd4 = b->castlesKWhite && b->castlesLRWhite;
            cnd5 = isBitSet(b->wKing, 4) && isBitSet(b->wRook, 0);
        }
        if(cnd1 && cnd2 && cnd3 && cnd4 && cnd5){
            generateCastlingState(node, b, castlePass);
        }
    }
}

//Remove mentions of white and black generations of castling at the bottom of this functionS
void genJumpOrStepSuccStates(T_Node *node, T_boardState *b, int n, int piece){
    T_bitboard jumpMovementRules[8][64] =
    {
        {131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 0, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888, 0, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328, 0, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968, 0, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1024, 2048, 4096, 8192, 16384, 32768, 0, 0, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 0, 0, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 0, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888, 0, 0, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328, 0, 0, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968, 0, 0, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 4, 8, 16, 32, 64, 128, 0, 0, 1024, 2048, 4096, 8192, 16384, 32768, 0, 0, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 0, 0, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 0, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888, 0, 0, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328, 0, 0, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 8, 16, 32, 64, 128, 0, 512, 1024, 2048, 4096, 8192, 16384, 32768, 0, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 0, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888, 0, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 64, 0, 256, 512, 1024, 2048, 4096, 8192, 16384, 0, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 0, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 0, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 0, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 0, 0, 256, 512, 1024, 2048, 4096, 8192, 0, 0, 65536, 131072, 262144, 524288, 1048576, 2097152, 0, 0, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 0, 0, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 0, 0, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 0, 0, 281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992},
        {0, 0, 256, 512, 1024, 2048, 4096, 8192, 0, 0, 65536, 131072, 262144, 524288, 1048576, 2097152, 0, 0, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 0, 0, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 0, 0, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 0, 0, 281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 0, 0, 72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 0, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 0, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 0, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 0, 281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 0, 72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    T_bitboard stepMovementRules[8][64] =
    {
        {256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328, 281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968, 72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808, 0, 0, 0, 0, 0, 0, 0, 0},
        {512, 1024, 2048, 4096, 8192, 16384, 32768, 0, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 0, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888, 0, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328, 0, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968, 0, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 4, 8, 16, 32, 64, 128, 0, 512, 1024, 2048, 4096, 8192, 16384, 32768, 0, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 0, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888, 0, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328, 0, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968, 0, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 8, 16, 32, 64, 128, 0, 512, 1024, 2048, 4096, 8192, 16384, 32768, 0, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 0, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 0, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888, 0, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328, 0, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328, 281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 64, 0, 256, 512, 1024, 2048, 4096, 8192, 16384, 0, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 0, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 0, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 0, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 0, 281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984},
        {0, 1, 2, 4, 8, 16, 32, 64, 0, 256, 512, 1024, 2048, 4096, 8192, 16384, 0, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 0, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 0, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 0, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 0, 281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 0, 72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904},
        {0, 256, 512, 1024, 2048, 4096, 8192, 16384, 0, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 0, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 0, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 0, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 0, 281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 0, 72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    int numOfBeforeStatesN = node->fp;
    T_boardState cpy = *b;
    int j;
    T_bitboard test;
    for(int i = 0; i < 8; i++){
        if(piece == whiteKing || piece == blackKing){
            j = __builtin_ctzll(stepMovementRules[i][n]);
        }
        else if(piece == whiteKnight || piece == blackKnight){
            j = __builtin_ctzll(jumpMovementRules[i][n]);
        }
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
    int numOfAfterStatesN = node->fp;

    if(piece == whiteKing && n == 4){
        for(int i = numOfBeforeStatesN; i < numOfAfterStatesN; i++){
            node->scc[i]->b.castlesKWhite = 0;
        }
    }
    else if(piece == blackKing && n == 60){
        for(int i = numOfBeforeStatesN; i < numOfAfterStatesN; i++){
            node->scc[i]->b.castlesKBlack = 0;
        }
    }
    if(piece == whiteKing || piece == blackKing){
        //generateCastlingStates(node, b, piece, BLACK_KINGSIDE_PASS);
        //generateCastlingStates(node, b, piece, BLACK_QUEENSIDE_PASS);
        //generateCastlingStates(node, b, piece, WHITE_KINGSIDE_PASS);
        //generateCastlingStates(node, b, piece, WHITE_QUEENSIDE_PASS);
    }
}

//Look at potentially removing this. It would have worked if the moveGenerators took the same info
//wPawnGenerate doesnt take the last argument piece so this needs to be corrected
void (*genPieceSuccStates(int piece))(T_Node *node, T_boardState *b, int n, int piece){
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
