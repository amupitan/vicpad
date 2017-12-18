#include <string>

#include "../include/vicpad/app.h"
#include "../include/vicpad/display.h"

namespace vicpad {

  App::App() {
    cli = new CLIDisplay();
    
    // default interactions
    interaction.length = 0;
    interaction.line_length = 0;
    interaction.user_quit = false;
    interaction.current_input = -1;
  }
  
  void App::start(config c) {
    message("hello world");
    filename = "file.cpp";
    while (should_be_open()){
      update_state();
      update_line_number();
      // set_cursor_position();
      int input = cli->get_input();
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
    msg = msg + " L" + std::to_string(cursor.y + 1) + ":" + std::to_string(cursor.x + 1); 
    cli->left_message(msg.c_str());
  }
  
  void App::process_input(int16_t input) {
    if (input == 27) { //ESC pressed
      interaction.user_quit = true;
    }
    
    interaction.length = 1; //
    interaction.current_input = input;
  }
  
  void App::set_cursor_position() {
    cli->set_cursor_position(cursor.y, cursor.x);
  }
  
  void App::update_state()  {
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
    delete cli;
  }

} //vicpad