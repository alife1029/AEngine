#include "AEngine/Scene/Scene.hpp"
#include "AEngine/Scene/Entity.hpp"
#include "AEngine/Scene/Components/Transform.hpp"
#include "AEngine/Scene/Components/SpriteRenderer.hpp"
#include "AEngine/Graphics/Renderer2D.hpp"
#include <glm/glm.hpp>

namespace aengine
{
    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    }

    Entity* Scene::CreateEntity() noexcept
    {
        Entity* newEnt = new Entity();
        newEnt->AddComponent(new Transform());
        mEntites.push_back(newEnt);
        return newEnt;
    }

    // TODO: Delete entity
    void Scene::DeleteEntity(Entity* entity) noexcept
    {
    }

    void Scene::DeleteEntity(int index) noexcept
    {
    }

    void Scene::Start()
    {
        for (auto entity : mEntites)
            entity->Start();
    }

    void Scene::Update()
    {
        for (auto entity : mEntites)
            entity->Update();
    }

    void Scene::Dispose()
    {
        for (auto entity : mEntites)
            entity->Dispose();
        Entity::lastID = 0;
    }

    void Scene::StartRenderers()
    {
        for (auto entity : mEntites)
        {
            entity->GetComponent<Transform>()->Start();
            entity->GetComponent<SpriteRenderer>()->Start();
        }
    }

    void Scene::UpdateRenderers()
    {
        for (auto entity : mEntites)
        {
            entity->GetComponent<Transform>()->Update();
            entity->GetComponent<SpriteRenderer>()->Update();
        }
    }

    const std::vector<Entity*>& Scene::Entities() const { return mEntites; }
}
