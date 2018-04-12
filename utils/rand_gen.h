#ifndef _RAND_GEN
#define _RAND_GEN

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <chrono>

class rand_gen {
 public:
  rand_gen();
  ~rand_gen();
  // random number generator - int
  int irand(int LO,int HI);
  // random number generator - float
  float frand(double LO,double HI);
  // generate exponential random variable
  double exponential(double lambda);
  // generate uniform random variable (int)
  int uniform_int(int lb,int ub);
  // generate uniform random variable
  double uniform_real(double lb,double ub);
 private:
  std::default_random_engine generator;
};

#endif