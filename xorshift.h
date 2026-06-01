#ifndef XORSHIFT_H
#define XORSHIFT_H

#include <stdint.h>

void     xs_seed(uint32_t seed);
uint32_t xs_rand(void);

#endif
