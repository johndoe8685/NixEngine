#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	:m_Vertices(vertices), m_Indices(indices), m_Stride(0)
{
	m_Layouts.push_back({ 3 });
	m_Layouts.push_back({ 2 });
	m_Layouts.push_back({ 3 });

	setupMesh();
}

void Mesh::setupMesh()
{
	//Creating Buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);
	glBindVertexArray(VAO);

	//Load data into Vertex Buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);
	

	//Load data into Index Buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_Indices.size(), &m_Indices[0], GL_STATIC_DRAW);
	

	//Creating Vertex Buffer Layout
	//Layout only accepts float type
	for (int i = 0; i < m_Layouts.size(); i++)
	{
		m_Elements.push_back({ GL_FLOAT, m_Layouts[i], GL_FALSE});
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * m_Layouts[i];
	}
	//Adding Vertex Buffer and layout to the Vertex Array
	const auto& elements = m_Elements;
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glVertexAttribPointer(i, element.count, element.type, element.normalized, m_Stride, (const void*)offset);
		glEnableVertexAttribArray(i);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void Mesh::RenderMesh()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_Indices.size()), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::ClearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}

Mesh::~Mesh()
{
	ClearMesh();
}