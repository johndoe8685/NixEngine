#include "light.h"

int Light::m_PointLightIndex = 0;
int Light::m_SpotLightIndex = 0;
int	Light::m_CurrentPointSize = 0;
int Light::m_CurrentSpotSize = 0;

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
		struct ambientUniformList list;
		shader.SetUniform3f(list.m_colorName, m_color.x, m_color.y, m_color.z);
    	shader.SetUniform1f(list.m_ambientIntensityName, ambient.m_ambientIntensity);
	}
	else if(light == LightType::directionalLight)
	{
		struct directionalUniformList list;
		shader.SetUniform3f(list.m_colorName, m_color.x, m_color.y, m_color.z);
    	shader.SetUniform1f(list.m_ambientIntensityName, directional.m_ambientIntensity);
    
    	shader.SetUniform3f(list.m_directionName, directional.m_direction.x, directional.m_direction.y, directional.m_direction.z);
    	shader.SetUniform1f(list.m_diffuseIntensityName, directional.m_diffuseIntensity);
	}
	else if (light == LightType::pointLight)
	{
		shader.SetUniform3f(pointList.m_colorName, m_color.x, m_color.y, m_color.z);
		shader.SetUniform1f(pointList.m_ambientIntensityName, point.directional.m_ambientIntensity);
		shader.SetUniform1f(pointList.m_diffuseIntensityName, point.directional.m_diffuseIntensity);

		shader.SetUniform3f(pointList.m_positionName, point.m_position.x, point.m_position.y, point.m_position.z);
		shader.SetUniform1f(pointList.m_linearName, point.m_linear);
		shader.SetUniform1f(pointList.m_constantName, point.m_constant);
		shader.SetUniform1f(pointList.m_exponentName, point.m_exponent);
		
		shader.SetUniform1i(pointList.m_pointSizeName, point.m_pointSize);

		shader.SetPointLightInUse(1);
		shader.SetUniform1i(pointList.m_inUseName, shader.GetPointLightInUse());
	}
	else if (light == LightType::spotLight)
	{
		shader.SetUniform3f(spotList.m_colorName, m_color.x, m_color.y, m_color.z);
		shader.SetUniform1f(spotList.m_ambientIntensityName, spot.point.directional.m_ambientIntensity);
		shader.SetUniform1f(spotList.m_diffuseIntensityName, spot.point.directional.m_diffuseIntensity);

		shader.SetUniform3f(spotList.m_positionName, spot.point.m_position.x, spot.point.m_position.y, spot.point.m_position.z);
		shader.SetUniform1f(spotList.m_linearName, spot.point.m_linear);
		shader.SetUniform1f(spotList.m_constantName, spot.point.m_constant);
		shader.SetUniform1f(spotList.m_exponentName, spot.point.m_exponent);

		shader.SetUniform3f(spotList.m_directionName, spot.m_direction.x, spot.m_direction.y, spot.m_direction.z);
		shader.SetUniform1f(spotList.m_edgeName, spot.m_edge);
		shader.SetUniform1i(spotList.m_spotSizeName, spot.m_spotSize);
	}
	else if (light == LightType::flashLight)
	{
		struct FlashUniformList list;
		shader.SetUniform3f(list.m_colorName, m_color.x, m_color.y, m_color.z);
		shader.SetUniform1f(list.m_ambientIntensityName, flash.spot.point.directional.m_ambientIntensity);
		shader.SetUniform1f(list.m_diffuseIntensityName, flash.spot.point.directional.m_diffuseIntensity);

		shader.SetUniform3f(list.m_positionName, flash.spot.point.m_position.x, flash.spot.point.m_position.y, flash.spot.point.m_position.z);
		shader.SetUniform1f(list.m_linearName, flash.spot.point.m_linear);
		shader.SetUniform1f(list.m_constantName, flash.spot.point.m_constant);
		shader.SetUniform1f(list.m_exponentName, flash.spot.point.m_exponent);

		shader.SetUniform3f(list.m_directionName, flash.spot.m_direction.x, flash.spot.m_direction.y, flash.spot.m_direction.z);
		shader.SetUniform1f(list.m_edgeName, flash.spot.m_edge);
	}
}

void Light::stopLight(Shader& shader)
{
	if (light == LightType::ambientLight)
	{
		struct ambientUniformList list;
		shader.SetUniform3f(list.m_colorName, 0, 0, 0);
		shader.SetUniform1f(list.m_ambientIntensityName, 0);
	}
	else if (light == LightType::directionalLight)
	{
		struct directionalUniformList list;
		shader.SetUniform3f(list.m_colorName, 0, 0, 0);
		shader.SetUniform1f(list.m_ambientIntensityName, 0);

		shader.SetUniform3f(list.m_directionName, 0, 0, 0);
		shader.SetUniform1f(list.m_diffuseIntensityName, 0);
	}
	else if (light == LightType::pointLight)
	{
		shader.SetUniform3f(pointList.m_colorName, 0, 0, 0);
		shader.SetUniform1f(pointList.m_ambientIntensityName, 0);
		shader.SetUniform1f(pointList.m_diffuseIntensityName, 0);

		shader.SetUniform3f(pointList.m_positionName, 0, 0, 0);
		shader.SetUniform1f(pointList.m_linearName, 0);
		shader.SetUniform1f(pointList.m_constantName, 0);
		shader.SetUniform1f(pointList.m_exponentName, 0);

		shader.SetUniform1i(pointList.m_pointSizeName, 0);

		shader.SetUniform1i(pointList.m_inUseName, 0);
	}
	else if (light == LightType::spotLight)
	{
		shader.SetUniform3f(spotList.m_colorName, 0, 0, 0);
		shader.SetUniform1f(spotList.m_ambientIntensityName, 0);
		shader.SetUniform1f(spotList.m_diffuseIntensityName, 0);

		shader.SetUniform3f(spotList.m_positionName, 0, 0, 0);
		shader.SetUniform1f(spotList.m_linearName, 0);
		shader.SetUniform1f(spotList.m_constantName, 0);
		shader.SetUniform1f(spotList.m_exponentName, 0);

		shader.SetUniform3f(spotList.m_directionName, 0, 0, 0);
		shader.SetUniform1f(spotList.m_edgeName, 0);
		shader.SetUniform1i(spotList.m_spotSizeName, 0);
	}
	else if (light == LightType::flashLight)
	{
		struct FlashUniformList list;
		shader.SetUniform3f(list.m_colorName, 0, 0, 0);
		shader.SetUniform1f(list.m_ambientIntensityName, 0);
		shader.SetUniform1f(list.m_diffuseIntensityName, 0);

		shader.SetUniform3f(list.m_positionName, 0, 0, 0);
		shader.SetUniform1f(list.m_linearName, 0);
		shader.SetUniform1f(list.m_constantName, 0);
		shader.SetUniform1f(list.m_exponentName, 0);

		shader.SetUniform3f(list.m_directionName, 0, 0, 0);
		shader.SetUniform1f(list.m_edgeName, 0);
	}
}

void Light::setAsAmbientLight(float ambientIntensity)
{
    ambient.m_ambientIntensity = ambientIntensity;
	light = LightType::ambientLight;
}
void Light::setAsDirectionalLight(float ambientIntensity, float diffuseIntensity, float x, float y, float z)
{
	directional.m_ambientIntensity = ambientIntensity;
	directional.m_diffuseIntensity = diffuseIntensity;
	directional.m_direction = glm::vec3(x, y, z);
	light = LightType::directionalLight;
}
void Light::setAsPointLight(float ambientIntensity, float diffuseIntensity, float x, float y, float z, float constant, float linear, float exponent)
{
	if (m_PointLightIndex > MAX_POINT_LIGHT) std::cerr << "[ERROR] Maximum point lights already initialized" << std::endl;
	else
	{
		point.directional.m_ambientIntensity = ambientIntensity;
		point.directional.m_diffuseIntensity = diffuseIntensity;
		point.m_position = glm::vec3(x,y,z);
		point.m_constant = constant;
		point.m_linear = linear;
		point.m_exponent = exponent;
		point.m_inUse = 0;
		
		char Buffer[1024] = { "\0" };

		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_colorName, m_PointLightIndex);
		pointList.m_colorName = Buffer;
		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_ambientIntensityName, m_PointLightIndex);
		pointList.m_ambientIntensityName = Buffer;
		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_diffuseIntensityName, m_PointLightIndex);
		pointList.m_diffuseIntensityName = Buffer;
		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_positionName, m_PointLightIndex);
		pointList.m_positionName = Buffer;
		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_constantName, m_PointLightIndex);
		pointList.m_constantName = Buffer;
		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_linearName, m_PointLightIndex);
		pointList.m_linearName = Buffer;
		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_exponentName, m_PointLightIndex);
		pointList.m_exponentName = Buffer;
		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_inUseName, m_PointLightIndex);
		pointList.m_inUseName = Buffer;

		light = LightType::pointLight;
		m_PointLightIndex++;
		point.m_pointSize = m_PointLightIndex;
	}
}

void Light::setAsSpotLight(float ambientIntensity, float diffuseIntensity, float x, float y, float z, float constant, float linear, float exponent, glm::vec3 direction, float edge)
{
	if (m_SpotLightIndex > MAX_SPOT_LIGHT) std::cerr << "[ERROR] Maximum spot lights already initialized" << std::endl;
	else
	{
		spot.point.directional.m_ambientIntensity = ambientIntensity;
		spot.point.directional.m_diffuseIntensity = diffuseIntensity;
		spot.point.m_position = glm::vec3(x, y, z);
		spot.point.m_constant = constant;
		spot.point.m_linear = linear;
		spot.point.m_exponent = exponent;
		spot.m_direction = glm::normalize(direction);
		spot.m_edge = cosf(glm::radians(edge));

		char Buffer[1024] = { "\0" };

		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_colorName, m_SpotLightIndex);
		spotList.m_colorName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_ambientIntensityName, m_SpotLightIndex);
		spotList.m_ambientIntensityName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_diffuseIntensityName, m_SpotLightIndex);
		spotList.m_diffuseIntensityName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_positionName, m_SpotLightIndex);
		spotList.m_positionName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_constantName, m_SpotLightIndex);
		spotList.m_constantName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_linearName, m_SpotLightIndex);
		spotList.m_linearName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_exponentName, m_SpotLightIndex);
		spotList.m_exponentName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_directionName, m_SpotLightIndex);
		spotList.m_directionName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_edgeName, m_SpotLightIndex);
		spotList.m_edgeName = Buffer;
		
		light = LightType::spotLight;
		m_SpotLightIndex++;
		spot.m_spotSize = m_SpotLightIndex;
	}
}
//Implement This Later
void Light::setAsFlashLight(float ambientIntensity, float diffuseIntensity, float x, float y, float z, float constant, float linear, float exponent, glm::vec3 direction, float edge)
{
	spot.point.directional.m_ambientIntensity = ambientIntensity;
	spot.point.directional.m_diffuseIntensity = diffuseIntensity;
	spot.point.m_position = glm::vec3(x, y, z);
	spot.point.m_constant = constant;
	spot.point.m_linear = linear;
	spot.point.m_exponent = exponent;
	spot.m_direction = glm::normalize(direction);
	spot.m_edge = cosf(glm::radians(edge));

	char Buffer[1024] = { "\0" };

	snprintf(Buffer, sizeof(Buffer), spotArrayList.m_colorName, m_SpotLightIndex);
	spotList.m_colorName = Buffer;
	snprintf(Buffer, sizeof(Buffer), spotArrayList.m_ambientIntensityName, m_SpotLightIndex);
	spotList.m_ambientIntensityName = Buffer;
	snprintf(Buffer, sizeof(Buffer), spotArrayList.m_diffuseIntensityName, m_SpotLightIndex);
	spotList.m_diffuseIntensityName = Buffer;
	snprintf(Buffer, sizeof(Buffer), spotArrayList.m_positionName, m_SpotLightIndex);
	spotList.m_positionName = Buffer;
	snprintf(Buffer, sizeof(Buffer), spotArrayList.m_constantName, m_SpotLightIndex);
	spotList.m_constantName = Buffer;
	snprintf(Buffer, sizeof(Buffer), spotArrayList.m_linearName, m_SpotLightIndex);
	spotList.m_linearName = Buffer;
	snprintf(Buffer, sizeof(Buffer), spotArrayList.m_exponentName, m_SpotLightIndex);
	spotList.m_exponentName = Buffer;
	snprintf(Buffer, sizeof(Buffer), spotArrayList.m_directionName, m_SpotLightIndex);
	spotList.m_directionName = Buffer;
	snprintf(Buffer, sizeof(Buffer), spotArrayList.m_edgeName, m_SpotLightIndex);
	spotList.m_edgeName = Buffer;

	light = LightType::flashLight;
}

void Light::setMovingLight(glm::vec3 position, glm::vec3 direction)
{
	if (LightType::spotLight) spot.setFlash(position, direction);
	else if (LightType::flashLight) flash.spot.setFlash(position, direction);
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