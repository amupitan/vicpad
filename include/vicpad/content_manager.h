#ifndef CONTENT_MANAGER_H_
#define CONTENT_MANAGER_H_

#include <string>
#include <vector>

#include "./types.h"

namespace vicpad {

class ContentManager {
  Content buf;

 public:
  ContentManager();
  void do_something() const;
  /**
   * Populates the content manager with content from the file with that filename
   */
  void populate(const std::string& filename);

  /**
   * Writes the content of the content manager into the file with that filename
   */
  void dump(const std::string& filename) const;
  void add_line(const std::string& line, uint32_t line_number);
  void add_char(char32_t ch, uint32_t line_number, uint32_t index);
  void add_string(const std::string& str, uint32_t line_number, uint32_t index);
  void repeat(uint64_t line_number, uint64_t index, char32_t ch, uint64_t n);
  void delete_line(uint32_t line_number);
  // TODO: remove string
  void remove_char(uint32_t line_number, uint32_t index);
  std::string get_line(uint32_t line_number) const;
  uint64_t get_line_length(uint32_t line_number) const;
  const Content& data() const;
  const Content data(int start, int end) const;
  uint64_t length() const;
};

}  // namespace vicpad

#endif