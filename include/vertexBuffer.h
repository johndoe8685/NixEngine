#pragma once
#include <iostream>
#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer {
private:
    unsigned int m_ModuleID;
public:
    VertexBuffer(unsigned int size,const void* data, unsigned int mode);
    ~VertexBuffer();
};