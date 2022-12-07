#include "Light/ambientlight.h"

AmbientLight::AmbientLight(glm::vec3 color, float ambientIntensity)
	:Light(color), m_ambientIntensity(ambientIntensity)
{
}

void AmbientLight::UseLight()
{
	shader->SetUniform3f(m_colorName, m_color.x, m_color.y, m_color.z);
	shader->SetUniform1f(m_ambientIntensityName, m_ambientIntensity);
}

void AmbientLight::StopLight()
{
	shader->SetUniform3f(m_colorName, 0, 0, 0);
	shader->SetUniform1f(m_ambientIntensityName, 0);
}
