#ifndef CONTENT_MANAGER_H_
#define CONTENT_MANAGER_H_

#include <string>
#include <vector>

namespace vicpad {

    class ContentManager {
        std::vector<std::vector<char32_t> > buf;
    public:
        ContentManager();
        void do_something() const;
        void populate(const std::string& filename);
        void dump(const std::string& filename) const;
        void add_line(const std::string& line, uint32_t line_number);
        void add_char(char32_t ch, uint32_t line_number, uint32_t index); 
        void add_string(const std::string& str, uint32_t line_number, uint32_t index);
        void repeat(uint64_t line_number, uint64_t index, char32_t ch, uint64_t n);
        void delete_line(uint32_t line_number);
        void remove_char(uint32_t line_number, uint32_t index); // TODO: remove string
        std::string get_line(uint32_t line_number) const;
        uint64_t get_line_length(uint32_t line_number) const;
        const std::vector<std::vector<char32_t> >& data() const;
        uint64_t length() const;
    };

}

#endif