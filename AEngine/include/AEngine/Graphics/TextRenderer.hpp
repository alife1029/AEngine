#pragma once 

#include <AE_API.hpp>
#include "FontManager.hpp"

namespace aengine
{
    class AE_API TextRenderer
    {
    public:
        

    private:
        static void Initialize();
        static void Shutdown();
    
    private:
        static FontManager* m_FontManager;
    };
}
