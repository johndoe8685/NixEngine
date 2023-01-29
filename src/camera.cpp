#include "camera.h"
#include <GLFW/glfw3.h>

Camera::Camera(std::string componentName, glm::vec3 position, glm::vec3 up, float yaw, float pitch, float movementSpeed, float sensivity, Projection projectionMode, float near, float far)
	:System(componentName, "Camera"), position(position), worldUp(up), m_yaw(yaw), m_pitch(pitch), 
	m_moveSpeed(movementSpeed), m_turnSpeed(sensivity), front(glm::vec3(0.0f, 0.0f, -1.0f)), isFocused(false), m_near(near), m_far(far), m_ProjectionMode(projectionMode)
{
	shadermanager = ShaderManager::Get();
	m_projection = glm::mat4(1.0f);
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
        float velocity = m_moveSpeed * deltaTime;

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
        xChange *= m_turnSpeed;
	    yChange *= m_turnSpeed;

	    m_yaw += xChange;
	    m_pitch += yChange;

	    if (m_pitch > 89.0f)
	    {
	    	m_pitch = 89.0f;
	    }

	    if (m_pitch < -89.0f)
	    {
	    	m_pitch = -89.0f;
	    }

	    update();
    }
}

glm::mat4 Camera::getProjection()
{
	glm::mat4 projection;
	shadermanager = ShaderManager::Get();
	if (shadermanager.currentWindowWidth != 0 && shadermanager.currentWindowHeight != 0)
	{
		m_projection = glm::perspective(glm::radians(shadermanager.currentCameraFov), (float)shadermanager.currentWindowWidth / (float)shadermanager.currentWindowHeight, m_near, m_far);
		return m_projection;
	}
	else
	{
		return m_projection;
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
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}