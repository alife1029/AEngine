// Linux implementation of file dialogs
// This is empty implementation because AEngine supports custom file dialog on linux

#include "AEngine/Application/FileDialogs.hpp"
#include "AEngine/Application/FileDialogFilter.hpp"

#include <iostream>

namespace aengine
{
    void FileDialog::Initialize(int* argc, char*** argv, GLFWwindow* window)
    {
        
    }

    std::string FileDialog::OpenFile(const FileDialogFilter& filter)
    {
        std::cout << "AEngine supports only custom file dialog on Linux!" << std::endl;
        return std::string();
    }

    std::string FileDialog::SaveFile(const FileDialogFilter& filter)
    {
        std::cout << "AEngine supports only custom file dialog on Linux!" << std::endl;
        return std::string();
    }

    std::string FileDialog::BrowseFolder()
    {
        std::cout << "AEngine supports only custom file dialog on Linux!" << std::endl;
        return std::string();
    }
}
