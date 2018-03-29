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
    args->set_args_rules("s","simulation times","100","int");
    // parse it!
    args->parsing(argc,argv);

    int upperbound = std::atoi(args->get_args_val("k").val.c_str());
    int lambda1 = std::atoi(args->get_args_val("1").val.c_str());
    int lambda2 = std::atoi(args->get_args_val("2").val.c_str());

    // ===================================== Mathematical Model ===================================== 

    // Write file 
    FILE *fp;
    fp=fopen("output/part_a.output","w+");
    // Set upperbound for gnuplot to use
    fprintf(fp,"# %d\n",upperbound);

    // Calculate
    for(int i=0;i<=upperbound;i++){
        // Get total P{X+Y=i}
        double p_s,px,py,p_xy=0;
        p_s = poisson(lambda1+lambda2,i);
        
        for(int j=0;j<=i;j++){
            // j represent X , so j increased, it represent that Y is decreased
            px = poisson(lambda1,j);
            py = poisson(lambda2,i-j);
            p_xy += (px*py);
        }
        fprintf(fp,"%d %lf %lf\n",i,p_s,p_xy);
    }

    // printf("%lf %lf %lf\n",poisson_rand_gen(lambda1),poisson_rand_gen(lambda2),poisson_rand_gen(lambda1+lambda2));

    // ===================================== Simulation Part ===================================== 
    int simulation_time = std::atoi(args->get_args_val("s").val.c_str());

    std::map<int,int> x,y,S;

    for(int i=0;i<simulation_time;i++){
        x[poisson_rand_gen(lambda1)]++;
        y[poisson_rand_gen(lambda2)]++;
        S[poisson_rand_gen(lambda1+lambda2)]++;
    }

    /*for(auto& it: x){
        printf("%d %d\n",it.first,it.second);
    }

    for(auto& it: y){
        printf("%d %d\n",it.first,it.second);
    }*/

    for(auto& it: S){
        printf("%d %d\n",it.first,it.second);
    }

    return 0;
}