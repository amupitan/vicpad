#include <fstream>
#include <string>

#include "../include/vicpad/content_manager.h"

namespace vicpad {
ContentManager::ContentManager() {}

void ContentManager::do_something() const {}

void ContentManager::populate(const std::string& filename) {
  std::ifstream infile(filename);
  if (!infile.good()) {
    std::ofstream{filename};
    return;
  }

  std::string line;
  while (std::getline(infile, line)) {
    Line vline(line.begin(), line.end());
    buf.push_back(vline);
  }
}

const Content& ContentManager::data() const {
  return buf;
}

const Content ContentManager::data(int start, int end) const {
  return Content(buf.begin() + start, buf.begin() + end);
}

void ContentManager::dump(const std::string& filename) const {
  std::ofstream outfile(filename);
  if (outfile.is_open()) {
    for (auto& line : buf) {
      outfile << std::string(line.begin(), line.end()) << "\n";
    }
  }

  outfile.close();
}

void ContentManager::add_line(const std::string& line, uint32_t line_number) {
  if (line_number > buf.size())
    line_number = buf.size();
  Line vline(line.begin(), line.end());
  buf.insert(buf.begin() + line_number, vline);
}

void ContentManager::add_char(char32_t ch,
                              uint32_t line_number,
                              uint32_t index) {
  if (!buf.size())
    buf.push_back(Line());
  if (line_number >= buf.size())
    line_number = buf.size() - 1;
  // if (line_number == buf.size()) buf.push_back(Line());
  // TODO: check
  auto& line = buf[line_number];
  if (index > line.size())
    index = line.size();

  line.insert(line.begin() + index, ch);
}

void ContentManager::add_string(const std::string& str,
                                uint32_t line_number,
                                uint32_t index) {
  if (!buf.size())
    buf.push_back(Line());
  if (line_number >= buf.size())
    line_number = buf.size() - 1;
  // if (line_number == buf.size()) buf.push_back(Line());
  // TODO: check
  auto& line = buf[line_number];
  if (index > line.size())
    index = line.size();

  std::string new_line = std::string(line.begin(), line.begin() + index) + str +
                         std::string(line.begin() + index, line.end());
  buf[line_number] = Line(new_line.begin(), new_line.end());
}

void ContentManager::repeat(uint64_t line_number,
                            uint64_t index,
                            char32_t ch,
                            uint64_t n) {
  if (line_number >= buf.size())
    return;
  auto& line = buf[line_number];
  line.insert(line.begin() + index, n, ch);
}

void ContentManager::delete_line(uint32_t line_number) {
  if (line_number >= buf.size())
    return;
  buf.erase(buf.begin() + line_number);
}

void ContentManager::remove_char(uint32_t line_number, uint32_t index) {
  if (line_number >= buf.size())
    return;
  auto& line = buf[line_number];
  if (index >= line.size())
    return;
  line.erase(line.begin() + index);
}

std::string ContentManager::get_line(uint32_t line_number) const {
  if (line_number >= buf.size())
    return "";
  auto& line = buf[line_number];
  return std::string(line.begin(), line.end());
}

uint64_t ContentManager::get_line_length(uint32_t line_number) const {
  if (buf.size() == 0)
    return 0;
  if (line_number >= buf.size())
    line_number = buf.size() - 1;
  return buf[line_number].size();
}

uint64_t ContentManager::length() const {
  return buf.size();
}
}  // namespace vicpad