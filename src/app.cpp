#include <iostream>

#include "../include/vicpad/app.h"
#include "../include/vicpad/display.h"

namespace vicpad {

  App::App() {
    cli = new CLIDisplay();
  }
  
  void App::start(config c) const {
    
  }
  
  App::~App() {
    delete cli;
  }

} //vicpad