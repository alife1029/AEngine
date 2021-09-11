#ifndef AE_SCENE_MANAGER_HPP
#define AE_SCENE_MANAGER_HPP

#include "AE_API.hpp"
#include "Scene.hpp"

namespace aengine
{
    class AE_API SceneManager
    {
    public:
        static void LoadScene(const std::string& sceneFile);
        static Scene* ActiveScene();
    private:
        static Scene* mActiveScene;
    };
}

#endif
