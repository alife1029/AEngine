#ifndef AE_COMPONENT_HPP
#define AE_COMPONENT_HPP

#include "AE_API.hpp"
#include <typeinfo>
#include <string>

#define GETTYPE_DEC() virtual std::string GetType()
#define GETTYPE_IMP(__className__) std::string __className__::GetType() { return typeid(*this).name(); }

namespace aengine
{
    class Entity;
    class AE_API Component
    {
    public:
        virtual void Start();
        virtual void Update();
        virtual void Dispose();
        GETTYPE_DEC();
    protected:
        Entity* mEntity;

    friend Entity;
    };
}

#endif
