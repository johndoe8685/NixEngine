#include "renderer.h"

Renderer::Renderer() 
{
    glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
    
}

void Renderer::DrawMesh(Mesh* mesh, Shader* shader) const
{
    shader->Bind();
    mesh->RenderMesh();
    shader->SetPointLightInUse(0);
    shader->Unbind();
}

void Renderer::DrawModel(Model* model, Shader* shader) const
{
    shader->Bind();
    model->RenderModel();
    shader->SetPointLightInUse(0);
    shader->Unbind();
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}