#include "shadermanager.h"

ShaderManager ShaderManager::s_Instance;
int ShaderManager::currentWindowWidth;
int ShaderManager::currentWindowHeight;
float ShaderManager::currentCameraFov;
float ShaderManager::deltaTime;

ShaderManager::ShaderManager()
	:System("Default", "ShaderManager")
{
}

Shader* ShaderManager::find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<Shader>> map)
{
	return map[componentName].get();
}

void ShaderManager::AddShader(std::string componentName, const std::string& fragmentShader, const std::string& vertexShader)
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(componentName, fragmentShader, vertexShader);
	m_shaderMap[componentName] = shader;
}

Shader* ShaderManager::getShader(std::string componentName)
{
	Shader* shader = find(componentName, m_shaderMap);
	return shader;
}
