#ifndef LCG_H
#define LCG_H

#include <stdint.h>

//carry state between calls

typedef struct {
  uint64_t state;
  uint64_t a;
  uint64_t c;
  uint64_t m;
} LCG;

//functions

void lcg_seed(LCG *rng, uint64_t seed);
uint64_t lcg_next(LCG *rng);
double lcg_next_float(LCG *rng);

#endif
