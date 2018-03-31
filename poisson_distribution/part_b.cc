#include <cstdio>
// user-defined library
#include "../utils/poisson.h"
#include "../utils/parse_arg.h"
#include "../utils/rand_gen.h"
#include "../utils/event.h"

int main(int argc,char *argv[]){
    // create parsing args object
    parse_args *args = new parse_args();
    // set rules 
    args->set_args_rules("p","Probability of Poisson X","0.4","float");
    args->set_args_rules("l","lambda of Poisson N","3","int");
    args->set_args_rules("k","upperbound of k (for N, which N can derive to N1, N2 according to p and 1-p)","100","int");
    args->set_args_rules("s","simulation times","10000","int");
    // parse it!
    args->parsing(argc,argv);

    double p = std::atof(args->get_args_val("p").val.c_str());
    double l = std::atof(args->get_args_val("l").val.c_str());
    int upperbound = std::atoi(args->get_args_val("k").val.c_str());
    int simulation_time = std::atoi(args->get_args_val("s").val.c_str());

    // Write file
    FILE *fp;
    fp=fopen("output/part_b.output","w+");
    // Set upperbound for gnuplot to use
    fprintf(fp,"# %d\n",upperbound);

    // ===================================== Mathematic Part ===================================== 
    // Calculate 
    for(double i=1;i<=upperbound;i++){
        // Get total P{X+Y=i}
        double p_s,px=0,py=0;
        p_s = poisson(l,i);
        px = poisson(l*p,i*p);
        py = poisson(l*(1-p),i*(1-p));

        fprintf(fp,"%lf %lf %lf\n",i,p_s,px*py);
    }

    // ===================================== Simulation Part ===================================== 
    // discrete event simulation
    rand_gen *gen = new rand_gen();
    event_list *elist = new event_list();
    int rnt=simulation_time;
    FILE *fp_sim = fopen("output/part_b_sim.output","w+");

    event_type S;
    // init with rand 
    if(gen->frand(0,1)>p){
        // become Y event
        elist->set(0,std::string("Y"));
    }
    else{
        elist->set(0,std::string("X"));
    }
    

    while(rnt){
        // pop out 
        if(elist->get(S)){
            // Using probability P to decide which event will be push 
            if(gen->frand(0,1)>p){
                // become Y event
                elist->set(gen->exponential(l*(1-p),l),std::string("Y"));
            }
            else{
                elist->set(gen->exponential(l*p,l),std::string("X"));
            }
            // record 
            elist->record(S);
            rnt--;
        }
    }

    // Then eliminate first event (init)
    elist->rec.erase(elist->rec.begin(),elist->rec.begin()+1);

    // check 
    int count=0,count_x=0,count_y=0;
    double slot=exp(-1.0/(l)),slot_x=exp(-1.0/(l*p)),slot_y=exp(-1.0/(l*(1-p))),
        record_slot=slot,record_slot_x=slot_x,record_slot_y=slot_y;
    std::map<int,int> counter,counter_x,counter_y;

    while(elist->rec.size()!=0){
        event_type tmp;
        tmp=elist->rec.front();
        elist->rec.erase(elist->rec.begin(),elist->rec.begin()+1);
        // total: S=X+Y
        if(tmp.timestamp<=record_slot)
            count++;
        else{
            record_slot+=slot;
            counter[count]++;
            count=0;
        }
        // And then do X mode 
        if(tmp.type==std::string("X")){
            if(tmp.timestamp<=record_slot_x)
                count_x++;
            else{
                record_slot_x+=slot_x;
                counter_x[count_x]++;
                count_x=0;
            }
        }
        if(tmp.type==std::string("Y")){
            if(tmp.timestamp<=record_slot_y)
                count_y++;
            else{
                record_slot_y+=slot_y;
                counter_y[count_y]++;
                count_y=0;
            }
        }
        
    }


    if(count!=0)
        counter[count]++;
    if(count_x!=0)
        counter_x[count_x]++;
    if(count_y!=0)
        counter_y[count_y]++;


    count=0,count_x=0,count_y=0;

    for(auto&it : counter){
        count+=it.second;
    }

    for(auto&it : counter_x){
        //printf("X: %d %d\n",it.first,it.second);
        count_x+=it.second;
    }

    for(auto&it : counter_y){
        //printf("Y: %d %d\n",it.first,it.second);
        count_y+=it.second;
    }

    for(auto&it : counter){
        double p_xy=0.0;
        for(int i=0;i<=it.first;i++){
            // S=X+Y, X:0~it.first, Y:it.first~0
            p_xy+=((float)counter_x[i]/count_x)*((float)counter_y[it.first-i]/count_y);
        }

        fprintf(fp_sim,"%d %lf %lf\n",it.first,(float)it.second/count,p_xy);
    }

    return 0;
}