#include <cstdio>
// user-defined library
#include "../utils/poisson.h"
#include "../utils/parse_arg.h"
#include "../utils/rand_gen.h"
#include "../utils/event.h"

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

    /*std::map<int,int> x,y,S; 
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

    // Third way => to construct X, Y separately, and map to an Time queue

    for(auto& it: sim){
        // Calculate result
        fprintf(fpx,"%d %f %f\n",it.first,(float)it.second.s/simulation_time,(float)it.second.xy/(2*simulation_time));
    }*/

    // discrete event simulation
    rand_gen *gen = new rand_gen();
    event_list *elist = new event_list();
    int rnt=simulation_time;
    /*while(rnt){
        // printf("%lf\n",gen->exponential(lambda2,5*lambda1));
        event_type x;
        x.timestamp = gen->exponential(lambda2,5);
        x.type = std::string("X");
        elist->set(x);
    }*/
    // init with one X, Y event
    event_type X,Y,S;
    X.timestamp=0;
    X.type=std::string("X");
    Y.timestamp=0;
    Y.type=std::string("Y");
    elist->set(X);
    elist->set(Y);
    while(rnt){
        // pop out
        if(elist->get(S)){
            if(S.type=="X"){
                X.timestamp=gen->exponential(lambda1,5);
                X.type=std::string("X");
                elist->set(X);
            }
            else{
                Y.timestamp=gen->exponential(lambda2,5);
                Y.type=std::string("Y");
                elist->set(Y);
            }
            // record S
            elist->record(S);
            rnt--;
        }
    }

    printf("size: %d, current time: %lf\n",(int)elist->rec.size(),elist->rec.back().timestamp);
    // erase the first 2 element
    elist->rec.erase(elist->rec.begin(),elist->rec.begin()+2);
    int count=0;
    double slot=1.0/(lambda1+lambda2),record_slot=slot;
    printf("slot: %lf\n",slot);
    std::map<int,int> counter;
    while(elist->rec.size()!=0){
        event_type tmp;
        tmp=elist->rec.front();
        elist->rec.erase(elist->rec.begin(),elist->rec.begin()+1);
        if(tmp.timestamp<=record_slot)
            count++;
        else{
            record_slot+=slot;
            counter[count]++;
            count=0;
        }
    }
    if(count!=0)
        counter[count]++;

    count=0;
    for(auto&it : counter){
        count+=it.second;
        //printf("%d %lf\n",it.first,(float)it.second);
    }
    float total=0.0;
    for(auto&it : counter){
        printf("%d %lf\n",it.first,(float)it.second/count);
        total+=(float)it.second/count;
    }
    printf("%f\n",total);

    return 0;
}