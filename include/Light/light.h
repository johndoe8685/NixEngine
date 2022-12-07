#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "vendor/glm/glm.hpp"
#include "shadermanager.h"

class Light
{
private:

    unsigned int m_FBO;
    unsigned int m_DepthMap;
    int m_ShadowWidth;
    int m_ShadowHeight;

public:
    glm::vec3 m_color;
    glm::mat4 m_lightProj;

    Shader* shader;

    Light();
    Light(glm::vec3 color);
    ~Light();

    bool createShadowMap(int shadowWidth, int shadowHeight);
    void ShadowMapWrite();
    void ShadowMapRead(unsigned int slot);
    glm::mat4 CalculateLightTransform();

    virtual void UseLight() = 0;
    virtual void StopLight() = 0;
};