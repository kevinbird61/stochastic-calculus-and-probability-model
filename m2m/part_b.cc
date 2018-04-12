#include <cstdio>
// user-defined library
#include "../utils/parse_arg.h"
#include "../utils/rand_gen.h"

int main(int argc,char *argv[]) {
  // ===================================== Getting User Input (by parse_arg) =====================================
  // create parsing args object
  parse_args *args = new parse_args();
  // set rules
  args->set_args_rules("n","Total number of preamble.","10","int");
  args->set_args_rules("m","Total number of devices(MTC device/UE).","20","int");
  args->set_args_rules("s","simulation times.","100","int");
  // parse it!
  args->parsing(argc,argv);
  // get result
  int n = std::atoi(args->get_args_val("n").val.c_str());
  int m = std::atoi(args->get_args_val("m").val.c_str());
  int s = std::atoi(args->get_args_val("s").val.c_str());

  // ===================================== Perform the random access process =====================================

}