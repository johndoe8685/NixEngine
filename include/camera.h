#pragma once

#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>
#include <vendor/glm/glm.hpp>
#include <vendor/glm/gtc/matrix_transform.hpp>
#include "shader.h"

class Camera
{
private:
    unsigned int m_ModuleID;
    glm::vec3 position;
    glm::vec3 front, up, right;
    glm::vec3 worldUp;

    bool isFocused;

    float yaw, pitch;
    float moveSpeed, turnSpeed;
public:
    Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed);
    ~Camera();

    void keyControl(bool* keys, float deltaTime);
    void mouseControl(double xChange, double yChange);

    bool getIsFocused() { return isFocused; }
    void setIsFocused(bool value) { isFocused = value; }
    void setUniformCameraPosition(Shader &shader);
    glm::mat4 calculateViewMatrix();

    glm::vec3 getPosition() { return position; }
    glm::vec3 getDirection() { return glm::normalize(front); }
private:
    void update();
};