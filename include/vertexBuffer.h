#pragma once
#include <iostream>
#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer {
private:
    unsigned int m_ModuleID;
public:
    VertexBuffer(unsigned int size,const void* data, unsigned int mode);
    ~VertexBuffer() { glDeleteBuffers(1, &m_ModuleID); }

    void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_ModuleID); }
    void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
};