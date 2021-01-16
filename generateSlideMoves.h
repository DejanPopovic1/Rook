#ifndef GENERATESLIDEMOVES_H
#define GENERATESLIDEMOVES_H

#include "state.h"
#include "stdbool.h"

T_bitboard castRay(int(*castDir)(),int index);
T_bitboard *castRays(bool (*castDir)(int*));
bool castN(int *index);
bool castNE(int *index);
bool castE(int *index);
bool castSE(int *index);
bool castS(int *index);
bool castSW(int *index);
bool castW(int *index);
bool castNW(int *index);
void createRays();

#endif // GENERATESLIDEMOVES_H
