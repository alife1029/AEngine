#include "AEngine/Exception/OpenGLException.hpp"

#include <sstream>
#include <glad/glad.h>

namespace aengine
{
    OpenGLException::OpenGLException(int line, const char* file, uint32_t errCode) noexcept
        : AEexception(line, file), errCode(errCode) 
    {
        switch(errCode)
        {
        case 1280:  errString = "GL_INVALID_ENUM (0x0500)"; break;
        case 1281:  errString = "GL_INVALID_VALUE (0x0501)"; break;
        case 1282:  errString = "GL_INVALID_OPERATION (0x0502)"; break;
        case 1283:  errString = "GL_STACK_OVERFLOW (0x0503)"; break;
        case 1284:  errString = "GL_STACK_UNDERFLOW (0x0504)"; break;
        case 1285:  errString = "GL_OUT_OF_MEMORY (0x0505)"; break;
        case 1286:  errString = "GL_INVALID_FRAMEBUFFER_OPERATION (0x0506)"; break;
        default:    errString = "UNKNOWN_ERROR_CODE"; break;
        };
    }

    const char* OpenGLException::GetType() const noexcept
    {
        return "AEngine OpenGL Graphics Exception";
    }

    std::string OpenGLException::GetOriginString() const noexcept
    {
        std::ostringstream oss;
        oss << AEexception::GetOriginString() << std::endl
            << "[ERROR_CODE] " << errString;
        return oss.str();
    }
}
