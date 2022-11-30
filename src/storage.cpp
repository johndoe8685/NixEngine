#include "storage.h"

Storage::Storage()
	:System("Default", "Storage"), m_shaderList(), m_sceneList(), m_cameraList()
{
}

void Storage::addShader(std::string componentName, const std::string& fragmentShader, const std::string& vertexShader)
{
	Shader* shader = new Shader(componentName, fragmentShader, vertexShader);
	m_shaderList.push_back(shader);
}

void Storage::addScene(std::string componentName)
{
	Scene* scene = new Scene(componentName);
	m_sceneList.push_back(scene);
}

//Implement Camera Later

template<typename T>
unsigned int Storage::find(std::string componentName, std::vector<T*> list)
{
	for (size_t i = 0; i < list.size(); i++)
	{
		if (list[i]->m_componentName == componentName)
		{
			return i;
		}
	}
	debugger.giveMessage(Debugger::Error, "FindShader::Component not found.", componentName);
	return -1;
}

Shader* Storage::getShader(std::string componentName)
{
	unsigned int id = find(componentName, m_shaderList);
	if (id == -1) return m_shaderList[0];
	else return m_shaderList[id];
}

Scene* Storage::getScene(std::string componentName)
{
	unsigned int id = find(componentName, m_sceneList);
	if (id == -1) return m_sceneList[0];
	else return m_sceneList[id];
}



Storage::~Storage()
{
	for (size_t i = 0; i < m_shaderList.size(); i++)
	{
		delete m_shaderList[i];
	}
	for (size_t i = 0; i < m_sceneList.size(); i++)
	{
		delete m_sceneList[i];
	}
	for (size_t i = 0; i < m_cameraList.size(); i++)
	{
		delete m_cameraList[i];
	}
}
