#include "lcg.h"


//LINEAR CONGRUENTIAL GENERATOR

void lcg_seed(LCG *rng, uint32_t seed){
  rng->state = seed;
  rng->a = 0x41C64E6DUL; // Pokemon Gen 3 (Ruby/Sapphire/FRLG/Emerald)
  rng->c = 0x6073UL;
}

uint32_t lcg_next(LCG *rng){
  rng->state = rng->a * rng->state + rng->c; // mod 2^32 via implicit uint32_t overflow
  return rng->state;
}

double lcg_next_float(LCG *rng){
  return (double)lcg_next(rng) * (1.0 / 4294967296.0);
}

