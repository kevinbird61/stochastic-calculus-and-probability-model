#include <cstdio>
#include <unistd.h>
#include <cstdlib>

// Get summation of Ai, with specify numbers
float sumA(int size);

int main(int argc,char *argv[]){
    int M=5,N;
    float p[M]={0.2,0.2,0.2,0.2,0.2};
    // specify m=5, all probability=0.2
    // calculate the result from mathematic model

    // Get N from argc
    if(argc<2){
        printf("Error, Please specify 'N' now.\n");
        exit(EXIT_FAILURE);
    }
    else{
        N=std::atoi(argv[1]);
        printf("N=%d\n",N);
    }

    // specify Ai, = (1-pi)

    // P {X>N} = p(Ai)

    return 0;
}