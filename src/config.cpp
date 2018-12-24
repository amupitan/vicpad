#include <string>

#include "../include/vicpad/config.h"

namespace vicpad {

const config parse_args(int argc, char** args) {
  config c;
  c.filename = argc > 1 ? args[1] : "untitled.txt";
  c.tab_length = argc > 2 ? std::atoi(args[2]) : 2;
  // TODO(DEV) tabs are not yet supported. i.e. backspace & rendering
  c.use_spaces = true;  // TODO(DEV) set based on config
  return c;
}

}  // namespace vicpad