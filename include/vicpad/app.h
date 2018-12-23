#ifndef APP_H_
#define APP_H_

#include "config.h"
#include "content_manager.h"
#include "display.h"
#include "unint.h"

namespace vicpad {

class App {
  const char* filename;
  display::Display* cli;
  ContentManager cm;
  struct {
    utils::unint x;
    utils::unint y;
    bool normal;
  } cursor;

  struct {
    bool user_quit;
    bool handled;
    uint64_t length;
    int64_t current_input;
    uint16_t line_length;
  } interaction;

  struct {
    uint8_t tab_length;
    bool use_spaces;
  } state;

  void message(const char* msg) const;
  void update_line_number() const;
  bool should_be_open() const;
  void process_input(display::key_code input);
  void set_cursor_position();
  void update_state();
  void handle_backspace();
  void handle_enter();
  void handle_char();
  void handle_tab();
  void handle_arrow_key();
  void save() const;
  void start_command_executer();

 public:
  App();
  void start(config c);
  ~App();
};

}  // namespace vicpad
#endif
