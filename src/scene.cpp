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

void Scene::AddCamera(std::string componentName, glm::vec3 position, glm::vec3 up, float yaw, float pitch, float movementSpeed, float sensivity, Projection projectionMode, float near, float far)
{
	Camera* camera = new Camera(componentName, position, up, yaw, pitch, movementSpeed, sensivity, projectionMode, near, far);
	m_CameraMap[componentName] = camera;
}

void Scene::AddSkybox(std::string componentName, std::string fileName)
{
	m_skybox = new Skybox(componentName, fileName);
}

Model* Scene::getModel(std::string componentName)
{
	for (size_t i = 0; i < m_ModelList.size(); i++)
	{
		if (m_ModelList[i]->m_componentName == componentName)
		{
			m_ModelList[i]->isDraw = true;
			return m_ModelList[i];
		}
	}
	debugger.giveMessage(Debugger::Error, "getModel::Failed to get model", componentName);
	m_ModelList[0]->isDraw = true;
	return m_ModelList[0];
}

Camera* Scene::getCamera(std::string componentName)
{
	if (m_CameraMap.find(componentName) != m_CameraMap.end())
	{
		return m_CameraMap[componentName];
	}
	else
	{
		debugger.giveMessage(Debugger::Error, "Camera not found", componentName);
		return m_CameraMap["Default"];
	}
}

void Scene::RenderScene(ShadowMap* shadowMap, Shader* shader, std::string cameraName, glm::mat4 projection)
{
	Camera* camera = getCamera(cameraName);
	glm::mat4 view = camera->calculateViewMatrix();
	glm::mat4 proj = camera->getProjection();

	m_skybox->DrawSkybox(view, proj);

	//Set view and projection
	shader->SetUniformMatrix4fv("view", view);
	shader->SetUniformMatrix4fv("projection", proj);

	//Geçici bir çözüm birden fazla shadow map kullanıldığında değiştirilecek
	shader->SetUniformMatrix4fv("lightSpaceMatrix", shadowMap->GetLightSpaceMatrix());
	shader->SetUniform1f("ShadowMapBiasMin", shadowMap->m_biasMin);
	shader->SetUniform1f("ShadowMapBiasMax", shadowMap->m_biasMax);
	shader->SetUniform1i("aTexture", 0);
	shader->SetUniform1i("shadowMap", 1);

	for (size_t i = 0; i < m_ModelList.size(); i++)
	{
		if (m_ModelList[i]->isDraw)
		{
			m_ModelList[i]->ProcessModel(shader);

			shader->Bind();
			m_ModelList[i]->RenderModel(shadowMap);
			shader->Unbind();
		}
	}
}

void Scene::RenderScene(Shader* shader)
{
	for (size_t i = 0; i < m_ModelList.size(); i++)
	{
		if (m_ModelList[i]->isDraw && m_ModelList[i]->m_componentName != "Error")
		{
			m_ModelList[i]->ProcessModel(shader);

			shader->Bind();
			m_ModelList[i]->RenderModel();
			shader->Unbind();
		}
	}
}

void Scene::ProcessScene(Shader* shader)
{
	for (size_t i = 0; i < m_ModelList.size(); i++)
	{
		m_ModelList[i]->ProcessModel(shader);
	}
}

void Scene::ProcessShadowMap(ShadowMap* shadowMap, Shader* shader)
{
	shadowMap->Write();
	shadowMap->Process(shader);
}

Scene::~Scene()
{
	for (size_t i = 0; i < m_ModelList.size(); i++)
	{
		delete m_ModelList[i];
	}
}