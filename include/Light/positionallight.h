#pragma once
#include "Light/ambientlight.h"

class PositionalLight : public AmbientLight
{
public:
	glm::vec3 m_position;
	float m_diffuseIntensity;
	PositionalLight(glm::vec3 color, glm::vec3 position, float ambientIntensity, float diffuseIntensity);
};