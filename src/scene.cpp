#include "scene.h"

Scene::Scene(std::string componentName)
	:System(componentName, "Scene")
{

}

void Scene::AddModel(std::string componentName, std::string Path)
{
	Model* model = new Model(componentName, Path);
	m_ModelList.push_back(model);
}

Model* Scene::getModel(std::string componentName)
{
	for (size_t i = 0; i < m_ModelList.size(); i++)
	{
		if (m_ModelList[i]->m_componentName == componentName)
		{
			return m_ModelList[i];
		}
	}
	debugger.giveMessage(Debugger::Error, "getModel::Failed to get model", componentName);
	return m_ModelList[0];
}

void Scene::RenderScene()
{
	Shader* shader = ShaderManager::Get().getShader("Basic");

	for (size_t i = 0; i < m_ModelList.size(); i++)
	{
		m_ModelList[i]->processModel();
		shader->Bind();
		m_ModelList[i]->RenderModel();
		shader->Unbind();
	}
}

Scene::~Scene()
{
	for (size_t i = 0; i < m_ModelList.size(); i++)
	{
		delete m_ModelList[i];
	}
}