#include "mersenne.h"

#define N          624
#define M          397
#define MATRIX_A   0x9908b0dfUL
#define UPPER_MASK 0x80000000UL
#define LOWER_MASK 0x7fffffffUL

uint32_t mt_state[MT_N];
int mt_idx = MT_N + 1;

void mt_seed(uint32_t seed) {
    mt_state[0] = seed;
    for (int i = 1; i < N; i++)
        mt_state[i] = 1812433253UL * (mt_state[i-1] ^ (mt_state[i-1] >> 30)) + i;
    mt_idx = MT_N;
}

static void twist(void) {
    static uint32_t mag01[2] = {0, MATRIX_A};
    uint32_t y;
    for (int i = 0; i < N; i++) {
        y = (mt_state[i] & UPPER_MASK) | (mt_state[(i+1) % N] & LOWER_MASK);
        mt_state[i] = mt_state[(i + M) % N] ^ (y >> 1) ^ mag01[y & 1];
    }
    mt_idx = 0;
}

uint32_t mt_rand(void) {
    if (mt_idx >= MT_N)
        twist();

    uint32_t y = mt_state[mt_idx++];
    y ^= (y >> 11);
    y ^= (y << 7)  & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);
    return y;
}
