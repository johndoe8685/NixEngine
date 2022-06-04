#include "Application.h"
#include "vertexBufferLayout.h"

namespace NixEngine {
    Application::Application()
    {
        
    }
    void Application::Run()
    {   
        Window window;
        float vertices[] =  {
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
             0.0f,  1.0f, 0.0f, 0.5f, 1.0f
        };
        VertexArray va;
        VertexBuffer vb(sizeof(vertices), vertices, GL_STATIC_DRAW);
        VertexBufferLayout layout;
        layout.AddLayout(VertexType::FLOAT, 3);
        layout.AddLayout(VertexType::FLOAT, 2);
        va.AddBuffer(vb, layout);
        Shader shader("/res/shader/basic.frag", "/res/shader/basic.vert");
        Texture hmmtexture("/res/texture/hmm.png");
        while (!window.GetWindowShouldClose())
        {
            glfwPollEvents();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.Bind();
            va.Bind();
            hmmtexture.Bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
            va.Unbind();
            shader.Unbind();
            
            window.SwapBuffers();
        }
        
    }

    Application::~Application()
    {

    }
}
