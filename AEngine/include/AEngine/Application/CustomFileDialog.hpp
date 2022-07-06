#pragma once

#include "AE_API.hpp"
#include "Window.hpp"
#include "FileDialogFilter.hpp"

namespace aengine
{
    class AE_API CustomFileDialog
    {
    public:
        CustomFileDialog(const std::string& title, const FileDialogFilter& filter);
        ~CustomFileDialog();
        std::string ShowDialog();
    private:
        virtual void Update(std::string& ret);
    private:
        Window* m_Window;
        FileDialogFilter filter;
    };
}
