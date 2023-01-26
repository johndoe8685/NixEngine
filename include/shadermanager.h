#pragma once
#include <unordered_map>
#include <memory>
#include "shader.h"

class ShaderManager : public System
{
private:
	static ShaderManager s_Instance;

	std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaderMap;
	Shader* find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<Shader>> map);
public:
	glm::mat4 view, projection;
	ShaderManager();

	static ShaderManager& Get() { return s_Instance; }

	void AddShader(std::string componentName, const std::string& fragmentShader, const std::string& vertexShader);
	Shader* getShader(std::string componentName);
};