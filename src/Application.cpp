#include "Application.h"
#include "light.h"
#include "material.h"

namespace NixEngine {
    Application::Application()
    {
        
    }
    void Application::Run()
    {       
        float toRadians = 3.14159265358979323846f / 180.f;
        float vertices[] =  {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
             0.0f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
             0.0f,  0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f
        };
        unsigned int indices[] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
        };
        unsigned int layouts[] = { 3, 2, 3 };
        
        Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.2f);
        Window window(800, 600, &camera);
        
        Light mainLight = Light(1.0f, 1.0f, 1.0f, 0.2f, 2.0f, -1.0f, -2.0f, 0.8f);
        Material shinyMaterial(1.0f, 32);
        Material dullMaterial(1.0f, 4);
        mainLight.calcAverageNormals(indices, 12, vertices, 32, 8, 5);
        
        Mesh *obj1 = new Mesh(vertices, indices, layouts, 32, 12, 3);
        m_meshList.push_back(obj1);
        Shader *shader = new Shader("/res/shader/basic.frag", "/res/shader/basic.vert");
        m_shaderList.push_back(shader);

        Mesh *obj2 = new Mesh(vertices, indices, layouts, 32, 12, 3);
        m_meshList.push_back(obj2);

        Renderer renderer;
        Texture hmmtexture("/res/texture/hmm.png");
        
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
        float curAngle = 0.0f, angle = 10.0f;
        float speed = 0.0f;
        float deltaTime = 0.0f, curFrame = 0.0f, lastFrame = 0.0f;
        float red = 0.0f, green = 0.0f, blue = 0.0f;
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

            //Do math calculations on mesh
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(x, y, z));
            model = glm::rotate(model, curAngle, glm::vec3(0.0f, 1.0f, 0.0f));
            m_shaderList[0]->SetUniformMatrix4fv("model", model);
            m_shaderList[0]->SetUniformMatrix4fv("projection", projection);
            m_shaderList[0]->SetUniformMatrix4fv("view", camera.calculateViewMatrix());

            //Bind the texture
            hmmtexture.Bind();

            //Use Light 
            mainLight.useLight(*m_shaderList[0], "directionalLight.color", "directionalLight.ambientIntensity", "directionalLight.direction", "directionalLight.diffuseIntensity");
            dullMaterial.useMaterial(*m_shaderList[0], "material.specularIntensity", "material.shininess");

            //Draw the mesh
            renderer.Draw(m_meshList[0], m_shaderList[0]);

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
