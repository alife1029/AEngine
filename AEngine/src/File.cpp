#include "AEngine/File.hpp"

#include <fstream>
#include <sstream>

namespace aengine
{
    std::string File::ReadFile(const std::string& file)
    {
        std::stringstream ret;
        std::ifstream ifs(file);

        if (ifs.is_open()) ret << ifs.rdbuf();
        
        ifs.close();
        return ret.str();
    }
}
