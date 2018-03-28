#include <cstdio>
// user-defined library
#include "../utils/poisson.h"
#include "../utils/parse_arg.h"

int main(int argc,char *argv[]){
    // create parsing args object
    parse_args *args = new parse_args();
    // set rules 
    args->set_args_rules("1","lambda 1 of Poisson X","1","int");
    args->set_args_rules("2","lambda 2 of Poisson Y","2","int");
    args->set_args_rules("k","upperbound of k (for S, which S=X+Y)","100","int");
    // parse it!
    args->parsing(argc,argv);

    int upperbound = std::atoi(args->get_args_val("k").val.c_str());
    int lambda1 = std::atoi(args->get_args_val("1").val.c_str());
    int lambda2 = std::atoi(args->get_args_val("2").val.c_str());

    for(int i=0;i<=upperbound;i++){
        // P{X+Y=i}
        printf("P{X+Y=%d}=%lf\n",i,poisson(lambda1+lambda2,i));
    }

    return 0;
}