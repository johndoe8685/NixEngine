#pragma once
#include <unordered_map>
#include <memory>
#include "scene.h"

class AssetManager : public System
{
private:
	static AssetManager s_Instance;

	std::unordered_map<std::string, std::shared_ptr<Scene>> m_sceneMap;
	Scene* find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<Scene>> map);
public:
	AssetManager();

	static AssetManager& Get() { return s_Instance; }

	void addScene(std::string componentName);
	Scene* getScene(std::string componentName);
};