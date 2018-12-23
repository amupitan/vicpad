#ifndef CONFIG_H_
#define CONFIG_H_

namespace vicpad {
struct config {
  const char* filename;
  int code;
  int tab_length;
  bool use_spaces;
};

const config parse_args(int argc, char** args);
}  // namespace vicpad

#endif