#include <string>
#include <unordered_map>

#include "../include/vicpad/app.h"
#include "../include/vicpad/content_manager.h"
#include "../include/vicpad/display.h"

namespace vicpad {
using key = display::key;
using key_code = display::key_code;

enum editor_cmd {
  EDIT,
  SAVE,
  QUIT,
  SAVE_AND_QUIT,
};

const std::unordered_map<std::string, editor_cmd> commands = {
    {"save", editor_cmd::SAVE},        {"s", editor_cmd::SAVE},
    {"quit", editor_cmd::QUIT},        {"q", editor_cmd::QUIT},
    {"sq", editor_cmd::SAVE_AND_QUIT}, {"wq", editor_cmd::SAVE_AND_QUIT},
    {"edit", editor_cmd::EDIT},        {"i", editor_cmd::EDIT},
};

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
  filename = c.filename;
  state.tab_length = c.tab_length;
  state.use_spaces = c.use_spaces;
  cm.populate(filename);
  cli->populate(cm.data());
  while (should_be_open()) {
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

bool App::should_be_open() const {
  if (interaction.user_quit)
    return false;
  return true;
}

void App::update_line_number() const {
  std::string msg = filename;
  cli->clear_bottom();
  msg = msg + " L" + std::to_string(cursor.y + 1) + ":" +
        std::to_string(cursor.x + 1) + "C";
  message("vic pad");
  cli->left_message(msg.c_str());
}

void App::handle_backspace() {
  interaction.handled = true;
  if (cursor.x == 0) {
    if (cursor.y) {
      // merge prev line with current line
      cm.merge_lines(--cursor.y);

      cursor.x = cm.get_line_length(cursor.y);

      cli->render(cm.data(cursor.y), cursor.y);
      cli->set_cursor_position(cursor.x, cursor.y);
    }

    return;
  }

  cm.remove_char(cursor.y, cursor.x - 1);

  // get updated line
  auto curr_line = cm.data(cursor.y, cursor.y + 1);
  if (curr_line.size() == 0)
    return;

  // render updated line
  cli->render(curr_line[0], cursor.y);

  // adjust cursor for backspace and update display
  cursor.x--;
  cli->set_cursor_position(cursor.x, cursor.y);
}

void App::handle_enter() {
  cm.line_break(cursor.y, cursor.x);
  cli->render(cm.data(cursor.y), cursor.y);

  cursor.x = 0;
  cursor.y++;
  cli->set_cursor_position(cursor.x, cursor.y);

  interaction.handled = true;
  interaction.line_length++;
}

void App::save() const {
  cm.dump(filename);  // TODO move to on save;
}

void App::handle_char() {
  cm.add_char((char32_t)interaction.current_input, cursor.y, cursor.x);
}

void App::handle_tab() {
  std::string spaces(state.tab_length, ' ');
  // TODO(DEV) tab is not yet supported because
  // backspace isn't handled correctly with cm & cli
  std::string tab = state.use_spaces ? spaces : "\t";

  // cm.repeat(cursor.y, cursor.x, ' ', state.tab_length);
  cm.add_string(tab, cursor.y, cursor.x);  // TODO: use the commented version
  cli->write(cursor.x, cursor.y, spaces.c_str());
  auto new_position = cli->get_cursor_position();
  cursor.x = new_position.x;
  cursor.y = new_position.y;
  interaction.handled = true;
}

void App::handle_arrow_key() {
  auto line_length = cm.get_line_length(cursor.y);
  if (cursor.x >= line_length)
    cursor.x = line_length;

  auto num_lines = cm.length();
  if (cursor.y >= num_lines)
    cursor.y = num_lines - 1;
  interaction.handled = true;
  cli->set_cursor_position(cursor.x, cursor.y);
}

void App::process_input(key_code input) {
  auto code = input.code;
  interaction.length = 1;  // TODO
  interaction.current_input = input.value;

  switch (code) {
    case key::ALPHANUM:
      handle_char();
      break;
    case key::ESC:  // ESC
      start_command_executer();
      break;
    case key::ENTER:  // Enter
      handle_enter();
      break;
    case key::TAB:
      handle_tab();
      break;
    case key::BACKSPACE:
      handle_backspace();
      break;
    case key::UP:
      cursor.y--;
      handle_arrow_key();
      break;
    case key::DOWN:
      cursor.y++;
      handle_arrow_key();
      break;
    case key::LEFT:
      cursor.x--;
      handle_arrow_key();
      break;
    case key::RIGHT:
      cursor.x++;
      handle_arrow_key();
      break;
    case key::UNKNOWN:
      break;
  }
}

void App::start_command_executer() {
  interaction.handled = true;
  // cli display command palette
  cli->open_command_palette();

  // cli get word
  std::string cmd_str = cli->get_command();
  auto cmd = commands.find(cmd_str);
  if (cmd == commands.end()) {
    // TODO handle error
    return;
  }

  switch (cmd->second) {
    case SAVE:
      save();
      break;
    case QUIT:
      interaction.user_quit = true;
      break;
    case SAVE_AND_QUIT:
      save();
      interaction.user_quit = true;
      break;
    case EDIT:
      break;
  }

  cli->close_command_palette();
}

void App::set_cursor_position() {
  auto pos = cli->get_cursor_position();
  cursor.y = pos.y;
  cursor.x = pos.x;
}

void App::update_state() {
  if (interaction.handled)
    return;
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
  delete cli;
}

}  // namespace vicpad