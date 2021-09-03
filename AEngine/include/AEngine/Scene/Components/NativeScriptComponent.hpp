#ifndef AE_NATIVE_CPP_SCRIPT_COMPONENT_HPP
#define AE_NATIVE_CPP_SCRIPT_COMPONENT_HPP

#include "AE_API.hpp"
#include "../Component.hpp"

namespace aengine
{
    class AE_API NativeScript : public Component
    {
    public:
        virtual void Start() override;
        virtual void Update() override;
        virtual void Dispose() override;
        GETTYPE_DEC();

        /*
        TODO: Implement those methods
        virtual void OnInspector();
        virtual void OnSerialize();
        */
    };
}

#endif
