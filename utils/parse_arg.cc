#include "parse_arg.h"

parse_args::parse_args(){
    options="h";
}

parse_args::~parse_args(){

}

int parse_args::parsing(int argc,char *argv[]){
    char c;
    while((c=getopt(argc,argv,options.c_str()))!=-1){
        switch(c){
            case 'h':
                helper(stdout,argv[0]);
                exit(1);
            break;
            default:
                args[std::string(&c)].val=std::string(optarg);
        }
    }
}

int parse_args::set_args_rules(
    std::string flags,
    std::string description,
    std::string default_val,
    std::string type){
    // add flags
    options+=(flags+":");
    // create
    rawdata data;
    data.description=description;
    data.val=default_val;
    data.type=type;
    // insert 
    args[flags]=data;

}

rawdata parse_args::get_args_val(std::string flags){
    return args[flags];
}

void parse_args::helper(FILE *fp,char *prog){
    // Get parameter info
    std::map<std::string, rawdata>::iterator it;
    std::string param,description;
    for(it=args.begin();it!=args.end();it++){
        param+=("[-"+it->first+" val ] ");
        description+=(ANSI_COLOR_GREEN "  -"+it->first+" val : " ANSI_COLOR_RESET + it->second.description+"\n");
    }
    param+="[-h] ";
    description+=ANSI_COLOR_MAGENTA "  -h: print out detail information of program.\n" ANSI_COLOR_RESET;
    // print helper info
    fprintf(fp,
        ANSI_COLOR_RED "Usage: %s %s" ANSI_COLOR_RESET "\n\n%s",
        prog,
        param.c_str(),
        description.c_str()
        );
}