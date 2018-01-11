#ifndef APP_H_
#define APP_H_

// #include <cstdint>
#include "display.h"
#include "config.h"
#include "content_manager.h"

namespace vicpad{
  
  class App {
    const char* filename;
    display::Display* cli;
    ContentManager cm;
    struct {
      uint16_t x;
      uint16_t y;
      bool normal;
    } cursor;
    
    struct {
      bool user_quit;
      bool handled;
      uint64_t length;
      int64_t current_input;
      uint16_t line_length;
    } interaction;
    
    void message(const char* msg) const;
    void update_line_number() const;
    bool should_be_open() const;
    void process_input(display::key_code input);
    void set_cursor_position();
    void update_state();
    void handle_backspace();
  public:
    App();
    void start(config c);
    ~App();
  };
  
} // vicpad
#endif
