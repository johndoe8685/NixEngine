#pragma once
#include "Light/directionallight.h"

class PointLight : public DirectionalLight
{
private:
    glm::vec3 m_position;
    float m_constant;
    float m_linear;
    float m_exponent;
    int m_pointSize;
    bool m_inUse;
};