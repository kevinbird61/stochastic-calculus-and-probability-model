#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cmath>

// Get permutations - C(m,n), which m>=n
int permutations(int m,int n);

int main(int argc,char *argv[]){
    int M=5,N;
    float p=0.2;
    // specify m=5, all probability=0.2
    // calculate the result from mathematic model

    // Get N from argc
    if(argc<2){
        printf("Error, Please specify 'N' now.\n");
        exit(EXIT_FAILURE);
    }
    else{
        N=std::atoi(argv[1]);
        printf("Range: 1~%d , with iteration N=%d\n",M,N);
    }

    // Calculate result
    int comp_flag=1;
    float result=0.0;
    for(int i=0;i<M;i++){
        // get the probability
        float p=0.2;
        for(int j=0;j<i;j++)
            p+=0.2;

        result+=(comp_flag)*(permutations(M,i+1))*p*pow(1-p,N-1);

        // last step, reverse flag
        comp_flag=-comp_flag;
    }

    printf("The probability of P{X=%d} = %f\n",N,result);

    return 0;
}

int permutations(int m,int n){
    int numerator=1,denominator=1;

    for(int i=0;i<n;i++){
        numerator*=(m-i);
        denominator*=(i+1);
    }

    return numerator/denominator;
}