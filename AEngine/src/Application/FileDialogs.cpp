#include "AEngine/Application/FileDialogs.hpp"

namespace aengine
{
    GLFWwindow* FileDialog::window = nullptr;

    FileDialog::Filter::Filter(const std::string& name, const std::vector<std::string>& extensions)
    : 
    name(name),
    extensions(extensions)
{ }
}
