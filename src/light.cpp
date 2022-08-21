#include "light.h"


Light::Light()
:m_color(glm::vec3(1.0f, 1.0f, 1.0f))
{
	
}

Light::Light(float red, float green, float blue)
:m_color(glm::vec3(red, green, blue))
{

}

void Light::useLight(Shader &shader)
{
	if (light == LightType::ambientLight)
	{
		shader.SetUniform3f(ambient.m_ambientName, m_color.x, m_color.y, m_color.z);
    	shader.SetUniform1f(ambient.m_ambientIntensityName, ambient.m_ambientIntensity);
	}
	else if(light == LightType::directionalLight)
	{
		shader.SetUniform3f(directional.ambient.m_ambientName, m_color.x, m_color.y, m_color.z);
    	shader.SetUniform1f(directional.ambient.m_ambientIntensityName, directional.ambient.m_ambientIntensity);
    
    	shader.SetUniform3f(directional.m_diffuseName, directional.m_direction.x, directional.m_direction.y, directional.m_direction.z);
    	shader.SetUniform1f(directional.m_diffuseIntensityName, directional.m_diffuseIntensity);
	}
	else if (light == LightType::pointLight)
	{
		shader.SetUniform3f(point.directional.ambient.m_ambientName, m_color.x, m_color.y, m_color.z);
		shader.SetUniform1f(point.directional.ambient.m_ambientIntensityName, point.directional.ambient.m_ambientIntensity);
		shader.SetUniform1f(point.directional.m_diffuseIntensityName, point.directional.m_diffuseIntensity);

		shader.SetUniform3f(point.m_pointName, point.m_position.x, point.m_position.y, point.m_position.z);
		shader.SetUniform1f(point.m_linearName, point.m_linear);
		shader.SetUniform1f(point.m_constantName, point.m_constant);
		shader.SetUniform1f(point.m_exponentName, point.m_exponent);
	}
}
void Light::setAsAmbientLight(float ambientIntensity, const std::string& ambientName, const std::string& ambientIntensityName)
{
    ambient.m_ambientIntensity = ambientIntensity;
	ambient.m_ambientName = ambientName;
	ambient.m_ambientIntensityName = ambientIntensityName;
	light = LightType::ambientLight;
}
void Light::setAsDirectionalLight(float ambientIntensity, float x, float y, float z, float diffuseIntensity, const std::string& ambientName, const std::string& ambientIntensityName, const std::string& diffuseName, const std::string& diffuseIntensityName)
{
	directional.ambient.m_ambientIntensity = ambientIntensity;
	directional.ambient.m_ambientName = ambientName;
	directional.ambient.m_ambientIntensityName = ambientIntensityName;
	directional.m_diffuseIntensity = diffuseIntensity;
	directional.m_direction = glm::vec3(x,y,z);
	directional.m_diffuseName = diffuseName;
	directional.m_diffuseIntensityName = diffuseIntensityName;
	light = LightType::directionalLight;
}
void Light::setAsPointLight(float x, float y, float z, float constant, float linear, float exponent, float ambientIntensity, float diffuseIntensity, const std::string& ambientName, const std::string& ambientIntensityName, const std::string& diffuseName, const std::string& diffuseIntensityName, const std::string& pointPositionName, const std::string& pointConstantName, const std::string& pointLinearName, const std::string& pointExponentName)
{
	point.directional.ambient.m_ambientIntensity = ambientIntensity;
	point.directional.ambient.m_ambientName = ambientName;
	point.directional.ambient.m_ambientIntensityName = ambientIntensityName;
	point.directional.m_diffuseIntensity = diffuseIntensity;
	point.directional.m_diffuseName = diffuseName;
	point.directional.m_diffuseIntensityName = diffuseIntensityName;
	point.m_position = glm::vec3(x,y,z);
	point.m_pointName = pointPositionName;
	point.m_constant = constant;
	point.m_linear = linear;
	point.m_exponent = exponent;
	light = LightType::pointLight;
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