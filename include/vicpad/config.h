#ifndef CONFIG_H_
#define CONFIG_H_

namespace vicpad {
  struct config {
    const char* filename;
    int code;
  };
  
  const config parse_args(int argc, char** args);
}

#endif