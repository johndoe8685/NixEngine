#pragma once
#include <vector>
#include "texture.h"
#include "renderer.h"
#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "camera.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"
#include "vendor/imGui/imgui.h"
#include "vendor/imGui/imgui_impl_glfw.h"
#include "vendor/imGui/imgui_impl_opengl3.h"



namespace NixEngine {
    class Application
    {
    private:
        std::vector<Mesh*> m_meshList;
        std::vector<Shader*> m_shaderList;
    public:
        Application();
        ~Application();
        void Run();
    };
}
