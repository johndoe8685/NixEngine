#pragma once
#include "shader.h"

class Material
{
private:
    float m_specularIntensity;
    float m_shininess;
public:
    Material();
    Material(float specularIntensity, float shininess);

    void useMaterial(Shader* shader, const std::string& specularIntensityName, const std::string& shininessName);    
};