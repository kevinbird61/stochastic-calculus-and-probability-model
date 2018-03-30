#include <cstdio>
// user-defined library
#include "../utils/poisson.h"
#include "../utils/parse_arg.h"

// For gathering simulation result
struct multi{
    float xy;
    int s;
};

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
    std::map<int,multi> sim;

    FILE *fpx;
    fpx=fopen("output/part_a_sim.output","w+");

    for(int i=0;i<simulation_time;i++){
        x[poisson_rand_gen(lambda1)]++;
        y[poisson_rand_gen(lambda2)]++;
        S[poisson_rand_gen(lambda1+lambda2)]++;
    }

    for(auto& it: S){
        sim[it.first].s=it.second;
        for(int i=0;i<it.first;i++){
            sim[it.first].xy+=((x[i]+y[it.first-i])/2);
        }
        sim[it.first].xy /= (it.first);
    }

    for(auto& it: sim){
        // Calculate result
        fprintf(fpx,"%d %f %f\n",it.first,(float)it.second.s/simulation_time,(float)it.second.xy/(2*simulation_time));
    }

    return 0;
}