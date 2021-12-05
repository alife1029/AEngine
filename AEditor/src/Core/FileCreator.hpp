#pragma once

#include <string>

class FileCreator
{
public:
    static std::string CreateNativeCppFile(const std::string& directory, const std::string& title);
};
