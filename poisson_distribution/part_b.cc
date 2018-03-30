#include <cstdio>
// user-defined library
#include "../utils/poisson.h"
#include "../utils/parse_arg.h"

int main(int argc,char *argv[]){
    // create parsing args object
    parse_args *args = new parse_args();
    // set rules 
    args->set_args_rules("p","Probability of Poisson X","0.4","float");
    args->set_args_rules("l","lambda of Poisson N","3","int");
    args->set_args_rules("k","upperbound of k (for N, which N can derive to N1, N2 according to p and 1-p)","100","int");
    // parse it!
    args->parsing(argc,argv);

    double p = std::atof(args->get_args_val("p").val.c_str());
    double l = std::atof(args->get_args_val("l").val.c_str());
    int upperbound = std::atoi(args->get_args_val("k").val.c_str());

    // Write file
    FILE *fp;
    fp=fopen("output/part_b.output","w+");
    // Set upperbound for gnuplot to use
    fprintf(fp,"# %d\n",upperbound);

    // Calculate 
    for(double i=1;i<=upperbound;i++){
        // Get total P{X+Y=i}
        double p_s,px=0,py=0;
        p_s = poisson(l,i);
        px = poisson(l*p,i*p);
        py = poisson(l*(1-p),i*(1-p));

        fprintf(fp,"%lf %lf %lf %lf %lf\n",i,p_s,px*py,px,py);
    }

    return 0;
}