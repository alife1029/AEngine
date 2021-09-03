#ifndef AE_ENTITY_HPP
#define AE_ENTITY_HPP

#include "AE_API.hpp"
#include "Scene.hpp"
#include "Component.hpp"
#include "../Exception/Exception.hpp"

#include <string>
#include <vector>
#include <sstream>

namespace aengine
{
    class AE_API Entity
    {
    public:
        Entity(const std::string& tag = "Untagged");
        Entity(const Entity&) = default;

        void Start();
        void Update();
        void Dispose();
        void OnInspector();
        void Serialize();
        void Deserialize();

        template<typename T> T* GetComponent()
        {
            size_t componentCount = mComponents->size(); 
            for (size_t i = 0; i < componentCount; i++)
                if (mComponents->operator[](i)->GetType() == typeid(T).name())
                    return static_cast<T*>(mComponents->operator[](i));

            std::stringstream ss;
            ss  << "Component not found!" << std::endl
                << "[COMPONENT_CLASS]: " << typeid(T).name();
            
            ThrowAEexceptionWMSG(ss.str());
        }
        void AddComponent(Component* component);

        const std::string& Tag() const noexcept;
        void SetTag(const std::string& tag) noexcept;
        bool CompareTag(const Entity& entity) const noexcept;
        size_t ID() const;
        operator size_t() const;
    private:
        std::string mTag;
        std::vector<Component*>* mComponents;
        size_t mId;
    private:
        static size_t lastID;

        friend Scene;
    };
}

#endif
