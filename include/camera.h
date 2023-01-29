#pragma once
#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>
#include <vendor/glm/glm.hpp>
#include <vendor/glm/gtc/matrix_transform.hpp>
#include "system.h"
#include "shadermanager.h"
#include "shader.h"

enum Projection
{
    Perspective = 0,
    Orthographic = 1
};

class Camera : public System
{
private:
    unsigned int m_ModuleID;
    glm::vec3 position;
    glm::vec3 front, up, right;
    glm::vec3 worldUp;

    glm::mat4 m_projection;

    bool isFocused;

    float m_yaw, m_pitch;
    float m_moveSpeed, m_turnSpeed;
    float m_near, m_far;

    Projection m_ProjectionMode;
    ShaderManager shadermanager;
public:
    Camera(std::string componentName, glm::vec3 position, glm::vec3 up, float yaw, float pitch, float movementSpeed, float sensivity, Projection projectionMode, float near, float far);
    ~Camera();

    void keyControl(bool* keys, float deltaTime);
    void mouseControl(double xChange, double yChange);

    bool getIsFocused() { return isFocused; }
    glm::vec3 getPosition() { return position; }
    glm::vec3 getDirection() { return glm::normalize(front); }
    glm::mat4 getProjection();

    void setIsFocused(bool value) { isFocused = value; }
    void setUniformCameraPosition(Shader* shader);
    
    glm::mat4 calculateViewMatrix();
private:
    void update();
};