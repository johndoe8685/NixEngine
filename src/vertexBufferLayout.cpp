#include "vertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
:m_Stride(0)
{

}

VertexBufferLayout::~VertexBufferLayout()
{

}

void VertexBufferLayout::AddLayout(enum VertexType type, unsigned int count)
{
    if (type == FLOAT)
    {
        m_Elements.push_back( {GL_FLOAT, count, GL_FALSE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
    }
    if (type == UINT)
    {
        m_Elements.push_back( {GL_UNSIGNED_INT, count, GL_FALSE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
    }
    if (type == UCHAR)
    {
        m_Elements.push_back( {GL_UNSIGNED_BYTE, count, GL_FALSE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
    }
}