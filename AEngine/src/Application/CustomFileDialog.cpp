#include "AEngine/Application/CustomFileDialog.hpp"
#include "AEngine/Utils/Time.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace aengine
{
    CustomFileDialog::CustomFileDialog(const std::string& title, const FileDialogFilter& filter)
        :
        filter(filter)
    {
        m_Window = new Window(720, 540, title.c_str(), false);
    }

    CustomFileDialog::~CustomFileDialog()
    {
        delete m_Window;
    }

    std::string CustomFileDialog::ShowDialog()
    {
        GLFWwindow* lastContext = glfwGetCurrentContext();
        
        glfwMakeContextCurrent(m_Window->m_GlfwWindow);
        m_Window->InitGLAD();

        glfwSwapInterval(1);

        std::string ret;

        while(m_Window->IsOpen())
        {
            m_Window->Clear();

            Update(ret);

            m_Window->PollEvents();
            m_Window->SwapBuffers();

            Time::Update();
        }

        glfwMakeContextCurrent(lastContext);

        return ret;
    }

    void CustomFileDialog::Update(std::string& ret)
    {
        
    }
}
