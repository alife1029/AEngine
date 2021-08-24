#ifndef AE_SCENE_HPP
#define AE_SCENE_HPP

#include "AE_API.hpp"
#include <vector>

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

        // For editor
        void StartRenderers();
        void UpdateRenderers();
        const std::vector<Entity*>& Entities() const;
    private:
        std::vector<Entity*> mEntites;

    friend Entity;
    };
}

#endif
