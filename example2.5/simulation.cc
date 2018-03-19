// standard lib
#include <cstdio>
#include <unistd.h>
#include <time.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
// user-defined
#include <ansi_color.h>
#define DEFAULT_ROUNDS 100
#define DEFAULT_RANGES 10

// user-defined function
void helper(FILE *fp,char *prog);
int checker();

bool comp(int a,int b){
    return a<b;
}

int main(int argc,char *argv[]){
    // specify the n rounds, in range: 1~m; with X = m (default value)
    int c,n=DEFAULT_ROUNDS,testcase=n,m=DEFAULT_RANGES,x=DEFAULT_RANGES;
    std::vector<int> steps_record;
    std::map<int, int> cumulate;
    // parsing arguments
    while((c=getopt(argc,argv,"x:n:m:h"))!=-1){
        switch(c){
            case 'x':
                if(optarg)
                    x=std::atoi(optarg);
                break;
            case 'n':
                if(optarg) 
                    n=std::atoi(optarg);
                break;
            case 'm':
                if(optarg) 
                    m=std::atoi(optarg);
                break;
            case 'h':
                helper(stdout,argv[0]);
                exit(1);
                break;
            default:
                helper(stderr,argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    // print 
    //printf("Rounds: %d, Range: 1~%d\n",n,m);

    int count=0,*count_arr,total=0,avg_total=0,avg=0;
    count_arr=(int *)calloc(m,sizeof(int));
    // run testcase time
    while(n--){        
        memset(count_arr,0,m*sizeof(int));
        // need a totally random generator
        srand(time(NULL)+rand());
        while(count<m){
            int rnd=rand()%m;
            //printf("Count: %d, Random %d\n",count,rnd);
            if(count_arr[rnd]==0) count++;
            count_arr[rnd]++;
            // total sum
            total++;
        }
        // get summation 
        for(int i=0;i<m;i++){
            printf("%d: %d(%.3f)\n",i,count_arr[i],(float)count_arr[i]/total);
        }
        printf("Total steps: %d\n",total);
        steps_record.push_back(total);
        avg_total+=total;
        count=0;
        total=0;
        avg++;
    }
    printf("================================\n");
    printf("Average X: %f\n",(float)avg_total/avg);
    std::sort(steps_record.begin(),steps_record.end(),comp);
    int x_count=0;
    for (std::vector<int>::iterator it=steps_record.begin(); it!=steps_record.end(); ++it){
        //printf("%d ",*it);
        if(*it == x){
            x_count++;
        }
        cumulate[*it]++;
    }

    printf("P{X=%d}= %f\n",x, (float)x_count/steps_record.size());

    // Write file
    int last_index;
    FILE *fp_plot;
    fp_plot = fopen("simulation.output","w+");
    if(!cumulate.empty())
        last_index=(--cumulate.end())->first;
    //fprintf(fp_plot,"# testcase map.size last_index\n");
    fprintf(fp_plot,"# %d %d %d\n",testcase,(int)cumulate.size(),last_index);
    /*for(auto it = cumulate.cbegin(); it != cumulate.cend(); ++it)
    {
        printf("[%d]: %d (%f)\n",it->first, it->second, (float)it->second/steps_record.size());
        fprintf(fp_plot,"%d %f\n",it->first, (float)it->second/steps_record.size());
        //std::cout << it->first << " " << it->second.first << " " << it->second.second << "\n";
    }*/

    for(int i=1;i<=last_index;i++){
        if(cumulate.find(i)!=cumulate.end()){
            printf("[%d]: %d (%f)\n",i,cumulate.at(i),(float)cumulate.at(i)/steps_record.size());
            fprintf(fp_plot,"%d %f\n",i, (float)cumulate.at(i)/steps_record.size());
        }
        else{
            printf("[%d]: %d (%f)\n",i,0,0.0);
            fprintf(fp_plot,"%d %f\n",i, 0.0);
        }
    }

    return 0;
}

void helper(FILE *fp,char *prog){
    fprintf(fp,
        ANSI_COLOR_RED "Usage: %s [-x threshold] [-n rounds] [-m range] [-h]" ANSI_COLOR_RESET "\n\n%s\n%s\n%s\n%s\n",
        prog,
        ANSI_COLOR_GREEN "  -x threshold" ANSI_COLOR_RESET ":\tspecify the 'threshold' of the execution times of 1~m occurs at least one time.",
        ANSI_COLOR_GREEN "  -n rounds" ANSI_COLOR_RESET ":\tspecify how many times you want to run the simulation routine.",
        ANSI_COLOR_GREEN "  -m range" ANSI_COLOR_RESET ":\tspecify the range of each execution.",
        ANSI_COLOR_GREEN "  -h " ANSI_COLOR_RESET ":\tprint out the helper information."
        );
}