#include <cstdio>
// user-defined library
#include "../utils/poisson.h"
#include "../utils/parse_arg.h"
#include "../utils/rand_gen.h"
#include "../utils/event.h"

int main(int argc,char *argv[]) {
  // create parsing args object
  parse_args *args = new parse_args();
  // set rules
  args->set_args_rules("1","lambda 1 of Poisson X","1","int");
  args->set_args_rules("2","lambda 2 of Poisson Y","2","int");
  args->set_args_rules("k","upperbound of k (for S, which S=X+Y)","100","int");
  args->set_args_rules("s","simulation times","10000","int");
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
  for(int i=0; i<=upperbound; i++) {
    // Get total P{X+Y=i}
    double p_s,px,py,p_xy=0;
    p_s = poisson(lambda1+lambda2,i);

    for(int j=0; j<=i; j++) {
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

  // discrete event simulation
  rand_gen *gen = new rand_gen();
  event_list *elist = new event_list();
  int rnt=simulation_time;
  FILE *fp_sim = fopen("output/part_a_sim.output","w+");
  // init with one X, Y event
  event_type X,Y,S;
  elist->set(0,std::string("X"));
  elist->set(0,std::string("Y"));

  // Scheduling S=X+Y
  while(rnt) {
    // pop out
    if(elist->get(S)) {
      if(S.type=="X") {
        elist->set(gen->exponential(lambda1),std::string("X"));
        //printf("X\n");
      } else if(S.type=="Y") {
        elist->set(gen->exponential(lambda2),std::string("Y"));
        //printf("Y\n");
      }
      // record S
      elist->record(S);
      rnt--;
    }
  }

  //printf("size: %d, current time: %lf\n",(int)elist->rec.size(),elist->rec.back().timestamp);
  // erase the init element
  elist->rec.erase(elist->rec.begin(),elist->rec.begin()+2);

  int count=0,count_x=0,count_y=0;
  double slot=exp(-1.0/(lambda1+lambda2)),slot_x=exp(-1.0/lambda1),slot_y=exp(-1.0/lambda2),
         record_slot=slot,record_slot_x=slot_x,record_slot_y=slot_y;
  std::map<int,int> counter,counter_x,counter_y;

  while(elist->rec.size()!=0) {
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
    // And then do X mode
    if(tmp.type=="X") {
      if(tmp.timestamp<=record_slot_x)
        count_x++;
      else {
        record_slot_x+=slot_x;
        counter_x[count_x]++;
        count_x=0;
      }
    }
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

  if(count!=0)
    counter[count]++;
  if(count_x!=0)
    counter_x[count_x]++;
  if(count_y!=0)
    counter_y[count_y]++;

  count=0,count_x=0,count_y=0;

  for(auto&it : counter) {
    count+=it.second;
  }

  for(auto&it : counter_x) {
    //printf("X: %d %d\n",it.first,it.second);
    count_x+=it.second;
  }

  for(auto&it : counter_y) {
    //printf("Y: %d %d\n",it.first,it.second);
    count_y+=it.second;
  }

  for(auto&it : counter) {
    double p_xy=0.0;
    for(int i=0; i<=it.first; i++) {
      // S=X+Y, X:0~it.first, Y:it.first~0
      p_xy+=((float)counter_x[i]/count_x)*((float)counter_y[it.first-i]/count_y);
    }

    fprintf(fp_sim,"%d %lf %lf\n",it.first,(float)it.second/count,p_xy);
  }

  return 0;
}