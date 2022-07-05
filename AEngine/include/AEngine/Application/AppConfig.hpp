#ifndef AE_APP_CONFIG_HPP
#define AE_APP_CONFIG_HPP

#include "AE_API.hpp"

namespace aengine
{
    struct AE_API AppConfig
    {
        int scrWidth = 800;
        int scrHeight = 600;
        const char* title = "AEngine Application";
        bool fullScreen = false;
        bool vSync = true;
        int argc;
        char** argv;
    };
    
}

#endif
