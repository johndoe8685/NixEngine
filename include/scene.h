#pragma once
#include <vector>
#include "system.h"
#include "model.h"

class Scene : public System
{
private:
	std::vector<Model*> m_ModelList;
public:
	Scene(std::string componentName);
	~Scene();
	
	void AddModel(std::string componentName, std::string Path);

	Model* getModel(std::string componentName);
	
	void RenderScene();
};