#pragma once
#include <vector>
#include "system.h"
#include "model.h"
#include "shadowmap.h"


class Scene : public System
{
private:
	std::vector<Model*> m_ModelList;
public:
	Scene(std::string componentName);
	~Scene();
	
	void AddModel(std::string componentName, std::string Path);

	Model* getModel(std::string componentName);

	void RenderScene(ShadowMap* shadowMap, Shader* shader);
	void RenderScene(Shader* shader);
	void ProcessScene(Shader* shader);
	void ProcessShadowMap(ShadowMap* shadowMap, Shader* shader);
};