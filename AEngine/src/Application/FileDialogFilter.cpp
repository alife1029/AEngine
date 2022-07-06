#include "AEngine/Application/FileDialogFilter.hpp"

namespace aengine
{
    FileDialogFilter::FileDialogFilter(const std::string& name, const std::vector<std::string>& extensions)
        :
        name(name),
        extensions(extensions)
    { }
}
