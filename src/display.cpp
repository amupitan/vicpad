#include <cstring>

#include <ncurses.h>

#include "../include/vicpad/display.h"

namespace vicpad{
  
  using pair = display::pair;
  
  CLIDisplay::CLIDisplay(uint16_t width, uint16_t height) : width(width), height(height) {
    // start curses mode
    initscr();
    noecho();
	 // printw("Hello World !!!");	/* Print Hello World		  */
	 // refresh();			/* Print it on to the real screen */
	 // getch();			/* Wait for user input */
  }
  
  CLIDisplay::CLIDisplay() {
    initscr();
    noecho();
    getmaxyx(stdscr, height, width);
  }
  
  void CLIDisplay::resize(uint16_t width, uint16_t height) {
    this->width = width;
    this->height = height;
  }
  
  void CLIDisplay::message(const char* msg) const {
    int prev_x, prev_y;
    getyx(stdscr, prev_y, prev_x);
    print(position::BOTTOM, position::CENTER, msg);
    move(prev_y, prev_x);
  }
  
  void CLIDisplay::left_message(const char* msg) const {
    int prev_x, prev_y;
    getyx(stdscr, prev_y, prev_x);
    mvprintw(height - 1, 0, msg);
    move(prev_y, prev_x);
    refresh();
    // getch();
  }
  
  void CLIDisplay::print(position screen_position, position align, const char* msg) const {
    int y = screen_position == position::TOP ? 0 : height - 1;
    int x;
    
    switch(align) {
      case position::RIGHT:
        x = width - strlen(msg);
        break;
      case position::CENTER:
        x = (width - strlen(msg))/2;
        break;
      default:
        x = 0;
    };
    
    mvprintw(y,x, msg);
    refresh();
    // getch();
  }
  
  int16_t CLIDisplay::get_input() const {
    return getch();
  }
  
  void CLIDisplay::set_cursor_position(int&& x, int&& y) const {
    getyx(stdscr, y, x);
  }
  
  pair CLIDisplay::render(int64_t x, int64_t y, int64_t c) const {
    mvaddch(y, x, c);
    getyx(stdscr, y, x);
    return {x, y};
  }
  
  CLIDisplay::~CLIDisplay(){
    // end curses mode
    endwin();
  }

} //vicpad