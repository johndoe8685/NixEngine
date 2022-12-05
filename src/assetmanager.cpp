#include "assetmanager.h"

AssetManager AssetManager::s_Instance;

AssetManager::AssetManager()
	:System("Default", "AssetManager")
{
}

Scene* AssetManager::find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<Scene>> map)
{
	return map[componentName].get();
}

void AssetManager::addScene(std::string componentName)
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(componentName);
	m_sceneMap[componentName] = scene;
}

Scene* AssetManager::getScene(std::string componentName)
{
	Scene* scene = find(componentName, m_sceneMap);
	return scene;
}


