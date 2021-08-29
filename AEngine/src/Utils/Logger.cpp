#include "AEngine/Utils/Logger.hpp"

#include <fstream>
#include <chrono>

namespace aengine
{
    void Logger::LogToFile(const std::string& data, const std::string& file, LogType type)
    {
        std::ofstream ofs(file, std::ios::app);

        if (ofs.is_open())
        {
            // Calculate current time
            time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::string currentTimeStr = std::string(ctime(&currentTime));
            
            // Print current time
            ofs << "[" << currentTimeStr.substr(0, currentTimeStr.size() - 1) << "] ";

            // Print log type
            switch (type)
            {
            case LogType::Info:
                ofs << "[INFO]\t";
                break;
            case LogType::Warning:
                ofs << "[WARNING]\t";
                break;
            case LogType::Error:
                ofs << "[ERROR]\t";
                break;
            default:
                ofs << "[LOG]\t";
                break;
            }

            // Print log message
            ofs << data << std::endl;
        }

        ofs.close();
    }
}
