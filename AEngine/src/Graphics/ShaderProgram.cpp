#include "AEngine/Graphics/ShaderProgram.hpp"
#include "AEngine/Exception/ShaderException.hpp"
#include "AEngine/File.hpp"

#include <glad/glad.h>

namespace aengine
{
    ShaderProgram::ShaderProgram(const char* vs, const char* fs)
    {
        mId = glCreateProgram();
        Compile(vs, GL_VERTEX_SHADER);
        Compile(fs, GL_FRAGMENT_SHADER);
        Link();
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(mId);
    }

    void ShaderProgram::Compile(const char* shaderFile, uint32_t shaderType) const
    {
        // Read shader source
        std::string strShaderSource = File::ReadFile(shaderFile);
        const char* shaderSource = strShaderSource.c_str();

        uint32_t shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        // Shader compile error handling
        int isCompiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (!isCompiled)
        {
            char log[1024];
            glGetShaderInfoLog(shader, 1024, NULL, log);
            ThrowShaderCompileException(shaderType, shaderFile, log);
        }

        glAttachShader(mId, shader);
        glDeleteShader(shader);
    }

    void ShaderProgram::Link() const
    {
        glLinkProgram(mId);

        // Program linking exception handling
        int isLinked;
        glGetProgramiv(mId, GL_LINK_STATUS, &isLinked);
        if (!isLinked)
        {
            char log[1024];
            glGetProgramInfoLog(mId, 1024, NULL, log);
            ThrowShaderLinkingException(log);
        }
    }

    void ShaderProgram::Use() const noexcept
    {
        glUseProgram(mId);
    }

    uint32_t ShaderProgram::ID() const noexcept
    {
        return mId;
    }
    ShaderProgram::operator uint32_t() const noexcept
    {
        return mId;
    }
}
