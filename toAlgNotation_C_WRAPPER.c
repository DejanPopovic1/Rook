#include "toAlgNotation_C_WRAPPER.h"
extern "C" {
    #include "toAlgNotation.hpp"
}

const char* toAlgebraicNotation_C_WRAPPER(T_boardState *c, T_boardState *ss){
    return (toAlgebraicNotation(c, ss)).c_str();
}
