#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "lcg.h"
#include "mersenne.h"
#include "xorshift.h"
#include "xorshiro.h"

#define PREVIEW 5 

void print_state_preview(const char *label) {
    printf("%s (index=%d):\n", label, mt_idx);
    for (int i = 0; i < PREVIEW; i++)
        printf("  state[%d]: %10u\n", i, mt_state[i]);
    printf("  ...\n");
}

int main(void){

  //LCG
  LCG lcg;
  uint32_t seed = (uint32_t)time(NULL);
  lcg_seed(&lcg, seed);


  printf("==== LCG ====\n");
  printf("Seed State: %u\n", lcg.state);
  printf("Multiplier: 0x41C64E6D (1103515245) — Pokemon Gen 3\n");
  printf("Increment:  0x6073 (24691)\n");
  printf("Modulus:    2^32 (implicit uint32_t overflow)\n");
  printf("State size: 1 x 32-bit integer\n\n");

  printf("%-6s  %-12s  %-12s  %-12s\n", "Call", "Raw Value", "Float [0,1)", "Int [1,100]");


  for(int i = 0; i < PREVIEW; i++){
    uint32_t raw = lcg_next(&lcg);
    double   f   = (double)raw * (1.0 / 4294967296.0);
    uint32_t r   = 1 + (raw % 100);
    printf("%-6d  %-12u  %-12.6f  %-12u\n", i, raw, f, r);
  }
  

 //MERSENNE TWISTER 
  printf("\n==== MERSENNE TWISTER ====\n");

    uint32_t seed1 = 1608637542;
    mt_seed(seed1);
    printf("Seed: %u\n", seed1);
    printf("State array size: %d integers\n\n", MT_N);


    print_state_preview("State after seeding (no twist yet)");

    printf("\n--- Generating 5 numbers (triggers first twist) ---\n");
    for (int i = 0; i < 5; i++) {
        uint32_t raw = mt_rand();
        double   f   = (double)raw * (1.0 / 4294967296.0);
        printf("mt_rand[%d]: %10u  |  float: %.6f  |  range[1-100]: %u\n",
               i, raw, f, 1 + (raw % 100));
    }

  
    printf("\n");
    print_state_preview("State after first twist");

    printf("\nPeriod: 2^19937 - 1 (never repeats in practice)\n");

  // XORSHIFT 
  
 uint32_t xs_seed_val = (uint32_t)time(NULL);
    xs_seed(xs_seed_val);

  printf("\n==== XORSHIFT ====\n");
  printf("Seed:        %u\n", xs_seed_val);
  printf("State size:  1 x 32-bit integer\n");
  printf("Operations:  XOR + shift only (no multiply, no modulo)\n");
  printf("Period:      2^32 - 1\n\n");

  printf("%-6s  %-12s  %-12s  %-12s\n",
           "Call", "Raw Value", "Float [0,1)", "Int [1,100]");
  printf("%-6s  %-12s  %-12s  %-12s\n",
           "------", "------------", "------------", "------------");

  for (int i = 0; i < PREVIEW; i++) {
        uint32_t raw = xs_rand();
        double   f   = (double)raw * (1.0 / 4294967296.0);
        uint32_t r   = 1 + (raw % 100);
        printf("%-6d  %-12u  %-12.6f  %-12u\n", i, raw, f, r);
    }
  printf("\nNote: state IS the output — no separation between internal state and result.\n");
  

  //XORSHIRO128+
    uint64_t s0 = (uint64_t)time(NULL);
    uint64_t s1 = s0 + 0x9e3779b97f4a7c15ULL; // golden ratio constant offset
    xoro_seed(s0, s1);

    printf("\n==== XOROSHIRO128+ ====\n");
    printf("Seed s0:     %lu\n", s0);
    printf("Seed s1:     %lu\n", s1);
    printf("State size:  2 x 64-bit integers (128 bits)\n");
    printf("Output:      s0 + s1 before state update (the '+' in the name)\n");
    printf("Period:      2^128 - 1\n\n");

    printf("%-6s  %-20s  %-20s  %-12s  %-12s\n",
           "Call", "s0 (state)", "s1 (state)", "Float [0,1)", "Int [1,100]");
    printf("%-6s  %-20s  %-20s  %-12s  %-12s\n",
           "------", "--------------------", "--------------------",
           "------------", "------------");

    for (int i = 0; i < PREVIEW; i++) {
        uint64_t s0_snap = xoro_s0, s1_snap = xoro_s1;
        uint64_t raw = xoro_rand();
        double   f   = (double)(raw >> 11) / (double)(1ULL << 53);
        uint64_t r   = 1 + (raw % 100);
        printf("%-6d  %-20lu  %-20lu  %-12.6f  %-12lu\n",
               i, s0_snap, s1_snap, f, r);
    }

    printf("\nNote: two state variables — each call updates BOTH s0 and s1.\n");
    printf("Seeded with s1 = s0 + golden ratio offset: mimics CSPRNG-fed seeding.\n");

  return EXIT_SUCCESS;
}
