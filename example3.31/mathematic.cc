#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <time.h>
#include <cmath>
#include <ansi_color.h>
/* Default value
    DEFAULT_R = default range, e.g. the event number
    DEFAULT_M = default execution times
*/
#define DEFAULT_R 5
#define DEFAULT_M 100
/* Global variables, array list
    p : probability array (with dynamic size)
*/
float *p;

/* Function 
    combination: Calculate C(m, j)
    conditional_probability: the new way to calculate probability, with execution time: "m" and current posible categories: "r"
    helper: print out the helping information
*/
// calculate permutation
int combination(int m,int n);
// calculate with conditional probability - recursive function
float conditional_probability(int m,int r);
// command helper 
void helper(FILE *fp,char *prog);

// Main Program goes here
int main(int argc, char *argv[]){
    /* Local variables
        c: arg flag
        r: maximum size of categories
        m: our execution times
    */
    int c,r=DEFAULT_R,m=DEFAULT_M;
    // get the probability with size
    while((c=getopt(argc,argv,"m:r:h"))!=-1){
        switch(c){
            case 'r':
                if(optarg)
                    r=std::atoi(optarg);
                break;
            case 'm':
                if(optarg) 
                    m=std::atoi(optarg);
                break;
            case 'h':
                helper(stdout,argv[0]);
                exit(0);
                break;
            default:
                helper(stderr,argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    //printf("Specify r=`%d`, m=`%d`\n",r,m);
    // initialize the probability array
    p = (float*)calloc(m,sizeof(float));
    memset(p,0,m*sizeof(float));
    for(int i=0;i<r;i++){
        p[i]=1/(float)r;
    }

    // Calculate the probability by condition probability method, calculate from r~m
    float result=0.0,pre=0.0;
    for(int i=1;i<=m;i++){
        // if execution times < event number, then result=0
        if(i>=r)
            result=conditional_probability(i,r);
        else 
            result=0.0;
        
        printf("%d %f\n",i,result-pre);
        // store previous value
        pre=result;
    }

    free(p);
    return 0;
}

float conditional_probability(int m,int r){
    // if r larger than m, we don't need to discuss this case
    if(r>m)
        return 0;
    if(r==1){
        // if r == 1 , and if m >= 1, then there have only one result; if m=0, it means
        // there no any execution time left.
        if(m>=1)
            return 1.0;
        else if(m==0)
            return 0.0;
    }
    else{
        // normal cases go here
        float result_p=0.0,sum_Pr=0.0;
        // get probability summation
        for(int j=0;j<r;j++){
            sum_Pr+=p[j];
        }
        // Sigma: r ~ (m-r+1)
        for(int i=1;i<=(m-r+1);i++){
            // Get result recursively
            result_p+=(conditional_probability(m-i,r-1)*combination(m,i)*powf(p[r-1]/sum_Pr,i)*powf((float)1-(p[r-1]/sum_Pr),m-i));
        }
        
        // return the result of current stage
        return result_p;
    }
}

int combination(int m,int n){
    return (n==0||m==n)?1:combination(m-1,n)+combination(m-1,n-1);
}

void helper(FILE *fp,char *prog){
    fprintf(fp,
        ANSI_COLOR_RED "Usage: %s [-r size] [-m execution_times] [-h]" ANSI_COLOR_RESET "\n\n%s\n%s\n%s\n",
        prog,
        ANSI_COLOR_GREEN "  -r size" ANSI_COLOR_RESET ":\tspecify size of categories.",
        ANSI_COLOR_GREEN "  -m execution_times" ANSI_COLOR_RESET ":\tspecify the execution times.",
        ANSI_COLOR_GREEN "  -h " ANSI_COLOR_RESET ":\tprint out the helper information."
        );
}