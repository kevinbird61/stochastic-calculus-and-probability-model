#include <cstdio>
#include <map>
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
  args->set_args_rules("s","simulation times.","10000","int");
  args->set_args_rules("r","Range of preamble","100","int");
  args->set_args_rules("i","Interval in range of preamble.(From `n` ~ `n+r`)","10","int");
  // parse it!
  args->parsing(argc,argv);
  // get result
  int n = std::atoi(args->get_args_val("n").val.c_str());
  int m = std::atoi(args->get_args_val("m").val.c_str());
  int s = std::atoi(args->get_args_val("s").val.c_str());
  int range = std::atoi(args->get_args_val("r").val.c_str());
  int interval = std::atoi(args->get_args_val("i").val.c_str());

  // ===================================== Perform the random access process =====================================
  rand_gen *gen = new rand_gen();
  // ===================================== Simulation Part =====================================
  std::map<int,int> preamble;
  FILE *fp=fopen("output/part_b.output","w+");
  // Write experiment parameter into file header
  fprintf(fp,"# %d %d %d %d %d\n",n,m,s,range,interval);

  for(int pream=n; pream<=n+range; pream+=interval) {
    int sim=s,devices=m;
    double success_p=0.0;
    while(sim--) {
      // All non-sent device, using random variable to get
      for(int i=0; i<devices; i++) {
        // randomly pick a number from unifrom as "preamble"
        preamble[gen->uniform_int(1,pream)]++;
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
    // Get result from simulation - success_p/s
    // printf("%lf\n",success_p/s);

    // ===================================== Mathematic Part =====================================
    double success_p_math=0.0;
    // successful node = success_p_math*m
    success_p_math=powf(1-1/(float)pream,m-1);

    // Get result from mathematic - success_p_math
    //printf("%lf\n",success_p_math);

    // Write into file
    fprintf(fp,"%d %lf %lf\n",pream,success_p/s,success_p_math);
  }
  return 0;
}