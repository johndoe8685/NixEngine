#pragma once
#include "Light/pointlight.h"
#define MAX_SPOT_LIGHT 5

class SpotLight : public PointLight
{
private:
    char* m_colorName = "spotLights[%d].point.diffuse.ambient.base.color";
    char* m_ambientIntensityName = "spotLights[%d].point.diffuse.ambient.ambientIntensity";
    char* m_diffuseIntensityName = "spotLights[%d].point.diffuse.diffuseIntensity";
    char* m_positionName = "spotLights[%d].point.position";
    char* m_constantName = "spotLights[%d].point.constant";
    char* m_linearName = "spotLights[%d].point.linear";
    char* m_exponentName = "spotLights[%d].point.exponent";
    char* m_directionName = "spotLights[%d].direction";
    char* m_edgeName = "spotLights[%d].edge";

    std::string m_colorNameResult;
    std::string m_ambientIntensityNameResult;
    std::string m_diffuseIntensityNameResult;
    std::string m_positionNameResult;
    std::string m_constantNameResult;
    std::string m_linearNameResult;
    std::string m_exponentNameResult;
    std::string m_pointSizeNameResult= "pointLightCount";
    std::string m_directionNameResult;
    std::string m_edgeNameResult;
    std::string m_spotSizeNameResult= "spotLightCount";
public:
    static int m_SpotLightIndex;

    glm::vec3 m_direction;
	float m_edge;
	int m_spotSize;

    SpotLight(std::string componentName, glm::vec3 color, glm::vec3 position, glm::vec3 direction, float ambientIntensity, float diffuseIntensity, float edge, bool isSpot);
    void setFlash(glm::vec3 position, glm::vec3 direction);

    void UseLight();
    void StopLight();
};