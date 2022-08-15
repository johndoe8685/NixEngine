#pragma once
#include <iostream>
#include "vendor/glm/glm.hpp"
#include "shader.h"

class Light
{
private:
    glm::vec3 m_color;
    glm::vec3 m_direction;
    float m_diffuseIntensity;
    float m_ambientIntensity;
public:
    Light();
    Light(float red, float green, float blue, float ambientIntensity, float x, float y, float z, float diffuseIntensity);
    ~Light();

    void setLight(float red, float green, float blue, float intensity);
    void useLight(Shader &shader, const std::string& ambientName, const std::string& ambientIntensityName, const std::string& diffuseName, const std::string& diffuseIntensityName);
    void calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset);
};
