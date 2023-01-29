#pragma once
#include <unordered_map>
#include <memory>
#include "shader.h"

class ShaderManager : public System
{
private:
	static ShaderManager s_Instance;

	int m_currentWindowWidth, m_currentWindowHeight;
	float m_currentCameraFov;

	std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaderMap;
	Shader* find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<Shader>> map);
public:
	ShaderManager();

	static ShaderManager& Get() { return s_Instance; }

	void AddShader(std::string componentName, const std::string& fragmentShader, const std::string& vertexShader);
	
	void SetCurrentWindowWidth(int width) { m_currentWindowWidth = width; };
	void SetCurrentWindowHeight(int height) { m_currentWindowHeight = height; };
	void SetCurrentCameraFov(float fov) { m_currentCameraFov = fov; };

	int GetCurrentWindowWidth() { return m_currentWindowWidth; };
	int GetCurrentWindowHeight() { return m_currentWindowHeight; };
	float GetCurrentCameraFov() { return m_currentCameraFov; };
	
	Shader* getShader(std::string componentName);
public:
	//Public Variables
	static int currentWindowWidth;
	static int currentWindowHeight;
	static float currentCameraFov;
	static float deltaTime;
};