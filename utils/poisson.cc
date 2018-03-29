#include "poisson.h"

double factorial(int k){
    double sum=1;
    for(int i=1;i<=k;i++){
        sum*=i;
    }
    return sum;
}

double poisson(double lambda,double k){
    return exp(-lambda)*pow(lambda,k)/factorial(k);
}