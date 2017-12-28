#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <cstdint>

namespace vicpad{
  namespace display {

    enum key {
      BACKSPACE,
      UP,
      DOWN,
      LEFT,
      RIGHT,
      ENTER,
      ESC,
      ALPHANUM,
      UNKNOWN,
    };

    struct key_code {key code; int64_t value; };

    struct pair { int64_t x; int64_t y; };
    
    class Display {
    protected:
      Display(){}
    public:
      virtual void resize(uint16_t width, uint16_t height) = 0;
      virtual void message(const char* msg) const = 0;
      virtual void left_message(const char* msg) const = 0;
      virtual key_code get_input() const = 0;
      virtual pair get_cursor_position() const = 0;
      virtual void set_cursor_position(uint16_t x, uint16_t y) const = 0;
      virtual pair render(int64_t x, int64_t y, int64_t c) const = 0;
      virtual int16_t process_input(int16_t input) const = 0;
      virtual void backspace(uint64_t x, uint64_t y) const = 0;
      virtual ~Display(){}
    };
  } // display
  
  
  
  class CLIDisplay : public display::Display {
    uint16_t width; //< width of the screen
    uint16_t height;  //< height of the screen
    
    /** An enum
     * Represents the print positions
     * TOP and BOTTOM for level; LEFT, CENTER and RIGHT for alignment
     */
    enum position { TOP,BOTTOM, LEFT, CENTER, RIGHT };
    
    void print(position screen_position, position align, const char* msg) const;
  public:
    /**
     * Constructs a command line display for the CL's height and width
     * using ncurses
     */
    CLIDisplay();
    CLIDisplay(uint16_t width, uint16_t height);
    void resize(uint16_t width, uint16_t height);
    
    /**
     * Displays msg at the bottom center of the screen
     * \param msg message to be displayed
     */
    void message(const char* msg) const;
    
    /**
     * Displays msg at the bottom left of the screen
     * \param msg message to be displayed
     */
    void left_message(const char* msg) const;
    
    /**
     * Handles the input from the user
     * \return the encoding of the key pressed by the user
     */
    display::key_code get_input() const;
    
    display::pair get_cursor_position() const;
    
    /**
     * Writes the input character to the screen
     * \param c character to be displayed
     * \return the position of the rendered character
     */
    display::pair render(int64_t x, int64_t y, int64_t c) const;

    int16_t process_input(int16_t input) const;

    void backspace(uint64_t x, uint64_t y) const;    

    void set_cursor_position(uint16_t x, uint16_t y) const;    
    
    /**
     * Closes ncurses window
     */
    ~CLIDisplay();
  };
} //vicpad

#endif // header guard