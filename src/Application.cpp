#include "Application.h"
#include "renderer.h"
#include "vendor/glm/ext/matrix_float4x4.hpp"
#include "vendor/glm/ext/matrix_transform.hpp"
#include "vendor/imGui/imgui.h"
#include <cmath>


namespace NixEngine {
    Application::Application()
    {
        
    }
    void Application::Run()
    {   
        float toRadians = 3.14159265358979323846f / 180.f;
        float vertices[] =  {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.0f, -0.5f, 1.0f, 1.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.5f, 1.0f
        };
        unsigned int indices[] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
        };
        Window window;
        VertexArray va;
        VertexBuffer vb(sizeof(vertices), vertices, GL_STATIC_DRAW);
        IndexBuffer ib(indices, 12, GL_STATIC_DRAW);
        VertexBufferLayout layout;
        layout.AddLayout(VertexType::FLOAT, 3);
        layout.AddLayout(VertexType::FLOAT, 2);
        va.AddBuffer(vb, layout);
        Shader shader("/res/shader/basic.frag", "/res/shader/basic.vert");
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
        bool direction = true;
        float curAngle = 0.0f;
        float scale = 1.0f;
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        //For Camera Perspective
        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

        while (!window.GetWindowShouldClose())
        {
            glfwPollEvents();
            /*if(direction)
            {
                move += 0.005f;
            }
            else
            {
                move -= 0.005f;
            }
            if(abs(move) > 0.5f)
            {
                direction = !direction;
            }*/
            curAngle += 1.0f;
            if (curAngle >= 360)
            {
                curAngle -= 360;
            }
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            renderer.Clear();

            glm::mat4 model(1.0f);
            shader.Bind();
            model = glm::translate(model, glm::vec3(x, y, z));
            model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
            shader.SetUniformMatrix4fv("model", model);
            shader.SetUniformMatrix4fv("projection", projection);
            shader.Unbind();

            hmmtexture.Bind();
            renderer.Drawib(va, vb, ib, shader);

            //NixEngine Debug
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();     
            ImGui::Begin("Nix Engine Debug Console");                
            ImGui::Text("Nix Engine Debugging tool");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::Text("Positions of the object");
            ImGui::SliderFloat("X Position", &x, -1.0f, 1.0f);
            ImGui::SliderFloat("Y Position", &y, -1.0f, 1.0f);
            ImGui::SliderFloat("Z Position", &z, -2.5f, -5.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
            ImGui::End();
            if (show_another_window)
            {
                ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }
            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
