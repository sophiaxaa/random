#ifndef LCG_H
#define LCG_H

#include <stdint.h>

//carry state between calls

typedef struct {
  uint32_t state;
  uint32_t a;
  uint32_t c;
} LCG;

//functions

void lcg_seed(LCG *rng, uint32_t seed);
uint32_t lcg_next(LCG *rng);
double lcg_next_float(LCG *rng);

#endif
