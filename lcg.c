#include <stdint.h>
#include <stdio.h>
#include <time.h> //to seed generator from system clock: (uint64_t)time(NULL)
#include "lcg.h"


//LINEAR CONGRUENTIAL GENERATOR

void lcg_seed(LCG *rng, uint64_t seed){
  rng->state = seed;
  //numerical recipes values:
  rng->a = 1664525ULL;
  rng->c = 1013904223ULL;
  rng->m = 4294967296ULL;

}

uint64_t lcg_next(LCG *rng){
rng->state = (rng->a * rng->state + rng->c) % rng->m;
return rng->state;
}

double lcg_next_float(LCG *rng){
return (double)lcg_next(rng) / (double)rng->m;
}

