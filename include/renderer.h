#pragma once
#include <iostream>
#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "mesh.h"


class Renderer
{
private:
    unsigned int m_ModuleID;
public:
    Renderer();
    ~Renderer();
    void Draw(Mesh* mesh, Shader* shader) const;
    void Clear() const;
};