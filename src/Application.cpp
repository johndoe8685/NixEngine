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
        
        Light directionalLight = Light(1.0f, 1.0f, 1.0f);
        Light blueLight = Light(0.0f, 0.0f, 1.0f);
        Light greenLight = Light(0.0f, 1.0f, 0.0f);
        Light redLight = Light(1.0f, 0.0f, 0.0f);
        Light flashLight = Light(1.0f, 1.0f, 1.0f);
        
        directionalLight.setAsDirectionalLight(0.2f, 0.8f, 2.0f, -1.0f, -2.0f);
        blueLight.setAsPointLight(0.0f, 1.0f, -1.0f, 0.0f, -3.0f, 0.3f, 0.2f, 0.1f);
        greenLight.setAsPointLight(0.0f, 1.0f, 1.0f, 0.0f, -3.0f, 0.3f, 0.2f, 0.1f);
        redLight.setAsPointLight(0.0f, 0.5f, 0.0f, 0.0f, -1.732f, 0.3f, 0.2f, 0.1f);

        Material shinyMaterial(4.0f, 256);
        Material dullMaterial(1.0f, 4);
        
        Model floor("/res/model/floor.obj");
        Model backpack("/res/model/backpack.obj");
        Model dragon("/res/model/dragon2.obj");

        Shader *shader = new Shader("/res/shader/basic.frag", "/res/shader/basic.vert");
        m_shaderList.push_back(shader);

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

            //Get the deltaTime
            curFrame = glfwGetTime();
            deltaTime = curFrame - lastFrame;
            lastFrame = curFrame;

            camera.keyControl(window.getKeys(), deltaTime);
		    camera.mouseControl(window.getXChange(), window.getYChange());
            camera.setUniformCameraPosition(*m_shaderList[0]);

            //Rotate the triangle
            speed = debugconsole.getAngle() * toRadians * deltaTime;
            curAngle += speed;
            if (curAngle >= 360)
            {
                curAngle -= 360;
            }
            
            //Calculate fov
            projection = glm::perspective(glm::radians(debugconsole.getFov()), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

            //Clear the screen
            //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            renderer.Clear();

            glm::vec3 hand = camera.getPosition();
            hand.y = hand.y - 0.3f;
            flashLight.setMovingLight(hand, camera.getDirection());

            //Use Light
            if (debugconsole.getUseFlash()) flashLight.useLight(*m_shaderList[0]);
            else flashLight.stopLight(*m_shaderList[0]);
            blueLight.useLight(*m_shaderList[0]);
            greenLight.useLight(*m_shaderList[0]);
            redLight.useLight(*m_shaderList[0]);
            //directionalLight.useLight(*m_shaderList[0]);
            
            glm::mat4 model(1.0f);
            m_shaderList[0]->SetUniformMatrix4fv("projection", projection);
            m_shaderList[0]->SetUniformMatrix4fv("view", camera.calculateViewMatrix());
            
            //Draw Floor
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
            m_shaderList[0]->SetUniformMatrix4fv("model", model);
            dullMaterial.useMaterial(*m_shaderList[0], "material.specularIntensity", "material.shininess");
            renderer.DrawModel(&floor, m_shaderList[0]);

            //Draw Backpack
            model = glm::mat4(1.0f);
            model = glm::rotate(model, curAngle, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
            m_shaderList[0]->SetUniformMatrix4fv("model", model);
            shinyMaterial.useMaterial(*m_shaderList[0], "material.specularIntensity", "material.shininess");
            //renderer.DrawModel(&backpack, m_shaderList[0]);

            //Draw Dragon
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(debugconsole.getX(), debugconsole.getY(), debugconsole.getZ()));
            model = glm::rotate(model, curAngle, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
            m_shaderList[0]->SetUniformMatrix4fv("model", model);
            shinyMaterial.useMaterial(*m_shaderList[0], "material.specularIntensity", "material.shininess");
            renderer.DrawModel(&dragon, m_shaderList[0]);

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
