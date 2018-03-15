// standard lib
#include <cstdio>
#include <unistd.h>
#include <time.h>
#include <cstdlib>
#include <cstring>
// user-defined
#include <ansi_color.h>
#define DEFAULT_ROUNDS 100
#define DEFAULT_RANGES 10

// user-defined function
void helper(FILE *fp,char *prog);
int checker();

int main(int argc,char *argv[]){
    // specify the n rounds, in range: 1~m
    int c,n=DEFAULT_ROUNDS,m=DEFAULT_RANGES;
    // parsing arguments
    while((c=getopt(argc,argv,"x:n:m:h"))!=-1){
        switch(c){
            case 'x':
                if(optarg)
                    n=std::atoi(optarg);
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
        avg_total+=total;
        count=0;
        total=0;
        avg++;
    }
    printf("================================\n");
    printf("Average X: %f\n",(float)avg_total/avg);

    return 0;
}

void helper(FILE *fp,char *prog){
    fprintf(fp,
        ANSI_COLOR_RED"Usage: %s [-x threshold] [-n rounds] [-m range] [-h]"ANSI_COLOR_RESET"\n\n%s\n%s\n%s\n%s\n",
        prog,
        ANSI_COLOR_GREEN"  -x threshold"ANSI_COLOR_RESET":\tspecify the 'threshold' of the execution times of 1~m occurs at least one time.",
        ANSI_COLOR_GREEN"  -n rounds"ANSI_COLOR_RESET":\tspecify how many times you want to run the simulation routine.",
        ANSI_COLOR_GREEN"  -m range"ANSI_COLOR_RESET":\tspecify the range of each execution.",
        ANSI_COLOR_GREEN"  -h "ANSI_COLOR_RESET":\tprint out the helper information."
        );
}