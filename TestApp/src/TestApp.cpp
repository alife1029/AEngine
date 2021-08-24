#include <AEngine.hpp>

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <vector>

using namespace aengine;

// AEngine app instance
class TestApp : public Application
{
private:
    Scene* mActiveScene;

    Viewport* viewport;
    OrthographicCamera* camera;

    const AppConfig& cfg;

    float cameraSpeed = 1.0f;
    float cameraRotSpeed = 31.31f;
    float rotation = 0.0f;
    float rotationSpeed = 35.0f;
    Texture2D *dollarTex, *grassTex, *dirtTex;
    std::vector<Texture2D*> characterTextures;
    int currentFrame = 0;
    float frameDuration = 0.15f;
    float nextFrame;

    Entity* character;
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

        dollarTex = new Texture2D("Assets/dollar.png");
        grassTex = new Texture2D("Assets/grass.png", 128);
        dirtTex = new Texture2D("Assets/dirt.png", 128);

        characterTextures = {
            new Texture2D("Assets/Adventurer/idle0.png"),
            new Texture2D("Assets/Adventurer/idle1.png"),
            new Texture2D("Assets/Adventurer/idle2.png"),
            new Texture2D("Assets/Adventurer/idle3.png")
        };

        mActiveScene = new Scene();

        character =  mActiveScene->CreateEntity();
        SpriteRenderer* characterSpriteRenderer = new SpriteRenderer();
        characterSpriteRenderer->Texture = characterTextures[0];
        characterSpriteRenderer->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
        character->AddComponent(characterSpriteRenderer);

        nextFrame = frameDuration;

        mActiveScene->Start();
    }
    
    // Update calls once per frame
    void Update()
    {
        // Moving camera
        float currCmrSpeed = cameraSpeed * (float)Time::DeltaTime();
        float currCmrRotSpeed = cameraRotSpeed * (float)Time::DeltaTime();

        if (Input::IsKeyPressing(Key::A))
            camera->Translate(-currCmrSpeed, 0.0f);
        if (Input::IsKeyPressing(Key::D))
            camera->Translate(currCmrSpeed, 0.0f);
        if (Input::IsKeyPressing(Key::W))
            camera->Translate(0.0f, currCmrSpeed);
        if (Input::IsKeyPressing(Key::S))
            camera->Translate(0.0f, -currCmrSpeed);
        if (Input::IsKeyPressing(Key::Q))
            camera->Rotate(currCmrRotSpeed);
        if (Input::IsKeyPressing(Key::E))
            camera->Rotate(-currCmrRotSpeed);

        camera->Update();
        Renderer2D::Begin(camera->Combined());

        float scale = 0.4f;
        int counter = 0;
        float width = 8.0f;
        float height = 8.0f;
        for (float i = -width; i <= width + scale; i += scale)
        {
            for (float j = -height; j <= height + scale; j += scale)
            {
                if (counter % 2)
                    Renderer2D::DrawQuad(grassTex, { j, i, 0.0f }, { scale, scale, 0.0f });
                else 
                    Renderer2D::DrawQuad(dirtTex, { j, i, 0.0f }, { scale, scale, 0.0f });

                ++counter;
            }
        }

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

        mActiveScene->Update();

        Renderer2D::End();
        Renderer2D::Flush();

        //printf("FPS: %d  (%d ms)\n", (int)(1.0 / Time::DeltaTime()), (int)(Time::DeltaTime() * 1000.0));
    }

    void Dispose()
    {
        mActiveScene->Dispose();
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
