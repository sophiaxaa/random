#include "xorshiro.h"

uint64_t xoro_s0;
uint64_t xoro_s1;

static inline uint64_t rotl(uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}

void xoro_seed(uint64_t s0, uint64_t s1) {
    xoro_s0 = s0;
    xoro_s1 = s1;
}

uint64_t xoro_rand(void) {
    uint64_t result = xoro_s0 + xoro_s1;

    uint64_t t = xoro_s1 ^ xoro_s0;
    xoro_s0 = rotl(xoro_s0, 24) ^ t ^ (t << 16);
    xoro_s1 = rotl(t, 37);

    return result;
}
