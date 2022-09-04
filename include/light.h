#pragma once
#include <iostream>
#include <sstream>
#include "vendor/glm/glm.hpp"
#include "shader.h"
#define MAX_POINT_LIGHT 10
#define MAX_SPOT_LIGHT 5


class Light
{
    enum LightType
    {
        ambientLight = 0,
        directionalLight = 1,
        pointLight = 2,
        spotLight = 3,
        flashLight = 4
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
        bool m_inUse;
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
        char* m_inUseName = "pointLights[%d].inUse";
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
        std::string m_inUseName;
    };
    struct SpotLight
    {   
        struct pointLight point;

        glm::vec3 m_direction;
        float m_edge;
        int m_spotSize;

        void setFlash(glm::vec3 position, glm::vec3 direction)
        {
            point.m_position = position;
            m_direction = direction;
        }
    };
    struct SpotArrayList
    {
        char* m_colorName = "spotLights[%d].point.diffuse.ambient.base.color";
        char* m_ambientIntensityName = "spotLights[%d].point.diffuse.ambient.ambientIntensity";
        char* m_diffuseIntensityName = "spotLights[%d].point.diffuse.diffuseIntensity";
        char* m_positionName = "spotLights[%d].point.position";
        char* m_constantName = "spotLights[%d].point.constant";
        char* m_linearName = "spotLights[%d].point.linear";
        char* m_exponentName = "spotLights[%d].point.exponent";
        char* m_directionName = "spotLights[%d].direction";
        char* m_edgeName = "spotLights[%d].edge";
    };
    struct SpotUniformList
    {
        std::string m_colorName;
        std::string m_ambientIntensityName;
        std::string m_diffuseIntensityName;
        std::string m_positionName;
        std::string m_constantName;
        std::string m_linearName;
        std::string m_exponentName;
        std::string m_pointSizeName = "pointLightCount";
        std::string m_directionName;
        std::string m_edgeName;
        std::string m_spotSizeName = "spotLightCount";
    };
    struct FlashLight
    {
        struct SpotLight spot;
    };
    struct FlashUniformList
    {
        char* m_colorName = "flashLight.spot.point.diffuse.ambient.base.color";
        char* m_ambientIntensityName = "flashLight.spot.point.diffuse.ambient.ambientIntensity";
        char* m_diffuseIntensityName = "flashLight.spot.point.diffuse.diffuseIntensity";
        char* m_positionName = "flashLight.spot.point.position";
        char* m_constantName = "flashLight.spot.point.constant";
        char* m_linearName = "flashLight.spot.point.linear";
        char* m_exponentName = "flashLight.spot.point.exponent";
        char* m_directionName = "flashLight.spot.direction";
        char* m_edgeName = "flashLight.spot.edge";
    };

private:
    glm::vec3 m_color;
    
    struct ambientLight ambient;
    struct directionalLight directional;
    struct pointLight point;
    struct SpotLight spot;
    struct FlashLight flash;


    struct pointArrayList pointArrayList;
    struct pointUniformList pointList;
    struct SpotArrayList spotArrayList;
    struct SpotUniformList spotList;

    LightType light;
public:
    static int m_PointLightIndex;
    static int m_CurrentPointSize;
    static int m_SpotLightIndex;
    static int m_CurrentSpotSize;

    Light();
    Light(float red, float green, float blue);
    ~Light();
    
    void setAsAmbientLight(float ambientIntensity);
    void setAsDirectionalLight(float ambientIntensity, float diffuseIntensity, float x, float y, float z);
    void setAsPointLight(float ambientIntensity, float diffuseIntensity, float x, float y, float z, float constant, float linear, float exponent);
    void setAsSpotLight(float ambientIntensity, float diffuseIntensity, float x, float y, float z, float constant, float linear, float exponent, glm::vec3 direction, float edge);
    void setAsFlashLight(float ambientIntensity, float diffuseIntensity, float x, float y, float z, float constant, float linear, float exponent, glm::vec3 direction, float edge);
    void setMovingLight(glm::vec3 position, glm::vec3 direction);
    void useLight(Shader &shader);
    void stopLight(Shader& shader);

    void calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset);
};
