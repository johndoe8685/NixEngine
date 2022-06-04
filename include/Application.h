#pragma once
#include "texture.h"
#include "window.h"
#include "vertexBuffer.h"
#include "vertexArray.h"
#include "vertexBufferLayout.h"
#include "shader.h"


namespace NixEngine {
    class Application
    {
    private:

    public:
        Application();
        ~Application();
        void Run();
    };
}
