#include "renderer.h"

Renderer::Renderer() 
{
    glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
    
}

void Renderer::Draw(VertexArray& va, VertexBuffer& vb, Shader& shader) const
{
    va.Bind();
    shader.Bind();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    va.Unbind();
    shader.Unbind();
}

void Renderer::Drawib(VertexArray& va, VertexBuffer& vb, IndexBuffer& ib, Shader& shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    va.Unbind();
    ib.Unbind();
    shader.Unbind();
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}