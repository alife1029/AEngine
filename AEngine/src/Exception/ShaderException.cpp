#include "AEngine/Exception/ShaderException.hpp"

#include <sstream>
#include <glad/glad.h>

namespace aengine
{
    ShaderException::ShaderException(int line, const char* file, bool compileError, bool linkingError, uint32_t shaderType, const std::string& shaderFile, const std::string& gpuLog) noexcept
        : AEexception(line, file), compileError(compileError), linkingError(linkingError), shaderType(shaderType), shaderFile(shaderFile), gpuLog(gpuLog) 
    { 
        TranslateMessage();
    }

    const char* ShaderException::GetType() const noexcept
    {
        if (compileError)
            return "AEngine Shader Compile Exception";
        else if (linkingError)
            return "AEngine Shader Linking Exception";
        return "AEngine Shader Exception";
    }

    std::string ShaderException::GetOriginString() const noexcept
    {
        std::ostringstream oss;
        oss << AEexception::GetOriginString() << std::endl;

        if (compileError)
        {
            oss << "[SHADER_TYPE] " << strShaderType << std::endl
                << "[SHADER_FILE] " << shaderFile << std::endl
                << "[GPU_LOG] " << gpuLog << std::endl;
        }
        else if (linkingError)
        {
            oss << "[GPU_LOG] " << gpuLog << std::endl;
        }

        return oss.str();
    }

    void ShaderException::TranslateMessage() noexcept
    {
        if (!compileError)
            return;

        // Convert shader type to string
        switch (shaderType)
        {
        case GL_VERTEX_SHADER:
            strShaderType = "Vertex Shader";
            break;
        case GL_FRAGMENT_SHADER:
            strShaderType = "Fragment Shader";
            break;
        default:
            strShaderType = "Unknown";
            break;
        }
    }
}
