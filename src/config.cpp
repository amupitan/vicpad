#include <string>
#include "../include/vicpad/config.h"

namespace vicpad {
  
  const config parse_args(int argc, char** args) {
    config c;
    c.filename =  argc > 1 ? args[1] : "untitled.txt";
    c.tab_length = argc > 2 ? std::atoi(args[2]) : 0; 
    return c;  
  }
  
} //vicpad