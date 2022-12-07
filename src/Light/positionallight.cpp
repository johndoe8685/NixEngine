#include "Light/positionallight.h"

PositionalLight::PositionalLight(glm::vec3 color, glm::vec3 position, float ambientIntensity, float diffuseIntensity)
	:AmbientLight(color, ambientIntensity), m_position(position), m_diffuseIntensity(diffuseIntensity)
{
}
