#pragma once
#include <iostream>
#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "shader.h"
#include "indexBuffer.h"


class Renderer
{
private:
    unsigned int m_ModuleID;
public:
    Renderer();
    ~Renderer();
    void Draw(VertexArray& va, VertexBuffer& vb, Shader& shader) const;
    void Drawib(VertexArray& va, VertexBuffer& vb, IndexBuffer& ib, Shader& shader) const;
    void Clear() const;
};