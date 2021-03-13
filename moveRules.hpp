#ifndef MOVERULES_H
#define MOVERULES_H

#include <stdbool.h>
#include "state.hpp"

bool cast1(int *index);
bool cast2(int *index);
bool cast3(int *index);
bool cast4(int *index);
bool cast5(int *index);
bool cast6(int *index);
bool cast7(int *index);
bool cast8(int *index);
bool castN(int *index);
bool castNE(int *index);
bool castE(int *index);
bool castSE(int *index);
bool castS(int *index);
bool castSW(int *index);
bool castW(int *index);
bool castNW(int *index);
T_bitboard castStep(bool(*castDir)(int*),int index);
T_bitboard castRay(bool(*castDir)(int*),int index);
T_bitboard castJump(bool(*castDir)(int*),int index);
T_bitboard *castSteps(bool (*castDir)(int*));
T_bitboard *castRays(bool (*castDir)(int*));
T_bitboard *castJumps(bool (*castDir)(int*));
T_bitboard** createRays();
T_bitboard** createSteps();
T_bitboard** createJumps();
//T_bitboard *castWPawnAttacks(bool (*castE)(int *));
T_bitboard **createWPawnAttacks();

#endif // MOVERULES_H
