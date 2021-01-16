#include "state.h"
#include "movementRules.h"
#include "generateSlideMoves.h"

#include <stdint.h>

struct movementRules makeMovementRules(){
    struct movementRules result;
    result.nR = castRays(&castN);
    result.neR = castRays(&castNE);
    result.eR = castRays(&castE);
    result.seR = castRays(&castSE);
    result.sR = castRays(&castS);
    result.swR = castRays(&castSW);
    result.wR = castRays(&castW);
    result.nwR = castRays(&castNW);
    return result;
}
