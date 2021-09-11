#include "AEngine/Scene/Component.hpp"

namespace aengine
{
    void Component::Start() { }
    void Component::Update() { }
    void Component::Dispose() { }
    void Component::OnInspector() { }
    void Component::Serialize(YAML::Emitter& out) { }
    void Component::Deserialize(YAML::Node& node) { }
    GETTYPE_IMP(Component)
}
