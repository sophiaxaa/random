#include "xorshift.h"

static uint32_t xs_state;

void xs_seed(uint32_t seed) {
    xs_state = seed ? seed : 1;
}

uint32_t xs_rand(void) {
    xs_state ^= xs_state << 13;
    xs_state ^= xs_state >> 17;
    xs_state ^= xs_state << 5;
    return xs_state;
}
