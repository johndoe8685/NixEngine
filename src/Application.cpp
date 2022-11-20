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
        flashLight.setAsSpotLight(0.0f, 0.5f, 0.0f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, glm::vec3(-1.0f, 0.0f, 0.0f), 30.0f);

        Material shinyMaterial(4.0f, 256);
        Material dullMaterial(1.0f, 4);
        
        Model floor("/res/model/floor.obj");
        Model backpack("/res/model/backpack.obj");

        Shader *shader = new Shader("/res/shader/basic.frag", "/res/shader/basic.vert");
        m_shaderList.push_back(shader);

        Renderer renderer;

        //ImGui Stuff
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window.getGLFWwindow(), true);
        ImGui_ImplOpenGL3_Init("#version 330 core");

        //Variables
        float x = 0.0f;
        float y = 0.0f;
        float z = -2.5f;
        float fov = 90.0f;
        bool direction = true;
        float curAngle = 0.0f, angle = 80.0f;
        float speed = 0.0f;
        float deltaTime = 0.0f, curFrame = 0.0f, lastFrame = 0.0f;
        float red = 0.0f, green = 0.0f, blue = 0.0f;
        bool Useflash = true;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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
            speed = angle * toRadians * deltaTime;
            curAngle += speed;
            if (curAngle >= 360)
            {
                curAngle -= 360;
            }
            
            //Calculate fov
            projection = glm::perspective(glm::radians(fov), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

            //Clear the screen
            //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            renderer.Clear();

            glm::vec3 hand = camera.getPosition();
            hand.y = hand.y - 0.3f;
            flashLight.setMovingLight(hand, camera.getDirection());

            //Use Light
            if (Useflash) flashLight.useLight(*m_shaderList[0]);
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
            shinyMaterial.useMaterial(*m_shaderList[0], "material.specularIntensity", "material.shininess");
            renderer.DrawModel(&floor, m_shaderList[0]);

            //Draw Backpack
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(x, y, z));
            model = glm::rotate(model, curAngle, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
            m_shaderList[0]->SetUniformMatrix4fv("model", model);
            shinyMaterial.useMaterial(*m_shaderList[0], "material.specularIntensity", "material.shininess");
            renderer.DrawModel(&backpack, m_shaderList[0]);

            //NixEngine Debug
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGui::Begin("Nix Engine Debug Console");                
            ImGui::Text("Nix Engine Debugging tool");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("[DeltaTime] %.6f", deltaTime);
            ImGui::Text("Positions of the object");
            ImGui::SliderFloat("X Position", &x, -1.0f, 1.0f);
            ImGui::SliderFloat("Y Position", &y, -1.0f, 1.0f);
            ImGui::SliderFloat("Z Position", &z, -2.5f, -5.0f);
            ImGui::SliderFloat("Speed", &angle, 0.0f, 360.0f);
            ImGui::SliderFloat("FOV", &fov, 5.0f, 120.0f);
            ImGui::Checkbox("FlashLight", &Useflash);
            ImGui::End();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            //Swap Buffers
            window.SwapBuffers();
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwTerminate();
    }

    Application::~Application()
    {

    }

    
}
