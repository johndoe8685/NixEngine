#include "Light/spotlight.h"

int SpotLight::m_SpotLightIndex = 0;

SpotLight::SpotLight(std::string componentName, glm::vec3 color, glm::vec3 position, glm::vec3 direction, float ambientIntensity, float diffuseIntensity, float edge, bool isSpot)
	:PointLight(componentName, color ,position, ambientIntensity, diffuseIntensity, false), m_direction(direction), m_edge(edge)
{
	m_direction = glm::normalize(direction);
	m_edge = cosf(glm::radians(edge));

	char Buffer[1024] = { "\0" };

	snprintf(Buffer, sizeof(Buffer), m_colorName, m_SpotLightIndex);
	m_colorNameResult = Buffer;
	snprintf(Buffer, sizeof(Buffer), m_ambientIntensityName, m_SpotLightIndex);
	m_ambientIntensityNameResult = Buffer;
	snprintf(Buffer, sizeof(Buffer), m_diffuseIntensityName, m_SpotLightIndex);
	m_diffuseIntensityNameResult = Buffer;
	snprintf(Buffer, sizeof(Buffer), m_positionName, m_SpotLightIndex);
	m_positionNameResult = Buffer;
	snprintf(Buffer, sizeof(Buffer), m_constantName, m_SpotLightIndex);
	m_constantNameResult = Buffer;
	snprintf(Buffer, sizeof(Buffer), m_linearName, m_SpotLightIndex);
	m_linearNameResult = Buffer;
	snprintf(Buffer, sizeof(Buffer), m_exponentName, m_SpotLightIndex);
	m_exponentNameResult = Buffer;
	snprintf(Buffer, sizeof(Buffer), m_directionName, m_SpotLightIndex);
	m_directionNameResult = Buffer;
	snprintf(Buffer, sizeof(Buffer), m_edgeName, m_SpotLightIndex);
	m_edgeNameResult = Buffer;

	if(isSpot)
	{
	m_SpotLightIndex++;
	m_spotSize = m_SpotLightIndex;
	}
}

void SpotLight::setFlash(glm::vec3 position, glm::vec3 direction)
{
	m_position = position;
	m_direction = direction;
}

void SpotLight::UseLight()
{
	shader->SetUniform3f(m_colorNameResult, m_color.x, m_color.y, m_color.z);
	shader->SetUniform1f(m_ambientIntensityNameResult, m_ambientIntensity);
	shader->SetUniform1f(m_diffuseIntensityNameResult, m_diffuseIntensity);

	shader->SetUniform3f(m_positionNameResult, m_position.x, m_position.y, m_position.z);
	shader->SetUniform1f(m_linearNameResult, m_linear);
	shader->SetUniform1f(m_constantNameResult, m_constant);
	shader->SetUniform1f(m_exponentNameResult, m_exponent);

	shader->SetUniform3f(m_directionNameResult, m_direction.x, m_direction.y, m_direction.z);
	shader->SetUniform1f(m_edgeNameResult, m_edge);
	shader->SetUniform1i(m_spotSizeNameResult, m_spotSize);
}

void SpotLight::StopLight()
{
	shader->SetUniform3f(m_colorNameResult, 0, 0, 0);
	shader->SetUniform1f(m_ambientIntensityNameResult, 0);
	shader->SetUniform1f(m_diffuseIntensityNameResult, 0);

	shader->SetUniform3f(m_positionNameResult, 0, 0, 0);
	shader->SetUniform1f(m_linearNameResult, 0);
	shader->SetUniform1f(m_constantNameResult, 0);
	shader->SetUniform1f(m_exponentNameResult, 0);

	shader->SetUniform3f(m_directionNameResult, 0, 0, 0);
	shader->SetUniform1f(m_edgeNameResult, 0);
	shader->SetUniform1i(m_spotSizeNameResult, 0);
}
