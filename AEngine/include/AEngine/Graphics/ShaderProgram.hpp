#ifndef AE_SHADER_PROGRAM_HPP
#define AE_SHADER_PROGRAM_HPP

#include <string>
#include <cstdint>
#include <map>

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
    private:
        uint32_t mId;
    };
}


#endif
