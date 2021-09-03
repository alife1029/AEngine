#ifndef AE_SCENE_HPP
#define AE_SCENE_HPP

#include "AE_API.hpp"
#include <vector>
#include <string>

namespace aengine
{
    class Entity;
    class AE_API Scene
    {
    public:
        Scene();
        ~Scene();
        Entity* CreateEntity() noexcept;
        void DeleteEntity(Entity* entity) noexcept;
        void DeleteEntity(int index) noexcept;

        // Lifecycle methods
        void Start();
        void Update();
        void Dispose();
        void OnInspector();

        // Serialization methods
        void Serialize(const std::string& file);
        void Deserialize();

        // For editor
        void StartRenderers();
        void UpdateRenderers();
        const std::vector<Entity*>& Entities() const;
    private:
        std::vector<Entity*> mEntities;

    friend Entity;
    };
}

#endif
