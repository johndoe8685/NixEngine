#include "Application.h"

namespace NixEngine {
    Application::Application()
    {
        
    }
    void Application::Run()
    {
        float toRadians = 3.14159265358979323846f / 180.f;
        
        Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.2f);
        Window window(800, 600, &camera);

        ShaderManager& shaderManager = ShaderManager::Get();
        AssetManager& assetManager = AssetManager::Get();

        assetManager.AddScene("Default");
        shaderManager.AddShader("Basic", "/res/shader/basic.frag", "/res/shader/basic.vert");

        Shader* shader = shaderManager.getShader("Basic");
        Scene* scene = assetManager.GetScene("Default");

        assetManager.AddDirectionalLight("directionalLight", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(2.0f, -1.0f, -2.0f), 0.2f, 0.8f);
        assetManager.AddPointLight("blueLight", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, -3.0f), 0.0f, 1.0f);
        assetManager.AddPointLight("greenLight", glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, -3.0f), 0.0f, 1.0f);
        assetManager.AddPointLight("redLight", glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.732f), 0.0f, 1.0f);
        assetManager.AddSpotLight("flashLight", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), 0.0f, 1.0f, 30.0f);

        scene->AddModel("Floor", "/res/model/floor.obj");
        scene->AddModel("Dragon", "/res/model/dragon2.obj");
        
        DirectionalLight* directionalLight = assetManager.GetDirectionalLight("directionalLight");
        PointLight* blueLight = assetManager.GetPointLight("blueLight");
        PointLight* greenLight = assetManager.GetPointLight("greenLight");
        PointLight* redLight = assetManager.GetPointLight("redLight");
        SpotLight* flashLight = assetManager.GetSpotLight("flashLight");

        Material shinyMaterial(4.0f, 256);
        Material dullMaterial(1.0f, 4);

        Renderer renderer;
        
        DebugConsole debugconsole(&window);

        //Variables
        float curAngle = 0.0f;
        float speed = 0.0f;
        float deltaTime = 0.0f, curFrame = 0.0f, lastFrame = 0.0f;
        bool Useflash = true;

        //For Camera Perspective
        glm::mat4 projection(1.0f);

        //Get the first frame time
        lastFrame = glfwGetTime();

        while (!window.GetWindowShouldClose())
        {
            glfwPollEvents();

            //Set Model Variables
            Model* dragon = scene->getModel("Dragon");
            dragon->SetPosition(debugconsole.getX(), debugconsole.getY(), debugconsole.getZ());
            dragon->SetScale(0.25f, 0.25f, 0.25f);
            dragon->SetRotation(0.0f, curAngle, 0.0f);

            Model* floor = scene->getModel("Floor");
            floor->SetPosition(0.0f, -1.0f, 0.0f);

            //Get the deltaTime
            curFrame = glfwGetTime();
            deltaTime = curFrame - lastFrame;
            lastFrame = curFrame;

            camera.keyControl(window.getKeys(), deltaTime);
		    camera.mouseControl(window.getXChange(), window.getYChange());
            camera.setUniformCameraPosition(shader);

            //Rotate the triangle
            speed = debugconsole.getAngle() * toRadians * deltaTime;
            curAngle += speed;
            if (curAngle >= 360)
            {
                curAngle -= 360;
            }
            
            //Calculate fov
            if(window.getWidth() != 0 && window.getHeight() != 0) projection = glm::perspective(glm::radians(debugconsole.getFov()), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

            //Clear the screen
            //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            renderer.Clear();

            glm::vec3 hand = camera.getPosition();
            hand.y = hand.y - 0.3f;
            flashLight->setFlash(hand, camera.getDirection());

            //Use Light
            if (debugconsole.getUseFlash()) flashLight->UseLight();
            else flashLight->StopLight();
            blueLight->UseLight();
            redLight->UseLight();
            greenLight->UseLight();
            //directionalLight->UseLight();
            
            glm::mat4 model(1.0f);
            shader->SetUniformMatrix4fv("projection", projection);
            shader->SetUniformMatrix4fv("view", camera.calculateViewMatrix());

            //Draw Scene
            dullMaterial.useMaterial(shader, "material.specularIntensity", "material.shininess");
            renderer.DrawScene(scene, shader);

            debugconsole.Run();

            //Swap Buffers
            window.SwapBuffers();
        }

        glfwTerminate();
    }

    Application::~Application()
    {

    }
}
