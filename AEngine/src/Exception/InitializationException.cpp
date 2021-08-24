#include "AEngine/Exception/InitializationException.hpp"
#include <sstream>

namespace aengine
{
    InitializationException::InitializationException(int line, const char* file, const std::string& errDescription) noexcept
        : AEexception(line, file), errDescription(errDescription) { }

    const char* InitializationException::GetType() const noexcept
    {
        return "AEngine Initialization Exception";
    }

    std::string InitializationException::GetOriginString() const noexcept
    {
        std::ostringstream oss;
        oss << AEexception::GetOriginString() << std::endl
            << "[ERROR_DESCRIPTION] " << errDescription;
        return oss.str();
    }
}
