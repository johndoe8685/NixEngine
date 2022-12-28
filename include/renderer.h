#pragma once
#include <iostream>
#include <vector>
#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "scene.h"
#include "mesh.h"
#include "model.h"


class Renderer
{
private:
    ShaderManager shadermanager;
public:
    Renderer();
    ~Renderer();
    void DrawScene(Scene* scene);
    void ProcessShadowMap();
    void Clear();
};