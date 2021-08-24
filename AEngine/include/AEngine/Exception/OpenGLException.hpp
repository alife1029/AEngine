#ifndef AE_OPENGL_EXCEPTION_HPP
#define AE_OPENGL_EXCEPTION_HPP

#include "Exception.hpp"

#include <string>

namespace aengine
{
    class AE_API OpenGLException : public AEexception
    {
    public:
        OpenGLException(int line, const char* file, uint32_t errCode) noexcept;
        virtual const char* GetType() const noexcept;
        virtual std::string GetOriginString() const noexcept override;
    private:
        uint32_t errCode;
        std::string errString;
    };
}

#define ThrowOpenGLException(__errCode__) throw aengine::OpenGLException(__LINE__, __FILE__, __errCode__)

#endif
