#include "directionallight.h"

DirectionalLight::DirectionalLight(float x, float y, float z, float ambientIntensity, float diffuseIntensity)
	:m_direction(x, y, z), m_ambientIntensity(ambientIntensity), m_diffuseIntensity(diffuseIntensity)
{
}
