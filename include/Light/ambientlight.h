#pragma once
#include "light.h"

class AmbientLight : public Light
{
private:
	float m_ambientIntensity;

	const char* m_colorName = "ambientLight.base.color";
	const char* m_ambientIntensityName = "ambientLight.ambientIntensity";
public:
	AmbientLight(float ambientIntensity);
};