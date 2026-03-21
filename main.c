#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "lcg.h"

int main(void){

  //LCG
  LCG lcg;
  uint64_t seed = (uint64_t)time(NULL);
  lcg_seed(&lcg, seed);


  printf("==== LCG ====\n");
  printf("Seed State: %llu\n", lcg.state);

  for(int i = 0; i < 5; i++){
    printf("lcg_next[%d]: %llu\n", i, lcg_next(&lcg));
  }
  
  for(int i = 0; i < 5; i++){
    printf("lcg_float[%d]: %f\n", i, lcg_next_float(&lcg));
  }

  return EXIT_SUCCESS;
}
