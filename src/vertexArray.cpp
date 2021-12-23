#include "vertexArray.h"

VertexArray::VertexArray() 
{
    glGenVertexArrays(1, &m_ModuleID);
    glBindVertexArray(m_ModuleID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_ModuleID);
}

