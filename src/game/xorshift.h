#ifndef XORSHIFT_H
#define XORSHIFT_H

extern unsigned rng_seed(int n, int n2);
extern unsigned rng_next();
extern unsigned rng_random(int low, int high);

#endif
