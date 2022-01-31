#pragma once
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"

class VertexArray
{
private:
    unsigned int m_ModuleID;
public:
    VertexArray();
    ~VertexArray() { glDeleteVertexArrays(1, &m_ModuleID); }

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const { glBindVertexArray(m_ModuleID); }
	void Unbind() const { glBindVertexArray(0); }
};
