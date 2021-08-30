#ifndef AE_LOGGER_HPP
#define AE_LOGGER_HPP

#include "AE_API.hpp"
#include <string>

namespace aengine
{
    enum class LogType 
    { 
        Info, 
        Warning, 
        Error 
    };

    class AE_API Logger
    {
    public:
        static void LogToFile(const std::string& data, const std::string& path = "Logs.log", LogType type = LogType::Info);
    };
}

#endif
