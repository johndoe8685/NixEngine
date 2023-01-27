#pragma once
#include <vector>
#include <unordered_map>
#include "system.h"
#include "model.h"
#include "camera.h"
#include "shadowmap.h"
#include "skybox.h"


class Scene : public System
{
private:
	std::vector<Model*> m_ModelList;
	std::unordered_map<std::string, Camera*> m_CameraMap;
	Skybox* m_skybox;
public:
	Scene(std::string componentName);
	~Scene();
	
	void AddModel(std::string componentName, std::string Path);
	void AddCamera(std::string componentName, glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch, float moveSpeed, float sensivity);
	void AddSkybox(std::string componentName, std::string fileName);

	Model* getModel(std::string componentName);
	Camera* getCamera(std::string componentName);

	void RenderScene(ShadowMap* shadowMap, Shader* shader, glm::mat4 view, glm::mat4 projection);
	void RenderScene(Shader* shader);
	void ProcessScene(Shader* shader);
	void ProcessShadowMap(ShadowMap* shadowMap, Shader* shader);
};