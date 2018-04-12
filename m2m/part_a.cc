#include <cstdio>
#include <map>
// user-defined library
#include "../utils/parse_arg.h"
#include "../utils/rand_gen.h"

int main(int argc,char *argv[]){
    // ===================================== Getting User Input (by parse_arg) =====================================
    // create parsing args object
    parse_args *args = new parse_args();
    // set rules
    args->set_args_rules("p","Access Class Barring, p.","0.1","float");
    args->set_args_rules("d","Simulation duration (Start from `p`).","0.9","float");
    args->set_args_rules("i","Simulation duration interval.(Start from `p` to `p+d`)","0.1","float");
    args->set_args_rules("r","Retry after this period.","1.0","float");
    args->set_args_rules("m","Total number of devices(MTC device/UE).","20","int");
    args->set_args_rules("s","simulation times.","100","int");
    // parse it!
    args->parsing(argc,argv);
    // get result
    float p = std::atof(args->get_args_val("p").val.c_str());
    float duration = std::atof(args->get_args_val("d").val.c_str());
    float upperbound = ((p+duration) > 1.0 ? 1.0 : p+duration);
    float interval = std::atof(args->get_args_val("i").val.c_str());
    float retry = std::atof(args->get_args_val("r").val.c_str());
    int m = std::atoi(args->get_args_val("m").val.c_str());
    int s = std::atoi(args->get_args_val("s").val.c_str());

    // ===================================== (Mathematic) Barring: Draw a random number =====================================
    // For rand_gen 
    rand_gen *gen = new rand_gen();
    FILE *fp_a = fopen("output/part_a.output","w+");
    fprintf(fp_a,"# %d %d %f %f %f\n",s,m,p,p+duration,interval);
    for(float prob=p;prob<=upperbound;prob+=interval){
        // Record testcase 
        std::map<int,int> sim_record;
        double total_delay=0.0;
        // Run s time of simulation routine
        for(int i=0;i<s;i++){
            // Do m time for each device
            int devices=m;
            double cur_delay=0.0;
            while(devices){
                //printf("%lf\n",gen->uniform_real(0.0,1.0));
                if(gen->uniform_real(0.0,1.0)<prob){
                    // success 
                    devices--;
                }
                else{
                    // delay
                    cur_delay+=retry;
                }
            }
            // record
            sim_record[(int)cur_delay/retry]++;
            // print & iterative
            //printf("[%d] Current access delay: %lf(ms), with retry times: %lf\n",i,cur_delay,cur_delay/retry);
            total_delay+=cur_delay;
        }
        printf("\nIn '%d' times of simulation, total access delay is %lf(ms), access delay average: %lf(ms)\n",s,total_delay,total_delay/s);
        // Get summation, the last key
        int total_time=0, last_key=0;
        for(auto&it: sim_record){
            // total statistic number
            total_time+=it.second;
            // remand the largest key
            last_key=it.first;
        }
        // Write result 
        /*for(auto&it: sim_record){
            fprintf(fp_sim,"%d %f\n",it.first,(float)it.second/(float)total_time);
        }*/

        // ===================================== (Simulation) Barring: Draw a random number =====================================
        // using the last key (largest) as upperbound, to calculate all the probability from geometric distribution
        printf("%d\n",last_key);
        // Calculate the result by geometric 
        double total_delay_math=0.0;
        for(int k=0;k<=last_key;k++){
            // k represent the retry times
            total_delay_math+=(k*retry)*(prob)*powf((1-prob),k);
        }
        printf("\nIn mathematical model, Access delay average: %lf(ms)\n",m*total_delay_math);

        // Write result into file: (probability, simulation, mathematical)
        fprintf(fp_a,"%f %lf %lf\n",prob,total_delay/(s),m*total_delay_math);
    }
    return 0;
}