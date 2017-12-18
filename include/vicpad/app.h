#ifndef APP_H_
#define APP_H_

#include "display.h"
#include "config.h"

namespace vicpad{
  class App {
    display::Display* cli;
  public:
    App();
    void start(config c) const;
    ~App();
  };
  
} // vicpad
#endif
