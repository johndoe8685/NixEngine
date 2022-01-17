#pragma once
#include <vector>
#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>

enum VertexType
{
    FLOAT, UINT, UCHAR
};

struct VertexBufferElement
{
    unsigned int type;
	unsigned int count;
	unsigned char normalized;
    
    static unsigned int GetSizeOfType(unsigned int Type)
	{
		switch (Type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
	}
};


class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    void AddLayout(enum VertexType type, unsigned int count);
	const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	unsigned int GetStride() const& { return m_Stride; }
};