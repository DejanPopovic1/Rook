#include "state.h"
#include "movementRules.h"
#include "generateSlideMoves.h"

#include <stdint.h>

T_bitboard bitScanForward(T_bitboard b) {
    __asm__(
        "bsr %rcx,%rax\n"//Linux
        //"bsr %rdi,%rax\n"//Windows
        //"mov %edx,%eax\n"
        //"mov $2222,%rax\n"
        "leave\n"
        "ret\n"
    );
}

//int foo() {
//  __asm__( /* Assembly function body */
//"  mov $190,%eax\n"  /* moves 100 into eax! */
//"  leave\n"
//"  ret\n"
//  );
//}

struct movementRules* makeMovementRules(){
    struct movementRules *m = malloc(sizeof(struct movementRules));
    m->nR = castRays(&castN);
    m->neR = castRays(&castNE);
    m->eR = castRays(&castE);
    m->seR = castRays(&castSE);
    m->sR = castRays(&castS);
    m->swR = castRays(&castSW);
    m->wR = castRays(&castW);
    m->nwR = castRays(&castNW);
//    _BitScanForward();

    __asm__("movl %edx, %eax\n\t"
        "addl $2, %eax\n\t");
    return m;
}
