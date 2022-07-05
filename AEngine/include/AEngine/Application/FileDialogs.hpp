#ifndef AE_FILE_DIALOGS_HPP
#define AE_FILE_DIALOGS_HPP

#include "AE_API.hpp"
#include <string>
#include <vector>

struct GLFWwindow;

namespace aengine
{

    class AE_API FileDialog
    {
        friend class Application;
    public:
        struct Filter
        {
            Filter(const std::string& name, const std::vector<std::string>& extensions);

            std::string name;
            std::vector<std::string> extensions;
        };
    public:
        // Returns empty string if cancelled
        static std::string OpenFile(const Filter& filter);
        // Returns empty string if cancelled
        static std::string SaveFile(const Filter& filter);
        // Returns empty string if cancelled
        static std::string BrowseFolder();
    private:
        static GLFWwindow* window;
    };
}

#endif
