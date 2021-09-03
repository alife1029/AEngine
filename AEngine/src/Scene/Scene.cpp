#include "AEngine/Scene/Scene.hpp"
#include "AEngine/Scene/Entity.hpp"
#include "AEngine/Scene/Components/Transform.hpp"
#include "AEngine/Scene/Components/SpriteRenderer.hpp"
#include "AEngine/Graphics/Renderer2D.hpp"
#include <glm/glm.hpp>
#include <yaml-cpp/yaml.h>
#include <fstream>

// Linking yaml-cpp
#ifdef _DEBUG
    #ifdef AE_64BIT
        #pragma comment(lib, "yaml-cppd-x64.lib")
    #elif defined(AE_32BIT)
        #pragma comment(lib, "yaml-cppd-x86.lib")
    #else
        #error Unsupported CPU architecture
    #endif
#else
    #ifdef AE_64BIT
        #pragma comment(lib, "yaml-cpp-x64.lib")
    #elif defined(AE_32BIT)
        #pragma comment(lib, "yaml-cpp-x86.lib")
    #else
        #error Unsupported CPU architecture
    #endif
#endif

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
        mEntities.push_back(newEnt);
        return newEnt;
    }

    void Scene::DeleteEntity(Entity* entity) noexcept
    {
        size_t entityCount = mEntities.size();

        for (size_t i = 0; i < entityCount; i++)
        {
            if (mEntities[i] == entity)
            {
                mEntities.erase(mEntities.begin() + i);
                delete entity;
                return;
            }
        }
    }

    void Scene::DeleteEntity(int index) noexcept
    {
        Entity* entity = mEntities[index];
        mEntities.erase(mEntities.begin() + index);
        delete entity;
    }

    void Scene::Start()
    {
        for (auto entity : mEntities)
            entity->Start();
    }

    void Scene::Update()
    {
        for (auto entity : mEntities)
            entity->Update();
    }

    void Scene::Dispose()
    {
        for (auto entity : mEntities)
        {
            entity->Dispose();
            delete entity;
        }
        Entity::lastID = 0;
    }

    void Scene::OnInspector()
    {
        for (auto entity : mEntities)
            entity->OnInspector();
    }

    void Scene::Serialize(const std::string& file)
    {
        YAML::Emitter out;

        out << YAML::BeginMap 
            << YAML::Key << "Entities" 
                << YAML::Value << YAML::BeginMap;

        for (auto entity : mEntities)
            entity->Serialize(out);

        out << YAML::EndMap << YAML::EndMap;

        std::ofstream ofs(file);
        ofs << out.c_str();
        ofs.close();
    }

    void Scene::Deserialize()
    {
        for (auto entity : mEntities)
            entity->Deserialize();
    }

    void Scene::StartRenderers()
    {
        for (auto entity : mEntities)
        {
            entity->GetComponent<Transform>()->Start();
            entity->GetComponent<SpriteRenderer>()->Start();
        }
    }

    void Scene::UpdateRenderers()
    {
        for (auto entity : mEntities)
        {
            entity->GetComponent<Transform>()->Update();
            entity->GetComponent<SpriteRenderer>()->Update();
        }
    }

    const std::vector<Entity*>& Scene::Entities() const { return mEntities; }
}
