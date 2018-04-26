#include <cstdio>
#include "../utils/rand_gen.h"
#include <map>

int main(int argc,char *argv[]){
    // random number generator
    rand_gen *gen = new rand_gen();

    // upperbound: t = X1+X2
    double t=10000,counter=0.0,mu1=1,mu2=2;
    // X1, X2
    std::map<double,int> X1,X2;

    while(t--){
        // double ts = gen->exponential(mu1);
        X1[(int)gen->exponential(mu1)]++;
        X2[(int)gen->exponential(mu2)]++;
    }

    double sum_X1=0.0,sum_X2=0.0;
    for(auto&it: X1){
        sum_X1+=it.second;
    }
    for(auto&it: X2){
        sum_X2+=it.second;
    }

    for(auto&it:X1){
        printf("[ %lf ]: %lf\n",it.first,it.second/sum_X1);
    }
    /*for(auto&it:X2){
        printf("[ %lf ]: %lf\n",it.first,it.second/sum_X2);
    }*/

    return 0;
}