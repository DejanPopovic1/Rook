#include "state.h"
#include "movementRules.h"
#include "generateSlideMoves.h"

#include <stdint.h>

struct movementRules makeMovementRules(){
    //struct movementRules *m = malloc(sizeof(struct movementRules));
    struct movementRules m;
    m.nR = castRays(&castN);
    m.neR = castRays(&castNE);
    m.eR = castRays(&castE);
    m.seR = castRays(&castSE);
    m.sR = castRays(&castS);
    m.swR = castRays(&castSW);
    m.wR = castRays(&castW);
    m.nwR = castRays(&castNW);
//    _BitScanForward();

    return m;
}
