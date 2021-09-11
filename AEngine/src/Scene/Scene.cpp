#include "AEngine/Scene/Scene.hpp"
#include "AEngine/Scene/Entity.hpp"
#include "AEngine/Scene/Components/Transform.hpp"
#include "AEngine/Scene/Components/SpriteRenderer.hpp"
#include "AEngine/Graphics/Renderer2D.hpp"
#include "AEngine/Utils/Logger.hpp"
#include "AEngine/Utils/Parse.hpp"
#include "AEngine/Scene/SceneManager.hpp"
#include <glm/glm.hpp>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iomanip>

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
                entity->Dispose();
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
        mEntities.clear();
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
        ofs << out.c_str() << std::endl;
        ofs.close();
    }

    void Scene::Deserialize(const std::string& file)
    {
        YAML::Node map = YAML::LoadFile(file);
        YAML::Node& entities = map["Entities"];
        for (YAML::iterator entNode = entities.begin(); entNode != entities.end(); ++entNode)
        {
            std::string key = entNode->first.as<std::string>();
            YAML::Node& val = entNode->second;
            YAML::Node& components = val["Components"];

            // For conerting string to int
            std::stringstream ss(key);

            // Create entity
            Entity* newEntity = new Entity();
            newEntity->mTag = val["Tag"].as<std::string>();
            ss >> newEntity->mId;
            ss >> newEntity->lastID;

            // Deserialize components
            for (YAML::iterator compNode = components.begin(); compNode != components.end(); ++compNode)
            {
                std::string componentName = compNode->first.as<std::string>();
                YAML::Node& componentVal = compNode->second;

                // Transform Component
                if (componentName == GET_CLASSNAME(Transform)) 
                {
                    YAML::Node& posNode = componentVal["Position"];
                    YAML::Node& scaleNode = componentVal["Scale"];
                    YAML::Node& rotNode = componentVal["Rotation"];

                    // Create Component
                    Transform* comp = new Transform();
                    comp->Position = {
                        ParseNumber<float>(posNode[0].as<std::string>()),
                        ParseNumber<float>(posNode[1].as<std::string>()),
                        ParseNumber<float>(posNode[2].as<std::string>())
                    };
                    comp->Scale = {
                        ParseNumber<float>(scaleNode[0].as<std::string>()),
                        ParseNumber<float>(scaleNode[1].as<std::string>()),
                        ParseNumber<float>(scaleNode[2].as<std::string>())
                    };
                    comp->Rotation = ParseNumber<float>(rotNode.as<std::string>());

                    newEntity->AddComponent(comp);
                }

                // Sprite Renderer Component
                else if (componentName == GET_CLASSNAME(SpriteRenderer))
                {
                    YAML::Node& colorNode = componentVal["Color"];

                    SpriteRenderer* comp = new SpriteRenderer();
                    comp->Color = {
                        ParseNumber<float>(colorNode[0].as<std::string>()),
                        ParseNumber<float>(colorNode[1].as<std::string>()),
                        ParseNumber<float>(colorNode[2].as<std::string>()),
                        ParseNumber<float>(colorNode[3].as<std::string>())
                    };

                    newEntity->AddComponent(comp);
                }
            }

            mEntities.push_back(newEntity);
        }
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
