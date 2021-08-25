#include "AEngine/Exception/Exception.hpp"
#include <sstream>

namespace aengine
{
    AEexception::AEexception(int line, const char* file) noexcept
        : line(line), file(file), message("") { }
    AEexception::AEexception(int line, const char* file, const std::string& message) noexcept
        : line(line), file(file), message(message) { }

    const char* AEexception::what() const noexcept
    {
        std::ostringstream oss;
        if (message.size() > 0)
            oss << "[ERROR_TYPE] " << GetType() << std::endl
                << GetOriginString() << std::endl
                << "[MESSAGE] " << message;
        else
            oss << "[ERROR_TYPE] " << GetType() << std::endl
                << GetOriginString();
        whatBuffer = oss.str();
        return whatBuffer.c_str();
    }

    const char* AEexception::GetType() const noexcept
    {
        return "AEngine Exception";
    }

    int AEexception::GetLine() const noexcept
    {
        return line;
    }
    
    const std::string& AEexception::GetFile() const noexcept
    {
        return file;
    }

    const std::string& AEexception::GetMessage() const noexcept
    {
        return message;
    }

    std::string AEexception::GetOriginString() const noexcept
    {
        std::ostringstream oss;
        oss << "[FILE] " << file << std::endl
            << "[LINE] " << line;
        return oss.str();
    }
}
