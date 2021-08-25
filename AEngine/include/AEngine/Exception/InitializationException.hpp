#ifndef AE_INITIALIZATION_EXCEPTION_HPP
#define AE_INITIALIZATION_EXCEPTION_HPP

#include "Exception.hpp"

namespace aengine
{
    class AE_API InitializationException : public AEexception
    {
    public:
        InitializationException(int line, const char* file, const std::string& errDescription) noexcept;
        virtual const char* GetType() const noexcept;
        virtual std::string GetOriginString() const noexcept override;
    private:
        std::string errDescription;
    };
}

#define ThrowInitializationException(__description__) throw aengine::InitializationException(__LINE__, __FILE__, __description__)

#endif
