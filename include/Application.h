#pragma once
#include <vector>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"
#include "vendor/imGui/imgui.h"
#include "vendor/imGui/imgui_impl_glfw.h"
#include "vendor/imGui/imgui_impl_opengl3.h"
#include "shader.h"
#include "texture.h"
#include "renderer.h"
#include "window.h"
#include "mesh.h"
#include "camera.h"
#include "Light/light.h"
#include "Light/ambientlight.h"
#include "Light/directionallight.h"
#include "Light/pointlight.h"
#include "Light/spotlight.h"
#include "material.h"
#include "model.h"
#include "debugger.h"
#include "debugconsole.h"
#include "shadermanager.h"
#include "assetmanager.h"
#include "framebuffer.h"
#include "shadowmap.h"

namespace NixEngine {
    class Application
    {
    private:
        std::vector<Shader*> m_shaderList;
        std::vector<Material*> m_materialList;
        std::vector<Model*> m_modelList;

    public:
        Application();
        ~Application();
        void Run();
    };
}
