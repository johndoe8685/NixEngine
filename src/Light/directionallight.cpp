#include "Light/directionallight.h"

DirectionalLight::DirectionalLight(std::string componentName, glm::vec3 color, glm::vec3 direction , float ambientIntensity, float diffuseIntensity)
	:AmbientLight(componentName, color, ambientIntensity), m_direction(direction), m_diffuseIntensity(diffuseIntensity)
{
}

void DirectionalLight::UseLight()
{
    shader->SetUniform3f(m_colorName, m_color.x, m_color.y, m_color.z);
    shader->SetUniform1f(m_ambientIntensityName, m_ambientIntensity);

    shader->SetUniform3f(m_directionName, m_direction.x, m_direction.y, m_direction.z);
    shader->SetUniform1f(m_diffuseIntensityName, m_diffuseIntensity);
}

void DirectionalLight::StopLight()
{
	shader->SetUniform3f(m_colorName, 0, 0, 0);
	shader->SetUniform1f(m_ambientIntensityName, 0);

	shader->SetUniform3f(m_directionName, 0, 0, 0);
	shader->SetUniform1f(m_diffuseIntensityName, 0);
}
