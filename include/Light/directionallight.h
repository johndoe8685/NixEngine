#pragma once
#include "Light/light.h"

class DirectionalLight : public Light
{
private:
    glm::vec3 m_direction;
    float m_diffuseIntensity;
    float m_ambientIntensity;

    const char* m_colorName = "directionalLight.diffuse.ambient.base.color";
    const char* m_ambientIntensityName = "directionalLight.diffuse.ambient.ambientIntensity";
    const char* m_diffuseIntensityName = "directionalLight.diffuse.diffuseIntensity";
    const char* m_directionName = "directionalLight.direction";
public:
    DirectionalLight(float x, float y, float z, float ambientIntensity, float diffuseIntensity);
};