#include "rand_gen.h"

rand_gen::rand_gen() {

}

rand_gen::~rand_gen() {

}

float rand_gen::frand(double LO,double HI) {
  srand(time(NULL)+rand());
  return LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
}

double rand_gen::exponential(double lambda) {
  std::default_random_engine generator;
  // specify upperbound and lowerbound
  std::exponential_distribution<double> dist(lambda);
  // return random value
  return dist(generator);
}

double rand_gen::uniform_real(double lb,double ub) {
  std::default_random_engine generator;
  // specify upperbound and lowerbound
  std::uniform_real_distribution<double> dist(lb,ub);
  // return random value
  return dist(generator);
}