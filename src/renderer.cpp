#include "renderer.h"

Renderer::Renderer()
{
    shadermanager = ShaderManager::Get();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

Renderer::~Renderer()
{
    
}

void Renderer::DrawScene(Scene* scene)
{
    Shader* shader = shadermanager.getShader("Basic");
    scene->RenderScene(shader);
}

void Renderer::ProcessShadowMap()
{

}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}