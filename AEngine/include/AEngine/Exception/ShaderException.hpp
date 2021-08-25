#ifndef AE_SHADER_EXCEPTION
#define AE_SHADER_EXCEPTION

#include "Exception.hpp"
#include <string>

namespace aengine
{
    class AE_API ShaderException : public AEexception
    {
    public:
        ShaderException(int line, const char* file, bool compileError, bool linkingError, uint32_t shaderType, const std::string& shaderFile, const std::string& gpuLog) noexcept;
        virtual const char* GetType() const noexcept;
        virtual std::string GetOriginString() const noexcept override;
    private:
        void TranslateMessage() noexcept;
    private:
        bool compileError;
        bool linkingError;
        uint32_t shaderType;
        std::string strShaderType;
        std::string shaderFile;
        std::string gpuLog;
    };
}

#define ThrowShaderCompileException(__shaderType__, __shaderFile__, __gpuLog__) throw aengine::ShaderException(__LINE__, __FILE__, true, false, __shaderType__, __shaderFile__, __gpuLog__)
#define ThrowShaderLinkingException(__gpuLog__) throw aengine::ShaderException(__LINE__, __FILE__, false, true, 0, "None", __gpuLog__)

#endif
