#include "keyUtilities.hpp"
#include <stdint.h>
#include <stdlib.h>

uint64_t rand64(void){
    return rand() ^ ((uint64_t)rand() << 15) ^ ((uint64_t)rand() << 30) ^ ((uint64_t)rand() << 45) ^ ((uint64_t)rand() << 60);
}
