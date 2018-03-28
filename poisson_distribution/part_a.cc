#include <cstdio>
// user-defined library
#include "../utils/poisson.h"
#include "../utils/parse_arg.h"

int main(int argc,char *argv[]){
    // create parsing args object
    parse_args *args = new parse_args();
    // set rules 
    args->set_args_rules("v","version","0.0.1","string");
    args->set_args_rules("l","lambda","1","int");
    args->set_args_rules("k","execution times","5","int");
    // parse it!
    args->parsing(argc,argv);
    // print out 
    printf("%s\n",args->get_args_val("v").val.c_str());
    printf("%d\n",std::atoi(args->get_args_val("l").val.c_str()));
    printf("%s\n",args->get_args_val("k").val.c_str());

    printf("%lf\n",poisson(1,2));

    return 0;
}