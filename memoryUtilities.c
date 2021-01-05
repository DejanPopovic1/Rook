#include "GlobalDeclarations.h"

int offset(int x, int y, int z){
    return (z * MAX_SUCCESSOR_STATES * RANK_SIZE) + (y * MAX_SUCCESSOR_STATES) +  x;
}
