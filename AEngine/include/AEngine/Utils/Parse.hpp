#ifndef AE_PARSE_HPP
#define AE_PARSE_HPP

#include <string>
#include <sstream>

namespace aengine
{
    template <typename T>
    T ParseNumber(const std::string& str)
    {
        std::istringstream iss(str);
        T num;
        iss >> num;
        return num;
    }
}

#endif
