#include <stdlib.h>
#include "xorshift.h"

unsigned long long rngState[2] = { 1, 2 };

unsigned rng_seed(int n, int n2) {
  if (n) {
    rngState[0] = n;
  } else {
    rngState[0] = rand() * 65535 | 0;
  }
  if (n2) {
    rngState[1] = n2;
  } else {
    rngState[1] = (unsigned long long)(rand() * 65535 | 0) >> 32;
  }
  return 0;
}

unsigned rng_next() {
  unsigned long s0 = rngState[1];
  rngState[0] = s0;
  unsigned long s1 = rngState[0];
  s1 ^= s1 << 23;
  s1 ^= s1 >> 17;
  s1 ^= s0;
  s1 ^= s0 >> 26;
  rngState[1] = s1;
  return rngState[0] + rngState[1];
}

unsigned rng_random(int low, int high) {
  return low + (rng_next() % (high - low));
}

// int main(void) {
//   rng_seed(0, 0);
//   for (int i = 0; i < 10000; i += 1) {
//     printf("%d ", rng_random(0, 100));
//   }
//   return 0;
// }
