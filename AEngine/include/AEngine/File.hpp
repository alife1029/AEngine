#ifndef AE_FILE_HPP
#define AE_FILE_HPP

#include <string>

namespace aengine
{
    class File
    {
    public:
        static std::string ReadFile(const std::string& file);
    };
}

#endif
