#pragma once
#include "Light/positionallight.h"
#define MAX_POINT_LIGHT 10

class PointLight : public PositionalLight
{
private:
    char* m_colorName = "pointLights[%d].diffuse.ambient.base.color";
    char* m_ambientIntensityName = "pointLights[%d].diffuse.ambient.ambientIntensity";
    char* m_diffuseIntensityName = "pointLights[%d].diffuse.diffuseIntensity";
    char* m_positionName = "pointLights[%d].position";
    char* m_constantName = "pointLights[%d].constant";
    char* m_linearName = "pointLights[%d].linear";
    char* m_exponentName = "pointLights[%d].exponent";
    char* m_inUseName = "pointLights[%d].inUse";

    std::string m_colorNameResult;
    std::string m_ambientIntensityNameResult;
    std::string m_diffuseIntensityNameResult;
    std::string m_positionNameResult;
    std::string m_constantNameResult;
    std::string m_linearNameResult;
    std::string m_exponentNameResult;
    std::string m_pointSizeNameResult = "pointLightCount";
    std::string m_inUseNameResult;
public:
    static int m_PointLightIndex;
    static int m_pointSize;


    float m_constant;
    float m_linear;
    float m_exponent;
    bool m_inUse;

    PointLight(std::string componentName, glm::vec3 color, glm::vec3 position, float ambientIntensity, float diffuseIntensity, bool isPoint);
    void UseLight();
    void StopLight();
};