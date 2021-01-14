#ifndef MOVEMENTRULES_H_INCLUDED
#define MOVEMENTRULES_H_INCLUDED

struct movementRules{
    T_bitboard **nR;
    T_bitboard **neR;
    T_bitboard **eR;
    T_bitboard **seR;
    T_bitboard **sR;
    T_bitboard **swR;
    T_bitboard **wR;
    T_bitboard **nwR;
};

struct movementRules* makeMovementRules();

#endif // MOVEMENTRULES_H_INCLUDED


