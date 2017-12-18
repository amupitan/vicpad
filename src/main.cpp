#include <iostream>

#include "../include/vicpad/app.h"
#include "../include/vicpad/config.h"

using namespace vicpad;

int main(int argc, char** argv) {
  
  auto config = parse_args(argc, argv);
  App app;
  app.start(config);
  
  return 0;
}