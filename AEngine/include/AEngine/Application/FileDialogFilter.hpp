#pragma once

#include "AE_API.hpp"

#include <string>
#include <vector>

namespace aengine
{
    struct AE_API FileDialogFilter
    {
        FileDialogFilter(const std::string& name, const std::vector<std::string>& extensions);

        std::string name;
        std::vector<std::string> extensions;
    };
}
