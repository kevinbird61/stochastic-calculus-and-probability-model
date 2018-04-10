#include <cstdio>
#include <random>
// user-defined library
#include "../utils/poisson.h"
#include "../utils/parse_arg.h"
#include "../utils/rand_gen.h"
#include "../utils/event.h"

int main(int argc,char *argv[]) {
  // ===================================== Getting User Input (by parse_arg) =====================================
  // create parsing args object
  parse_args *args = new parse_args();
  // set rules
  args->set_args_rules("1","lambda 1 of Poisson X","1","int");
  args->set_args_rules("2","lambda 2 of Poisson Y","2","int");
  args->set_args_rules("k","upperbound of k (for S, which S=X+Y)","100","int");
  args->set_args_rules("s","simulation times","10000","int");
  // parse it!
  args->parsing(argc,argv);
  // get result
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
  for(int i=0; i<=upperbound; i++) {
    // Get total P{X+Y=i}
    double p_s,px,py,p_xy=0;
    p_s = poisson(lambda1+lambda2,i);

    // Get all case probability summation of X,Y combination
    for(int j=0; j<=i; j++) {
      // j represent X , so j increased, it represent that Y is decreased
      px = poisson(lambda1,j);
      py = poisson(lambda2,i-j);
      p_xy += (px*py);
    }
    fprintf(fp,"%d %lf %lf\n",i,p_s,p_xy);
  }

  // ===================================== Simulation Part =====================================
  int simulation_time = std::atoi(args->get_args_val("s").val.c_str());

  // discrete event simulation

  // self-defined random generator
  rand_gen *gen = new rand_gen();
  // STL random library - use to generate exponential random variables
  std::default_random_engine generator;
  std::exponential_distribution<double> dist_1(lambda1),dist_2(lambda2);

  event_list *elist = new event_list();
  int rnt=simulation_time;
  FILE *fp_sim = fopen("output/part_a_sim.output","w+");

  // init with one X, Y event respectively
  event_type X,Y,S;
  elist->set(0,std::string("X"));
  elist->set(0,std::string("Y"));

  // Scheduling S=X+Y
  while(rnt) {
    // pop out latest event
    if(elist->get(S)) {
      // Generate a timestamp from exponential random variable
      if(S.type=="X") {
        elist->set(dist_1(generator),std::string("X"));
      } else if(S.type=="Y") {
        elist->set(dist_2(generator),std::string("Y"));
      }
      // record S, detail information please check out: https://github.com/kevinbird61/stochastic-calculus-and-probability-model/tree/master/utils#event
      elist->record(S);
      rnt--;
    }
  }

  // erase the init element
  elist->rec.erase(elist->rec.begin(),elist->rec.begin()+2);

  // set the counter (measure simulation result)
  int count=0,count_x=0,count_y=0;
  double slot=1.0,record_slot=slot,record_slot_x=slot,record_slot_y=slot;
  std::map<int,int> counter,counter_x,counter_y;

  // start event scheduling
  while(elist->rec.size()!=0) {
    // fetch event from history record
    event_type tmp;
    tmp=elist->rec.front();
    elist->rec.erase(elist->rec.begin(),elist->rec.begin()+1);
    // total: S=X+Y
    if(tmp.timestamp<=record_slot)
      count++;
    else {
      record_slot+=slot;
      counter[count]++;
      count=0;
    }
    // And then do X event
    if(tmp.type=="X") {
      if(tmp.timestamp<=record_slot_x)
        count_x++;
      else {
        record_slot_x+=slot;
        counter_x[count_x]++;
        count_x=0;
      }
    }
    // Then the Y event
    if(tmp.type=="Y") {
      if(tmp.timestamp<=record_slot_y)
        count_y++;
      else {
        record_slot_y+=slot;
        counter_y[count_y]++;
        count_y=0;
      }
    }
  }

  // flush the rest of record
  if(count!=0)
    counter[count]++;
  if(count_x!=0)
    counter_x[count_x]++;
  if(count_y!=0)
    counter_y[count_y]++;

  // reset and reuse
  count=0,count_x=0,count_y=0;

  // calculate total event number, X, Y respectively
  for(auto&it : counter) {
    count+=it.second;
  }
  for(auto&it : counter_x) {
    count_x+=it.second;
  }
  for(auto&it : counter_y) {
    count_y+=it.second;
  }

  // Record the parameter we use for this time
  fprintf(fp_sim,"# %d %d %d %lf %d %d %d\n",simulation_time,lambda1,lambda2,slot,count,count_x,count_y);

  // Base on total event queue to calculate the result
  for(auto&it : counter) {
    double p_xy=0.0;
    // S=X+Y, X:0~it.first, Y:it.first~0
    for(int i=0; i<=it.first; i++) {
      p_xy+=((float)counter_x[i]/count_x)*((float)counter_y[it.first-i]/count_y);
    }
    fprintf(fp_sim,"%d %lf %lf\n",it.first,(float)it.second/count,p_xy);
  }

  return 0;
}