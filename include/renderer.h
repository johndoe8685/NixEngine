#pragma once
#include <iostream>
#include <vector>
#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "mesh.h"
#include "model.h"

class Renderer
{
private:

public:
    Renderer();
    ~Renderer();
    void DrawMesh(Mesh* mesh, Shader* shader);
    void DrawModel(Model* model, Shader* shader);
    void Clear();
};