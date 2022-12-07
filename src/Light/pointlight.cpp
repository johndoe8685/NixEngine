#include "Light/pointlight.h"

int PointLight::m_PointLightIndex = 0;
int PointLight::m_pointSize = 0;

PointLight::PointLight(std::string componentName, glm::vec3 color, glm::vec3 position, float ambientIntensity, float diffuseIntensity, bool isPoint)
	:PositionalLight(componentName, color, position, ambientIntensity, diffuseIntensity), m_constant(0.3f), m_linear(0.2f), m_exponent(0.1f), m_inUse(false)
{
	char Buffer[1024] = { "\0" };

	snprintf(Buffer, sizeof(Buffer), m_colorName, m_PointLightIndex);
	m_colorNameResult = Buffer;
	snprintf(Buffer, sizeof(Buffer), m_ambientIntensityName, m_PointLightIndex);
	m_ambientIntensityNameResult = Buffer;
	snprintf(Buffer, sizeof(Buffer), m_diffuseIntensityName, m_PointLightIndex);
	m_diffuseIntensityNameResult = Buffer;
	snprintf(Buffer, sizeof(Buffer), m_positionName, m_PointLightIndex);
	m_positionNameResult = Buffer;
	snprintf(Buffer, sizeof(Buffer), m_constantName, m_PointLightIndex);
	m_constantNameResult = Buffer;
	snprintf(Buffer, sizeof(Buffer), m_linearName, m_PointLightIndex);
	m_linearNameResult = Buffer;
	snprintf(Buffer, sizeof(Buffer), m_exponentName, m_PointLightIndex);
	m_exponentNameResult = Buffer;
	snprintf(Buffer, sizeof(Buffer), m_inUseName, m_PointLightIndex);
	m_inUseNameResult = Buffer;

	if (isPoint)
	{
		m_PointLightIndex++;
		m_pointSize = m_PointLightIndex;
	}
}

void PointLight::UseLight()
{
	shader->SetUniform3f(m_colorNameResult, m_color.x, m_color.y, m_color.z);
	shader->SetUniform1f(m_ambientIntensityNameResult, m_ambientIntensity);
	shader->SetUniform1f(m_diffuseIntensityNameResult, m_diffuseIntensity);

	shader->SetUniform3f(m_positionNameResult, m_position.x, m_position.y, m_position.z);
	shader->SetUniform1f(m_linearNameResult, m_linear);
	shader->SetUniform1f(m_constantNameResult, m_constant);
	shader->SetUniform1f(m_exponentNameResult, m_exponent);

	shader->SetUniform1i(m_pointSizeNameResult, m_pointSize);

	shader->SetUniform1i(m_inUseNameResult, true);
}

void PointLight::StopLight()
{
	shader->SetUniform3f(m_colorNameResult, 0, 0, 0);
	shader->SetUniform1f(m_ambientIntensityNameResult, 0);
	shader->SetUniform1f(m_diffuseIntensityNameResult, 0);

	shader->SetUniform3f(m_positionNameResult, 0, 0, 0);
	shader->SetUniform1f(m_linearNameResult, 0);
	shader->SetUniform1f(m_constantNameResult, 0);
	shader->SetUniform1f(m_exponentNameResult, 0);

	shader->SetUniform1i(m_pointSizeNameResult, 0);

	shader->SetUniform1i(m_inUseNameResult, false);
}
