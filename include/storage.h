#pragma once
#include <vector>
#include "scene.h"
#include "shader.h"
#include "camera.h"

class Storage : public System
{
private:
	std::vector<Shader*> m_shaderList;
	std::vector<Scene*> m_sceneList;
	std::vector<Camera*> m_cameraList;

	template <typename T> unsigned int find(std::string componentName, std::vector<T*> list);
public:
	Storage();

	void addShader(std::string componentName,const std::string& fragmentShader, const std::string& vertexShader);
	void addScene(std::string componentName);

	Shader* getShader(std::string componentName);
	Scene* getScene(std::string componentName);
	~Storage();
};
