#include <cstring>

#include <string>
#include <unordered_map>

#include <ncurses.h>

#include "../include/vicpad/display.h"

namespace vicpad {

using pair = display::pair;
using key = display::key;
using key_code = display::key_code;

const std::unordered_map<int16_t, key> keycodes = {
    {0, key::ALPHANUM},  // TODO: empty
    {KEY_BACKSPACE, key::BACKSPACE},
    {127, key::BACKSPACE},
    {KEY_UP, key::UP},
    {KEY_DOWN, key::DOWN},
    {KEY_LEFT, key::LEFT},
    {KEY_RIGHT, key::RIGHT},
    {KEY_STAB, key::TAB},
    {KEY_BTAB, key::TAB},
    {KEY_CTAB, key::TAB},
    {KEY_CATAB, key::TAB},
    {'\t', key::TAB},
    {10, key::ENTER},  // KEY_ENTER
    {27, key::ESC},

};

bool is_ascii(int64_t c) { return c >= 32 && c <= 126; }

CLIDisplay::CLIDisplay(uint16_t width, uint16_t height)
    : width(width), height(height) {
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
  keypad(stdscr, true);
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

void CLIDisplay::set_cursor_position(uint16_t x, uint16_t y) const {
  move(y, x);
}

void CLIDisplay::print(position screen_position, position align,
                       const char* msg) const {
  int y = screen_position == position::TOP ? 0 : height - 1;
  int x;

  switch (align) {
    case position::RIGHT:
      x = width - strlen(msg);
      break;
    case position::CENTER:
      x = (width - strlen(msg)) / 2;
      break;
    default:
      x = 0;
  };

  mvprintw(y, x, msg);
  refresh();
  // getch();
}

key_code CLIDisplay::get_input() const {
  auto input = getch();
  if (is_ascii(input)) {  // is readbale char
    return {key::ALPHANUM, input};
  }

  auto input_key = keycodes.find(input);
  if (input_key == keycodes.end()) {
    return {key::UNKNOWN, -1};
  }

  return {input_key->second, input};
}

pair CLIDisplay::get_cursor_position() const {
  int64_t x, y;
  getyx(stdscr, y, x);
  return {x, y};
}

pair CLIDisplay::render(uint64_t x, uint64_t y, int64_t c) const {
  // TODO: might not be the best approach
  if (c == 10) {
    mvaddch(y, x, c);
  } else {
    mvinsch(y, x, c);
    move(y, x + 1);
  }

  getyx(stdscr, y, x);
  return {(uint32_t)x, (uint32_t)y};  // TODO: narrowing
}

void CLIDisplay::backspace(uint64_t x, uint64_t y) const {
  mvaddch(y, x, '\b');
  delch();
  refresh();
}

void CLIDisplay::write(const char* line) const {
  printw(line);
  refresh();
}

void CLIDisplay::write(uint64_t x, uint64_t y, const char* line) const {
  mvinsstr(y, x, line);
  move(y, x + strlen(line));
  refresh();
}

void CLIDisplay::clear_bottom() const {
  int64_t curr_x, curr_y, max_x, max_y;
  getyx(stdscr, curr_y, curr_x);
  getmaxyx(stdscr, max_y, max_x);

  move(max_y - 1, 0);
  clrtoeol();
  move(curr_y, curr_x);
}

void CLIDisplay::open_command_palette() {
  getyx(stdscr, cache_cursor.y, cache_cursor.x);
  clear_bottom();

  mvprintw(height - 1, 0, "> ");
}

const char* CLIDisplay::get_command() const {
  int64_t ch;
  std::string cmd;
  int max_x = getmaxx(stdscr);

  while ((ch = getch()) != '\n') {
    switch (ch) {
      case 127:
        if (cmd.length() == 0) {
          beep();
          continue;
        }
        cmd = cmd.substr(0, cmd.length() - 1);
        addch('\b');
        delch();
        break;
      case 27:  // quit on ESC
        return "quit";
      default:
        if (cmd.length() < max_x && is_ascii(ch)) {
          cmd += keyname(ch);
          addch(ch);
        } else {
          beep();
          continue;
        }
    }
  }

  return cmd.c_str();
}

void CLIDisplay::close_command_palette() const {
  move(cache_cursor.y, cache_cursor.x);
}

CLIDisplay::~CLIDisplay() {
  // end curses mode
  endwin();
}

}  // namespace vicpad