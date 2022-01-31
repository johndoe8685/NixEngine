#include "indexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count, unsigned int mode)
{
    glGenBuffers(1, &m_ModuleID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ModuleID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, mode);
}
IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_ModuleID);
}