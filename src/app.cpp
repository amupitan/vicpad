#include <string>
#include <iostream>

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
    interaction.current_input = -1;
  }
  
  void App::start(config c) {
    message("hello world");
    filename = c.filename;
    cm.populate(filename);
    render_buffer();
    while (should_be_open()){
      update_state();
      update_line_number();
      interaction.handled = false;
      auto input = cli->get_input();
      process_input(input);
    }
    
  }
  
  void App::message(const char* msg) const {
    cli->message(msg);
  }
  
  void App::render_buffer() const {
    auto buffer = cm.data();
    for (auto line : buffer) {
      cli->write(std::string(line.begin(), line.end()).c_str());
      cli->write("\n");
    }
    
    
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
      if (cursor.y) {
        cm.delete_line(cursor.y);
        cursor.y--;
      }
      // TODO set x based on contnet
      cursor.x = cm.get_line_length(cursor.y);
      cli->set_cursor_position(cursor.x, cursor.y);
      return;
    }
    cli->backspace(cursor.x, cursor.y);
    cm.remove_char(cursor.y, cursor.x-1);
    set_cursor_position();
  }
  
  
  void App::handle_enter() {
    interaction.line_length++;
    cm.add_line("", cursor.y+1);
  }
  
  void App::save() const {
    cm.dump(filename); //TODO move to on save;
  }
  
  void App::handle_char() {
    cm.add_char((char32_t)interaction.current_input, cursor.y, cursor.x);
  }
  
  void App::process_input(key_code input) {
    auto code = input.code;
    interaction.length = 1; // TODO
    interaction.current_input = input.value;
    
    switch (code) {
      case key::ALPHANUM:
        handle_char();
        break;
      case key::ESC: // ESC
        interaction.user_quit = true;
        save();
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
      cursor.y = cm.length() ? cm.length() - 1 : 0;
      cursor.x = cm.get_line_length(cursor.y);
      
      cli->set_cursor_position(cursor.x, cursor.y);
      // TODO: set to last position
      return;
    }
    
    
    auto coords = cli->render(cursor.x, cursor.y, interaction.current_input);
    cursor.x = coords.x;
    cursor.y = coords.y;
  }
  
  App::~App() {
    save();
    delete cli;
  }

} //vicpad