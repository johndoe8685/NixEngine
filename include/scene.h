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
	void AddCamera(std::string componentName, glm::vec3 position, glm::vec3 up, float yaw, float pitch, float movementSpeed, float sensivity, Projection projectionMode, float near, float far);
	void AddSkybox(std::string componentName, std::string fileName);

	Model* getModel(std::string componentName);
	Camera* getCamera(std::string componentName);

	void RenderScene(ShadowMap* shadowMap, Shader* shader, std::string cameraName, glm::mat4 projection);
	void RenderScene(Shader* shader);
	void ProcessScene(Shader* shader);
	void ProcessShadowMap(ShadowMap* shadowMap, Shader* shader);
};