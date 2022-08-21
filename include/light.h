#pragma once
#include <iostream>
#include "vendor/glm/glm.hpp"
#include "shader.h"

enum LightType
{
    ambientLight = 0,
    directionalLight = 1,
    pointLight = 2
};
struct ambientLight
{
    float m_ambientIntensity;
    std::string m_ambientName;
    std::string m_ambientIntensityName;
};
struct directionalLight
{
    glm::vec3 m_direction;
    float m_diffuseIntensity;
    std::string m_diffuseName;
    std::string m_diffuseIntensityName;
    struct ambientLight ambient;
};

struct pointLight
{
    glm::vec3 m_position;
    float m_constant;
    float m_linear;
    float m_exponent;
    std::string m_pointName;
    std::string m_constantName;
    std::string m_linearName;
    std::string m_exponentName;
    struct directionalLight directional;
};

class Light
{
private:
    glm::vec3 m_color;
    struct ambientLight ambient;
    struct directionalLight directional;
    struct pointLight point;
    LightType light;
public:
    Light();
    Light(float red, float green, float blue);
    ~Light();
    
    void setAsAmbientLight(float ambientIntensity, const std::string& ambientName, const std::string& ambientIntensityName);
    void setAsDirectionalLight(float ambientIntensity, float x, float y, float z, float diffuseIntensity, const std::string& ambientName, const std::string& ambientIntensityName, const std::string& diffuseName, const std::string& diffuseIntensityName);
    void setAsPointLight(float x, float y, float z, float constant, float linear, float exponent, float ambientIntensity, float diffuseIntensity, const std::string& ambientName, const std::string& ambientIntensityName, const std::string& diffuseName, const std::string& diffuseIntensityName, const std::string& pointPositionName, const std::string& pointConstantName, const std::string& pointLinearName, const std::string& pointExponentName);
    void useLight(Shader &shader);
    void calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset);
};
