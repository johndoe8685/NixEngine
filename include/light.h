#pragma once
#include <iostream>
#include <sstream>
#include "vendor/glm/glm.hpp"
#include "shader.h"
#define MAX_POINT_LIGHT 10


class Light
{
    enum LightType
    {
        ambientLight = 0,
        directionalLight = 1,
        pointLight = 2
    };
    struct ambientLight
    {
        float m_ambientIntensity;
    };
    struct ambientUniformList
    {
        const char* m_colorName = "ambientLight.base.color";
        const char* m_ambientIntensityName = "ambientLight.ambientIntensity";
    };
    struct directionalLight
    {
        glm::vec3 m_direction;
        float m_diffuseIntensity;
        float m_ambientIntensity;
    };
    struct directionalUniformList
    {
        const char* m_colorName = "directionalLight.diffuse.ambient.base.color";
        const char* m_ambientIntensityName = "directionalLight.diffuse.ambient.ambientIntensity";
        const char* m_diffuseIntensityName = "directionalLight.diffuse.diffuseIntensity";
        const char* m_directionName = "directionalLight.direction";
    };
    struct pointLight
    {
        struct directionalLight directional;

        glm::vec3 m_position;
        float m_constant;
        float m_linear;
        float m_exponent;
        int m_pointSize;
    };
    struct pointArrayList
    {
        char* m_colorName = "pointLights[%d].diffuse.ambient.base.color";
        char* m_ambientIntensityName = "pointLights[%d].diffuse.ambient.ambientIntensity";
        char* m_diffuseIntensityName = "pointLights[%d].diffuse.diffuseIntensity";
        char* m_positionName = "pointLights[%d].position";
        char* m_constantName = "pointLights[%d].constant";
        char* m_linearName = "pointLights[%d].linear";
        char* m_exponentName = "pointLights[%d].exponent";
    };
    struct pointUniformList
    {
        std::string m_colorName;
        std::string m_ambientIntensityName;
        std::string m_diffuseIntensityName;
        std::string m_positionName;
        std::string m_constantName;
        std::string m_linearName;
        std::string m_exponentName;
        std::string m_pointSizeName = "pointLightCount";
    };
private:
    glm::vec3 m_color;
    
    struct ambientLight ambient;
    struct directionalLight directional;
    struct pointLight point;

    struct pointArrayList pointArrayList;
    struct pointUniformList pointList;

    LightType light;
public:
    static int m_PointLightIndex;

    Light();
    Light(float red, float green, float blue);
    ~Light();
    
    void setAsAmbientLight(float ambientIntensity);
    void setAsDirectionalLight(float ambientIntensity, float diffuseIntensity, float x, float y, float z);
    void setAsPointLight(float ambientIntensity, float diffuseIntensity, float x, float y, float z, float constant, float linear, float exponent);
    void useLight(Shader &shader);
    void calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset);
};
