#ifndef CONTENT_MANAGER_H_
#define CONTENT_MANAGER_H_
#include <vector>

namespace vicpad {

    class ContentManager {
        std::vector<std::vector<char> > buf;
    public:
        ContentManager(){}
        void do_something() const;
    };

}

#endif