#include "Utils.hpp"
#include <filesystem>

bool CheckFileExtension(const std::string& path, const std::string& extension, bool checkDirectory)
{
    if (checkDirectory)
        if (std::filesystem::is_directory(path)) 
            return false;

    auto const extensionPos = path.find_last_of('.');
    const auto ext = path.substr(extensionPos + 1);

    if (ext != extension) return false;
    return true;
}
