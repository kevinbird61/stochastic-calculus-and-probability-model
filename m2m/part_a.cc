#include <cstdio>
// user-defined library
#include "../utils/parse_arg.h"
#include "../utils/rand_gen.h"

int main(int argc,char *argv[]){
    // ===================================== Getting User Input (by parse_arg) =====================================
    // create parsing args object
    parse_args *args = new parse_args();
    // set rules
    args->set_args_rules("p","Access Class Barring, p.","0.6","float");
    args->set_args_rules("r","Retry after this period.","1.0","float");
    args->set_args_rules("m","Total number of devices(MTC device/UE).","20","int");
    args->set_args_rules("s","simulation times.","100","int");
    // parse it!
    args->parsing(argc,argv);
    // get result
    float p = std::atof(args->get_args_val("p").val.c_str());
    float retry = std::atof(args->get_args_val("r").val.c_str());
    int m = std::atoi(args->get_args_val("m").val.c_str());
    int s = std::atoi(args->get_args_val("s").val.c_str());

    // ===================================== Barring: Draw a random number =====================================

}