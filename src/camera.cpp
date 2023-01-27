#include "camera.h"
#include <GLFW/glfw3.h>

Camera::Camera(std::string componentName, glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed)
:System(componentName, "Camera"), position(startPosition), worldUp(startUp), yaw(startYaw), pitch(startPitch), moveSpeed(startMoveSpeed), turnSpeed(startTurnSpeed), front(glm::vec3(0.0f, 0.0f, -1.0f)), isFocused(false)
{
	debugger.giveMessage(Debugger::Info, "Init");
    update();
}

Camera::~Camera()
{
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
    if(isFocused)
    {
        float velocity = moveSpeed * deltaTime;

	    if (keys[GLFW_KEY_W])
	    {
	    	position += front * velocity;
	    }

	    if (keys[GLFW_KEY_S])
	    {
	    	position -= front * velocity;
	    }

	    if (keys[GLFW_KEY_A])
	    {
	    	position -= right * velocity;
	    }

	    if (keys[GLFW_KEY_D])
	    {
	    	position += right * velocity;
	    }
    }
}

void Camera::mouseControl(double xChange, double yChange)
{
	glfwPollEvents();
    if(isFocused)
    {
        xChange *= turnSpeed;
	    yChange *= turnSpeed;

	    yaw += xChange;
	    pitch += yChange;

	    if (pitch > 89.0f)
	    {
	    	pitch = 89.0f;
	    }

	    if (pitch < -89.0f)
	    {
	    	pitch = -89.0f;
	    }

	    update();
    }
}

void Camera::setUniformCameraPosition(Shader *shader)
{
	shader->SetUniform3f("eyePosition", position.x, position.y, position.z);
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}