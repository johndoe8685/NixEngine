#include "material.h"

Material::Material()
:m_specularIntensity(1.0f), m_shininess(0.2f)
{

}

Material::Material(float specularIntensity, float shininess)
:m_specularIntensity(specularIntensity), m_shininess(shininess)
{

}

void Material::useMaterial(Shader &shader, const std::string& specularIntensityName, const std::string& shininessName)
{
    shader.SetUniform1f(specularIntensityName, m_specularIntensity);
    shader.SetUniform1f(shininessName, m_shininess);
}