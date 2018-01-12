#include <string>

#include "../include/vicpad/app.h"
#include "../include/vicpad/display.h"
#include "../include/vicpad/content_manager.h"

namespace vicpad {
  using key = display::key;
  using key_code = display::key_code;

  App::App() {
    cli = new CLIDisplay();
    
    // default interactions
    interaction.length = 0;
    interaction.line_length = 1;
    interaction.user_quit = false;
    interaction.handled = false;
    interaction.is_enter = false;
    interaction.current_input = -1;
  }
  
  void App::start(config c) {
    message("hello world");
    filename = c.filename;
    while (should_be_open()){
      update_state();
      update_line_number();
      // set_cursor_position();
      interaction.handled = false;
      auto input = cli->get_input();
      process_input(input);
      
      
    }
    
  }
  
  void App::message(const char* msg) const {
    cli->message(msg);
  }
  
  bool App::should_be_open() const {
    if (interaction.user_quit) return false;
    return true;
  }
  
  void App::update_line_number() const{
    std::string msg = filename;
    msg = msg + " L" + std::to_string(interaction.line_length) + ":" + std::to_string(cursor.x + 1) + "C"; 
    cli->left_message(msg.c_str());
  }

  void App::handle_backspace() {
    interaction.handled = true;
    if (cursor.x == 0) {
      cursor.y--;
      cli->set_cursor_position(cursor.x, cursor.y);
      return;
    }
    cli->backspace(cursor.x, cursor.y);
    set_cursor_position();
  }
  
  
  void App::handle_enter() {
    //interaction.handled = true;
    interaction.line_length++;
    // interaction.is_enter = true;
    cm.add_line("", cursor.y);
  }
  
  void App::handle_char() {
    cm.add_char((char32_t)interaction.current_input, cursor.y, cursor.x);
  }
  
  void App::process_input(key_code input) {
    auto code = input.code;
    interaction.length = 1; //
    interaction.current_input = input.value;
    
    switch (code) {
      case key::ALPHANUM:
        handle_char();
        break;
      case key::ESC: // ESC
        interaction.user_quit = true;
        break;
      case key::ENTER: // Enter
        handle_enter();
        break;
      case key::BACKSPACE:
        handle_backspace();
        break;
      case key::UP:
        cli->set_cursor_position(cursor.x, --cursor.y);
        interaction.handled = true;        
        break;
      case key::DOWN:
        cli->set_cursor_position(cursor.x, ++cursor.y); 
        interaction.handled = true;               
        break;
      case key::LEFT:
        cli->set_cursor_position(--cursor.x, cursor.y);    
        interaction.handled = true;    
        break;
      case key::RIGHT:
        cli->set_cursor_position(++cursor.x, cursor.y);
        interaction.handled = true;        
        break;
      case key::UNKNOWN:
        break;
    }
    
    // interaction.length = 1; //
    // interaction.current_input = input.value;
  }
  
  void App::set_cursor_position() {
    auto pos = cli->get_cursor_position();
    cursor.y = pos.y;
    cursor.x = pos.x;
  }
  
  void App::update_state()  {
    if (interaction.handled) return;
    if (interaction.current_input == -1) {
      cursor.y = 0;
      cursor.x = 0;
      // TODO: set to last position
      return;
    }
    
    
    auto coords = cli->render(cursor.x, cursor.y, interaction.current_input);
    cursor.x = coords.x;
    cursor.y = coords.y;
  }
  
  App::~App() {
    cm.dump("dump.txt");
    delete cli;
  }

} //vicpad