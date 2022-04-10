#include "AEngine/Graphics/ShaderProgram.hpp"
#include "AEngine/Exception/ShaderException.hpp"
#include "AEngine/File.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <string>

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

    void ShaderProgram::SetFloat(const char* varName, float val) const noexcept
    {
        glUniform1f(glGetUniformLocation(mId, varName), val);
    }
    void ShaderProgram::SetVec2(const char* varName, const glm::vec2& val) const noexcept
    {
        glUniform2f(glGetUniformLocation(mId, varName), val.x, val.y);
    }
    void ShaderProgram::SetIVec2(const char* varName, const glm::ivec2& val) const noexcept
    {
        glUniform2i(glGetUniformLocation(mId, varName), val.x, val.y);
    }
    void ShaderProgram::SetVec3(const char* varName, const glm::vec3& val) const noexcept
    {
        glUniform3f(glGetUniformLocation(mId, varName), val.x, val.y, val.z);
    }
    void ShaderProgram::SetIVec3(const char* varName, const glm::ivec3& val) const noexcept
    {
        glUniform3i(glGetUniformLocation(mId, varName), val.x, val.y, val.z);
    }
    void ShaderProgram::SetVec4(const char* varName, const glm::vec4& val) const noexcept
    {
        glUniform4f(glGetUniformLocation(mId, varName), val.r, val.g, val.b, val.a);
    }
    void ShaderProgram::SetIVec4(const char* varName, const glm::ivec4& val) const noexcept
    {
        glUniform4i(glGetUniformLocation(mId, varName), val.r, val.g, val.b, val.a);
    }
    void ShaderProgram::SetMat4(const char* varName, const glm::mat4& val) const noexcept
    {
        glUniformMatrix4fv(glGetUniformLocation(mId, varName), 1, GL_FALSE, glm::value_ptr(val));
    }
    void ShaderProgram::SetIntArr(const char* varName, size_t size, int* arr) const noexcept
    {
        glUniform1iv(glGetUniformLocation(mId, varName), size, arr);        
    }
}
