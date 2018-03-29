#ifndef _POSISSON
#define _POSISSON

#include <math.h>
#include <stdlib.h>
#include <time.h>

double factorial(int k);
// Get P(X=k)
double poisson(double lambda,double k);
// poisson random number
double poisson_rand_gen(double lambda);

#endif