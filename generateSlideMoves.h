#ifndef GENERATESLIDEMOVES_H
#define GENERATESLIDEMOVES_H

#include "state.h"
#include "stdbool.h"

T_bitboard **castRays();
bool castN(int *index);
bool castNE(int *index);
bool castE(int *index);
bool castSE(int *index);
bool castS(int *index);
bool castSW(int *index);
bool castW(int *index);
bool castNW(int *index);
T_bitboard* castRay(int(*direction)(),int index);
void setBit(T_bitboard *number, int n);
void createRays();

#endif // GENERATESLIDEMOVES_H
