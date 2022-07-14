#pragma once
#include <iostream>
#include <vector>
#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>

class Mesh
{

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

private:
    unsigned int m_ModuleID;
    unsigned int m_Stride;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int IBO;
    unsigned int indexCount;
    std::vector<VertexBufferElement> m_Elements;
public:
    Mesh(float *vertices, unsigned int *indices, unsigned int *layouts, unsigned int numOfVertices, unsigned int numOfIndices, unsigned int numOfLayouts);
    ~Mesh();
    void RenderMesh();
    void ClearMesh();
};