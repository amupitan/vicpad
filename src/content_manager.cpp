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
  
  const std::vector<std::vector<char32_t> >& ContentManager::data() const {
    return buf;
  }
  
  void ContentManager::dump(std::string filename) const {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
      for (auto& line : buf) {
        outfile << std::string(line.begin(), line.end()) << "\n";
      }
    }
    
    outfile.close();
  }
  
  void ContentManager::add_line(std::string line, uint32_t line_number) {
    if (line_number > buf.size()) line_number = buf.size();
    std::vector<char32_t> vline(line.begin(), line.end());
    buf.insert(buf.begin() + line_number, vline);
  }
  
  void ContentManager::add_char(char32_t ch, uint32_t line_number, uint32_t index) {
    if (!buf.size()) buf.push_back(std::vector<char32_t>());
    if (line_number >= buf.size()) line_number = buf.size() - 1;
    // if (line_number == buf.size()) buf.push_back(std::vector<char32_t>()); TODO: check
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
  
  uint64_t ContentManager::get_line_length(uint32_t line_number) const {
    if (buf.size() == 0) return 0;
    if (line_number >= buf.size()) line_number = buf.size() - 1;
    return buf[line_number].size();
  }
   
   uint64_t ContentManager::length() const {
     return buf.size();
   }
}