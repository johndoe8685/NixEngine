#pragma once
#include "Light/light.h"

class AmbientLight : public Light
{
private:
	std::string m_colorName = "ambientLight.base.color";
	std::string m_ambientIntensityName = "ambientLight.ambientIntensity";
public:
	float m_ambientIntensity;

	AmbientLight(glm::vec3 color, float ambientIntensity);
	void UseLight();
	void StopLight();
};