#include <cstdio>
#include <map>
// user-defined library
#include "../utils/parse_arg.h"
#include "../utils/rand_gen.h"

int combination(int m,int n) {
  return (n==0||m==n)?1:combination(m-1,n)+combination(m-1,n-1);
}

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
  rand_gen *gen = new rand_gen();
  // ===================================== Simulation Part =====================================
  std::map<int,int> preamble;

  int sim=s,devices=m;
  double success_p=0.0;
  while(sim--) {
    // All non-sent device, using random variable to get
    for(int i=0; i<devices; i++) {
      // randomly pick a number from unifrom as "preamble"
      preamble[gen->uniform_int(1,n)]++;
    }
    // Calculate if there exist repeated number
    // If not, then represent there has a success.
    double success=0.0;
    for(auto&it: preamble) {
      if(it.second==1)
        success++;
    }
    // Calculate successful rate
    //printf("Successful Probability: %lf\n",success,success/m);
    success_p+=(success/m);
    preamble.clear();
    devices=m;
  }

  printf("%lf\n",success_p/s);

  // ===================================== Mathematic Part =====================================
  // i represent the success devices, calculate its probability
  double success_p_math=0.0;
  for(int i=1; i<=m; i++) {
    success_p_math+=combination(m,i)*powf(1/(float)n,i)*powf((n-i)/(float)n,m-i);
  }

  printf("%lf\n",success_p_math);
  return 0;
}