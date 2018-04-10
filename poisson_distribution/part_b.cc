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
  args->set_args_rules("p","Probability of Poisson X","0.5","float");
  args->set_args_rules("l","lambda of Poisson N","3","int");
  args->set_args_rules("k","upperbound of k (for N, which N can derive to N1, N2 according to p and 1-p)","10000","int");
  args->set_args_rules("s","simulation times","10000","int");
  // parse it!
  args->parsing(argc,argv);
  // get result
  double p = std::atof(args->get_args_val("p").val.c_str());
  double l = std::atof(args->get_args_val("l").val.c_str());
  int upperbound = std::atoi(args->get_args_val("k").val.c_str());
  int simulation_time = std::atoi(args->get_args_val("s").val.c_str());

  // ===================================== Mathematic Part =====================================
  // Write file
  FILE *fp;
  fp=fopen("output/part_b.output","w+");
  // Set upperbound for gnuplot to use
  fprintf(fp,"# %d\n",upperbound);

  // Calculate
  for(double i=1; i<=upperbound; i++) {
    // Get total P{X+Y=i}
    double p_s,p_xy=0;
    p_s = poisson(l,i);
    // Get all case probability summation of X,Y combination
    for(int j=0; j<=i; j++) {
      // j represent X , so j increased, it represent that Y is decreased
      p_xy += poisson(l*p,j)*poisson(l*(1-p),(i-j));
    }
    fprintf(fp,"%lf %lf %lf\n",i,p_s,p_xy);
  }

  // ===================================== Simulation Part =====================================
  // discrete event simulation
  // 3 independent event queue
  event_list *elist = new event_list(),*elist_x = new event_list(), *elist_y = new event_list();
  int rnt=simulation_time;
  // different case store into different output file
  FILE *fp_sim = fopen("output/part_b_sim.output","w+"),
        *fp_sim_X = fopen("output/part_b_sim_X.output","w+"),
         *fp_sim_LX = fopen("output/part_b_sim_LX.output","w+"),
          *fp_sim_Y = fopen("output/part_b_sim_Y.output","w+"),
           *fp_sim_LY = fopen("output/part_b_sim_LY.output","w+");

  // self-defined random generator
  rand_gen *gen = new rand_gen();
  // STL random library - use to generate exponential random variables
  std::default_random_engine generator;
  std::exponential_distribution<double> dist(l),dist_1(l*p),dist_2(l*(1-p));

  event_type S;
  // init with one of each X,Y event for N
  elist->set(0,std::string("X"));
  elist->set(0,std::string("Y"));
  // init one event of X and Y respectively
  elist_x->set(0,std::string("X"));
  elist_y->set(0,std::string("Y"));

  // Scheduling N -> X, Y
  while(rnt) {
    // pop out, don't care it's type
    if(elist->get(S)) {
      // Using probability P to decide which event will be push
      if(gen->frand(0,l)>=(l*p)) {
        // become Y event
        elist->set(dist(generator),std::string("Y"));
      } else {
        // become X event
        elist->set(dist(generator),std::string("X"));
      }
      // record S, detail information please check out: https://github.com/kevinbird61/stochastic-calculus-and-probability-model/tree/master/utils#event
      elist->record(S);
      rnt--;
    }
  }

  // Scheduling X, with size = N*p
  rnt=(simulation_time*p);
  while(rnt) {
    // pop out latest event
    if(elist_x->get(S)) {
      // Generate a timestamp from exponential random variable
      elist_x->set(dist_1(generator),std::string("X"));
      // record S, detail information please check out: https://github.com/kevinbird61/stochastic-calculus-and-probability-model/tree/master/utils#event
      elist_x->record(S);
      rnt--;
    }
  }

  // Scheduling Y, with size = N*(1-p)
  rnt=(simulation_time*(1-p));
  while(rnt) {
    // pop out latest event
    if(elist_y->get(S)) {
      // Generate a timestamp from exponential random variable
      elist_y->set(dist_2(generator),std::string("Y"));
      // record S, detail information please check out: https://github.com/kevinbird61/stochastic-calculus-and-probability-model/tree/master/utils#event
      elist_y->record(S);
      rnt--;
    }
  }

  // Then eliminate first 2 event (init)
  elist->rec.erase(elist->rec.begin(),elist->rec.begin()+2);
  // Then eliminate first event (init) respectively
  elist_x->rec.erase(elist_x->rec.begin(),elist_x->rec.begin()+1);
  elist_y->rec.erase(elist_y->rec.begin(),elist_y->rec.begin()+1);

  // set the counter (measure simulation result)
  // "*_ind" is for the independent Poisson
  int count=0,count_x=0,count_x_ind=0,count_y=0,count_y_ind=0;
  double slot=1.0,slot_x=1.0,slot_y=1.0,record_slot=slot,record_slot_x=slot_x,record_slot_y=slot_y;
  std::map<int,int> counter,counter_x,counter_x_ind,counter_y,counter_y_ind;

  // start event scheduling - N
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
    // And then do X event (derive from N)
    if(tmp.type=="X") {
      if(tmp.timestamp<=record_slot_x)
        count_x++;
      else {
        record_slot_x+=slot_x;
        counter_x[count_x]++;
        count_x=0;
      }
    }
    // Then do Y event (derive from N)
    if(tmp.type=="Y") {
      if(tmp.timestamp<=record_slot_y)
        count_y++;
      else {
        record_slot_y+=slot_y;
        counter_y[count_y]++;
        count_y=0;
      }
    }
  }

  // flush the rest of record, and reset
  record_slot_x=slot_x,record_slot_y=slot_y;
  if(count!=0)
    counter[count]++;
  if(count_x!=0)
    counter_x[count_x]++;
  if(count_y!=0)
    counter_y[count_y]++;

  // Independent X queue
  while(elist_x->rec.size()!=0) {
    // fetch event from history record
    event_type tmp;
    tmp=elist_x->rec.front();
    elist_x->rec.erase(elist_x->rec.begin(),elist_x->rec.begin()+1);
    // X event 
    if(tmp.type=="X") {
      if(tmp.timestamp<=record_slot_x)
        count_x_ind++;
      else {
        record_slot_x+=slot_x;
        counter_x_ind[count_x_ind]++;
        count_x_ind=0;
      }
    }
  }

  // Independent Y queue
  while(elist_y->rec.size()!=0) {
    // fetch event from history record
    event_type tmp;
    tmp=elist_y->rec.front();
    elist_y->rec.erase(elist_y->rec.begin(),elist_y->rec.begin()+1);
    // Y event
    if(tmp.type=="Y") {
      if(tmp.timestamp<=record_slot_y)
        count_y_ind++;
      else {
        record_slot_y+=slot_y;
        counter_y_ind[count_y_ind]++;
        count_y_ind=0;
      }
    }
  }

  // flush the rest of record, and reset
  if(count_x_ind!=0)
    counter_x_ind[count_x_ind]++;
  if(count_y_ind!=0)
    counter_y_ind[count_y_ind]++;

  // reset and reuse
  count=0,count_x=0,count_x_ind=0,count_y=0,count_y_ind=0;

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
  for(auto&it : counter_x_ind) {
    count_x_ind+=it.second;
  }
  for(auto&it : counter_y_ind) {
    count_y_ind+=it.second;
  }

  // Write P(N) compare with P(X)*P(Y), X and Y is derive from N
  // Record the parameter we use for this time
  fprintf(fp_sim,"# %d %lf %lf %f\n",simulation_time,l,slot,p);

  // Base on total event queue to calculate the result
  for(auto&it : counter) {
    double p_xy=0.0;
    for(int i=0; i<=it.first; i++) {
      // S=X+Y, X:0~it.first, Y:it.first~0
      p_xy+=((float)counter_x[i]/(float)count_x)*((float)counter_y[it.first-i]/(float)count_y);
    }
    fprintf(fp_sim,"%d %lf %lf\n",it.first,(float)it.second/(float)count,p_xy);
  }

  // Write result of X (derive from N) and Independent X queue
  fprintf(fp_sim_X,"# %d %lf %lf %f\n",simulation_time,l,slot_x,p);
  for(auto&it : counter_x) {
    fprintf(fp_sim_X, "%d %lf\n",it.first,(float)it.second/(float)count_x);
  }
  fprintf(fp_sim_LX,"# %d %lf %lf %f\n",simulation_time,l,slot_x,p);
  for(auto&it : counter_x_ind) {
    fprintf(fp_sim_LX, "%d %lf\n",it.first,(float)it.second/(float)count_x_ind);
  }
  // Write result of Y (derive from N) and Independent Y queue
  fprintf(fp_sim_Y,"# %d %lf %lf %f\n",simulation_time,l,slot_y,(1-p));
  for(auto&it : counter_y) {
    fprintf(fp_sim_Y, "%d %lf\n",it.first,(float)it.second/(float)count_y);
  }
  fprintf(fp_sim_LY,"# %d %lf %lf %f\n",simulation_time,l,slot_y,(1-p));
  for(auto&it : counter_y_ind) {
    fprintf(fp_sim_LY, "%d %lf\n",it.first,(float)it.second/(float)count_y_ind);
  }

  return 0;
}