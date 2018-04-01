#include "poisson.h"

double factorial(int k) {
  double sum=1;
  for(int i=1; i<=k; i++) {
    sum*=i;
  }
  return sum;
}

double poisson(double lambda,double k) {
  return exp(-lambda)*pow(lambda,k)/factorial(k);
}

double poisson_rand_gen(double lambda) {
  double L=exp(-lambda),k=0,p=1;
  srand(time(NULL)+rand());
  do {
    k++;
    p=p*(rand()%2);
  } while(p > L);

  return k;
}