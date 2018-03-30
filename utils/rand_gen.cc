#include "rand_gen.h"

rand_gen::rand_gen(){

}

rand_gen::~rand_gen(){

}

float rand_gen::frand(double LO,double HI){
    srand(time(NULL)+rand());
    return LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
}

double rand_gen::exponential(double lambda,int x){
    if(x!=0)
        return lambda*exp(-lambda*(frand(1,x)));
    else 
        return 0;
}