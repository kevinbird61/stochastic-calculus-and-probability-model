#ifndef _PARSE_ARG
#define _PARSE_ARG

#include <map>
#include <utility>
#include <string>
#include <unistd.h>
#include "ansi_color.h"
// define data structure
struct rawdata {
  std::string description;
  std::string val;
  std::string type;
};

// implement parsing argument function
class parse_args {
 public:
  parse_args();
  ~parse_args();
  // parse from argc,argv
  int parsing(int argc, char *argv[]);
  // set rules
  int set_args_rules(
    std::string flags,
    std::string description,
    std::string default_val,
    std::string type);
  // get value
  rawdata get_args_val(std::string flags);
  // helper info
  void helper(FILE *fp,char *prog);
 private:
  std::map<std::string, rawdata> args;
  std::string options;
};

#endif