#pragma once
#include <unordered_map>
#include <memory>
#include "scene.h"
#include "shader.h"
#include "camera.h"

class Storage : public System
{
private:
	static Storage s_Instance;

	std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaderMap;
	std::unordered_map<std::string, std::shared_ptr<Scene>> m_sceneMap;
	std::unordered_map<std::string, std::shared_ptr<Camera>> m_cameraMap;

	template <typename T> T* find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<T>> map);
public:
	Storage();
	Storage(std::string componentName);

	static Storage& get() { return s_Instance; }

	void addShader(std::string componentName,const std::string& fragmentShader, const std::string& vertexShader);
	void addScene(std::string componentName);

	Shader* getShader(std::string componentName);
	Scene* getScene(std::string componentName);
};