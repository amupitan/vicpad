#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <cstdint>

namespace vicpad{
  namespace display {
    class Display {
    protected:
      Display(){}
    public:
      virtual void resize(uint16_t width, uint16_t height) = 0;
      virtual ~Display(){}
    };
  } // display
  
  class CLIDisplay : public display::Display {
  public:
    CLIDisplay();
    void resize(uint16_t width, uint16_t height);
    ~CLIDisplay();
  };
} //vicpad

#endif // header guard