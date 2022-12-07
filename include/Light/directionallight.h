#pragma once
#include "Light/ambientlight.h"

class DirectionalLight : public AmbientLight
{
private:
    std::string m_colorName = "directionalLight.diffuse.ambient.base.color";
    std::string m_ambientIntensityName = "directionalLight.diffuse.ambient.ambientIntensity";
    std::string m_diffuseIntensityName = "directionalLight.diffuse.diffuseIntensity";
    std::string m_directionName = "directionalLight.direction";
public:
    glm::vec3 m_direction;
    float m_diffuseIntensity;

    DirectionalLight(glm::vec3 color, glm::vec3 direction, float ambientIntensity, float diffuseIntensity);
    void UseLight();
    void StopLight();
};