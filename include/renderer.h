#pragma once
#include <iostream>
#include <vector>
#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>
#include "shadermanager.h"
#include "assetmanager.h"
#include "window.h"

class Renderer
{
private:
    ShaderManager shadermanager;
    AssetManager assetmanager;
    Window* m_window;
    unsigned int quadVAO;
    unsigned int quadVBO;
    
    int m_shadowMapSize;
public:
    Renderer(Window* window);
    ~Renderer();
    void DrawScene(Scene* scene, glm::mat4 view, glm::mat4 projection);
    void ProcessShadowMap(Scene* scene);
    void Clear();

    void DepthDebug(Scene* scene);
    void renderQuad();

    void GetDefaultFrameBuffer();
};