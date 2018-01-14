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
        void populate(std::string filename);
        void dump(std::string filename) const;
        void add_line(std::string line, uint32_t line_number);
        void add_char(char32_t ch, uint32_t line_number, uint32_t index); //TODO: add string
        void delete_line(uint32_t line_number);
        void remove_char(uint32_t line_number, uint32_t index); // TODO: remove string
        std::string get_line(uint32_t line_number) const;
        uint64_t get_line_length(uint32_t line_number) const;
        const std::vector<std::vector<char32_t> >& data() const;
        uint64_t length() const;
    };

}

#endif