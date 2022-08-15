#include "light.h"
#include "vendor/glm/fwd.hpp"


Light::Light()
:m_color(glm::vec3(1.0f, 1.0f, 1.0f)), m_ambientIntensity(0.5f), m_direction(glm::vec3(0.0f, -1.0f, 0.0f)), m_diffuseIntensity(1.0f)
{

}

Light::Light(float red, float green, float blue, float ambientIntensity, float x, float y, float z, float diffuseIntensity)
:m_color(glm::vec3(red, green, blue)), m_ambientIntensity(ambientIntensity), m_direction(glm::vec3(x, y, z)), m_diffuseIntensity(diffuseIntensity) 
{

}

void Light::useLight(Shader &shader, const std::string& ambientName, const std::string& ambientIntensityName, const std::string& diffuseName, const std::string& diffuseIntensityName)
{
    shader.SetUniform3f(ambientName, m_color.x, m_color.y, m_color.z);
    shader.SetUniform1f(ambientIntensityName, m_ambientIntensity);
    
    shader.SetUniform3f(diffuseName, m_direction.x, m_direction.y, m_direction.z);
    shader.SetUniform1f(diffuseIntensityName, m_diffuseIntensity);
}

void Light::setLight(float red, float green, float blue, float intensity)
{
    m_color = glm::vec3(red, green, blue);
    m_ambientIntensity = intensity;
}

void Light::calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}
	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

Light::~Light()
{

}