#include "../include/vicpad/args.h"

namespace vicpad {
   config parse_args(int argc, const char** args) {
    config c;
    if (argc == 3) {
      c.code = -1;
    }else{
      c.code = 0;
    }
    
    return c;  
  }
  
}