#pragma once
#include <iostream>
#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "mesh.h"
#include "model.h"

class Renderer
{
private:
    unsigned int m_ModuleID;
public:
    Renderer();
    ~Renderer();
    void DrawMesh(Mesh* mesh, Shader* shader) const;
    void DrawModel(Model* model, Shader* shader) const;
    void Clear() const;
};