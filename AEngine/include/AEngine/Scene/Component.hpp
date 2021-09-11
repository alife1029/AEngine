#ifndef AE_COMPONENT_HPP
#define AE_COMPONENT_HPP

#include "AE_API.hpp"
#include <typeinfo>
#include <string>
#include <imgui.h>
#include <yaml-cpp/yaml.h>

#define GETTYPE_DEC() virtual std::string GetType()
#define GETTYPE_IMP(__className__) std::string __className__::GetType() { return typeid(*this).name(); }
#define GET_CLASSNAME(__className__) typeid(__className__).name()

namespace aengine
{
    class Entity;
    class AE_API Component
    {
    public:
        virtual void Start();
        virtual void Update();
        virtual void Dispose();
        virtual void OnInspector();
        virtual void Serialize(YAML::Emitter& out);
        virtual void Deserialize(YAML::Node& node);
        GETTYPE_DEC();
    protected:
        Entity* mEntity;

    friend Entity;
    };
}

#endif
