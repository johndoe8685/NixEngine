#include "assetmanager.h"

AssetManager AssetManager::s_Instance;

AssetManager::AssetManager()
	:System("Default", "AssetManager")
{
}

template<typename T>
T* AssetManager::find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<T>> map)
{
	return map[componentName].get();
}

void AssetManager::AddScene(std::string componentName)
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(componentName);
	m_sceneMap[componentName] = scene;
}

void AssetManager::AddAmbientLight(std::string componentName, glm::vec3 color, float ambientIntensity)
{
	std::shared_ptr<AmbientLight> light = std::make_shared<AmbientLight>(componentName, color, ambientIntensity);
	m_AmbientLightMap[componentName] = light;
}

void AssetManager::AddDirectionalLight(std::string componentName, glm::vec3 color, glm::vec3 direction, float ambientIntensity, float diffuseIntensity)
{
	std::shared_ptr<DirectionalLight> light = std::make_shared<DirectionalLight>(componentName, color, direction, ambientIntensity, diffuseIntensity);
	m_DirectionalLightMap[componentName] = light;

	std::shared_ptr<ShadowMap> shadowMap = std::make_shared<ShadowMap>(componentName, 8192, 8192, direction);
	m_ShadowMapList.push_back(shadowMap);
}

void AssetManager::AddPointLight(std::string componentName, glm::vec3 color, glm::vec3 position, float ambientIntensity, float diffuseIntensity)
{
	std::shared_ptr<PointLight> light = std::make_shared<PointLight>(componentName, color, position, ambientIntensity, diffuseIntensity, true);
	m_PointLightMap[componentName] = light;
}

void AssetManager::AddSpotLight(std::string componentName, glm::vec3 color, glm::vec3 position, glm::vec3 direction, float ambientIntensity, float diffuseIntensity, float edge)
{
	std::shared_ptr<SpotLight> light = std::make_shared<SpotLight>(componentName, color, position, direction, ambientIntensity, diffuseIntensity, edge, true);
	m_SpotLightMap[componentName] = light;
}

Scene* AssetManager::GetScene(std::string componentName)
{
	Scene* scene = find(componentName, m_sceneMap);
	return scene;
}

AmbientLight* AssetManager::GetAmbientLight(std::string componentName)
{
	return dynamic_cast<AmbientLight*>(find(componentName, m_AmbientLightMap));
}

DirectionalLight* AssetManager::GetDirectionalLight(std::string componentName)
{
	return dynamic_cast<DirectionalLight*>(find(componentName, m_DirectionalLightMap));
}

PointLight* AssetManager::GetPointLight(std::string componentName)
{
	return dynamic_cast<PointLight*>(find(componentName, m_PointLightMap));
}

SpotLight* AssetManager::GetSpotLight(std::string componentName)
{
	return dynamic_cast<SpotLight*>(find(componentName, m_SpotLightMap));
}

ShadowMap* AssetManager::GetShadowMap(size_t index)
{
	return dynamic_cast<ShadowMap*>(m_ShadowMapList[index].get());
}

std::vector<std::shared_ptr<ShadowMap>>* AssetManager::GetShadowMapList()
{
	return &m_ShadowMapList;
}




