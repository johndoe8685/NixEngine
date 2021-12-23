#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer {
private:
    unsigned int m_ModuleID;
public:
    VertexBuffer();
    ~VertexBuffer();
};