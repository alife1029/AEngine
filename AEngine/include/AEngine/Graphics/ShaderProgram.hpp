#ifndef AE_SHADER_PROGRAM_HPP
#define AE_SHADER_PROGRAM_HPP

#include <cstdint>
#include <glm/glm.hpp>

namespace aengine
{
    class ShaderProgram
    {
    public:
        ShaderProgram(const char* vs, const char* fs);
        ~ShaderProgram();
        void Compile(const char* shaderFile, uint32_t shaderType) const;
        void Link() const;
        void Use() const noexcept;

        uint32_t ID() const noexcept;
        operator uint32_t() const noexcept;

        // Uniform variables
        void SetFloat(const char* varName, float val) const noexcept;
        void SetVec2(const char* varName, const glm::vec2& val) const noexcept;
        void SetIVec2(const char* varName, const glm::ivec2& val) const noexcept;
        void SetVec3(const char* varName, const glm::vec3& val) const noexcept;
        void SetIVec3(const char* varName, const glm::ivec3& val) const noexcept;
        void SetVec4(const char* varName, const glm::vec4& val) const noexcept;
        void SetIVec4(const char* varName, const glm::ivec4& val) const noexcept;
        void SetMat4(const char* varName, const glm::mat4& val) const noexcept;
        void SetIntArr(const char* varName, size_t size, int* arr) const noexcept;
    private:
        uint32_t mId;
    };
}


#endif
