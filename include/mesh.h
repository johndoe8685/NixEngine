#pragma once
#include <iostream>
#include <vector>
#include <vendor/glad/glad.h>
#include <vendor/glm/glm.hpp>
#include <GLFW/glfw3.h>

struct Vertex
{
    glm::vec3 Position;
    glm::vec2 TexCoord;
    glm::vec3 Normal;
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

class Mesh
{
private:
    unsigned int m_Stride;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int IBO;
    unsigned int indexCount;
    std::vector<VertexBufferElement> m_Elements;
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<unsigned int> m_Layouts;
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    ~Mesh();
    void setupMesh();
    void RenderMesh();
    void ClearMesh();
};