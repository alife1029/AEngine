#include "AEngine/Scene/SceneManager.hpp"

namespace aengine
{
    Scene* SceneManager::mActiveScene = new Scene();

    Scene* SceneManager::ActiveScene()
    {
        return mActiveScene;
    }

    void SceneManager::LoadScene(const std::string& sceneFile)
    {
        mActiveScene->Dispose();
        mActiveScene->Deserialize(sceneFile);
        mActiveScene->Start();
    }
}
