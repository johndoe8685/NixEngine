#pragma once
#include "Light/ambientlight.h"
#include "shadowmap.h"

class DirectionalLight : public AmbientLight
{
private:
    std::string m_colorName = "directionalLight.diffuse.ambient.base.color";
    std::string m_ambientIntensityName = "directionalLight.diffuse.ambient.ambientIntensity";
    std::string m_diffuseIntensityName = "directionalLight.diffuse.diffuseIntensity";
    std::string m_directionName = "directionalLight.direction";

    ShadowMap* m_shadowMap;
public:
    glm::vec3 m_direction;
    float m_diffuseIntensity;

    DirectionalLight(std::string componentName, glm::vec3 color, glm::vec3 direction, float ambientIntensity, float diffuseIntensity, ShadowMap* shadowmap);
    void SetDirection(glm::vec3 direction);
    void UseLight();
    void StopLight();
};