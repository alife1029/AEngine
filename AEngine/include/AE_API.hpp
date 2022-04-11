#ifndef AENGINE_AE_API_HPP
#define AENGINE_AE_API_HPP

// Detect platform
#if defined(_WIN32)
    #define AE_PLATFORM_WINDOWS
#elif defined(__linux__)
    #define AE_PLATFORM_UNIX
#endif

// Shared library imports and exports
#ifdef AE_PLATFORM_WINDOWS // Windows
    #ifdef AE_BUILD_SHARED
        #define AE_API __declspec(dllexport)
    #elif defined(AE_SHARED)
        #define AE_API __declspec(dllimport)
    #else
        #define AE_API
    #endif
// BUG: Currently only windows supporting
/*#elif defined(AE_PLATFORM_UNIX) // Linux
    #ifdef AE_BUILD_SHARED
        #define AE_API __attribute__((visibility("default")))
        #define IMGUI_API __attribute__((visibility("default")))
        #define _GLFW_BUILD_DLL
        #define GLAD_GLAPI_EXPORT
        #define GLAD_GLAPI_EXPORT_BUILD
    #else
        #define AE_API
    #endif*/
#else // Unsupported platforms
    //#error AEngine supports only Windows and Linux!
    #error AEngine supports only Windows!
#endif

// Set C++ entry point
#ifdef AE_PLATFORM_WINDOWS
    // Prevent secure warnings on Windows
    #pragma warning(disable : 4996)

    // Make Win32 app on Windows builds
    #include <Windows.h>
    #define CPP_ENTRY_POINT int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
    #define CPP_ENTRY_POINT int main()
#endif

#endif
