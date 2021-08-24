#ifndef AE_EXCEPTION_HPP
#define AE_EXCEPTION_HPP

#include "AE_API.hpp"
#include <exception>
#include <string>

namespace aengine 
{
    class AE_API AEexception : public std::exception
    {
    public:
        AEexception(int line, const char* file) noexcept;
        AEexception(int line, const char* file, const std::string& message) noexcept;
        const char* what() const noexcept override;
        virtual const char* GetType() const noexcept;
        int GetLine() const noexcept;
        const std::string& GetFile() const noexcept;
        const std::string& GetMessage() const noexcept;
        virtual std::string GetOriginString() const noexcept;
    private:
        int line;
        std::string file;
        std::string message;
    protected:
        mutable std::string whatBuffer;
    };
}


// Useful macros
#define ThrowAEexception() throw aengine::AEexception(__LINE__, __FILE__)
#define ThrowAEexceptionWMSG(__msg__) throw aengine::AEexception(__LINE__, __FILE__, __msg__)

#endif
