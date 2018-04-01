#ifndef _RAND_GEN
#define _RAND_GEN

#include <math.h>
#include <stdlib.h>
#include <time.h>

class rand_gen {
 public:
  rand_gen();
  ~rand_gen();
  // random number generator - float
  float frand(double LO,double HI);
  // generate exponential random variable
  double exponential(double lambda);
};

#endif