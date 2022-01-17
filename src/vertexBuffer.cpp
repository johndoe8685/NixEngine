#include "vertexBuffer.h"

VertexBuffer::VertexBuffer(unsigned int size,const void* data, unsigned int mode)
{
    glGenBuffers(1, &m_ModuleID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ModuleID);
    glBufferData(GL_ARRAY_BUFFER, size, data, mode);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ModuleID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() 
{
    glDeleteBuffers(1, &m_ModuleID);
}

