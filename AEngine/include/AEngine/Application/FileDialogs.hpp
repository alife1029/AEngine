#ifndef AE_FILE_DIALOGS_HPP
#define AE_FILE_DIALOGS_HPP

#include "AE_API.hpp"
#include "FileDialogFilter.hpp"
#include <string>
#include <vector>

struct GLFWwindow;

namespace aengine
{

    class AE_API FileDialog
    {
        friend class Application;
    public:
        // TODO: Implement this for Win32 api
        static void Initialize(int* argc, char*** argv, GLFWwindow* window);
        // Returns empty string if cancelled
        static std::string OpenFile(const FileDialogFilter& filter);
        // Returns empty string if cancelled
        static std::string SaveFile(const FileDialogFilter& filter);
        // Returns empty string if cancelled
        static std::string BrowseFolder();
    private:
        static GLFWwindow* window;
    };
}

#endif
