#include "vertexBuffer.h"

VertexBuffer::VertexBuffer(unsigned int size,const void* data, unsigned int mode)
{
    glGenBuffers(1, &m_ModuleID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ModuleID);
    glBufferData(GL_ARRAY_BUFFER, size, data, mode);
}

VertexBuffer::~VertexBuffer() 
{
    glDeleteBuffers(1, &m_ModuleID);
}

