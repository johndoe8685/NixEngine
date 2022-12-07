#include "Light/positionallight.h"

PositionalLight::PositionalLight(std::string componentName, glm::vec3 color, glm::vec3 position, float ambientIntensity, float diffuseIntensity)
	:AmbientLight(componentName, color, ambientIntensity), m_position(position), m_diffuseIntensity(diffuseIntensity)
{
}
