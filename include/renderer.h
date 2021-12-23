#pragma once
#include <iostream>
#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer
{
private:
    unsigned int m_ModuleID;
public:
    Renderer();
    ~Renderer();
};