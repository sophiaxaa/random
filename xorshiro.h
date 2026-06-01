#ifndef XOROSHIRO_H
#define XOROSHIRO_H

#include <stdint.h>

extern uint64_t xoro_s0;
extern uint64_t xoro_s1;

void     xoro_seed(uint64_t s0, uint64_t s1);
uint64_t xoro_rand(void);

#endif
