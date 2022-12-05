#include "storage.h"

Storage Storage::s_Instance;

Storage::Storage()
	:System("Default", "Storage")
{
}

Storage::Storage(std::string componentName)
	:System(componentName, "Storage")
{
}

void Storage::addShader(std::string componentName, const std::string& fragmentShader, const std::string& vertexShader)
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(componentName, fragmentShader, vertexShader);
	m_shaderMap[componentName] = shader;
}

void Storage::addScene(std::string componentName)
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(componentName);
	m_sceneMap[componentName] = scene;
}

//Implement Camera Later

template<typename T>
T* Storage::find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<T>> map)
{
	return map[componentName].get();
}

Shader* Storage::getShader(std::string componentName)
{
	Shader* shader = find(componentName, m_shaderMap);
	return shader;
}

Scene* Storage::getScene(std::string componentName)
{
	Scene* scene = find(componentName, m_sceneMap);
	return scene;
}