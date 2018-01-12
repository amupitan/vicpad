#include <string>
#include <fstream>

#include "../include/vicpad/content_manager.h"

namespace vicpad {
  ContentManager::ContentManager(){}
  
  void ContentManager::do_something() const {}
  
  void ContentManager::populate(std::string filename) {
   
    std::ifstream infile(filename);
    if (!infile.good()) {
      std::ofstream{ filename };
      return;
    }
    
    std::string line;
    while (std::getline(infile, line)) {
      std::vector<char32_t> vline(line.begin(), line.end());
      buf.push_back(vline);
    }
  }
  
  void ContentManager::add_line(std::string line, uint32_t line_number) {
    if (line_number >= buf.size()) line_number = buf.size() - 1;
    std::vector<char32_t> vline(line.begin(), line.end());
    buf.insert(buf.begin() + line_number, vline);
  }
  
  void ContentManager::add_char(char32_t ch, uint32_t line_number, uint32_t index) {
    if (line_number >= buf.size()) line_number = buf.size() - 1;
    auto & line = buf[line_number];
    if (index > line.size()) index = line.size();
    
    line.insert(line.begin() + index, ch);
  }

  void ContentManager::delete_line(uint32_t line_number) {
    if (line_number >= buf.size()) return;
    buf.erase(buf.begin() + line_number);
  }
  
  void ContentManager::remove_char(uint32_t line_number, uint32_t index) {
    if (line_number >= buf.size()) return;
    auto & line = buf[line_number];
    if (index >= line.size()) return;
    line.erase(line.begin() + index);
  }
  
  std::string ContentManager::get_line(uint32_t line_number) const {
    if (line_number >= buf.size()) return "";
    auto & line = buf[line_number];
    return std::string(line.begin(), line.end());
  }
}