#include <AEngine.hpp>
#include <fstream>
#include <ctime>
#include <chrono>

#include "AEditor.hpp"

CPP_ENTRY_POINT
{
    try 
    {
        // Create app config object
        aengine::AppConfig appCfg = aengine::AppConfig();
        appCfg.title = "AEditor";
        appCfg.scrWidth = 1200;
        appCfg.scrHeight = 640;
        // Create AEngine application instance and pass app config
        aengine::Application* editor = new AEditor(appCfg);

        // Run application
        editor->Run();
        // Clear app data
        delete editor;
        // Close app with success value
        return 0;
    }
    catch(const std::exception& ex)
    {
        std::ofstream ofs("AEerror.log", std::ios::app);

        if (ofs.is_open())
        {
            // Print error details to log file
            time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::string currentTimeStr = std::string(ctime(&currentTime));
            ofs << "[" << currentTimeStr.substr(0, currentTimeStr.size() - 1) << "]" << std::endl
                << ex.what() << "\n\n" << std::endl;
        }

        ofs.close();

#ifdef AE_PLATFORM_WINDOWS
        // Show error message on windows
        MessageBox(nullptr, ex.what(), "An Error Occured!", MB_ICONERROR);
#endif

        // Close app with fail value
        return -1;
    }
}
