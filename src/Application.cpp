#include "Application.h"

namespace NixEngine {
    Application::Application()
    {
        
    }
    void Application::Run()
    {
        float toRadians = 3.14159265358979323846f / 180.f;

        Window window(800, 600);

        ShaderManager& shaderManager = ShaderManager::Get();
        AssetManager& assetManager = AssetManager::Get();

        assetManager.AddScene("Default");
        shaderManager.AddShader("Basic", "/res/shader/basic.frag", "/res/shader/basic.vert");
        shaderManager.AddShader("Shadow", "/res/shader/shadow_map.frag", "/res/shader/shadow_map.vert");
        shaderManager.AddShader("DepthDebug", "/res/shader/debug_quad.frag", "/res/shader/debug_quad.vert");
        
        Shader* shader = shaderManager.getShader("Basic");
        Shader* shadow_shader = shaderManager.getShader("Shadow");
        Scene* scene = assetManager.GetScene("Default");
        
        assetManager.AddDirectionalLight("directionalLight", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(2.0f, -1.0f, 2.0f), 0.2f, 0.8f);
        assetManager.AddPointLight("blueLight", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, -3.0f), 0.0f, 1.0f);
        assetManager.AddPointLight("greenLight", glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, -3.0f), 0.0f, 1.0f);
        assetManager.AddPointLight("redLight", glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.732f), 0.0f, 1.0f);
        assetManager.AddSpotLight("flashLight", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), 0.0f, 1.0f, 30.0f);

        scene->AddCamera("Default", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.2f);
        scene->AddModel("Error", "/res/model/error.obj");
        scene->AddModel("Floor", "/res/model/floor.obj");
        scene->AddModel("Dragon", "/res/model/dragon.obj");
        scene->AddModel("Baba", "/res/model/backpack.obj");
        scene->AddSkybox("Blue", "Blue");

        Camera* camera = scene->getCamera("Default");
        window.SetCamera(camera);

        DirectionalLight* directionalLight = assetManager.GetDirectionalLight("directionalLight");
        PointLight* blueLight = assetManager.GetPointLight("blueLight");
        PointLight* greenLight = assetManager.GetPointLight("greenLight");
        PointLight* redLight = assetManager.GetPointLight("redLight");
        SpotLight* flashLight = assetManager.GetSpotLight("flashLight");

        Material shinyMaterial(4.0f, 256);
        Material dullMaterial(1.0f, 4);

        Renderer renderer(&window);
        
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

        //Set Model Variables staticly
        Model* floor = scene->getModel("Floor");
        floor->SetPosition(0.0f, -1.0f, 0.0f);

        Model* baba = scene->getModel("Baba");
        baba->SetPosition(5.0f, 0.0f, 0.0f);
        baba->SetScale(0.25f, 0.25f, 0.25f);

        while (!window.GetWindowShouldClose())
        {
            glfwPollEvents();

            directionalLight->SetDirection(glm::vec3(debugconsole.m_dx, debugconsole.m_dy, debugconsole.m_dz));

            //Set Model Variables
            Model* dragon = scene->getModel("Dragon");
            dragon->SetPosition(debugconsole.getX(), debugconsole.getY(), debugconsole.getZ());
            dragon->SetScale(0.25f, 0.25f, 0.25f);
            dragon->SetRotation(0.0f, curAngle, 0.0f);

            //Get the deltaTime
            curFrame = glfwGetTime();
            deltaTime = curFrame - lastFrame;
            lastFrame = curFrame;

            camera->keyControl(window.getKeys(), deltaTime);
		    camera->mouseControl(window.getXChange(), window.getYChange());
            camera->setUniformCameraPosition(shader);

            //Rotate the triangle
            speed = debugconsole.getAngle() * toRadians * deltaTime;
            curAngle += speed;
            if (curAngle >= 360)
            {
                curAngle -= 360;
            }

            //Calculate fov
            if(window.getWidth() != 0 && window.getHeight() != 0) projection = glm::perspective(glm::radians(debugconsole.getFov()), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.0f);

            //Clear the screen
            renderer.Clear();

            glm::vec3 hand = camera->getPosition();
            hand.y = hand.y - 0.3f;
            flashLight->setFlash(hand, camera->getDirection());

            //Use Light
            if (debugconsole.m_Useflash) flashLight->UseLight();
            else flashLight->StopLight();
            if (debugconsole.m_UseDirectional) 
            {
                directionalLight->UseLight();
                blueLight->StopLight();
                redLight->StopLight();
                greenLight->StopLight();
            }
            else 
            {
                directionalLight->StopLight();
                blueLight->UseLight();
                redLight->UseLight();
                greenLight->UseLight();
            }
            
            glm::mat4 view = camera->calculateViewMatrix();
            shader->SetUniformMatrix4fv("projection", projection);
            shader->SetUniformMatrix4fv("view", view);

            //Draw Scene
            dullMaterial.useMaterial(shader, "material.specularIntensity", "material.shininess");
            //renderer.DepthDebug(scene);
            renderer.DrawScene(scene, camera->calculateViewMatrix(), projection);

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
