#include "AEngine/Scene/Entity.hpp"

namespace aengine
{
    size_t Entity::lastID = 0;

    Entity::Entity(const std::string& tag)
        : mTag(tag) 
    {
        mId = lastID++;
        mComponents = new std::vector<Component*>();
    }

    // Lifecycle methods
    void Entity::Start() 
    { 
        size_t componentCount = mComponents->size();
        for (size_t i = 0; i < componentCount; i++) {
            mComponents->operator[](i)->Start();
        }
    }
    void Entity::Update() 
    { 
        size_t componentCount = mComponents->size();
        for (size_t i = 0; i < componentCount; i++)
            mComponents->operator[](i)->Update();
    }
    void Entity::Dispose() 
    {
        size_t componentCount = mComponents->size();
        for (size_t i = 0; i < componentCount; i++)
            mComponents->operator[](i)->Dispose();
    }

    void Entity::AddComponent(Component* component)
    {
        component->mEntity = this;
        mComponents->push_back(component);
    }

    const std::string& Entity::Tag() const noexcept
    {
        return mTag;
    }
    void Entity::SetTag(const std::string& tag) noexcept
    {
        mTag = tag;
    }
    bool Entity::CompareTag(const Entity& entity) const noexcept
    {
        return mTag == entity.mTag;
    }

    size_t Entity::ID() const { return mId; }
    Entity::operator size_t() const { return mId; }
}
