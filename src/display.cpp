#include <ncurses.h>
#include "../include/vicpad/display.h"

namespace vicpad{
  namespace display {

  } // display
  
  CLIDisplay::CLIDisplay() {
    // start curses mode
    initscr();
	  printw("Hello World !!!");	/* Print Hello World		  */
	  refresh();			/* Print it on to the real screen */
	  getch();			/* Wait for user input */
  }
  
  void CLIDisplay::resize(uint16_t width, uint16_t height) {}
  
  CLIDisplay::~CLIDisplay(){
    // end curses mode
    endwin();
  }

} //vicpad