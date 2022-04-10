#include <AEngine.hpp>

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <vector>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "Scripts/CameraController.hpp"

using namespace aengine;

// AEngine app instance
class TestApp : public Application
{
private:
    Scene* mActiveScene;

    Viewport* viewport;
    OrthographicCamera* camera;

    const AppConfig& cfg;

    float rotation = 0.0f;
    float rotationSpeed = 35.0f;
    Texture2D *dollarTex, *grassTex, *dirtTex;
    std::vector<Texture2D*> characterTextures;
    int currentFrame = 0;
    float frameDuration = 0.15f;
    float nextFrame;

    Entity *character, *cameraController;

    FontFamily* fontFamily;
    FontManager* fontManager;
public:
    // Constructor for pass config object to base class
    TestApp(const AppConfig& config) 
        : Application(config), cfg(config) { }

    // Start calls once before first frame 
    void Start()
    {
        std::cout << "Start!" << std::endl;

        viewport = new Viewport(cfg.scrWidth, cfg.scrHeight, Viewport::Type::Fill);
        camera = new OrthographicCamera(viewport, 2.0f);

        BindMainCamera(camera);

        dollarTex = new Texture2D("Assets/dollar.png");
        grassTex = new Texture2D("Assets/grass.png", 128);
        dirtTex = new Texture2D("Assets/dirt.png", 128);

        characterTextures = {
            new Texture2D("Assets/Adventurer/idle0.png"),
            new Texture2D("Assets/Adventurer/idle1.png"),
            new Texture2D("Assets/Adventurer/idle2.png"),
            new Texture2D("Assets/Adventurer/idle3.png")
        };

        fontManager = new FontManager();
        fontFamily = fontManager->LoadFont("Assets/Righteous.ttf");

        // Set static rendering data
        Renderer2DStatic::Begin();
        float scale = 0.4f;
        int counter = 0;
        float width = 8.0f;
        float height = 8.0f;
        for (float i = -width; i <= width + scale; i += scale)
        {
            for (float j = -height; j <= height + scale; j += scale)
            {
                if (counter % 2)
                    Renderer2DStatic::AddQuad(grassTex, { j, i, 0.0f }, { scale, scale, 0.0f });
                else 
                    Renderer2DStatic::AddQuad(dirtTex, { j, i, 0.0f }, { scale, scale, 0.0f });

                ++counter;
            }
        }
        Renderer2DStatic::End();

        mActiveScene = new Scene();

        character =  mActiveScene->CreateEntity();
        SpriteRenderer* characterSpriteRenderer = new SpriteRenderer();
        characterSpriteRenderer->Texture = characterTextures[0];
        characterSpriteRenderer->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
        character->AddComponent(characterSpriteRenderer);

        cameraController = mActiveScene->CreateEntity();
        CameraController* comp = new CameraController();
        comp->camera = camera;
        cameraController->AddComponent(comp);

        nextFrame = frameDuration;

        mActiveScene->Start();
    }
    
    // Update calls once per frame
    void Update()
    {
        Renderer2D::DrawQuad(dollarTex, { -0.85f, 0.85f, 0.0f }, { 0.2f, 0.2f, 0.0f });

        rotation += rotationSpeed * Time::DeltaTimeF();
        nextFrame -= Time::DeltaTimeF();
        if (nextFrame <= 0.0f)
        {
            if (currentFrame < 3) ++currentFrame;
            else currentFrame = 0;
            nextFrame = frameDuration;
            character->GetComponent<SpriteRenderer>()->Texture = characterTextures[currentFrame];
        }

        TextRenderer::SetRenderingFont(fontFamily);
        TextRenderer::RenderText("Hello World", 50.0f, 50.0f, 1.0f, { 0.1f, 0.1f, 0.1f, 1.0f });
        TextRenderer::RenderText("Lorem ipsum dolor sit amet.", 50.0f, 150.0f, 0.5f, { 0.1f, 0.1f, 0.1f, 1.0f });

        mActiveScene->Update();
    }

    void Dispose()
    {
        mActiveScene->Dispose();
        delete mActiveScene;
    }

    void OnResize(int width, int height)
    {
        Application::OnResize(width, height);
        viewport->Update(width, height);
    }
};

// C++ entry point
CPP_ENTRY_POINT
{
    try 
    {
        // Create app config object
        AppConfig appCfg = AppConfig();
        appCfg.vSync = true;
        // Create AEngine application instance and pass app config
        Application* game = new TestApp(appCfg);

        // Run application
        game->Run();
        // Clear game data
        delete game;
        // Close app with success value
        return 0;
    }
    catch(const std::exception& ex)
    {
        std::ofstream ofs("Error.log", std::ios::app);

        if (ofs.is_open())
        {
            // Print error details to log file
            time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::string currentTimeStr = std::string(ctime(&currentTime));
            ofs << "[" << currentTimeStr.substr(0, currentTimeStr.size() - 1) << "]" << std::endl
                << ex.what() << "\n\n" << std::endl;
        }

        ofs.close();

        // Close app with fail value
        return -1;
    }
}
