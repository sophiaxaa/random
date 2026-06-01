#ifndef MERSENNE_H
#define MERSENNE_H

#include <stdint.h>

#define MT_N 624

extern uint32_t mt_state[MT_N];
extern int mt_idx;

void     mt_seed(uint32_t seed);
uint32_t mt_rand(void);

#endif
