#ifndef AE_FILE_DIALOGS_HPP
#define AE_FILE_DIALOGS_HPP

#include "AE_API.hpp"
#include <string>

struct GLFWwindow;

namespace aengine
{
    class AE_API FileDialog
    {
        friend class Application;
    public:
        // Returns empty string if cancelled
        static std::string OpenFile(const char* filter);
        // Returns empty string if cancelled
        static std::string SaveFile(const char* filter);
    private:
        static GLFWwindow* window;
    };
}

#endif
